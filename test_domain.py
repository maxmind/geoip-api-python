#!/usr/bin/python

import GeoIP

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPDomain.dat",GeoIP.GEOIP_STANDARD)

print gi.org_by_addr("24.24.24.24")
