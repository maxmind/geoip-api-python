import GeoIP
from nose.tools import assert_equals


def test_region():
    gi = GeoIP.open("tests/data/GeoIPRegion.dat", GeoIP.GEOIP_STANDARD)

    gir = gi.region_by_addr('64.17.254.223')

    region = {
        'region': 'CA',
        'region_name': 'California',
        'country_code': 'US'
    }
    assert_equals(gir, region)
