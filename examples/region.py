#!/usr/bin/python

from __future__ import print_function

import GeoIP

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPRegion.dat", GeoIP.GEOIP_STANDARD)

gir = gi.region_by_name("www.google.com")
if gir is not None:
            print(gir['country_code'])

            print(gir['region'])
            print(gir['region_name'])
gir = gi.region_by_addr("24.24.24.24")
if gir is not None:
            print(gir['country_code'])
            print(gir['region'])
            print(gir['region_name'])
