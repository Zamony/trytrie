import os
import sys
import glob

from setuptools import setup, find_packages, Extension

os.chdir(os.path.dirname(sys.argv[0]) or ".")

setup(
    name="trytrie",
    version="1.0",
    description="Fast and memory efficient Trie implementation for Python",
    long_description=open("README.md").read(),
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
    ]
)

