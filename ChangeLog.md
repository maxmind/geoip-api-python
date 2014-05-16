# Change Log

## 1.3.x (2014-XX-XX)

* The description for `org_by_name` incorrectly directed people to use
  `name_by_addr` rather than `name_by_name`.

## 1.3.1 (2014-03-21)

* Fix for broken strings in Python 3. Strings with non-ASCII characters
  would throw a UTF-8 decoding error. In Python 3, all strings from the
  database are in UTF-8 and using `set_charset` to set the character set
  to something other than UTF-8 will throw an `ValueError` exception.

## 1.3.0 (2014-03-21)

* Python 3 support and significant code cleanup. ( Zack Weinberg )
* The methods `name_by_addr`, `name_by_addr_v6`, `name_by_name`, and
  `name_by_name_v6` were added for ISP, Org, and ASNum lookups.
  ( Carlos Rodrigues )
* Portability fixes.
* Expose `GEOIP_MMAP_CACHE` from the C library. ( George Macon )
* Unit tests were added.

## 1.2.9 (2013-11-04)

* Packaging fix. PyPI-only release.

## 1.2.8 (2013-03-20)
* Remove unused code. ( Boris Zentner )
* Fix low memory error handling and refcount issues on error
  reported by Matt Domsch

## 1.2.7 (2011-08-23)
* Add example test_netspeedcell.py ( Boris Zentner )

## 1.2.6 (2011-06-06)
* Add new methods record_by_name_v6 and record_by_addr_v6 to support
  GeoIPCityv6 databases. ( Boris Zentner )

## 1.2.5 (2011-05-10)
* Remove Confidence and Accuracy Database it is unsued anyway. ( Boris
  Zentner )
* Add new methods enable_teredo, teredo, time_zone_by_country_and_region and
  lib_version ( Boris Zentner )
* Add support for Confidence and Accuracy Database.
* Add support for Netspeed Database. via: id_by_addr id_by_name
* Add IPv6 glue *** needs libGeoIP 1.4.7 ***
  * country_code_by_name_v6
  * country_name_by_name_v6
  * country_code_by_addr_v6
  * country_name_by_addr_v6 ( Boris Zentner )

## 1.2.4 (2008-12-16)
* Add charset and set_charset methods, as well as the new attributes
  GeoIP.GEOIP_CHARSET_ISO_8859_1 and GeoIP.GEOIP_CHARSET_UTF8
  ( Boris Zentner )
* Add test_city_charset.py script showing howto use charset and set_charset
  ( Boris Zentner )
* Add last_netmask ( Boris Zentner )
* Fix compile warnings ( Boris Zentner )
* fix small memoryleak in database_info, org_by_name and org_by_addr
  ( Boris Zentner )
* fix version number in setup.py ( Boris Zentner )
* remove dma_code from test_city.py example ( Boris Zentner )

## 1.2.3 (2008-09-11)
* update test.py - replace www.government.de with www.bundestag.de.
  Add range_by_ip example. ( Boris Zentner )
* Add range_by_ip - returns largest start and stop ip for any ip.
  Remember to use a IP not a name ( Boris Zentner )
* Add metro_code as a alias for the depreciated dma_code ( Boris Zentner )

## 1.2.2 (2008-08-13)
* Update test_city.py and test_region.py ( Boris Zentner )
* Add region_name to GeoIPRegion ( Boris Zentner )
* Add database_info and database_edition attributes to GeoIP object
  (James Henstridge)
* Add region_name and time_zone keys to GeoIPRecord wrapper (James
  Henstridge).
* Export the country list, country code -> country name mapping, and
  country->continent mapping ( Ignacio Vazquez-Abrams )
* Raise country code counter from 251 to 253 ( Boris Zentner )
* record_by_addr and record_by_name return None instead of throwing a
  exception. See test_city.py ( Boris Zentner )
* Add a py_geoip.error Exception object. (Boris Zentner)
* Export the country list, country code -> country name mapping, and country->continent
  mapping ( Ignacio Vazquez-Abrams )
* Changed license to LGPL from GPL

## 1.2.1 (2005-06-28)
* Added support for GeoIP Region

## 1.2.0 (2003-05-08)
* Added support for GeoIP City

## 1.1.0 (2003-03-18)
* Added support for GeoIP ISP and Organization

## 0.2.0 (2002-06-25)
* Initial Release
