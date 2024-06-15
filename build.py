#!/usr/bin/python3
import scripts.virtual_env_tools as vtool
import os
import platform
import argparse
import subprocess

profiles = {"Darwin":'MacosProfile.txt', "Windows":'WindowsProfile.txt', "Linux":'LinuxProfile.txt'}
build_type = 'Release'

def main():
    venv_context = vtool.VenvContext("kai_o_venv")
    if 1:
        vtool.create_venv(venv_context)
    if 1:
        vtool.initialize_venv(venv_context, os.path.join('data', 'requirements.txt'))

    profile = 'default'

    try:
        venv_context.run_command('conan', 'profile', 'detect')
    except: 
        pass
    
    venv_context.run_command('conan', 'install', '.', '-of=build', '-s', f'build_type={build_type}', '--build=missing', f"-pr:a={profile}")
    venv_context.run_command('conan', 'build', '.',  '-of=build', '-s', f'build_type={build_type}')

    if platform.system() == 'Windows':
        subprocess.check_call([os.path.join('install', 'run', 'kaio.exe')])
    else:
        subprocess.check_call(['./install/run/kaio'])

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('--create', action='store_true', help='Execute "conan create"')
    parser.add_argument('--build_type', type=str, help='Specify build type')
    main()
