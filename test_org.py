#!/usr/bin/python

import GeoIP

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPOrg.dat",GeoIP.GEOIP_STANDARD)

print gi.org_by_name("yahoo.com")
print gi.org_by_name("www.government.de")
print gi.org_by_addr("203.195.93.0")
