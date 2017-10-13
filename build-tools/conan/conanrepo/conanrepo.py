#!/usr/bin/env python

import configparser
from os import path


class ConanRepoException(Exception):
    def __init__(self, message):
        super(ConanRepoException, self).__init__("ERROR: " + message)


class ConfigFileNotFoundException(ConanRepoException):
    def __init__(self, file_name):
        super(ConfigFileNotFoundException, self).__init__("Could not locate config file: '%s'" % file_name)


class NonSectionFileException(ConanRepoException):
    def __init__(self, file_name):
        super(NonSectionFileException, self).__init__("File '%s' does not contain any section or is ill formatted." % file_name)


class SectionNotFoundException(ConanRepoException):
    def __init__(self, section, file_name):
        super(SectionNotFoundException, self).__init__("Could not locate section: '%s' in file: '%s'" % (section, file_name))


class OptionNotFoundException(ConanRepoException):
    def __init__(self, option, section):
        super(OptionNotFoundException, self).__init__("Could not locate option: '%s' in section: '%s'" % (option, section))


class NotSupportedOptionException(ConanRepoException):
    def __init__(self, option):
        super(NotSupportedOptionException, self).__init__("Not supported option: %s" % option)


class Config:
    REQUIRED_OPTIONS = ['username', 'password', 'remote']

    def __init__(self, config_file_name, section_name):

        config_file = path.realpath(config_file_name)

        if not path.isfile(config_file_name):
            raise ConfigFileNotFoundException(config_file)
        self.conan_repo_parser = configparser.RawConfigParser()

        with open(config_file_name) as fp:
            try:
                self.conan_repo_parser.readfp(fp)
            except configparser.MissingSectionHeaderError:
                raise NonSectionFileException(config_file)

        if not self.conan_repo_parser.has_section(section_name):
            raise SectionNotFoundException(section_name, config_file)

        self._parameters = dict()
        for option in self.REQUIRED_OPTIONS:
            if not self.conan_repo_parser.has_option(section_name, option):
                raise OptionNotFoundException(option, section_name)
            else:
                self._parameters[option] = self.conan_repo_parser.get(section_name, option)

    def get_option(self, option):
        if option not in self.REQUIRED_OPTIONS:
            raise NotSupportedOptionException(option)
        return self._parameters[option]
