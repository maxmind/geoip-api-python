# -*- coding: utf-8 -*-

import GeoIP
from nose.tools import assert_equal


def test_charset():
    gi = GeoIP.open("tests/data/GeoIPOrg.dat", GeoIP.GEOIP_STANDARD)

    gi.set_charset(GeoIP.GEOIP_CHARSET_UTF8)
    assert_equal(gi.charset(), GeoIP.GEOIP_CHARSET_UTF8)

    assert_equal(gi.name_by_addr("142.217.214.0"),
                 'LINO Solutions Internet de Télébec')
