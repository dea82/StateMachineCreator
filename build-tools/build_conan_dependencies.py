#!/usr/bin/env python

import argparse

import json
import conan.conanrepo.conanrepo as conanrepo
from subprocess import call

def decorated_print(string):
    print("*" * 60)
    print('*   ' + string)
    print("*" * 60)


def get_login_credentials(config_file, section):
    try:
        conan_repo_config = conanrepo.Config(config_file, section)
        return {'username': conan_repo_config.get_option('username'),
                'password': conan_repo_config.get_option('password')}
    except conanrepo.ConanRepoException as e:
        print(e)
        exit(1)


def login(credentials, remote):
    call(["conan", "user", "-p", credentials['password'], "-r", remote, credentials['username']])


def main():
    parser = argparse.ArgumentParser(description="Builds, installs and uploads conan dependencies.")
    parser.add_argument('-c', '--config', action='store', required=True, help='Conan client configuration')
    parser.add_argument('-pr', '--profile', action='append', required=True, help='Conan profiles used for build')
    parser.add_argument('-ar', '--artifact-repo', action='store', help='Config file with conan repo authentication parameters.')
    parser.add_argument('path')
    args = parser.parse_args()

    upload_requested = args.artifact_repo

    decorated_print('Downloading conan config')
    call(["conan", "config", "install", args.config])

    logged_in = False
    packages_to_upload = []
    for profile in args.profile:
        build_directory = args.path + '/build/' + profile + '/'
        json_file_name = 'conan-install.json'
        decorated_print('Installing for profile: ' + profile)
        call(["conan", "install", args.path, "--install-folder=" + build_directory, "--pr=" + profile,
             "--build=outdated", "-u", "-j=" + json_file_name])
        with open(json_file_name) as json_data:
            d = json.load(json_data)
            for i in d['installed']:
                reference = i['recipe']['id']
                for p in i['packages']:
                    if p['built']:
                        packages_to_upload.append({'id': p['id'], 'reference': reference})
        if upload_requested:
            if packages_to_upload:
                decorated_print('Preparing upload - login to repo')
                if not logged_in:
                    login(get_login_credentials(args.artifact_repo, 'public-conan'), 'private-repo')
                    logged_in = True
                decorated_print('Uploading to private repository for profile: ' + profile)
                for p in packages_to_upload:
                    call(["conan", "upload", "-p", p['id'], p['reference'], "-r", "private-repo", "--all", "-c"])
        packages_to_upload = []


if __name__ == "__main__":
    main()
