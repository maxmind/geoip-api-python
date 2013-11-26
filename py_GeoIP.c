/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
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

staticforward PyTypeObject GeoIP_GeoIPType;

/* Exception object for python */
static PyObject *PyGeoIPError;

typedef struct {
    PyObject_HEAD
    GeoIP *gi;
} GeoIP_GeoIPObject;

static PyObject *GeoIP_new_Py(PyObject *UNUSED(self), PyObject * args)
{
    GeoIP_GeoIPObject *GeoIP;
    int flags;

    if (!PyArg_ParseTuple(args, "i", &flags)) {
        return NULL;
    }

    GeoIP = PyObject_New(GeoIP_GeoIPObject, &GeoIP_GeoIPType);

    if (!GeoIP) {
        return NULL;
    }

    GeoIP->gi = GeoIP_new(flags);

    if (!GeoIP->gi) {
        PyErr_SetString(PyGeoIPError, "Can't create GeoIP->gi object");
        Py_DECREF(GeoIP);
        return NULL;
    }

    return (PyObject *)GeoIP;
}

static PyObject *GeoIP_open_Py(PyObject *UNUSED(self), PyObject * args)
{
    GeoIP_GeoIPObject *GeoIP;
    char *filename;
    int flags;

    if (!PyArg_ParseTuple(args, "si", &filename, &flags)) {
        return NULL;
    }

    GeoIP = PyObject_New(GeoIP_GeoIPObject, &GeoIP_GeoIPType);

    if (!GeoIP) {
        return NULL;
    }

    GeoIP->gi = GeoIP_open(filename, flags);

    if (!GeoIP->gi) {
        PyErr_SetString(PyGeoIPError, "Can't create GeoIP->gi object");
        Py_DECREF(GeoIP);
        return NULL;
    }

    return (PyObject *)GeoIP;
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

static PyMethodDef GeoIP_Object_methods[] = {
    { "country_code_by_name",    GeoIP_country_code_by_name_Py,    METH_VARARGS,
      "Lookup Country Code By Name" },
    { "country_name_by_name",    GeoIP_country_name_by_name_Py,    METH_VARARGS,
      "Lookup Country Name By Name" },
    { "country_code_by_addr",    GeoIP_country_code_by_addr_Py,    METH_VARARGS,
      "Lookup Country Code By IP Address" },
    { "country_name_by_addr",    GeoIP_country_name_by_addr_Py,    METH_VARARGS,
      "Lookup Country Name By IP Address" },
    { "name_by_addr",             GeoIP_name_by_addr_Py,           METH_VARARGS,
      "Lookup ASN, Domain, ISP and Organisation By IP Address" },
    { "name_by_name",             GeoIP_name_by_name_Py,           METH_VARARGS,
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
    { NULL,                      NULL,                             0,
      NULL }
};

static PyObject *GeoIP_GetAttr(PyObject * self, char *attrname)
{
    PyObject *ret;
    char *database_info;
    GeoIP_GeoIPObject *GeoIP = (GeoIP_GeoIPObject *)self;
    if (strcmp(attrname, "GEOIP_STANDARD") == 0) {
        return Py_BuildValue("i", 0);
    } else if (strcmp(attrname, "database_info") == 0) {
        database_info = GeoIP_database_info(GeoIP->gi);
        ret = Py_BuildValue("z", database_info);
        free(database_info);
        return ret;
    } else if (strcmp(attrname, "database_edition") == 0) {
        return Py_BuildValue("z",
                             GeoIPDBDescription[GeoIP_database_edition
                                                    (GeoIP->gi)]);
    }
    return Py_FindMethod(GeoIP_Object_methods, self, attrname);
}

static PyTypeObject GeoIP_GeoIPType = {
    PyObject_HEAD_INIT(NULL)
    0,
    "GeoIP",
    sizeof(GeoIP_GeoIPObject),
    0,
    GeoIP_GeoIP_dealloc,        /*tp_dealloc */
    0,                          /*tp_print */
    (getattrfunc) GeoIP_GetAttr,        /*tp_getattr */
    0,                          /*tp_setattr */
    0,                          /*tp_compare */
    0,                          /*tp_repr */
    0,                          /*tp_as_number */
    0,                          /*tp_as_sequence */
    0,                          /*tp_as_mapping */
    0,                          /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "GeoIP database object",   /* tp_doc */
   0,                         /*  tp_traverse */
   0,                         /*  tp_clear */
   0,                         /*  tp_richcompare */
   0,                         /*  tp_weaklistoffset */
   0,                         /*  tp_iter */
   0,                         /*  tp_iternext */
   0,                         /*  tp_methods */
   0,                         /*  tp_members */
   0,                         /*  tp_getset */
   0,               /*  tp_base */
   0,                         /*  tp_dict */
   0,                         /*  tp_descr_get */
   0,                         /*  tp_descr_set */
   0,                         /*  tp_dictoffset */
   0,                         /*  tp_init */
   0,                         /*  tp_alloc */
   0,                         /*  tp_new */
   0,                         /*  tp_free */
   0,                         /*  tp_is_gc */
   0,                         /*  tp_bases */
   0,                         /*  tp_mro */
   0,                         /*  tp_cache */
   0,                         /*  tp_subclasses */
   0                          /*  tp_weaklist */
#if PY_MAJOR_VERSION >= 2 && PY_MINOR_VERSION >= 3
   , 0                        /*  tp_del */
#endif
#if PY_MAJOR_VERSION >= 2 && PY_MINOR_VERSION >= 6
   , 0                        /*  tp_version_tag */
#endif
};

static PyMethodDef GeoIP_Class_methods[] = {
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
    { NULL,                              NULL,
      0,
      NULL }
};

DL_EXPORT(void) initGeoIP(void){
    PyObject *m, *d, *tmp, *ccode, *cname, *ccont, *name;
    int i;
    const int total_ccodes = sizeof(GeoIP_country_code) /
                             sizeof(GeoIP_country_code[0]);
    GeoIP_GeoIPType.ob_type = &PyType_Type;

    m = Py_InitModule("GeoIP", GeoIP_Class_methods);
    d = PyModule_GetDict(m);

    PyGeoIPError = PyErr_NewException("py_geoip.error", NULL, NULL);
    PyDict_SetItemString(d, "error", PyGeoIPError);

    ccode = PyTuple_New(total_ccodes);
    cname = PyDict_New();
    ccont = PyDict_New();

    for (i = 0; i < total_ccodes; i++) {
        name = PyString_FromString(GeoIP_country_code[i]);
        PyTuple_SET_ITEM(ccode, i, name);

        tmp = PyString_FromString(GeoIP_country_name[i]);
        PyDict_SetItem(cname, name, tmp);
        Py_DECREF(tmp);

        tmp = PyString_FromString(GeoIP_country_continent[i]);
        PyDict_SetItem(ccont, name, tmp);
        Py_DECREF(tmp);
    }

    PyDict_SetItemString(d, "country_codes", ccode);
    Py_DECREF(ccode);
    PyDict_SetItemString(d, "country_names", cname);
    Py_DECREF(cname);
    PyDict_SetItemString(d, "country_continents", ccont);
    Py_DECREF(ccont);

    tmp = PyInt_FromLong(GEOIP_STANDARD);
    PyDict_SetItemString(d, "GEOIP_STANDARD", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_MEMORY_CACHE);
    PyDict_SetItemString(d, "GEOIP_MEMORY_CACHE", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_CHECK_CACHE);
    PyDict_SetItemString(d, "GEOIP_CHECK_CACHE", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_INDEX_CACHE);
    PyDict_SetItemString(d, "GEOIP_INDEX_CACHE", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_CHARSET_ISO_8859_1);
    PyDict_SetItemString(d, "GEOIP_CHARSET_ISO_8859_1", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_CHARSET_UTF8);
    PyDict_SetItemString(d, "GEOIP_CHARSET_UTF8", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_UNKNOWN_SPEED);
    PyDict_SetItemString(d, "GEOIP_UNKNOWN_SPEED", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_DIALUP_SPEED);
    PyDict_SetItemString(d, "GEOIP_DIALUP_SPEED", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_CABLEDSL_SPEED);
    PyDict_SetItemString(d, "GEOIP_CABLEDSL_SPEED", tmp);
    Py_DECREF(tmp);

    tmp = PyInt_FromLong(GEOIP_CORPORATE_SPEED);
    PyDict_SetItemString(d, "GEOIP_CORPORATE_SPEED", tmp);
    Py_DECREF(tmp);
}
