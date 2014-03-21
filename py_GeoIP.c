/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* py_GeoIP.c
 *
 * Copyright (C) 2007 MaxMind LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <Python.h>

#include "GeoIP.h"
#include "GeoIPCity.h"

#ifdef __GNUC__
    #  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
    #  define UNUSED(x) UNUSED_ ## x
#endif

/* Python 2.x compatibility: in all the places PyUnicode_FromString is used,
   we actually want whatever the default str() for that Python is */
#if PY_MAJOR_VERSION <= 2
    #  undef PyUnicode_FromString
    #  define PyUnicode_FromString(s) PyString_FromString(s)
#endif

/* Python 2.5 compatibility */
#ifndef PyVarObject_HEAD_INIT
    #  define PyVarObject_HEAD_INIT(x, y) PyObject_HEAD_INIT(x) y,
#endif
#ifndef PyModule_AddIntMacro
    #  define PyModule_AddIntMacro(m, c) PyModule_AddIntConstant(m, # c, c)
#endif

static PyTypeObject GeoIP_GeoIPType;

/* Exception object for python */
static PyObject *GeoIP_GeoIPError;

typedef struct {
    PyObject_HEAD
    GeoIP *gi;
} GeoIP_GeoIPObject;

static int
GeoIP_GeoIP_init(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "filename", "flags", NULL };
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    char *filename = NULL;
    int flags;

    /* For consistency with the C API, positional arguments are in the
       order filename, flags; but it is filename that is optional. */
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", kwlist + 1, &flags)) {
        GeoIP->gi = GeoIP_new(flags);
    } else{
        PyErr_Clear();
        if (PyArg_ParseTupleAndKeywords(args, kwargs, "si", kwlist,
                                        &filename, &flags)) {
            GeoIP->gi = GeoIP_open(filename, flags);
        } else{
            return -1;
        }
    }

    if (!GeoIP->gi) {
        /* Failure is probably due to a system-call-level failure. */
        if (!filename) {
            filename = GeoIPDBFileName[GEOIP_COUNTRY_EDITION];
        }
        PyErr_SetFromErrnoWithFilename(GeoIP_GeoIPError, filename);
        return -1;
    }

    return 0;
}

static void GeoIP_GeoIP_dealloc(PyObject *self)
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    GeoIP_delete(GeoIP->gi);
    PyObject_Del(self);
}

static PyObject *GeoIP_country_code_by_name_v6_Py(PyObject * self,
                                                  PyObject * args)
{
    char *name;
    const char *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_code_by_name_v6(GeoIP->gi, name);
    return Py_BuildValue("s", retval);
}

static PyObject *GeoIP_country_name_by_name_v6_Py(PyObject * self,
                                                  PyObject * args)
{
    char *name;
    const char *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_name_by_name_v6(GeoIP->gi, name);
    return Py_BuildValue("s", retval);
}

static PyObject *GeoIP_country_code_by_addr_v6_Py(PyObject * self,
                                                  PyObject * args)
{
    char *name;
    const char *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_code_by_addr_v6(GeoIP->gi, name);
    return Py_BuildValue("s", retval);
}

static PyObject *GeoIP_country_name_by_addr_v6_Py(PyObject * self,
                                                  PyObject * args)
{
    char *name;
    const char *retval;
    PyObject *ret;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_name_by_addr_v6(GeoIP->gi, name);
    ret = Py_BuildValue("s", retval);
    return ret;
}

static PyObject *GeoIP_country_code_by_name_Py(PyObject * self, PyObject * args)
{
    char *name;
    const char *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_code_by_name(GeoIP->gi, name);
    return Py_BuildValue("s", retval);
}

static PyObject *GeoIP_country_name_by_name_Py(PyObject * self, PyObject * args)
{
    char *name;
    const char *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_name_by_name(GeoIP->gi, name);
    return Py_BuildValue("s", retval);
}

static PyObject *GeoIP_country_code_by_addr_Py(PyObject * self, PyObject * args)
{
    char *name;
    const char *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_code_by_addr(GeoIP->gi, name);
    return Py_BuildValue("s", retval);
}

static PyObject *GeoIP_country_name_by_addr_Py(PyObject * self, PyObject * args)
{
    char *name;
    const char *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_country_name_by_addr(GeoIP->gi, name);
    return Py_BuildValue("s", retval);
}

static PyObject *GeoIP_name_by_addr_Py(PyObject * self, PyObject * args)
{
    char *name;
    char *org;
    PyObject *ret;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    org = GeoIP_name_by_addr(GeoIP->gi, name);
    ret = Py_BuildValue("s", org);
    free(org);
    return ret;
}

static PyObject *GeoIP_name_by_addr_v6_Py(PyObject * self, PyObject * args)
{
    char *name;
    char *org;
    PyObject *ret;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    org = GeoIP_name_by_addr_v6(GeoIP->gi, name);
    ret = Py_BuildValue("s", org);
    free(org);
    return ret;
}

static PyObject *GeoIP_name_by_name_Py(PyObject * self, PyObject * args)
{
    char *name;
    char *org;
    PyObject *ret;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    org = GeoIP_name_by_name(GeoIP->gi, name);
    ret = Py_BuildValue("s", org);
    free(org);
    return ret;
}

static PyObject *GeoIP_name_by_name_v6_Py(PyObject * self, PyObject * args)
{
    char *name;
    char *org;
    PyObject *ret;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    org = GeoIP_name_by_name_v6(GeoIP->gi, name);
    ret = Py_BuildValue("s", org);
    free(org);
    return ret;
}

static PyObject *GeoIP_id_by_addr_Py(PyObject * self, PyObject * args)
{
    char *name;
    int i;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    i = GeoIP_id_by_addr(GeoIP->gi, name);
    return Py_BuildValue("i", i);
}

static PyObject *GeoIP_id_by_name_Py(PyObject * self, PyObject * args)
{
    char *name;
    int i;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    i = GeoIP_id_by_name(GeoIP->gi, name);
    return Py_BuildValue("i", i);
}

void GeoIP_SetItemString(PyObject * dict, const char *name, const char *value)
{
    PyObject *nameObj;
    PyObject *valueObj;
    if ((nameObj = Py_BuildValue("s", name))) {
        if ((valueObj = Py_BuildValue("s", value))) {
            PyDict_SetItem(dict, nameObj, valueObj);
            Py_DECREF(valueObj);
        }
        Py_DECREF(nameObj);
    }
}

void GeoIP_SetItemFloat(PyObject * dict, const char *name, float value)
{
    PyObject *nameObj;
    PyObject *valueObj;
    if ((nameObj = Py_BuildValue("s", name))) {
        if ((valueObj = Py_BuildValue("f", value))) {
            PyDict_SetItem(dict, nameObj, valueObj);
            Py_DECREF(valueObj);
        }
        Py_DECREF(nameObj);
    }
}

void GeoIP_SetItemInt(PyObject * dict, const char *name, int value)
{
    PyObject *nameObj;
    PyObject *valueObj;
    if ((nameObj = Py_BuildValue("s", name))) {
        if ((valueObj = Py_BuildValue("i", value))) {
            PyDict_SetItem(dict, nameObj, valueObj);
            Py_DECREF(valueObj);
        }
        Py_DECREF(nameObj);
    }
}

static PyObject *GeoIP_region_populate_dict(GeoIPRegion * gir)
{
    PyObject *retval;
    const char *region_name = NULL;
    retval = PyDict_New();
    GeoIP_SetItemString(retval, "country_code", gir->country_code);
    GeoIP_SetItemString(retval, "region", gir->region);
    if (gir->country_code[0]) {
        region_name = GeoIP_region_name_by_code(gir->country_code, gir->region);
    }
    GeoIP_SetItemString(retval, "region_name", region_name);
    GeoIPRegion_delete(gir);
    return retval;
}

static PyObject *GeoIP_populate_dict(GeoIP * gi, GeoIPRecord * gir)
{
    PyObject *retval;
    retval = PyDict_New();
    GeoIP_SetItemString(retval, "country_code", gir->country_code);
    GeoIP_SetItemString(retval, "country_code3", gir->country_code3);
    GeoIP_SetItemString(retval, "country_name", gir->country_name);
    GeoIP_SetItemString(retval, "region", gir->region);
    GeoIP_SetItemString(retval, "city", gir->city);
    GeoIP_SetItemString(retval, "postal_code", gir->postal_code);
    GeoIP_SetItemFloat(retval, "latitude", gir->latitude);
    GeoIP_SetItemFloat(retval, "longitude", gir->longitude);
    GeoIP_SetItemString(retval, "region_name",
                        GeoIP_region_name_by_code(gir->country_code,
                                                  gir->region));
    GeoIP_SetItemString(retval, "time_zone",
                        GeoIP_time_zone_by_country_and_region(gir->country_code,
                                                              gir->region));
    if (gi->databaseType != GEOIP_CITY_EDITION_REV0) {
        /*
         * metro_code is a alias for the depreciated dma_code.
         * we use the depreciated gir->dma_code since the CAPI
         * wrapper might be outdated and does not supply metro_code
         */
        GeoIP_SetItemInt(retval, "dma_code", gir->dma_code);
        /* we did __NOT__ use gir->metro_code here, since metro_code is
         * somewhat new */
        GeoIP_SetItemInt(retval, "metro_code", gir->dma_code);
        GeoIP_SetItemInt(retval, "area_code", gir->area_code);
    }

    GeoIPRecord_delete(gir);
    return retval;
}

static PyObject *GeoIP_record_by_addr_v6_Py(PyObject * self, PyObject * args)
{
    char *addr;
    GeoIPRecord *gir;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &addr)) {
        return NULL;
    }
    gir = GeoIP_record_by_addr_v6(GeoIP->gi, addr);
    if (gir == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return GeoIP_populate_dict(GeoIP->gi, gir);
}

static PyObject *GeoIP_record_by_name_v6_Py(PyObject * self, PyObject * args)
{
    char *name;
    GeoIPRecord *gir;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    gir = GeoIP_record_by_name_v6(GeoIP->gi, name);
    if (gir == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return GeoIP_populate_dict(GeoIP->gi, gir);
}

static PyObject *GeoIP_record_by_addr_Py(PyObject * self, PyObject * args)
{
    char *addr;
    GeoIPRecord *gir;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &addr)) {
        return NULL;
    }
    gir = GeoIP_record_by_addr(GeoIP->gi, addr);
    if (gir == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return GeoIP_populate_dict(GeoIP->gi, gir);
}

static PyObject *GeoIP_record_by_name_Py(PyObject * self, PyObject * args)
{
    char *name;
    GeoIPRecord *gir;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    gir = GeoIP_record_by_name(GeoIP->gi, name);
    if (gir == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return GeoIP_populate_dict(GeoIP->gi, gir);
}

static PyObject *GeoIP_region_by_name_Py(PyObject * self, PyObject * args)
{
    char *name;
    GeoIPRegion *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_region_by_name(GeoIP->gi, name);
    if (retval == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return GeoIP_region_populate_dict(retval);
}

static PyObject *GeoIP_region_by_addr_Py(PyObject * self, PyObject * args)
{
    char *name;
    GeoIPRegion *retval;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    retval = GeoIP_region_by_addr(GeoIP->gi, name);
    if (retval == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return GeoIP_region_populate_dict(retval);
}

static PyObject *GeoIP_range_by_ip_Py(PyObject * self, PyObject * args)
{
    char *name;
    char **start_stop_ptr;
    PyObject *retval;

    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    start_stop_ptr = GeoIP_range_by_ip(GeoIP->gi, name);
    if (!start_stop_ptr) {
        return NULL;
    }

    retval = Py_BuildValue("ss", start_stop_ptr[0], start_stop_ptr[1]);

    /* relplace this code with GeoIP_range_by_ip_delete in the next version
     * otherwise the users need 1.4.5 instead of 1.4.4 */
    if (retval) {
        if (start_stop_ptr[0]) {
            free(start_stop_ptr[0]);
        }
        if (start_stop_ptr[1]) {
            free(start_stop_ptr[1]);
        }
        free(start_stop_ptr);
    }
    return retval;
}

static PyObject *GeoIP_charset_Py(PyObject *self, PyObject *UNUSED(args))
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    return Py_BuildValue("i", GeoIP_charset(GeoIP->gi));
}

static PyObject *GeoIP_set_charset_Py(PyObject * self, PyObject * args)
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    int charset;
    if (!PyArg_ParseTuple(args, "i", &charset)) {
        return NULL;
    }
    return Py_BuildValue("i", GeoIP_set_charset(GeoIP->gi, charset));

}

static PyObject *GeoIP_last_netmask_Py(PyObject * self, PyObject *UNUSED(args))
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    return Py_BuildValue("i", GeoIP_last_netmask(GeoIP->gi));
}

static PyObject *GeoIP_teredo_Py(PyObject * self, PyObject *UNUSED(args))
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    return Py_BuildValue("i", GeoIP_teredo(GeoIP->gi));
}

static PyObject *GeoIP_enable_teredo_Py(PyObject * self, PyObject * args)
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    int teredo;
    if (!PyArg_ParseTuple(args, "i", &teredo)) {
        return NULL;
    }
    return Py_BuildValue("i", GeoIP_enable_teredo(GeoIP->gi, teredo));
}


static PyObject *GeoIP_new_Py(PyObject *UNUSED(self), PyObject * args)
{
    int dummy;
    /* enforce calling convention */
    if (!PyArg_ParseTuple(args, "i", &dummy)) {
        return NULL;
    }
    return PyObject_Call((PyObject *)&GeoIP_GeoIPType, args, NULL);
}

static PyObject *GeoIP_open_Py(PyObject *UNUSED(self), PyObject * args)
{
    char *dummy1;
    int dummy2;
    /* enforce calling convention */
    if (!PyArg_ParseTuple(args, "si", &dummy1, &dummy2)) {
        return NULL;
    }
    return PyObject_Call((PyObject *)&GeoIP_GeoIPType, args, NULL);
}

static PyObject *GeoIP_lib_version_Py(PyObject *UNUSED(self),
                                      PyObject *UNUSED(args))
{
    return Py_BuildValue("s", GeoIP_lib_version());
}

static PyObject *GeoIP_time_zone_by_country_and_region_Py(PyObject *UNUSED(self),
                                                          PyObject * args)
{
    char *country_code, *region;
    if (!PyArg_ParseTuple(args, "ss", &country_code, &region)) {
        return NULL;
    }
    return Py_BuildValue("s",
                         GeoIP_time_zone_by_country_and_region(country_code,
                                                               region));
}

static PyMethodDef GeoIP_GeoIP_methods[] = {
    { "country_code_by_name",    GeoIP_country_code_by_name_Py,    METH_VARARGS,
      "Lookup Country Code By Name" },
    { "country_name_by_name",    GeoIP_country_name_by_name_Py,    METH_VARARGS,
      "Lookup Country Name By Name" },
    { "country_code_by_addr",    GeoIP_country_code_by_addr_Py,    METH_VARARGS,
      "Lookup Country Code By IP Address" },
    { "country_name_by_addr",    GeoIP_country_name_by_addr_Py,    METH_VARARGS,
      "Lookup Country Name By IP Address" },
    { "name_by_addr",            GeoIP_name_by_addr_Py,            METH_VARARGS,
      "Lookup ASN, Domain, ISP and Organisation By IP Address" },
    { "name_by_name",            GeoIP_name_by_name_Py,            METH_VARARGS,
      "Lookup ASN, Domain, ISP and Organisation By Name" },
    { "org_by_addr",             GeoIP_name_by_addr_Py,            METH_VARARGS,
      "Lookup ASN, Domain, ISP and Organisation By IP Address ( deprecated use name_by_addr instead )" },
    { "org_by_name",             GeoIP_name_by_name_Py,            METH_VARARGS,
      "Lookup ASN, Domain, ISP and Organisation By Name ( deprecated use name_by_addr instead )" },
    { "region_by_addr",          GeoIP_region_by_addr_Py,          METH_VARARGS,
      "Lookup Region By IP Address" },
    { "region_by_name",          GeoIP_region_by_name_Py,          METH_VARARGS,
      "Lookup Region By Name" },
    { "record_by_addr",          GeoIP_record_by_addr_Py,          METH_VARARGS,
      "Lookup City Region By IP Address" },
    { "record_by_name",          GeoIP_record_by_name_Py,          METH_VARARGS,
      "Lookup City Region By Name" },
    { "range_by_ip",             GeoIP_range_by_ip_Py,             METH_VARARGS,
      "Lookup start and end IP's for a given IP" },
    { "charset",                 GeoIP_charset_Py,                 METH_NOARGS,
      "Return the current charset ( either GEOIP_CHARSET_ISO_8859_1 or GEOIP_CHARSET_UTF8 )" },
    { "set_charset",             GeoIP_set_charset_Py,             METH_VARARGS,
      "Set the charset for city records" },
    { "last_netmask",            GeoIP_last_netmask_Py,            METH_NOARGS,
      "Return the netmask depth of the last lookup" },
    { "country_code_by_name_v6", GeoIP_country_code_by_name_v6_Py, METH_VARARGS,
      "Lookup IPv6 Country Code By Name" },
    { "country_name_by_name_v6", GeoIP_country_name_by_name_v6_Py, METH_VARARGS,
      "Lookup IPv6 Country Name By Name" },
    { "country_code_by_addr_v6", GeoIP_country_code_by_addr_v6_Py, METH_VARARGS,
      "Lookup IPv6 Country Code By IP Address" },
    { "country_name_by_addr_v6", GeoIP_country_name_by_addr_v6_Py, METH_VARARGS,
      "Lookup IPv6 Country Name By IP Address" },
    { "enable_teredo",           GeoIP_enable_teredo_Py,           METH_VARARGS,
      "Enable / disable teredo" },
    { "teredo",                  GeoIP_teredo_Py,                  METH_NOARGS,
      "Returns true if teredo is enabled" },
    { "id_by_addr",              GeoIP_id_by_addr_Py,              METH_VARARGS,
      "Lookup Netspeed By IP Address" },
    { "id_by_name",              GeoIP_id_by_name_Py,              METH_VARARGS,
      "Lookup Netspeed By Name" },
    { "record_by_addr_v6",       GeoIP_record_by_addr_v6_Py,       METH_VARARGS,
      "Lookup City Region By IP Address" },
    { "record_by_name_v6",       GeoIP_record_by_name_v6_Py,       METH_VARARGS,
      "Lookup City Region By Name" },
    { "name_by_addr_v6",         GeoIP_name_by_addr_v6_Py,         METH_VARARGS,
      "Lookup IPv6 ASN, Domain, ISP and Organisation By IP Address" },
    { "name_by_name_v6",         GeoIP_name_by_name_v6_Py,         METH_VARARGS,
      "Lookup IPv6 ASN, Domain, ISP and Organisation By Name" },
    { NULL,                      NULL,                             0,
      NULL }
};

static PyObject *GeoIP_get_GEOIP_STANDARD(PyObject *UNUSED(self),
                                          void *UNUSED(closure))
{
    return Py_BuildValue("i", GEOIP_STANDARD);
}

static PyObject *GeoIP_get_database_info(PyObject *self,
                                         void *UNUSED(closure))
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    char *database_info = GeoIP_database_info(GeoIP->gi);
    PyObject *ret = Py_BuildValue("z", database_info);
    free(database_info);
    return ret;
}

static PyObject *GeoIP_get_database_edition(PyObject *self,
                                            void *UNUSED(closure))
{
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    return Py_BuildValue("z",
                         GeoIPDBDescription[GeoIP_database_edition
                                                (GeoIP->gi)]);
}

static PyGetSetDef GeoIP_GeoIP_getsets[] = {
    { "database_edition", GeoIP_get_database_edition, NULL,
      "Edition of the database ( country, city, ISP, etc )", NULL },
    { "database_info",    GeoIP_get_database_info,    NULL,
      "Information about the database", NULL },
    { "GEOIP_STANDARD",   GeoIP_get_GEOIP_STANDARD,   NULL,
      "Same as module-level GEOIP_STANDARD constant ( deprecated )", NULL },
    { NULL,               NULL,                       NULL,NULL,NULL }
};

static PyTypeObject GeoIP_GeoIPType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "GeoIP.GeoIP",              /*tp_name*/
    sizeof(GeoIP_GeoIPObject),  /*tp_basicsize*/
    0,                          /*tp_itemsize*/
    GeoIP_GeoIP_dealloc,        /*tp_dealloc*/
    0,                          /*tp_print*/
    0,                          /*tp_getattr*/
    0,                          /*tp_setattr*/
    0,                          /*tp_compare*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping */
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    0,                          /*tp_getattro*/
    0,                          /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,         /*tp_flags*/
    "GeoIP database object",    /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    0,                          /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    GeoIP_GeoIP_methods,        /*tp_methods*/
    0,                          /*tp_members*/
    GeoIP_GeoIP_getsets,        /*tp_getset*/
    0,                          /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    GeoIP_GeoIP_init,           /*tp_init*/
    0,                          /*tp_alloc*/
    0,                          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
    0,                          /*tp_bases*/
    0,                          /*tp_mro*/
    0,                          /*tp_cache*/
    0,                          /*tp_subclasses*/
    0,                          /*tp_weaklist*/
    0,                          /*tp_del*/
#if PY_MAJOR_VERSION >= 3 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 6)
    0,                          /*tp_version_tag*/
#if PY_MAJOR_VERSION >= 4 || (PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION >= 4)
    0,                          /*tp_finalize*/
#endif
#endif

    /* More fields are present #ifdef COUNT_ALLOCS, but object.h
       specifically says not to explicitly initialize them.  */
};

static PyMethodDef GeoIP_module_methods[] = {
    { "new",                             GeoIP_new_Py,
      METH_VARARGS,
      "GeoIP Constructor" },
    { "open",                            GeoIP_open_Py,
      METH_VARARGS,
      "GeoIP Constructor with database filename argument" },
    { "lib_version",                     GeoIP_lib_version_Py,
      METH_NOARGS,
      "Returns the CAPI version" },
    { "time_zone_by_country_and_region",
      GeoIP_time_zone_by_country_and_region_Py, METH_VARARGS,
      "Returns time_zone for country, region" },
    { NULL,                              NULL,                0,NULL }
};

/* Code shared between 2.x and 3.x module initialization. */
static int
GeoIP_populate_module(PyObject *m)
{
    PyObject *tmp = NULL;
    PyObject *ccode = NULL;
    PyObject *cname = NULL;
    PyObject *ccont = NULL;
    size_t i;
    const size_t total_ccodes = sizeof(GeoIP_country_code) /
                                sizeof(GeoIP_country_code[0]);

#define CHECK(expr) do { if (expr) { goto fail; } } while (0)
#define CHECK_NULL(expr) do { if (!(expr)) { goto fail; } } while (0)

    GeoIP_GeoIPType.tp_new = PyType_GenericNew;
    CHECK(PyType_Ready(&GeoIP_GeoIPType));
    Py_INCREF(&GeoIP_GeoIPType);
    CHECK(PyModule_AddObject(m, "GeoIP", (PyObject *)&GeoIP_GeoIPType));

    GeoIP_GeoIPError = PyErr_NewException("GeoIP.error", PyExc_OSError, NULL);
    Py_INCREF(GeoIP_GeoIPError);
    CHECK(PyModule_AddObject(m, "error", GeoIP_GeoIPError));

    CHECK_NULL(ccode = PyTuple_New(total_ccodes));
    CHECK_NULL(cname = PyDict_New());
    CHECK_NULL(ccont = PyDict_New());

    for (i = 0; i < total_ccodes; i++) {
        CHECK_NULL(tmp = PyUnicode_FromString(GeoIP_country_code[i]));
        PyTuple_SET_ITEM(ccode, i, tmp);

        CHECK_NULL(tmp = PyUnicode_FromString(GeoIP_country_name[i]));
        CHECK(PyDict_SetItemString(cname, GeoIP_country_code[i], tmp));
        Py_DECREF(tmp);

        CHECK_NULL(tmp = PyUnicode_FromString(GeoIP_country_continent[i]));
        CHECK(PyDict_SetItemString(ccont, GeoIP_country_code[i], tmp));
        Py_DECREF(tmp);
    }
    tmp = NULL;

    CHECK(PyModule_AddObject(m, "country_codes", ccode));
    CHECK(PyModule_AddObject(m, "country_names", cname));
    CHECK(PyModule_AddObject(m, "country_continents", ccont));

    CHECK(PyModule_AddIntMacro(m, GEOIP_STANDARD));
    CHECK(PyModule_AddIntMacro(m, GEOIP_MEMORY_CACHE));
    CHECK(PyModule_AddIntMacro(m, GEOIP_MMAP_CACHE));
    CHECK(PyModule_AddIntMacro(m, GEOIP_CHECK_CACHE));
    CHECK(PyModule_AddIntMacro(m, GEOIP_INDEX_CACHE));
    CHECK(PyModule_AddIntMacro(m, GEOIP_CHARSET_ISO_8859_1));
    CHECK(PyModule_AddIntMacro(m, GEOIP_CHARSET_UTF8));
    CHECK(PyModule_AddIntMacro(m, GEOIP_UNKNOWN_SPEED));
    CHECK(PyModule_AddIntMacro(m, GEOIP_DIALUP_SPEED));
    CHECK(PyModule_AddIntMacro(m, GEOIP_CABLEDSL_SPEED));
    CHECK(PyModule_AddIntMacro(m, GEOIP_CORPORATE_SPEED));

    return 0;

#undef CHECK
#undef CHECK_NULL

 fail:
    Py_XDECREF(ccode);
    Py_XDECREF(cname);
    Py_XDECREF(ccont);
    Py_XDECREF(tmp);
    Py_XDECREF(m);
    Py_XDECREF(GeoIP_GeoIPError); GeoIP_GeoIPError = NULL;
    return -1;
}

#if PY_MAJOR_VERSION < 3

PyMODINIT_FUNC initGeoIP(void)
{
    PyObject *m = Py_InitModule3("GeoIP",
                                 GeoIP_module_methods,
                                 "MaxMind GeoIP databases - Python API.");
    if (m) {
        GeoIP_populate_module(m);
    }
}

#else

static PyModuleDef GeoIP_module = {
    PyModuleDef_HEAD_INIT,                    /*m_base*/
    "GeoIP",                                  /*m_name*/
    "MaxMind GeoIP databases - Python API",   /*m_doc*/
    -1,                                       /*m_size*/
    GeoIP_module_methods,                     /*m_methods*/
    0,                                        /*m_reload*/
    0,                                        /*m_traverse*/
    0,                                        /*m_clear*/
    0,                                        /*m_free*/
};

PyMODINIT_FUNC PyInit_GeoIP(void)
{
    PyObject *m = PyModule_Create(&GeoIP_module);
    if (!m) {
        return NULL;
    }
    if (GeoIP_populate_module(m)) {
        return NULL;
    }
    return m;
}

#endif
