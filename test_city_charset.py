#!/usr/bin/python

import GeoIP

# open the citydatabase. All cities return in iso-8859-1 by default
gi = GeoIP.open("/usr/local/share/GeoIP/GeoIPCity.dat",GeoIP.GEOIP_STANDARD)

# lookup a record, where cityname contains chars > 127 ( eg != ascii )
gir = gi.record_by_name("www.osnabrueck.de")

# print the cityname with iso-8859-1 charset
print gir['city'];

# print the cityname transformed to utf8
print unicode(gir['city'], 'iso-8859-1')

# however, at your option GeoIP can return the cityname in utf8
# just put GeoIP into utf8 mode
#
# from now on all records returns in UTF8 until you change the charset again
# Notice, that all previous records return in the previous charset
gi.set_charset(GeoIP.GEOIP_CHARSET_UTF8);

# get a new record, now in utf8
gir2 = gi.record_by_name("www.osnabrueck.de")

# and print it ( should be the same output as on line 2 )
print gir2['city']

## Some more charset examples
# current_charset = gi.charset()
# old_charset = gi.set_charset(GeoIP.GEOIP_CHARSET_ISO_8859_1);



