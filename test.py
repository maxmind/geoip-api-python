#!/usr/bin/python2.1

import GeoIP

#gi = GeoIP.new(GeoIP.GEOIP_STANDARD)
gi = GeoIP.new(GeoIP.GEOIP_MEMORY_CACHE)
#gi = GeoIP.open("/usr/local/share/GeoIP/GeoIP.data",GeoIP.GEOIP_STANDARD)

print gi.country_code_by_name("yahoo.com")
print gi.country_name_by_name("www.government.de")
print gi.country_code_by_addr("203.195.93.0")
print gi.country_name_by_addr("203.195.93.0")
