import os
import sys
import glob

from setuptools import setup, find_packages, Extension

with open("README.md", "r") as fh:
    long_description = fh.read()

setup(
    name="trytrie",
    version="1.2",
    description="Fast and memory efficient Trie implementation for Python",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/Zamony/trytrie",
    author="Nikita Mochalov",
    author_email="mochalov.n@yandex.ru",
    classifiers=[
        "Programming Language :: Python :: 3",
    ],
    packages=find_packages(),
    install_requires=["cffi>=1.0.0"],
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=[
        "./trytrie/build_trie.py:ffibuilder",
    ],
    package_data={'trytrie': ['libtrie.so', '_trytrie.c', '_trytrie.cpython-36m-x86_64-linux-gnu.so']},

)

