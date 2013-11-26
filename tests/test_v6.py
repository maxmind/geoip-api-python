import GeoIP
from nose.tools import assert_equals


def test_ipv6():
    gi = GeoIP.open("tests/data/GeoIPv6.dat", GeoIP.GEOIP_STANDARD)

    assert_equals(gi.country_code_by_addr_v6('2001:200::'), 'JP')
