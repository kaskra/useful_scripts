#!/usr/bin/env python
from setuptools import setup, find_packages


# Automatically sync requirements file to
def requirements():
    with open('requirements.txt') as f:
        f.read().splitlines()


def readme():
    with open('README.md') as f:
        return f.read()


setup(
    name='NAME',
    # version='0.0.0', # TODO: equivalent to "no versioning"
    description='DESCRIPTION',
    long_description=readme(),
    url='URL',
    author='AUTHOR',
    packages=find_packages(include=["INCLUDE.*"]),
    install_requires=requirements(),
    zip_safe=False)
