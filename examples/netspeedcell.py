#!/usr/bin/python

import GeoIP

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPNetSpeedCell.dat",GeoIP.GEOIP_STANDARD)

print gi.org_by_name("yahoo.com")
print gi.org_by_name("www.google.com")
print gi.org_by_addr("24.24.24.24")
