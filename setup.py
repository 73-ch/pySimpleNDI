import os
import platform

from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext


# version info
__version__ = "0.1.5"


# add libndi location to library_dirs
library_dirs = []
system = platform.system()

if system == "Windows":
    if os.environ['NDI_SDK_DIR']:
        library_dirs.append(os.environ['NDI_SDK_DIR'] + "/Lib/x64")
elif system == "Darwin":
    library_dirs.append("/Library/NDI SDK for Apple/lib/x64")
elif system == "Linux":
    library_dirs.append("/usr/lib")


# define ext_module
ext_module = Pybind11Extension("pysimplendi",
                               sorted(glob("src/*.cpp")),
                               include_dirs=["libs/include"],
                               library_dirs=library_dirs,
                               libraries=["ndi"],
                               define_macros=[('VERSION_INFO', __version__)],
                               )


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
    ext_modules=[ext_module],
    cmdclass=dict(build_ext=build_ext),
    zip_safe=False,
)
