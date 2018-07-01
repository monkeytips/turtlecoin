#! /usr/bin/python
<<<<<<< HEAD
# vim: tabstop=8 shiftwidth=8 expandtab
# $Id: setup.py,v 1.9 2012/05/23 08:50:10 nanard Exp $
# the MiniUPnP Project (c) 2007-2017 Thomas Bernard
=======
# $Id: setup.py,v 1.9 2012/05/23 08:50:10 nanard Exp $
# the MiniUPnP Project (c) 2007-2012 Thomas Bernard
>>>>>>> blood in blood out
# http://miniupnp.tuxfamily.org/ or http://miniupnp.free.fr/
#
# python script to build the miniupnpc module under unix
#
<<<<<<< HEAD
# Uses MAKE environment variable (defaulting to 'make')

from setuptools import setup, Extension
from setuptools.command import build_ext
import subprocess
import os

EXT = ['libminiupnpc.a']

class make_then_build_ext(build_ext.build_ext):
      def run(self):
            subprocess.check_call([os.environ.get('MAKE', 'make')] + EXT)
            build_ext.build_ext.run(self)

setup(name="miniupnpc",
      version=open('VERSION').read().strip(),
      author='Thomas BERNARD',
      author_email='miniupnp@free.fr',
      license=open('LICENSE').read(),
      url='http://miniupnp.free.fr/',
      description='miniUPnP client',
      cmdclass={'build_ext': make_then_build_ext},
      ext_modules=[
         Extension(name="miniupnpc", sources=["miniupnpcmodule.c"],
                   extra_objects=EXT)
      ])
=======
# replace libminiupnpc.a by libminiupnpc.so for shared library usage
from distutils.core import setup, Extension
from distutils import sysconfig
sysconfig.get_config_vars()["OPT"] = ''
sysconfig.get_config_vars()["CFLAGS"] = ''
setup(name="miniupnpc", version="1.7",
      ext_modules=[
	         Extension(name="miniupnpc", sources=["miniupnpcmodule.c"],
			           extra_objects=["libminiupnpc.a"])
			 ])
>>>>>>> blood in blood out

