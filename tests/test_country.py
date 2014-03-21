import GeoIP
from nose.tools import assert_equal


def test_country():
    for mode in [GeoIP.GEOIP_STANDARD, GeoIP.GEOIP_MEMORY_CACHE,
                 GeoIP.GEOIP_MMAP_CACHE, GeoIP.GEOIP_INDEX_CACHE]:
        gi = GeoIP.open("tests/data/GeoIP.dat", GeoIP.GEOIP_STANDARD)

        assert_equal(gi.country_code_by_addr('64.17.254.216'), 'US')
        assert_equal(gi.last_netmask(), 29)
        assert_equal(
            gi.country_name_by_addr('64.17.254.216'), 'United States')
        assert_equal(gi.range_by_ip('64.17.254.216'),
                      ('64.17.254.216', '64.17.254.223'))
