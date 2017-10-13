#!/usr/bin/env python

import unittest
from os import path
from conanrepo import conanrepo

def create_path_to_local_file(file_name):
    return path.join(path.dirname(path.realpath(__file__)), file_name)


class MyTestCase(unittest.TestCase):
    OK_CONFIG = create_path_to_local_file('ok_config')
    EXPECTED_SECTION = 'this-is-section'
    NOT_EXPECTED_SECTION = 'this-is-wrong-section'
    EXPECTED_USERNAME = 'my_username'
    EXPECTED_PASSWORD = 'my_password'
    EXPECTED_REMOTE = 'my_remote'
    NOT_EXPECTED_OPTION = 'not_existing_option'
    MISSING_OPTION = create_path_to_local_file('missing_option')
    NOT_EXISTING_FILE = create_path_to_local_file('not_existing.cfg')
    NOT_SUPPORTED_FILE_TYPE = create_path_to_local_file('no_section')

    def test_foo(self):
        self.assertEqual(1, 1)

    def test_all_passed(self):
        config = conanrepo.Config(self.OK_CONFIG, self.EXPECTED_SECTION)
        self.assertEqual(config.get_option('username'), self.EXPECTED_USERNAME)
        self.assertEqual(config.get_option('password'), self.EXPECTED_PASSWORD)
        self.assertEqual(config.get_option('remote'), self.EXPECTED_REMOTE)

    def test_non_existing_cfg_file(self):
        self.assertRaises(conanrepo.ConfigFileNotFoundException, conanrepo.Config, self.NOT_EXISTING_FILE,
                          self.EXPECTED_SECTION)

    def test_non_section_file(self):
        self.assertRaises(conanrepo.NonSectionFileException, conanrepo.Config, self.NOT_SUPPORTED_FILE_TYPE,
                          self.EXPECTED_SECTION)

    def test_non_existing_section(self):
        self.assertRaises(conanrepo.SectionNotFoundException, conanrepo.Config, self.OK_CONFIG,
                          self.NOT_EXPECTED_SECTION)

    def test_option_not_found(self):
        self.assertRaises(conanrepo.OptionNotFoundException, conanrepo.Config, self.MISSING_OPTION,
                          self.EXPECTED_SECTION)

    def test_not_supported_option_not_found(self):
        config = conanrepo.Config(self.OK_CONFIG, self.EXPECTED_SECTION)
        self.assertRaises(conanrepo.NotSupportedOptionException, config.get_option, self.NOT_EXPECTED_OPTION)


if __name__ == '__main__':
    unittest.main()
