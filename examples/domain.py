#!/usr/bin/python

from __future__ import print_function

import GeoIP

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPDomain.dat", GeoIP.GEOIP_STANDARD)

print(gi.org_by_addr("24.24.24.24"))
