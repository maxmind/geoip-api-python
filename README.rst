=========================================
MaxMind GeoIP Legacy Python Extension API
=========================================

Requirements
------------

* Python 2.x
* GeoIP C Library 1.4.7 or greater

Installation
------------

With `pip`:

.. code-block:: bash

    $ pip install GeoIP

From source:

.. code-block:: bash

    $ python setup.py build
    $ python setup.py install

Usage
-----

See the examples in `examples/`.

Troubleshooting
---------------

If you get a "libGeoIP.so.1: cannot open shared object  No such file or
directory" error, add /usr/local/lib to /etc/ld.so.conf then run
/sbin/ldconfig /etc/ld.so.conf

License
-------

Copyright (c) 2013 MaxMind LLC

All rights reserved.  This package is free software; it is licensed
under the LGPL 2.1 or greater.
