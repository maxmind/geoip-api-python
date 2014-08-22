import sys

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

libs = ['GeoIP']

if sys.platform == 'win32':
    libs.append('ws2_32')

compile_args = []
# http://bugs.python.org/issue969718
if sys.version_info[0] == 2:
    compile_args.append('-fno-strict-aliasing')

module1 = Extension('GeoIP',
                    libraries=libs,
                    sources=['py_GeoIP.c'],
                    extra_compile_args=compile_args)

setup(
    name='GeoIP',
    version='1.3.2',
    description='MaxMind GeoIP Legacy Database - Python API',
    long_description=open('README.rst').read(),
    author="MaxMind, Inc.",
    author_email="support@maxmind.com",
    url='http://www.maxmind.com/',
    bugtrack_url='https://github.com/maxmind/geoip-api-python/issues',
    license=open('LICENSE').read(),
    ext_modules=[module1],
    tests_require=['nose'],
    test_suite='nose.collector',
    classifiers=(
        'Development Status :: 6 - Mature',
        'Environment :: Web Environment',
        'Intended Audience :: Developers',
        'Intended Audience :: System Administrators',
        'License :: OSI Approved :: GNU Lesser General Public License v2 or later (LGPLv2+)',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python',
        'Topic :: Internet :: Proxy Servers',
        'Topic :: Internet',
    ),
)
