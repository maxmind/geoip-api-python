import GeoIP
from nose.tools import assert_equal


def test_domain():
    gi = GeoIP.open("tests/data/GeoIPDomain.dat", GeoIP.GEOIP_STANDARD)

    assert_equal(gi.org_by_addr("67.43.156.0"), 'shoesfin.NET')
