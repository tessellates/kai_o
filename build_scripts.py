#! /usr/bin/env python3
import subprocess
import os
import sys
import venv
import platform
import argparse
import json
import glob
import shutil

default_config = {
    "venvname": "venvfde",
    "build_type": "Release",
}

def print_red(text):
    red_start = "\033[91m"
    red_end = "\033[0m"
    print(f"{red_start}{text}{red_end}")

def load_config(config_file):
    if not os.path.exists(config_file):
        generate_default_config(config_file)
        return default_config
    with open(config_file, 'r') as file:
        data = json.load(file)
        for key, default_value in default_config.items():
            if key not in data:
                data[key] = default_value
    with open(config_file, 'w') as file:
        json.dump(data, file, indent=4)
    return data

def generate_default_config(config_file):
    with open(config_file, 'w') as file:
        json.dump(default_config, file, indent=4)
    print(f"Default config file created at {config_file}")

class VenvSetup:
    def __init__(self, no_setup=False):
        self.config = load_config('localconfig.json')
        self.venv_path = os.path.abspath(self.config['venvname'])
        self.bin_path = self._get_bin_path()
        self.venv_py = self._get_venv_py()
        self.verbose = True
        if no_setup:
            return

        self._create_venv()
        self._install_requirements()
        self._configure_conan()

    def _create_venv(self):
        if not os.path.exists(self.venv_path):
            print(f"Creating virtual environment in: {self.venv_path}")
            venv.create(self.venv_path, with_pip=True)  # with_pip=True ensures pip is installed in the venv
        else:
            print(f"Virtual environment exists at: {self.venv_path}")

    def _install_requirements(self):
        self.run_in_venv("install conan", [self.venv_py, '-m', 'pip', 'install', 'conan==1.62.0'], return_value=subprocess.PIPE)
        self.run_in_venv("install other", [self.venv_py, '-m', 'pip', 'install', '-r', 'data/requirements.txt'])

    def _configure_conan(self):
        remoteName = self.config['user_remote']
        if all(line.split(':', 1)[0] != remoteName for line in self.run_command('conan','remote','list', return_value=subprocess.PIPE).stdout.splitlines()):
            remoteUrl = self.config['remote_url']
            self.run_command('conan', 'remote','add', remoteName, remoteUrl) 

    def _get_bin_path(self):
        """Returns the path to the bin or Scripts directory based on the operating system."""
        if platform.system() == "Windows":
            return os.path.join(self.venv_path, 'Scripts')
        else:
            return os.path.join(self.venv_path, 'bin')

    def _get_venv_py(self):
        """Returns the path to the Python executable within the virtual environment."""
        if platform.system() == "Windows":
            return os.path.join(self.bin_path, 'python.exe')
        else:
            return os.path.join(self.bin_path, 'python')

    def run_in_venv(self, name, full_command, return_value=None):
        try:
            result = subprocess.run(
                full_command,
                text=True,  # Handle outputs as text (decode bytes to str)
                check=True,  # Raise exception on non-zero exit (which is caught below)
                capture_output=False,  # Don't capture output here
                stdout=return_value,
            )
            return result
        except subprocess.CalledProcessError as e:
            
            print_red(f"Error during {name}:")
            if self.verbose:
                print(f"Failed command: {' '.join(full_command)}")
            sys.exit(1)

    def run_script(self, script_path, *args):
        """Runs a Python script located at script_path with additional arguments using the virtual environment's Python."""
        command = [self.venv_py, script_path] + list(args)
        self.run_in_venv(os.path.basename(script_path), command)

    def run_command(self, command, *args, return_value=None):
        """Runs a command from the bin directory of the virtual environment."""
        executable = os.path.join(self.bin_path, command)
        full_command = [executable] + list(args)
        return self.run_in_venv(command, full_command, return_value)



def remove_files_and_dirs():
    paths = [
        'build/',
        'test_package/build',
        'CMakeUserPresets.json',
        'test_package/CMakeUserPresets.json',
        'localconfig.json'
    ]

    for path in paths:
        # Handle glob patterns like 'build*'
        if '*' in path or '?' in path or '[' in path:
            for matched_path in glob.glob(path):
                if os.path.isdir(matched_path):
                    shutil.rmtree(matched_path)
                elif os.path.isfile(matched_path):
                    os.remove(matched_path)
        else:
            if os.path.isdir(path):
                shutil.rmtree(path)
            elif os.path.isfile(path):
                os.remove(path)



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run Conan commands in a virtual environment.")
    parser.add_argument('--create', action='store_true', help='Execute "conan create"')
    parser.add_argument('--upload', action='store_true', help='Argument version to use for the "conan upload" command')    
    parser.add_argument('--so', action='store_true', help='setup only')
    parser.add_argument('--clean',  action='store_true', help='clean local files')
    parser.add_argument('--build_type', type=str, help='Specify build type')
    
    args, general_args = parser.parse_known_args()

    if general_args:
        venv = VenvSetup(True)
        if len(general_args) == 1:
            venv.run_command(general_args[0])
        else:
            venv.run_command(general_args[0], *general_args[1:])

        sys.exit(0)  # Exit the script

    venv = VenvSetup()

    if args.clean:
        venv.run_script(os.path.join("scripts", "conan-util.py"), "clean", ".", "--user=devops", "--channel=stable")
        remove_files_and_dirs()
        sys.exit(0)  # Exit the script

    # Extract values from config
    if not args.build_type:
        build_type = venv.config['build_type']
    else:
        build_type = args.build_type
    upload_remote_url = venv.config['upload_remote_url']
    upload_remote = venv.config['upload_remote']

    if args.so:
        sys.exit(0)  # Exit the script

    profile = 'profileLin.txt'
    if platform.system() == "Windows":
        profile = 'profileWin.txt'        

    venv.run_command('conan', 'install', '.', '-of=build', '-if=build', '-s', f'build_type={build_type}', '--build=missing', f"-pr:b={profile}", f"-pr:h={profile}")
    venv.run_command('conan', 'build', '.',  '-bf=build', '-if=build', '-s', f'build_type={build_type}')

