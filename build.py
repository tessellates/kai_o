#!/usr/bin/python3
import scripts.virtual_env_tools as vtool
import os
import platform
import argparse
import subprocess

profiles = {"Darwin":'MacosProfile.txt', "Windows":'WindowsProfile.txt', "Linux":'LinuxProfile.txt'}
build_type = 'Debug'

def main(setup = True, emscripten=False):
    venv_context = vtool.VenvContext("kai_o_venv")

    if setup:
        vtool.create_venv(venv_context)
    if setup:
        vtool.initialize_venv(venv_context, os.path.join('data', 'requirements.txt'))

    profile = 'default'
    hostprofile = profile
    if emscripten:
        hostprofile = os.path.join('data', 'emprofile')

    if setup:
        try:
            venv_context.run_command('conan', 'profile', 'detect')
        except: 
            pass

        venv_context.run_command('conan', 'install', '.', '-of=build', '-s', f'build_type={build_type}', '--build=missing', f"-pr:b={profile}", f"-pr:h={hostprofile}")

    venv_context.run_command('conan', 'build', '.',  '-of=build', '-s', f'build_type={build_type}', f"-pr:b={profile}", f"-pr:h={hostprofile}")

    if platform.system() == 'Windows':
        subprocess.check_call([os.path.join('install', 'run', 'main.exe')])
    else:
        subprocess.check_call(['./build/build/Release/bin/main'])

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('-bo', action='store_true', help='Execute "conan create"')
    parser.add_argument('-em', action='store_true', help='Execute "conan create"')
    argsparsed = parser.parse_args()
    main(not argsparsed.bo, argsparsed.em)
