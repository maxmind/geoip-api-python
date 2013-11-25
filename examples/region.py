#!/usr/bin/python

import GeoIP

gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPRegion.dat",GeoIP.GEOIP_STANDARD)

gir = gi.region_by_name("www.google.com")
if gir != None:
            print gir['country_code']

            print gir['region']
            print gir['region_name']
gir = gi.region_by_addr("24.24.24.24")
if gir != None:
            print gir['country_code']
            print gir['region']
            print gir['region_name']
	    
