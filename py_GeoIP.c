/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */
/* py_GeoIP.c
 *
 * Copyright (C) 2003 MaxMind LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <Python.h>
#include "GeoIP.h"
#include "GeoIPCity.h"

staticforward PyTypeObject GeoIP_GeoIPType;

typedef struct {
  PyObject_HEAD;
  GeoIP *gi;
} GeoIP_GeoIPObject;

static PyObject*
GeoIP_new_Py(PyObject* self, PyObject *args) {
  GeoIP_GeoIPObject* GeoIP;
  int flags;

  if (!PyArg_ParseTuple(args, "i", &flags)) {
    return NULL;
  }

  GeoIP = PyObject_New(GeoIP_GeoIPObject, &GeoIP_GeoIPType);

  GeoIP->gi = GeoIP_new(flags);

  if (!GeoIP->gi) {
    return NULL;
  }

  return (PyObject*)GeoIP;
}

static PyObject*
GeoIP_open_Py(PyObject* self, PyObject *args) {
  GeoIP_GeoIPObject* GeoIP;
  char * filename;
  int flags;

  if (!PyArg_ParseTuple(args, "si", &filename, &flags)) {
    return NULL;
  }

  GeoIP = PyObject_New(GeoIP_GeoIPObject, &GeoIP_GeoIPType);

  GeoIP->gi = GeoIP_open(filename, flags);

  if (!GeoIP->gi) {
    return NULL;
  }

  return (PyObject*)GeoIP;
}

static void
GeoIP_GeoIP_dealloc(PyObject* self)
{
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  GeoIP_delete(GeoIP->gi);
  PyObject_Del(self);
}

static PyObject * GeoIP_country_code_by_name_Py(PyObject *self, PyObject *args) {
  char * name;
  const char * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_country_code_by_name(GeoIP->gi, name);
  return Py_BuildValue("s", retval);
}

static PyObject * GeoIP_country_name_by_name_Py(PyObject *self, PyObject *args) {
  char * name;
  const char * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_country_name_by_name(GeoIP->gi, name);
  return Py_BuildValue("s", retval);
}

static PyObject * GeoIP_country_code_by_addr_Py(PyObject *self, PyObject *args) {
  char * name;
  const char * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_country_code_by_addr(GeoIP->gi, name);
  return Py_BuildValue("s", retval);
}

static PyObject * GeoIP_country_name_by_addr_Py(PyObject *self, PyObject *args) {
  char * name;
  const char * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_country_name_by_addr(GeoIP->gi, name);
  return Py_BuildValue("s", retval);
}

static PyObject * GeoIP_org_by_addr_Py(PyObject *self, PyObject *args) {
  char * name;
  const char * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_org_by_addr(GeoIP->gi, name);
  return Py_BuildValue("s", retval);
}

static PyObject * GeoIP_org_by_name_Py(PyObject *self, PyObject *args) {
  char * name;
  const char * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_org_by_name(GeoIP->gi, name);
  return Py_BuildValue("s", retval);
}

void GeoIP_SetItemString(PyObject *dict, const char * name, char * value) {
	PyObject * nameObj;
	PyObject * valueObj;
	nameObj = Py_BuildValue("s",name);
	valueObj = Py_BuildValue("s",value);
	PyDict_SetItem(dict,nameObj,valueObj);
	Py_DECREF(nameObj);
	Py_DECREF(valueObj);
}

void GeoIP_SetItemFloat(PyObject *dict, const char * name, float value) {
	PyObject * nameObj;
	PyObject * valueObj;
	nameObj = Py_BuildValue("s",name);
	valueObj = Py_BuildValue("f",value);
	PyDict_SetItem(dict,nameObj,valueObj);
	Py_DECREF(nameObj);
	Py_DECREF(valueObj);
}

void GeoIP_SetItemInt(PyObject *dict, const char * name, int value) {
	PyObject * nameObj;
	PyObject * valueObj;
	nameObj = Py_BuildValue("s",name);
	valueObj = Py_BuildValue("i",value);
	PyDict_SetItem(dict,nameObj,valueObj);
	Py_DECREF(nameObj);
	Py_DECREF(valueObj);
}

static PyObject * GeoIP_region_populate_dict(GeoIPRegion * gir) {
  PyObject * retval;
  retval = PyDict_New();
  GeoIP_SetItemString(retval,"country_code",gir->country_code);
  GeoIP_SetItemString(retval,"region",gir->region);
  GeoIPRegion_delete(gir);
  return retval;
}

static PyObject * GeoIP_populate_dict(GeoIPRecord *gir) {
	PyObject * retval;
	retval = PyDict_New();
	GeoIP_SetItemString(retval,"country_code",gir->country_code);
	GeoIP_SetItemString(retval,"country_code3",gir->country_code3);
	GeoIP_SetItemString(retval,"country_name",gir->country_name);
	GeoIP_SetItemString(retval,"region",gir->region);
	GeoIP_SetItemString(retval,"city",gir->city);
	GeoIP_SetItemString(retval,"postal_code",gir->postal_code);
	GeoIP_SetItemFloat(retval,"latitude",gir->latitude);
	GeoIP_SetItemFloat(retval,"longitude",gir->longitude);
	GeoIP_SetItemInt(retval,"dma_code",gir->dma_code);
	GeoIP_SetItemInt(retval,"area_code",gir->area_code);
	GeoIPRecord_delete(gir);
	return retval;
}

static PyObject * GeoIP_record_by_addr_Py(PyObject *self, PyObject *args) {
  char * addr;
  GeoIPRecord * gir;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &addr)) {
    return NULL;
  }
  gir = GeoIP_record_by_addr(GeoIP->gi, addr);
	if (gir == NULL) {
		return NULL;
	}
	return GeoIP_populate_dict(gir);
}

static PyObject * GeoIP_record_by_name_Py(PyObject *self, PyObject *args) {
  char * name;
  GeoIPRecord * gir;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  gir = GeoIP_record_by_name(GeoIP->gi, name);
	if (gir == NULL) {
		return NULL;
	}
	return GeoIP_populate_dict(gir);
}

static PyObject * GeoIP_region_by_name_Py(PyObject *self, PyObject * args) {
  char * name;
  GeoIPRegion * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_region_by_name(GeoIP->gi, name);
  return GeoIP_region_populate_dict(retval);
}

static PyObject * GeoIP_region_by_addr_Py(PyObject *self, PyObject * args) {
  char * name;
  GeoIPRegion * retval;
  GeoIP_GeoIPObject* GeoIP = (GeoIP_GeoIPObject*)self;
  if (!PyArg_ParseTuple(args, "s", &name)) {
    return NULL;
  }
  retval = GeoIP_region_by_addr(GeoIP->gi, name);
  return GeoIP_region_populate_dict(retval);
}

static PyMethodDef GeoIP_Object_methods[] = {
  {"country_code_by_name", GeoIP_country_code_by_name_Py, 1, "Lookup Country Code By Name"},
  {"country_name_by_name", GeoIP_country_name_by_name_Py, 1, "Lookup Country Name By Name"},
  {"country_code_by_addr", GeoIP_country_code_by_addr_Py, 1, "Lookup Country Code By IP Address"},
  {"country_name_by_addr", GeoIP_country_name_by_addr_Py, 1, "Lookup Country Name By IP Address"},
  {"org_by_addr", GeoIP_org_by_addr_Py, 1, "Lookup Organization or ISP By IP Address"},
  {"org_by_name", GeoIP_org_by_name_Py, 1, "Lookup Organization or ISP By Name"},
  {"region_by_addr", GeoIP_region_by_addr_Py, 1, "Lookup Region By IP Address"},
  {"region_by_name", GeoIP_region_by_name_Py, 1, "Lookup Region By Name"},
  {"record_by_addr", GeoIP_record_by_addr_Py, 1, "Lookup City Region By IP Address"},
  {"record_by_name", GeoIP_record_by_name_Py, 1, "Lookup City Region By Name"},
  {NULL, NULL, 0, NULL}
};

static PyObject *
GeoIP_GetAttr(PyObject *self, char *attrname)
{
  if (strcmp(attrname, "GEOIP_STANDARD") == 0) {
    return Py_BuildValue("i", 0);
  }
  return Py_FindMethod(GeoIP_Object_methods, self, attrname);
}

static PyTypeObject GeoIP_GeoIPType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "GeoIP",
  sizeof(GeoIP_GeoIPObject),
  0,
  GeoIP_GeoIP_dealloc, /*tp_dealloc*/
  0,          /*tp_print*/
  (getattrfunc)GeoIP_GetAttr,  /*tp_getattr*/
  0,          /*tp_setattr*/
  0,          /*tp_compare*/
  0,          /*tp_repr*/
  0,          /*tp_as_number*/
  0,          /*tp_as_sequence*/
  0,          /*tp_as_mapping*/
  0,          /*tp_hash */
};

static PyMethodDef GeoIP_Class_methods[] = {
  {"new", GeoIP_new_Py, 1, "GeoIP Constructor"},
  {"open", GeoIP_open_Py, 1, "GeoIP Constructor with database filename argument"},
  {NULL, NULL, 0, NULL}
};

DL_EXPORT(void)
initGeoIP(void) 
{
  PyObject *m, *d, *tmp;
  GeoIP_GeoIPType.ob_type = &PyType_Type;

  m = Py_InitModule("GeoIP", GeoIP_Class_methods);
  d = PyModule_GetDict(m);

  tmp = PyInt_FromLong(0);
  PyDict_SetItemString(d, "GEOIP_STANDARD", tmp);
  Py_DECREF(tmp);

  tmp = PyInt_FromLong(1);
  PyDict_SetItemString(d, "GEOIP_MEMORY_CACHE", tmp);
  Py_DECREF(tmp);
}
