import GeoIP
from nose.tools import assert_equal


def test_city():
    gi = GeoIP.open("tests/data/GeoIPCity.dat", GeoIP.GEOIP_STANDARD)

    gir = gi.record_by_addr("64.17.254.216")

    record = {
        'area_code': 310,
        'city': 'El Segundo',
        'country_code': 'US',
        'country_code3': 'USA',
        'country_name': 'United States',
        'dma_code': 803,
        'latitude': 33.91640090942383,
        'longitude': -118.40399932861328,
        'metro_code': 803,
        'postal_code': '90245',
        'region': 'CA',
        'region_name': 'California',
        'time_zone': 'America/Los_Angeles'
    }

    assert_equal(gir, record)
