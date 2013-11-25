#!/usr/bin/python

import GeoIP

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPNetspeed.dat",GeoIP.GEOIP_STANDARD)

# GEOIP_UNKNOWN_SPEED, GEOIP_DIALUP_SPEED, GEOIP_CABLEDSL_SPEED or
# GEOIP_CORPORATE_SPEED

print gi.id_by_name("yahoo.com")
print gi.id_by_name("www.maxmind.com") == GeoIP.GEOIP_UNKNOWN_SPEED
print gi.id_by_addr("203.195.93.0")
