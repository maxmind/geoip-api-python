from distutils.core import setup, Extension

module1 = Extension('GeoIP',
	libraries = ['GeoIP'],
	sources = ['py_GeoIP.c'],
	library_dirs = ['/usr/local/lib'],
	include_dirs = ['/usr/local/include'])

setup (name = 'GeoIP-Python',
	version = '1.2.5',
	description = 'This is a python wrapper to GeoIP',
	ext_modules = [module1])
