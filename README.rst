=========================================
MaxMind GeoIP Legacy Python Extension API
=========================================

End of Life
-----------

MaxMind will be retiring the GeoIP Legacy databases at the end of May
2022. Until then, this library will only receive critical security and bug
fixes. Support for this library will end completely with the last release of
the legacy GeoIP databases.

We recommend that you upgrade to our GeoIP2 databases. You can read these
from Python using `our GeoIP2 Python API <https://github.com/maxmind/GeoIP2-python>`_.

See `our blog post <https://blog.maxmind.com/2020/06/01/retirement-of-geoip-legacy-downloadable-databases-in-may-2022/>`_
for more information.

Requirements
------------

* Python 2.5+ or 3.3+
* GeoIP Legacy C Library 1.4.7 or greater

Installation
------------

With `pip`:

.. code-block:: bash

    $ pip install GeoIP

From source:

.. code-block:: bash

    $ python setup.py build
    $ python setup.py install


IP Geolocation Usage
--------------------

IP geolocation is inherently imprecise. Locations are often near the center of
the population. Any location provided by a GeoIP database should not be used to
identify a particular address or household.

Usage
-----

See the examples in the ``examples`` folder.

Troubleshooting
---------------

If you get a "libGeoIP.so.1: cannot open shared object  No such file or
directory" error, add /usr/local/lib to /etc/ld.so.conf then run
/sbin/ldconfig /etc/ld.so.conf

License
-------

Copyright (c) 2014 MaxMind LLC

All rights reserved.  This package is free software; it is licensed
under the LGPL 2.1 or greater.
