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


def test_non_ascii_city():
    gi = GeoIP.open("tests/data/GeoIPCity.dat", GeoIP.GEOIP_STANDARD)

    gir = gi.record_by_addr("89.92.212.80")

    record = {
        'city': 'F\xe2ches-thumesnil',
        'region_name': 'Nord-Pas-de-Calais',
        'region': 'B4', 'area_code': 0,
        'time_zone': 'Europe/Paris',
        'longitude': 3.0808000564575195,
        'metro_code': 0,
        'country_code3': 'FRA',
        'latitude': 50.5906982421875,
        'postal_code': None,
        'dma_code': 0,
        'country_code': 'FR',
        'country_name': 'France'
    }

    assert_equal(gir, record)
