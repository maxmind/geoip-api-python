#!/usr/bin/python

import GeoIP

#gi = GeoIP.new(GeoIP.GEOIP_STANDARD)
gi = GeoIP.new(GeoIP.GEOIP_MEMORY_CACHE)
#gi = GeoIP.open("/usr/local/share/GeoIP/GeoIP.dat",GeoIP.GEOIP_STANDARD)

print gi.country_code_by_name("yahoo.com")
print gi.last_netmask()
print gi.country_name_by_name("www.bundestag.de")
print gi.country_code_by_addr("24.24.24.24")
print gi.country_name_by_addr("24.24.24.24")
print gi.range_by_ip("68.180.206.184")

