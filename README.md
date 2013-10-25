# MaxMind GeoIP Legacy Python Extension API

## Requirements:

* Python 2.0 or greater
* GeoIP C Library 1.4.7 or greater

## Installation

With `pip`:

    $ pip install GeoIP

From source:

    $ python setup.py build
    $ python setup.py install

## Usage

* See test.py for example usage with GeoIP Country
* See test_org.py for example usage with GeoIP ISP and Organization
* See test_domain.py for an example of GeoIP Domain usage
* See test_city.py for example usage with GeoIP City
* See test_region.py for example usage with GeoIP Region
* See test_netspeed.py for example usage with GeoIP Netspeed
* See test_v6.py for example usage with GeoIP v6 Country Database
* See test_city_acc.py for example usage with GeoIP Confidence and Accuracy Database

## Troubleshooting

If you get a "libGeoIP.so.1: cannot open shared object  No such file or
directory" error, add /usr/local/lib to /etc/ld.so.conf then run
/sbin/ldconfig /etc/ld.so.conf

## License

Copyright (c) 2013 MaxMind LLC

All rights reserved.  This package is free software; it is licensed
under the LGPL 2.1 or greater.
