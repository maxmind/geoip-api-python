#!/usr/bin/python

import GeoIP
import GeoIPRecord

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPCity.dat",GeoIP.GEOIP_STANDARD)

gir = gi.record_by_addr("24.24.24.24")

print gir['country_code'] + '\t' + gir['country_code3'] + '\t' + gir['country_name'] + '\t' + gir['region'] + '\t' + gir['city'] + '\t' + gir['postal_code']
print gir['latitude']
print gir['longitude']
print gir['dma_code']
print gir['area_code'];
