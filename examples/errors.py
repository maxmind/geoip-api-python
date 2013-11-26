import GeoIP
from nose.tools import assert_equals


def test_errors():
    # The intent of these tests is to make sure there are no segfaults.
    # Most of the lookups are invalid. Unfortunately the API rarely throws
    # exceptions.
    gi = GeoIP.open("tests/data/GeoIP.dat", GeoIP.GEOIP_STANDARD)

    assert_equals(gi.org_by_addr('1.1.1.1'), None)

    assert_equals(gi.country_code_by_name('1.1.1.1'), None)

    assert_equals(gi.country_name_by_name('1.1.1.1'), None)

    assert_equals(gi.country_code_by_addr('1.1.1.1'), None)

    assert_equals(gi.country_name_by_addr('1.1.1.1'), None)

    assert_equals(gi.name_by_addr('1.1.1.1'), None)

    assert_equals(gi.name_by_name('1.1.1.1'), None)

    assert_equals(gi.org_by_addr('1.1.1.1'), None)

    assert_equals(gi.org_by_name('1.1.1.1'), None)

    assert_equals(gi.region_by_addr('1.1.1.1'), None)

    assert_equals(gi.region_by_name('1.1.1.1'), None)
    assert_equals(gi.record_by_addr('1.1.1.1'), None)

    assert_equals(gi.record_by_name('1.1.1.1'), None)

    assert_equals(gi.range_by_ip('1.1.1.1'), ('0.0.0.0', '12.87.117.255'))

    assert_equals(gi.charset('1.1.1.1'), 0)

    assert_equals(gi.set_charset(-1), 0)

    assert_equals(gi.last_netmask('1.1.1.1'), 5)

    assert_equals(gi.country_code_by_name_v6('1.1.1.1'), None)

    assert_equals(gi.country_name_by_name_v6('1.1.1.1'), None)

    assert_equals(gi.country_code_by_addr_v6('1.1.1.1'), None)

    assert_equals(gi.country_name_by_addr_v6('1.1.1.1'), None)

    assert_equals(gi.enable_teredo(-100), 1)
    assert_equals(gi.teredo('1.1.1.1'), 0)
    assert_equals(gi.id_by_addr('1.1.1.1'), 0)
    assert_equals(gi.id_by_name('1.1.1.1'), 0)
    assert_equals(gi.record_by_addr_v6('1.1.1.1'), None)

    assert_equals(gi.record_by_name_v6('1.1.1.1'), None)
