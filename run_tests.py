import json
import subprocess
import os
import sys
import re
import platform

# --- CONFIGURATION ---
TARGET_DIRS = [
    'BitField-Operations',
    'BitWise-Operations',
    'Bitwise-Rotation-and-Counting'
]
WRAPPER_DIR = 'TestWrapper'
WRAPPER_C_SOURCE = os.path.join(WRAPPER_DIR, 'test_wrapper.c')
TEMP_TEST_DATA_FILE = 'current_test_data.txt'

# --- HELPER FUNCTIONS ---

def is_windows():
    """Check if the current OS is Windows."""
    return platform.system() == "Windows"

def get_executable_name(base_name):
    """Appends .exe to the filename on Windows."""
    if is_windows():
        return f"{base_name}.exe"
    return base_name

def get_run_command(executable_path):
    """Returns the command to run an executable."""
    # On Windows, we can call the .exe directly.
    # On Linux/macOS, it needs to be prefixed with ./
    if is_windows():
        return [executable_path]
    return [f'./{executable_path}']


def find_tests_for_single_file(c_file_path):
    """Finds the corresponding test json file for a given C file."""
    if not os.path.exists(c_file_path):
        return None
    
    match = re.search(r"problem_(\d+)\.c", os.path.basename(c_file_path))
    if match:
        test_num = match.group(1)
        json_filename = f"test_{test_num}.json"
        json_file_path = os.path.join(os.path.dirname(c_file_path), "Tests", json_filename)
        if os.path.exists(json_file_path):
            return [(c_file_path, json_file_path)]
    return None

def find_all_tests():
    """Finds all C files and their corresponding test JSON files."""
    tests_to_run = []
    for directory in TARGET_DIRS:
        if not os.path.isdir(directory):
            print(f"Warning: Directory '{directory}' not found. Skipping.")
            continue
        for root, _, files in os.walk(directory):
            # Exclude the 'Tests' subdirectory from the search for C files
            if 'Tests' in root.split(os.sep):
                continue
            for filename in files:
                if filename.startswith("problem_") and filename.endswith(".c"):
                    c_file_path = os.path.join(root, filename)
                    single_test = find_tests_for_single_file(c_file_path)
                    if single_test:
                        tests_to_run.append(single_test[0])
                    else:
                        print(f"Info: Found '{c_file_path}' but no corresponding test file was found.")
    return tests_to_run

def clean_up(files):
    """Removes a list of files, ignoring errors if they don't exist."""
    for f in files:
        try:
            if os.path.exists(f):
                os.remove(f)
        except OSError as e:
            print(f"Warning: Could not remove temporary file {f}: {e}")

def create_test_data_file(test_case):
    """Creates the temporary data file for the C wrapper to read."""
    with open(TEMP_TEST_DATA_FILE, 'w', newline='\n') as f:
        # **FIX:** Join all inputs into a single space-separated line.
        # This matches how a user would enter data for a multi-input scanf.
        if 'inputs' in test_case and test_case['inputs']:
            all_inputs = " ".join(map(str, test_case.get('inputs', [])))
            f.write(f"INPUT:{all_inputs}\n")
        
        if 'expected_outputs' in test_case:
            for item in test_case.get('expected_outputs', []):
                f.write(f"EXPECTED:{item}\n")

def run_test_on_program(c_file, json_file):
    """Compiles and runs all test cases for a single C program."""
    print(f"\n--- Testing Program: {c_file} ---")
    
    program_passed = 0
    program_failed = 0

    try:
        with open(json_file, 'r') as f:
            test_suite = json.load(f)
    except (json.JSONDecodeError, FileNotFoundError) as e:
        print(f"❌ Error loading or parsing {json_file}: {e}")
        return 0, 1

    base_name = os.path.splitext(os.path.basename(c_file))[0]
    executable_name = get_executable_name(f"{base_name}_test")
    user_obj = f"{base_name}.o"
    wrapper_obj = "test_wrapper.o"
    
    cleanup_files = [executable_name, TEMP_TEST_DATA_FILE, user_obj, wrapper_obj]

    test_cases = test_suite.get('test_cases', [])
    if not test_cases:
        print("   No test cases found in JSON file.")
        return 0,0

    # ----------- THIS IS THE CORRECTED LINE -----------
    # We must add -I to find the header and -include to force the macros.
    compile_user_code_cmd = [
        'gcc', '-c', c_file, '-o', user_obj, 
        '-Dmain=user_main', 
        f'-I{WRAPPER_DIR}', 
        '-include', os.path.join(WRAPPER_DIR, 'test_wrapper.h')
    ]
    # ----------------------------------------------------

    compile_wrapper_cmd = ['gcc', '-c', WRAPPER_C_SOURCE, '-o', wrapper_obj, f'-I{WRAPPER_DIR}']
    link_cmd = ['gcc', '-o', executable_name, user_obj, wrapper_obj]

    # Compile user code
    compile_user_process = subprocess.run(compile_user_code_cmd, capture_output=True, text=True)
    if compile_user_process.returncode != 0:
        print("❌ Compilation Failed (User Code)")
        print(compile_user_process.stderr)
        clean_up(cleanup_files)
        return 0, len(test_cases)
        
    # Compile wrapper
    compile_wrapper_process = subprocess.run(compile_wrapper_cmd, capture_output=True, text=True)
    if compile_wrapper_process.returncode != 0:
        print("❌ Compilation Failed (Wrapper Code)")
        print(compile_wrapper_process.stderr)
        clean_up(cleanup_files)
        return 0, len(test_cases)
        
    # Link
    link_process = subprocess.run(link_cmd, capture_output=True, text=True)
    if link_process.returncode != 0:
        print("❌ Linking Failed")
        print(link_process.stderr)
        clean_up(cleanup_files)
        return 0, len(test_cases)

    # Run tests
    for i, test_case in enumerate(test_cases):
        test_name = test_case.get('name', f"Test Case {i+1}")
        print(f"  Running: {test_name}...", end='', flush=True)

        create_test_data_file(test_case)

        try:
            run_command = get_run_command(executable_name)
            run_process = subprocess.run(run_command, capture_output=True, text=True, timeout=5)
            
            # Check for return code 0 (success)
            if run_process.returncode == 0:
                print(" ✅ PASSED")
                program_passed += 1

                # Print stderr on success too, if there's anything to show.
                if run_process.stderr:
                    print("\n" + "-"*10 + " STDERR Output " + "-"*10)
                    print(run_process.stderr.strip())
                    print("-" * 35 + "\n")
            else:
                print(" ❌ FAILED")
                program_failed += 1
                # Print details on failure
                print("\n" + "-"*10 + " Failure Details " + "-"*10)
                if run_process.stdout:
                    print("--- STDOUT ---")
                    print(run_process.stdout)
                if run_process.stderr:
                    print("--- STDERR ---")
                    print(run_process.stderr)
                print("-" * 37 + "\n")

        except subprocess.TimeoutExpired:
            print(" ❌ FAILED (Timeout)")
            program_failed += 1
    
    print(f"Program Summary: {program_passed} passed, {program_failed} failed")
    clean_up(cleanup_files)
    return program_passed, program_failed

def main():
    if not os.path.exists(WRAPPER_C_SOURCE):
        print(f"Error: Test wrapper C file not found at '{WRAPPER_C_SOURCE}'.")
        sys.exit(1)

    # Check for single file argument
    if len(sys.argv) > 1:
        target_file = sys.argv[1]
        tests_to_run = find_tests_for_single_file(target_file)
        if not tests_to_run:
            print(f"Error: Could not find a matching 'Tests/test_XXX.json' file for '{target_file}'.")
            sys.exit(1)
    else:
        tests_to_run = find_all_tests()
    
    if not tests_to_run:
        print("No tests found to run.")
        sys.exit(0)

    print("Starting C Program Test Runner\n" + "="*30)
    total_passed = 0
    total_failed = 0

    for c_file, json_file in tests_to_run:
        passed, failed = run_test_on_program(c_file, json_file)
        total_passed += passed
        total_failed += failed

    print("\n" + "="*30)
    print("           Overall Results")
    print("="*30)
    print(f"Total Tests Passed: {total_passed}")
    print(f"Total Tests Failed: {total_failed}")
    print("="*30)

    if total_failed > 0:
        sys.exit(1) # Exit with a non-zero code to indicate failure

if __name__ == '__main__':
    main()

