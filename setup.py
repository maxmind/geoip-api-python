from distutils.core import setup, Extension

module1 = Extension('GeoIP',
	libraries = ['GeoIP'],
	sources = ['py_GeoIP.c'])

setup (name = 'GeoIP-Python',
	version = '0.2.0',
	description = 'This is a python wrapper to GeoIP',
	ext_modules = [module1])
