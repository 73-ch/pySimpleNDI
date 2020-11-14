import os
import re
import sys
import platform
import subprocess

from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

__version__ = "0.1.5"

setup(
    name='pysimplendi',
    version=__version__,
    license='MIT',
    author='Kosaku Namikawa',
    author_email='cigarbox.nami@gmail.com',

    description='simple python NDI sender/receiver',
    long_description='',
    url='https://github.com/73-ch/pySimpleNDI',

    install_requires=["setuptools", "wheel", "pybind11==2.6.0"],
    ext_modules=[
        Pybind11Extension("pysimplendi",
                          sorted(glob("src/*.cpp")),
                          include_dirs=["libs/include"],
                          libraries=["ndi"],
                          define_macros=[('VERSION_INFO', __version__)],
                          ),
    ],
    cmdclass=dict(build_ext=build_ext),
    zip_safe=False,
)