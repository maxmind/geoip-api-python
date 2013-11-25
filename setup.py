try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

module1 = Extension('GeoIP',
                    libraries=['GeoIP'],
                    sources=['py_GeoIP.c'],
                    library_dirs=['/usr/local/lib'],
                    include_dirs=['/usr/local/include'])

setup(
    name='GeoIP',
    version='1.2.9',
    description='MaxMind GeoIP Legacy Extension',
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
        'Programming Language :: Python',
        'Topic :: Internet :: Proxy Servers',
        'Topic :: Internet',
    ),
)
