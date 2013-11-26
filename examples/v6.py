#!/usr/bin/python

import GeoIP

#gi = GeoIP.new(GeoIP.GEOIP_STANDARD)
#gi = GeoIP.new(GeoIP.GEOIP_MEMORY_CACHE)
gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPv6.dat",GeoIP.GEOIP_STANDARD)

print gi.country_code_by_name_v6("ipv6.google.com")
print gi.country_name_by_name_v6("ipv6.google.com")
print gi.country_code_by_addr_v6("2001:4860:0:1001::68")
print gi.country_name_by_addr_v6("2001:4860:0:1001::68")

