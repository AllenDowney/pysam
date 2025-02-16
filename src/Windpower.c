#include <Python.h>

#include <SAM_Windpower.h>
#include <SAM_api.h>

#include "PySAM_utils.h"

#include "Windpower_eqns.c"


/*
 * Resource Group
 */ 

typedef struct {
	PyObject_HEAD
	SAM_Windpower   data_ptr;
} ResourceObject;

static PyTypeObject Resource_Type;

static PyObject *
Resource_new(SAM_Windpower data_ptr)
{
	PyObject* new_obj = Resource_Type.tp_alloc(&Resource_Type,0);

	ResourceObject* Resource_obj = (ResourceObject*)new_obj;

	Resource_obj->data_ptr = data_ptr;

	return new_obj;
}

/* Resource methods */

static PyObject *
Resource_assign(ResourceObject *self, PyObject *args)
{
	PyObject* dict;
	if (!PyArg_ParseTuple(args, "O:assign", &dict)){
		return NULL;
	}

	if (!PySAM_assign_from_dict(self->data_ptr, dict, "Windpower", "Resource")){
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Resource_export(ResourceObject *self, PyObject *args)
{
	PyTypeObject* tp = &Resource_Type;
	PyObject* dict = PySAM_export_to_dict((PyObject *) self, tp);
	return dict;
}

static PyMethodDef Resource_methods[] = {
		{"assign",            (PyCFunction)Resource_assign,  METH_VARARGS,
			PyDoc_STR("assign() -> None\n Assign attributes from dictionary\n\n``Resource_vals = { var: val, ...}``")},
		{"export",            (PyCFunction)Resource_export,  METH_VARARGS,
			PyDoc_STR("export() -> dict\n Export attributes into dictionary")},
		{NULL,              NULL}           /* sentinel */
};

static PyObject *
Resource_get_weibull_k_factor(ResourceObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Resource_weibull_k_factor_nget, self->data_ptr);
}

static int
Resource_set_weibull_k_factor(ResourceObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Resource_weibull_k_factor_nset, self->data_ptr);
}

static PyObject *
Resource_get_weibull_reference_height(ResourceObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Resource_weibull_reference_height_nget, self->data_ptr);
}

static int
Resource_set_weibull_reference_height(ResourceObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Resource_weibull_reference_height_nset, self->data_ptr);
}

static PyObject *
Resource_get_weibull_wind_speed(ResourceObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Resource_weibull_wind_speed_nget, self->data_ptr);
}

static int
Resource_set_weibull_wind_speed(ResourceObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Resource_weibull_wind_speed_nset, self->data_ptr);
}

static PyObject *
Resource_get_wind_resource_data(ResourceObject *self, void *closure)
{
	return PySAM_table_getter(SAM_Windpower_Resource_wind_resource_data_tget, self->data_ptr);
}

static int
Resource_set_wind_resource_data(ResourceObject *self, PyObject *value, void *closure)
{
	return PySAM_table_setter(value, SAM_Windpower_Resource_wind_resource_data_tset, self->data_ptr);
}

static PyObject *
Resource_get_wind_resource_distribution(ResourceObject *self, void *closure)
{
	return PySAM_matrix_getter(SAM_Windpower_Resource_wind_resource_distribution_mget, self->data_ptr);
}

static int
Resource_set_wind_resource_distribution(ResourceObject *self, PyObject *value, void *closure)
{
		return PySAM_matrix_setter(value, SAM_Windpower_Resource_wind_resource_distribution_mset, self->data_ptr);
}

static PyObject *
Resource_get_wind_resource_filename(ResourceObject *self, void *closure)
{
	return PySAM_string_getter(SAM_Windpower_Resource_wind_resource_filename_sget, self->data_ptr);
}

static int
Resource_set_wind_resource_filename(ResourceObject *self, PyObject *value, void *closure)
{
	return PySAM_string_setter(value, SAM_Windpower_Resource_wind_resource_filename_sset, self->data_ptr);
}

static PyObject *
Resource_get_wind_resource_model_choice(ResourceObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Resource_wind_resource_model_choice_nget, self->data_ptr);
}

static int
Resource_set_wind_resource_model_choice(ResourceObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Resource_wind_resource_model_choice_nset, self->data_ptr);
}

static PyGetSetDef Resource_getset[] = {
{"weibull_k_factor", (getter)Resource_get_weibull_k_factor,(setter)Resource_set_weibull_k_factor,
	PyDoc_STR("*float*: Weibull K factor for wind resource\n\n*Required*: set to 1 if not provided."),
 	NULL},
{"weibull_reference_height", (getter)Resource_get_weibull_reference_height,(setter)Resource_set_weibull_reference_height,
	PyDoc_STR("*float*: Reference height for Weibull wind speed [m]\n\n*Constraints*: MIN=0\n\n*Required*: set to 50 if not provided."),
 	NULL},
{"weibull_wind_speed", (getter)Resource_get_weibull_wind_speed,(setter)Resource_set_weibull_wind_speed,
	PyDoc_STR("*float*: Average wind speed for Weibull model\n\n*Constraints*: MIN=0\n\n*Required*: set to 1 if not provided."),
 	NULL},
{"wind_resource_data", (getter)Resource_get_wind_resource_data,(setter)Resource_set_wind_resource_data,
	PyDoc_STR("*dict*: Wind resouce data in memory\n\n*Required*: False"),
 	NULL},
{"wind_resource_distribution", (getter)Resource_get_wind_resource_distribution,(setter)Resource_set_wind_resource_distribution,
	PyDoc_STR("*sequence[sequence]*: Wind Speed x Dir Distribution as 2-D PDF [m/s,deg]\n\n*Required*: set to 2 if not provided."),
 	NULL},
{"wind_resource_filename", (getter)Resource_get_wind_resource_filename,(setter)Resource_set_wind_resource_filename,
	PyDoc_STR("*str*: Local wind data file path\n\n*Constraints*: LOCAL_FILE\n\n*Required*: False"),
 	NULL},
{"wind_resource_model_choice", (getter)Resource_get_wind_resource_model_choice,(setter)Resource_set_wind_resource_model_choice,
	PyDoc_STR("*float*: Hourly or Weibull model [0/1]\n\n*Constraints*: INTEGER\n\n*Required*: True"),
 	NULL},
	{NULL}  /* Sentinel */
};

static PyTypeObject Resource_Type = {
		/* The ob_type field must be initialized in the module init function
		 * to be portable to Windows without using C++. */
		PyVarObject_HEAD_INIT(NULL, 0)
		"Windpower.Resource",             /*tp_name*/
		sizeof(ResourceObject),          /*tp_basicsize*/
		0,                          /*tp_itemsize*/
		/* methods */
		0,    /*tp_dealloc*/
		0,                          /*tp_print*/
		(getattrfunc)0,             /*tp_getattr*/
		0,                          /*tp_setattr*/
		0,                          /*tp_reserved*/
		0,                          /*tp_repr*/
		0,                          /*tp_as_number*/
		0,                          /*tp_as_sequence*/
		0,                          /*tp_as_mapping*/
		0,                          /*tp_hash*/
		0,                          /*tp_call*/
		0,                          /*tp_str*/
		0,                          /*tp_getattro*/
		0,                          /*tp_setattro*/
		0,                          /*tp_as_buffer*/
		Py_TPFLAGS_DEFAULT,         /*tp_flags*/
		0,                          /*tp_doc*/
		0,                          /*tp_traverse*/
		0,                          /*tp_clear*/
		0,                          /*tp_richcompare*/
		0,                          /*tp_weaklistofnset*/
		0,                          /*tp_iter*/
		0,                          /*tp_iternext*/
		Resource_methods,         /*tp_methods*/
		0,                          /*tp_members*/
		Resource_getset,          /*tp_getset*/
		0,                          /*tp_base*/
		0,                          /*tp_dict*/
		0,                          /*tp_descr_get*/
		0,                          /*tp_descr_set*/
		0,                          /*tp_dictofnset*/
		0,                          /*tp_init*/
		0,                          /*tp_alloc*/
		0,             /*tp_new*/
		0,                          /*tp_free*/
		0,                          /*tp_is_gc*/
};


/*
 * Turbine Group
 */ 

typedef struct {
	PyObject_HEAD
	SAM_Windpower   data_ptr;
} TurbineObject;

static PyTypeObject Turbine_Type;

static PyObject *
Turbine_new(SAM_Windpower data_ptr)
{
	PyObject* new_obj = Turbine_Type.tp_alloc(&Turbine_Type,0);

	TurbineObject* Turbine_obj = (TurbineObject*)new_obj;

	Turbine_obj->data_ptr = data_ptr;

	return new_obj;
}

/* Turbine methods */

static PyObject *
Turbine_assign(TurbineObject *self, PyObject *args)
{
	PyObject* dict;
	if (!PyArg_ParseTuple(args, "O:assign", &dict)){
		return NULL;
	}

	if (!PySAM_assign_from_dict(self->data_ptr, dict, "Windpower", "Turbine")){
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Turbine_export(TurbineObject *self, PyObject *args)
{
	PyTypeObject* tp = &Turbine_Type;
	PyObject* dict = PySAM_export_to_dict((PyObject *) self, tp);
	return dict;
}

static PyMethodDef Turbine_methods[] = {
		{"assign",            (PyCFunction)Turbine_assign,  METH_VARARGS,
			PyDoc_STR("assign() -> None\n Assign attributes from dictionary\n\n``Turbine_vals = { var: val, ...}``")},
		{"export",            (PyCFunction)Turbine_export,  METH_VARARGS,
			PyDoc_STR("export() -> dict\n Export attributes into dictionary")},
		{"calculate_powercurve", (PyCFunction)Turbine_calculate_powercurve, METH_VARARGS | METH_KEYWORDS,
			PyDoc_STR("Calculates the power produced by a wind turbine at windspeeds incremented by 0.25 m/s\nInput: var_table with key-value pairs\n     'turbine_size' - double [kW]\n     'rotor_diameter' - double [m]\n     'elevation' - double [m], required if using Weibull resource model, otherwise 0\n     'max_cp' - double max Cp [-],\n     'max_tip_speed' - double [m/s]\n     'max_tip_sp_ratio' - double max tip speed ratio [-]\n     'cut_in' - double cut in speed [m/s]\n     'cut_out' - double cut out speed [m/s]\n     'drive_train' - int 0: 3 Stage Planetary, 1: Single Stage - Low Speed Generator, 2: Multi-Generator, 3: Direct Drive\nOutput: key-value pairs added to var_table\n     'wind_turbine_powercurve_windspeeds' - array [m/s]\n     'wind_turbine_powercurve_powerout' - array [m/s]\n     'rated_wind_speed' - double [m/s[\n     'hub_efficiency' - array [m/s]")},
		{NULL,              NULL}           /* sentinel */
};

static PyObject *
Turbine_get_wind_resource_shear(TurbineObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Turbine_wind_resource_shear_nget, self->data_ptr);
}

static int
Turbine_set_wind_resource_shear(TurbineObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Turbine_wind_resource_shear_nset, self->data_ptr);
}

static PyObject *
Turbine_get_wind_turbine_hub_ht(TurbineObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Turbine_wind_turbine_hub_ht_nget, self->data_ptr);
}

static int
Turbine_set_wind_turbine_hub_ht(TurbineObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Turbine_wind_turbine_hub_ht_nset, self->data_ptr);
}

static PyObject *
Turbine_get_wind_turbine_max_cp(TurbineObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Turbine_wind_turbine_max_cp_nget, self->data_ptr);
}

static int
Turbine_set_wind_turbine_max_cp(TurbineObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Turbine_wind_turbine_max_cp_nset, self->data_ptr);
}

static PyObject *
Turbine_get_wind_turbine_powercurve_powerout(TurbineObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Turbine_wind_turbine_powercurve_powerout_aget, self->data_ptr);
}

static int
Turbine_set_wind_turbine_powercurve_powerout(TurbineObject *self, PyObject *value, void *closure)
{
	return PySAM_array_setter(value, SAM_Windpower_Turbine_wind_turbine_powercurve_powerout_aset, self->data_ptr);
}

static PyObject *
Turbine_get_wind_turbine_powercurve_windspeeds(TurbineObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Turbine_wind_turbine_powercurve_windspeeds_aget, self->data_ptr);
}

static int
Turbine_set_wind_turbine_powercurve_windspeeds(TurbineObject *self, PyObject *value, void *closure)
{
	return PySAM_array_setter(value, SAM_Windpower_Turbine_wind_turbine_powercurve_windspeeds_aset, self->data_ptr);
}

static PyObject *
Turbine_get_wind_turbine_rotor_diameter(TurbineObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Turbine_wind_turbine_rotor_diameter_nget, self->data_ptr);
}

static int
Turbine_set_wind_turbine_rotor_diameter(TurbineObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Turbine_wind_turbine_rotor_diameter_nset, self->data_ptr);
}

static PyGetSetDef Turbine_getset[] = {
{"wind_resource_shear", (getter)Turbine_get_wind_resource_shear,(setter)Turbine_set_wind_resource_shear,
	PyDoc_STR("*float*: Shear exponent\n\n*Constraints*: MIN=0\n\n*Required*: True"),
 	NULL},
{"wind_turbine_hub_ht", (getter)Turbine_get_wind_turbine_hub_ht,(setter)Turbine_set_wind_turbine_hub_ht,
	PyDoc_STR("*float*: Hub height [m]\n\n*Constraints*: POSITIVE\n\n*Required*: True"),
 	NULL},
{"wind_turbine_max_cp", (getter)Turbine_get_wind_turbine_max_cp,(setter)Turbine_set_wind_turbine_max_cp,
	PyDoc_STR("*float*: Max cp\n\n*Constraints*: MIN=0\n\n*Required*: set to 1 if not provided."),
 	NULL},
{"wind_turbine_powercurve_powerout", (getter)Turbine_get_wind_turbine_powercurve_powerout,(setter)Turbine_set_wind_turbine_powercurve_powerout,
	PyDoc_STR("*sequence*: Power curve turbine output array [kW]\n\n*Constraints*: LENGTH_EQUAL=wind_turbine_powercurve_windspeeds\n\n*Required*: True"),
 	NULL},
{"wind_turbine_powercurve_windspeeds", (getter)Turbine_get_wind_turbine_powercurve_windspeeds,(setter)Turbine_set_wind_turbine_powercurve_windspeeds,
	PyDoc_STR("*sequence*: Power curve wind speed array [m/s]\n\n*Required*: True"),
 	NULL},
{"wind_turbine_rotor_diameter", (getter)Turbine_get_wind_turbine_rotor_diameter,(setter)Turbine_set_wind_turbine_rotor_diameter,
	PyDoc_STR("*float*: Rotor diameter [m]\n\n*Constraints*: POSITIVE\n\n*Required*: True"),
 	NULL},
	{NULL}  /* Sentinel */
};

static PyTypeObject Turbine_Type = {
		/* The ob_type field must be initialized in the module init function
		 * to be portable to Windows without using C++. */
		PyVarObject_HEAD_INIT(NULL, 0)
		"Windpower.Turbine",             /*tp_name*/
		sizeof(TurbineObject),          /*tp_basicsize*/
		0,                          /*tp_itemsize*/
		/* methods */
		0,    /*tp_dealloc*/
		0,                          /*tp_print*/
		(getattrfunc)0,             /*tp_getattr*/
		0,                          /*tp_setattr*/
		0,                          /*tp_reserved*/
		0,                          /*tp_repr*/
		0,                          /*tp_as_number*/
		0,                          /*tp_as_sequence*/
		0,                          /*tp_as_mapping*/
		0,                          /*tp_hash*/
		0,                          /*tp_call*/
		0,                          /*tp_str*/
		0,                          /*tp_getattro*/
		0,                          /*tp_setattro*/
		0,                          /*tp_as_buffer*/
		Py_TPFLAGS_DEFAULT,         /*tp_flags*/
		0,                          /*tp_doc*/
		0,                          /*tp_traverse*/
		0,                          /*tp_clear*/
		0,                          /*tp_richcompare*/
		0,                          /*tp_weaklistofnset*/
		0,                          /*tp_iter*/
		0,                          /*tp_iternext*/
		Turbine_methods,         /*tp_methods*/
		0,                          /*tp_members*/
		Turbine_getset,          /*tp_getset*/
		0,                          /*tp_base*/
		0,                          /*tp_dict*/
		0,                          /*tp_descr_get*/
		0,                          /*tp_descr_set*/
		0,                          /*tp_dictofnset*/
		0,                          /*tp_init*/
		0,                          /*tp_alloc*/
		0,             /*tp_new*/
		0,                          /*tp_free*/
		0,                          /*tp_is_gc*/
};


/*
 * Farm Group
 */ 

typedef struct {
	PyObject_HEAD
	SAM_Windpower   data_ptr;
} FarmObject;

static PyTypeObject Farm_Type;

static PyObject *
Farm_new(SAM_Windpower data_ptr)
{
	PyObject* new_obj = Farm_Type.tp_alloc(&Farm_Type,0);

	FarmObject* Farm_obj = (FarmObject*)new_obj;

	Farm_obj->data_ptr = data_ptr;

	return new_obj;
}

/* Farm methods */

static PyObject *
Farm_assign(FarmObject *self, PyObject *args)
{
	PyObject* dict;
	if (!PyArg_ParseTuple(args, "O:assign", &dict)){
		return NULL;
	}

	if (!PySAM_assign_from_dict(self->data_ptr, dict, "Windpower", "Farm")){
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Farm_export(FarmObject *self, PyObject *args)
{
	PyTypeObject* tp = &Farm_Type;
	PyObject* dict = PySAM_export_to_dict((PyObject *) self, tp);
	return dict;
}

static PyMethodDef Farm_methods[] = {
		{"assign",            (PyCFunction)Farm_assign,  METH_VARARGS,
			PyDoc_STR("assign() -> None\n Assign attributes from dictionary\n\n``Farm_vals = { var: val, ...}``")},
		{"export",            (PyCFunction)Farm_export,  METH_VARARGS,
			PyDoc_STR("export() -> dict\n Export attributes into dictionary")},
		{NULL,              NULL}           /* sentinel */
};

static PyObject *
Farm_get_system_capacity(FarmObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Farm_system_capacity_nget, self->data_ptr);
}

static int
Farm_set_system_capacity(FarmObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Farm_system_capacity_nset, self->data_ptr);
}

static PyObject *
Farm_get_wind_farm_wake_model(FarmObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Farm_wind_farm_wake_model_nget, self->data_ptr);
}

static int
Farm_set_wind_farm_wake_model(FarmObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Farm_wind_farm_wake_model_nset, self->data_ptr);
}

static PyObject *
Farm_get_wind_farm_xCoordinates(FarmObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Farm_wind_farm_xCoordinates_aget, self->data_ptr);
}

static int
Farm_set_wind_farm_xCoordinates(FarmObject *self, PyObject *value, void *closure)
{
	return PySAM_array_setter(value, SAM_Windpower_Farm_wind_farm_xCoordinates_aset, self->data_ptr);
}

static PyObject *
Farm_get_wind_farm_yCoordinates(FarmObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Farm_wind_farm_yCoordinates_aget, self->data_ptr);
}

static int
Farm_set_wind_farm_yCoordinates(FarmObject *self, PyObject *value, void *closure)
{
	return PySAM_array_setter(value, SAM_Windpower_Farm_wind_farm_yCoordinates_aset, self->data_ptr);
}

static PyObject *
Farm_get_wind_resource_turbulence_coeff(FarmObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Farm_wind_resource_turbulence_coeff_nget, self->data_ptr);
}

static int
Farm_set_wind_resource_turbulence_coeff(FarmObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Farm_wind_resource_turbulence_coeff_nset, self->data_ptr);
}

static PyGetSetDef Farm_getset[] = {
{"system_capacity", (getter)Farm_get_system_capacity,(setter)Farm_set_system_capacity,
	PyDoc_STR("*float*: Nameplate capacity [kW]\n\n*Constraints*: MIN=0\n\n*Required*: True"),
 	NULL},
{"wind_farm_wake_model", (getter)Farm_get_wind_farm_wake_model,(setter)Farm_set_wind_farm_wake_model,
	PyDoc_STR("*float*: Wake Model [0/1/2/3]\n\n*Constraints*: INTEGER\n\n*Required*: True"),
 	NULL},
{"wind_farm_xCoordinates", (getter)Farm_get_wind_farm_xCoordinates,(setter)Farm_set_wind_farm_xCoordinates,
	PyDoc_STR("*sequence*: Turbine X coordinates [m]\n\n*Required*: True"),
 	NULL},
{"wind_farm_yCoordinates", (getter)Farm_get_wind_farm_yCoordinates,(setter)Farm_set_wind_farm_yCoordinates,
	PyDoc_STR("*sequence*: Turbine Y coordinates [m]\n\n*Constraints*: LENGTH_EQUAL=wind_farm_xCoordinates\n\n*Required*: True"),
 	NULL},
{"wind_resource_turbulence_coeff", (getter)Farm_get_wind_resource_turbulence_coeff,(setter)Farm_set_wind_resource_turbulence_coeff,
	PyDoc_STR("*float*: Turbulence coefficient [%]\n\n*Constraints*: MIN=0\n\n*Required*: True"),
 	NULL},
	{NULL}  /* Sentinel */
};

static PyTypeObject Farm_Type = {
		/* The ob_type field must be initialized in the module init function
		 * to be portable to Windows without using C++. */
		PyVarObject_HEAD_INIT(NULL, 0)
		"Windpower.Farm",             /*tp_name*/
		sizeof(FarmObject),          /*tp_basicsize*/
		0,                          /*tp_itemsize*/
		/* methods */
		0,    /*tp_dealloc*/
		0,                          /*tp_print*/
		(getattrfunc)0,             /*tp_getattr*/
		0,                          /*tp_setattr*/
		0,                          /*tp_reserved*/
		0,                          /*tp_repr*/
		0,                          /*tp_as_number*/
		0,                          /*tp_as_sequence*/
		0,                          /*tp_as_mapping*/
		0,                          /*tp_hash*/
		0,                          /*tp_call*/
		0,                          /*tp_str*/
		0,                          /*tp_getattro*/
		0,                          /*tp_setattro*/
		0,                          /*tp_as_buffer*/
		Py_TPFLAGS_DEFAULT,         /*tp_flags*/
		0,                          /*tp_doc*/
		0,                          /*tp_traverse*/
		0,                          /*tp_clear*/
		0,                          /*tp_richcompare*/
		0,                          /*tp_weaklistofnset*/
		0,                          /*tp_iter*/
		0,                          /*tp_iternext*/
		Farm_methods,         /*tp_methods*/
		0,                          /*tp_members*/
		Farm_getset,          /*tp_getset*/
		0,                          /*tp_base*/
		0,                          /*tp_dict*/
		0,                          /*tp_descr_get*/
		0,                          /*tp_descr_set*/
		0,                          /*tp_dictofnset*/
		0,                          /*tp_init*/
		0,                          /*tp_alloc*/
		0,             /*tp_new*/
		0,                          /*tp_free*/
		0,                          /*tp_is_gc*/
};


/*
 * Losses Group
 */ 

typedef struct {
	PyObject_HEAD
	SAM_Windpower   data_ptr;
} LossesObject;

static PyTypeObject Losses_Type;

static PyObject *
Losses_new(SAM_Windpower data_ptr)
{
	PyObject* new_obj = Losses_Type.tp_alloc(&Losses_Type,0);

	LossesObject* Losses_obj = (LossesObject*)new_obj;

	Losses_obj->data_ptr = data_ptr;

	return new_obj;
}

/* Losses methods */

static PyObject *
Losses_assign(LossesObject *self, PyObject *args)
{
	PyObject* dict;
	if (!PyArg_ParseTuple(args, "O:assign", &dict)){
		return NULL;
	}

	if (!PySAM_assign_from_dict(self->data_ptr, dict, "Windpower", "Losses")){
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Losses_export(LossesObject *self, PyObject *args)
{
	PyTypeObject* tp = &Losses_Type;
	PyObject* dict = PySAM_export_to_dict((PyObject *) self, tp);
	return dict;
}

static PyMethodDef Losses_methods[] = {
		{"assign",            (PyCFunction)Losses_assign,  METH_VARARGS,
			PyDoc_STR("assign() -> None\n Assign attributes from dictionary\n\n``Losses_vals = { var: val, ...}``")},
		{"export",            (PyCFunction)Losses_export,  METH_VARARGS,
			PyDoc_STR("export() -> dict\n Export attributes into dictionary")},
		{NULL,              NULL}           /* sentinel */
};

static PyObject *
Losses_get_avail_bop_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_avail_bop_loss_nget, self->data_ptr);
}

static int
Losses_set_avail_bop_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_avail_bop_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_avail_grid_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_avail_grid_loss_nget, self->data_ptr);
}

static int
Losses_set_avail_grid_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_avail_grid_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_avail_turb_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_avail_turb_loss_nget, self->data_ptr);
}

static int
Losses_set_avail_turb_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_avail_turb_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_elec_eff_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_elec_eff_loss_nget, self->data_ptr);
}

static int
Losses_set_elec_eff_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_elec_eff_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_en_icing_cutoff(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_en_icing_cutoff_nget, self->data_ptr);
}

static int
Losses_set_en_icing_cutoff(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_en_icing_cutoff_nset, self->data_ptr);
}

static PyObject *
Losses_get_en_low_temp_cutoff(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_en_low_temp_cutoff_nget, self->data_ptr);
}

static int
Losses_set_en_low_temp_cutoff(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_en_low_temp_cutoff_nset, self->data_ptr);
}

static PyObject *
Losses_get_env_degrad_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_env_degrad_loss_nget, self->data_ptr);
}

static int
Losses_set_env_degrad_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_env_degrad_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_env_exposure_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_env_exposure_loss_nget, self->data_ptr);
}

static int
Losses_set_env_exposure_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_env_exposure_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_env_ext_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_env_ext_loss_nget, self->data_ptr);
}

static int
Losses_set_env_ext_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_env_ext_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_env_icing_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_env_icing_loss_nget, self->data_ptr);
}

static int
Losses_set_env_icing_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_env_icing_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_icing_cutoff_rh(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_icing_cutoff_rh_nget, self->data_ptr);
}

static int
Losses_set_icing_cutoff_rh(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_icing_cutoff_rh_nset, self->data_ptr);
}

static PyObject *
Losses_get_icing_cutoff_temp(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_icing_cutoff_temp_nget, self->data_ptr);
}

static int
Losses_set_icing_cutoff_temp(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_icing_cutoff_temp_nset, self->data_ptr);
}

static PyObject *
Losses_get_low_temp_cutoff(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_low_temp_cutoff_nget, self->data_ptr);
}

static int
Losses_set_low_temp_cutoff(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_low_temp_cutoff_nset, self->data_ptr);
}

static PyObject *
Losses_get_ops_env_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_ops_env_loss_nget, self->data_ptr);
}

static int
Losses_set_ops_env_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_ops_env_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_ops_grid_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_ops_grid_loss_nget, self->data_ptr);
}

static int
Losses_set_ops_grid_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_ops_grid_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_ops_load_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_ops_load_loss_nget, self->data_ptr);
}

static int
Losses_set_ops_load_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_ops_load_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_ops_strategies_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_ops_strategies_loss_nget, self->data_ptr);
}

static int
Losses_set_ops_strategies_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_ops_strategies_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_turb_generic_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_turb_generic_loss_nget, self->data_ptr);
}

static int
Losses_set_turb_generic_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_turb_generic_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_turb_hysteresis_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_turb_hysteresis_loss_nget, self->data_ptr);
}

static int
Losses_set_turb_hysteresis_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_turb_hysteresis_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_turb_perf_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_turb_perf_loss_nget, self->data_ptr);
}

static int
Losses_set_turb_perf_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_turb_perf_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_turb_specific_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_turb_specific_loss_nget, self->data_ptr);
}

static int
Losses_set_turb_specific_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_turb_specific_loss_nset, self->data_ptr);
}

static PyObject *
Losses_get_wake_loss(LossesObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Losses_wake_loss_nget, self->data_ptr);
}

static int
Losses_set_wake_loss(LossesObject *self, PyObject *value, void *closure)
{
	return PySAM_double_setter(value, SAM_Windpower_Losses_wake_loss_nset, self->data_ptr);
}

static PyGetSetDef Losses_getset[] = {
{"avail_bop_loss", (getter)Losses_get_avail_bop_loss,(setter)Losses_set_avail_bop_loss,
	PyDoc_STR("*float*: Balance-of-plant availability loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"avail_grid_loss", (getter)Losses_get_avail_grid_loss,(setter)Losses_set_avail_grid_loss,
	PyDoc_STR("*float*: Grid availability loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"avail_turb_loss", (getter)Losses_get_avail_turb_loss,(setter)Losses_set_avail_turb_loss,
	PyDoc_STR("*float*: Turbine availabaility loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"elec_eff_loss", (getter)Losses_get_elec_eff_loss,(setter)Losses_set_elec_eff_loss,
	PyDoc_STR("*float*: Electrical efficiency loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"en_icing_cutoff", (getter)Losses_get_en_icing_cutoff,(setter)Losses_set_en_icing_cutoff,
	PyDoc_STR("*float*: Enable Icing Cutoff [0/1]\n\n*Constraints*: INTEGER\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"en_low_temp_cutoff", (getter)Losses_get_en_low_temp_cutoff,(setter)Losses_set_en_low_temp_cutoff,
	PyDoc_STR("*float*: Enable Low Temperature Cutoff [0/1]\n\n*Constraints*: INTEGER\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"env_degrad_loss", (getter)Losses_get_env_degrad_loss,(setter)Losses_set_env_degrad_loss,
	PyDoc_STR("*float*: Environmental Degradation loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"env_exposure_loss", (getter)Losses_get_env_exposure_loss,(setter)Losses_set_env_exposure_loss,
	PyDoc_STR("*float*: Environmental Exposure loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"env_ext_loss", (getter)Losses_get_env_ext_loss,(setter)Losses_set_env_ext_loss,
	PyDoc_STR("*float*: Environmental External Conditions loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"env_icing_loss", (getter)Losses_get_env_icing_loss,(setter)Losses_set_env_icing_loss,
	PyDoc_STR("*float*: Environmental Icing loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"icing_cutoff_rh", (getter)Losses_get_icing_cutoff_rh,(setter)Losses_set_icing_cutoff_rh,
	PyDoc_STR("*float*: Icing Cutoff Relative Humidity [%]\n\n*Constraints*: MIN=0\n\n*Required*: set to 1 if not provided."),
 	NULL},
{"icing_cutoff_temp", (getter)Losses_get_icing_cutoff_temp,(setter)Losses_set_icing_cutoff_temp,
	PyDoc_STR("*float*: Icing Cutoff Temperature [C]\n\n*Required*: set to 1 if not provided."),
 	NULL},
{"low_temp_cutoff", (getter)Losses_get_low_temp_cutoff,(setter)Losses_set_low_temp_cutoff,
	PyDoc_STR("*float*: Low Temperature Cutoff [C]\n\n*Required*: set to 1 if not provided."),
 	NULL},
{"ops_env_loss", (getter)Losses_get_ops_env_loss,(setter)Losses_set_ops_env_loss,
	PyDoc_STR("*float*: Environmental/Permit Curtailment loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"ops_grid_loss", (getter)Losses_get_ops_grid_loss,(setter)Losses_set_ops_grid_loss,
	PyDoc_STR("*float*: Grid curtailment loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"ops_load_loss", (getter)Losses_get_ops_load_loss,(setter)Losses_set_ops_load_loss,
	PyDoc_STR("*float*: Load curtailment loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"ops_strategies_loss", (getter)Losses_get_ops_strategies_loss,(setter)Losses_set_ops_strategies_loss,
	PyDoc_STR("*float*: Operational strategies loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"turb_generic_loss", (getter)Losses_get_turb_generic_loss,(setter)Losses_set_turb_generic_loss,
	PyDoc_STR("*float*: Turbine Generic Powercurve loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"turb_hysteresis_loss", (getter)Losses_get_turb_hysteresis_loss,(setter)Losses_set_turb_hysteresis_loss,
	PyDoc_STR("*float*: Turbine High Wind Hysteresis loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"turb_perf_loss", (getter)Losses_get_turb_perf_loss,(setter)Losses_set_turb_perf_loss,
	PyDoc_STR("*float*: Turbine Sub-optimal performance loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"turb_specific_loss", (getter)Losses_get_turb_specific_loss,(setter)Losses_set_turb_specific_loss,
	PyDoc_STR("*float*: Turbine Site-specific Powercurve loss [%]\n\n*Required*: set to 0 if not provided."),
 	NULL},
{"wake_loss", (getter)Losses_get_wake_loss,(setter)Losses_set_wake_loss,
	PyDoc_STR("*float*: Wake effects loss percent [%]\n\n*Required*: set to 3 if not provided."),
 	NULL},
	{NULL}  /* Sentinel */
};

static PyTypeObject Losses_Type = {
		/* The ob_type field must be initialized in the module init function
		 * to be portable to Windows without using C++. */
		PyVarObject_HEAD_INIT(NULL, 0)
		"Windpower.Losses",             /*tp_name*/
		sizeof(LossesObject),          /*tp_basicsize*/
		0,                          /*tp_itemsize*/
		/* methods */
		0,    /*tp_dealloc*/
		0,                          /*tp_print*/
		(getattrfunc)0,             /*tp_getattr*/
		0,                          /*tp_setattr*/
		0,                          /*tp_reserved*/
		0,                          /*tp_repr*/
		0,                          /*tp_as_number*/
		0,                          /*tp_as_sequence*/
		0,                          /*tp_as_mapping*/
		0,                          /*tp_hash*/
		0,                          /*tp_call*/
		0,                          /*tp_str*/
		0,                          /*tp_getattro*/
		0,                          /*tp_setattro*/
		0,                          /*tp_as_buffer*/
		Py_TPFLAGS_DEFAULT,         /*tp_flags*/
		0,                          /*tp_doc*/
		0,                          /*tp_traverse*/
		0,                          /*tp_clear*/
		0,                          /*tp_richcompare*/
		0,                          /*tp_weaklistofnset*/
		0,                          /*tp_iter*/
		0,                          /*tp_iternext*/
		Losses_methods,         /*tp_methods*/
		0,                          /*tp_members*/
		Losses_getset,          /*tp_getset*/
		0,                          /*tp_base*/
		0,                          /*tp_dict*/
		0,                          /*tp_descr_get*/
		0,                          /*tp_descr_set*/
		0,                          /*tp_dictofnset*/
		0,                          /*tp_init*/
		0,                          /*tp_alloc*/
		0,             /*tp_new*/
		0,                          /*tp_free*/
		0,                          /*tp_is_gc*/
};


/*
 * Outputs Group
 */ 

typedef struct {
	PyObject_HEAD
	SAM_Windpower   data_ptr;
} OutputsObject;

static PyTypeObject Outputs_Type;

static PyObject *
Outputs_new(SAM_Windpower data_ptr)
{
	PyObject* new_obj = Outputs_Type.tp_alloc(&Outputs_Type,0);

	OutputsObject* Outputs_obj = (OutputsObject*)new_obj;

	Outputs_obj->data_ptr = data_ptr;

	return new_obj;
}

/* Outputs methods */

static PyObject *
Outputs_assign(OutputsObject *self, PyObject *args)
{
	PyObject* dict;
	if (!PyArg_ParseTuple(args, "O:assign", &dict)){
		return NULL;
	}

	if (!PySAM_assign_from_dict(self->data_ptr, dict, "Windpower", "Outputs")){
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Outputs_export(OutputsObject *self, PyObject *args)
{
	PyTypeObject* tp = &Outputs_Type;
	PyObject* dict = PySAM_export_to_dict((PyObject *) self, tp);
	return dict;
}

static PyMethodDef Outputs_methods[] = {
		{"assign",            (PyCFunction)Outputs_assign,  METH_VARARGS,
			PyDoc_STR("assign() -> None\n Assign attributes from dictionary\n\n``Outputs_vals = { var: val, ...}``")},
		{"export",            (PyCFunction)Outputs_export,  METH_VARARGS,
			PyDoc_STR("export() -> dict\n Export attributes into dictionary")},
		{NULL,              NULL}           /* sentinel */
};

static PyObject *
Outputs_get_annual_energy(OutputsObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Outputs_annual_energy_nget, self->data_ptr);
}

static PyObject *
Outputs_get_capacity_factor(OutputsObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Outputs_capacity_factor_nget, self->data_ptr);
}

static PyObject *
Outputs_get_cutoff_losses(OutputsObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Outputs_cutoff_losses_nget, self->data_ptr);
}

static PyObject *
Outputs_get_gen(OutputsObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Outputs_gen_aget, self->data_ptr);
}

static PyObject *
Outputs_get_kwh_per_kw(OutputsObject *self, void *closure)
{
	return PySAM_double_getter(SAM_Windpower_Outputs_kwh_per_kw_nget, self->data_ptr);
}

static PyObject *
Outputs_get_monthly_energy(OutputsObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Outputs_monthly_energy_aget, self->data_ptr);
}

static PyObject *
Outputs_get_pressure(OutputsObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Outputs_pressure_aget, self->data_ptr);
}

static PyObject *
Outputs_get_temp(OutputsObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Outputs_temp_aget, self->data_ptr);
}

static PyObject *
Outputs_get_turbine_output_by_windspeed_bin(OutputsObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Outputs_turbine_output_by_windspeed_bin_aget, self->data_ptr);
}

static PyObject *
Outputs_get_wind_direction(OutputsObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Outputs_wind_direction_aget, self->data_ptr);
}

static PyObject *
Outputs_get_wind_speed(OutputsObject *self, void *closure)
{
	return PySAM_array_getter(SAM_Windpower_Outputs_wind_speed_aget, self->data_ptr);
}

static PyGetSetDef Outputs_getset[] = {
{"annual_energy", (getter)Outputs_get_annual_energy,(setter)0,
	PyDoc_STR("*float*: Annual Energy [kWh]"),
 	NULL},
{"capacity_factor", (getter)Outputs_get_capacity_factor,(setter)0,
	PyDoc_STR("*float*: Capacity factor [%]"),
 	NULL},
{"cutoff_losses", (getter)Outputs_get_cutoff_losses,(setter)0,
	PyDoc_STR("*float*: Cutoff losses [%]"),
 	NULL},
{"gen", (getter)Outputs_get_gen,(setter)0,
	PyDoc_STR("*sequence*: Total electric power to grid [kWh]"),
 	NULL},
{"kwh_per_kw", (getter)Outputs_get_kwh_per_kw,(setter)0,
	PyDoc_STR("*float*: First year kWh/kW [kWh/kW]"),
 	NULL},
{"monthly_energy", (getter)Outputs_get_monthly_energy,(setter)0,
	PyDoc_STR("*sequence*: Monthly Energy [kWh]"),
 	NULL},
{"pressure", (getter)Outputs_get_pressure,(setter)0,
	PyDoc_STR("*sequence*: Pressure [atm]"),
 	NULL},
{"temp", (getter)Outputs_get_temp,(setter)0,
	PyDoc_STR("*sequence*: Air temperature ['C]"),
 	NULL},
{"turbine_output_by_windspeed_bin", (getter)Outputs_get_turbine_output_by_windspeed_bin,(setter)0,
	PyDoc_STR("*sequence*: Turbine output by wind speed bin [kW]"),
 	NULL},
{"wind_direction", (getter)Outputs_get_wind_direction,(setter)0,
	PyDoc_STR("*sequence*: Wind direction [deg]"),
 	NULL},
{"wind_speed", (getter)Outputs_get_wind_speed,(setter)0,
	PyDoc_STR("*sequence*: Wind speed [m/s]"),
 	NULL},
	{NULL}  /* Sentinel */
};

static PyTypeObject Outputs_Type = {
		/* The ob_type field must be initialized in the module init function
		 * to be portable to Windows without using C++. */
		PyVarObject_HEAD_INIT(NULL, 0)
		"Windpower.Outputs",             /*tp_name*/
		sizeof(OutputsObject),          /*tp_basicsize*/
		0,                          /*tp_itemsize*/
		/* methods */
		0,    /*tp_dealloc*/
		0,                          /*tp_print*/
		(getattrfunc)0,             /*tp_getattr*/
		0,                          /*tp_setattr*/
		0,                          /*tp_reserved*/
		0,                          /*tp_repr*/
		0,                          /*tp_as_number*/
		0,                          /*tp_as_sequence*/
		0,                          /*tp_as_mapping*/
		0,                          /*tp_hash*/
		0,                          /*tp_call*/
		0,                          /*tp_str*/
		0,                          /*tp_getattro*/
		0,                          /*tp_setattro*/
		0,                          /*tp_as_buffer*/
		Py_TPFLAGS_DEFAULT,         /*tp_flags*/
		0,                          /*tp_doc*/
		0,                          /*tp_traverse*/
		0,                          /*tp_clear*/
		0,                          /*tp_richcompare*/
		0,                          /*tp_weaklistofnset*/
		0,                          /*tp_iter*/
		0,                          /*tp_iternext*/
		Outputs_methods,         /*tp_methods*/
		0,                          /*tp_members*/
		Outputs_getset,          /*tp_getset*/
		0,                          /*tp_base*/
		0,                          /*tp_dict*/
		0,                          /*tp_descr_get*/
		0,                          /*tp_descr_set*/
		0,                          /*tp_dictofnset*/
		0,                          /*tp_init*/
		0,                          /*tp_alloc*/
		0,             /*tp_new*/
		0,                          /*tp_free*/
		0,                          /*tp_is_gc*/
};

/*
 * Windpower
 */

typedef struct {
	PyObject_HEAD
	PyObject            *x_attr;        /* Attributes dictionary */
	SAM_Windpower   data_ptr;
} WindpowerObject;

static PyTypeObject Windpower_Type;

static WindpowerObject *
newWindpowerObject(void* data_ptr)
{
	WindpowerObject *self;
	self = PyObject_New(WindpowerObject, &Windpower_Type);

	PySAM_TECH_ATTR("Windpower", SAM_Windpower_construct)

	PyObject* Resource_obj = Resource_new(self->data_ptr);
	PyDict_SetItemString(attr_dict, "Resource", Resource_obj);
	Py_DECREF(Resource_obj);

	PyObject* Turbine_obj = Turbine_new(self->data_ptr);
	PyDict_SetItemString(attr_dict, "Turbine", Turbine_obj);
	Py_DECREF(Turbine_obj);

	PyObject* Farm_obj = Farm_new(self->data_ptr);
	PyDict_SetItemString(attr_dict, "Farm", Farm_obj);
	Py_DECREF(Farm_obj);

	PyObject* Losses_obj = Losses_new(self->data_ptr);
	PyDict_SetItemString(attr_dict, "Losses", Losses_obj);
	Py_DECREF(Losses_obj);

	PyObject* AdjustmentFactorsModule = PyImport_ImportModule("AdjustmentFactors");

	PyObject* data_cap = PyCapsule_New(self->data_ptr, NULL, NULL);
	PyObject* Adjust_obj = PyObject_CallMethod(AdjustmentFactorsModule, "new", "(O)", data_cap);
	Py_XDECREF(data_cap);
	Py_XDECREF(AdjustmentFactorsModule);

	if (!Adjust_obj){
		PyErr_SetString(PySAM_ErrorObject, "Couldn't create AdjustmentFactorsObject\n");
		return NULL;
	}

	PyDict_SetItemString(attr_dict, "AdjustmentFactors", Adjust_obj);
	Py_DECREF(Adjust_obj);

	PyObject* Outputs_obj = Outputs_new(self->data_ptr);
	PyDict_SetItemString(attr_dict, "Outputs", Outputs_obj);
	Py_DECREF(Outputs_obj);


	return self;
}

/* Windpower methods */

static void
Windpower_dealloc(WindpowerObject *self)
{
	Py_XDECREF(self->x_attr);
	SAM_Windpower_destruct(self->data_ptr);
	PyObject_Del(self);
}


static PyObject *
Windpower_execute(WindpowerObject *self, PyObject *args)
{
	int verbosity = 0;

	if (!PyArg_ParseTuple(args, "|i", &verbosity))
		return NULL;

	SAM_error error = new_error();
	SAM_Windpower_execute(self->data_ptr, verbosity, &error);
	if (PySAM_has_error(error )) return NULL;

	Py_INCREF(Py_None);
	return Py_None;
}


static PyObject *
Windpower_assign(WindpowerObject *self, PyObject *args)
{
	PyObject* dict;
	if (!PyArg_ParseTuple(args, "O:assign", &dict)){
		return NULL;
	}

	if (!PySAM_assign_from_nested_dict((PyObject*)self, self->x_attr, self->data_ptr, dict, "Windpower"))
		return NULL;

	Py_INCREF(Py_None);
	return Py_None;
}


static PyObject *
Windpower_export(WindpowerObject *self, PyObject *args)
{
	return PySAM_export_to_nested_dict((PyObject *) self, self->x_attr);
}

static PyMethodDef Windpower_methods[] = {
		{"execute",            (PyCFunction)Windpower_execute,  METH_VARARGS,
				PyDoc_STR("execute(int verbosity) -> None\n Execute simulation with verbosity level 0 (default) or 1")},
		{"assign",            (PyCFunction)Windpower_assign,  METH_VARARGS,
				PyDoc_STR("assign(dict) -> None\n Assign attributes from nested dictionary, except for Outputs\n\n``nested_dict = { 'Resource': { var: val, ...}, ...}``")},
		{"export",            (PyCFunction)Windpower_export,  METH_VARARGS,
				PyDoc_STR("export() -> dict\n Export attributes into nested dictionary")},
		{NULL,              NULL}           /* sentinel */
};

static PyObject *
Windpower_getattro(WindpowerObject *self, PyObject *name)
{
	return PySAM_get_attr((PyObject*) self, (PyObject*) self->x_attr, name);
}

static int
Windpower_setattr(WindpowerObject *self, const char *name, PyObject *v)
{
	return PySAM_set_attr((PyObject*)self, (PyObject*)self->x_attr, name, v);
}

static PyTypeObject Windpower_Type = {
		/* The ob_type field must be initialized in the module init function
		 * to be portable to Windows without using C++. */
		PyVarObject_HEAD_INIT(NULL, 0)
		"Windpower",            /*tp_name*/
		sizeof(WindpowerObject),/*tp_basicsize*/
		0,                          /*tp_itemsize*/
		/* methods */
		(destructor)Windpower_dealloc,    /*tp_dealloc*/
		0,                          /*tp_print*/
		(getattrfunc)0,             /*tp_getattr*/
		(setattrfunc)Windpower_setattr,   /*tp_setattr*/
		0,                          /*tp_reserved*/
		0,                          /*tp_repr*/
		0,                          /*tp_as_number*/
		0,                          /*tp_as_sequence*/
		0,                          /*tp_as_mapping*/
		0,                          /*tp_hash*/
		0,                          /*tp_call*/
		0,                          /*tp_str*/
		(getattrofunc)Windpower_getattro, /*tp_getattro*/
		0,                          /*tp_setattro*/
		0,                          /*tp_as_buffer*/
		Py_TPFLAGS_DEFAULT,         /*tp_flags*/
		"This class contains all the variable information for running a simulation. Variables are grouped together in the subclasses as properties. If property assignments are the wrong type, an error is thrown.",        /*tp_doc*/
		0,                          /*tp_traverse*/
		0,                          /*tp_clear*/
		0,                          /*tp_richcompare*/
		0,                          /*tp_weaklistofnset*/
		0,                          /*tp_iter*/
		0,                          /*tp_iternext*/
		Windpower_methods,      /*tp_methods*/
		0,                          /*tp_members*/
		0,       /*tp_getset*/
		0,                          /*tp_base*/
		0,                          /*tp_dict*/
		0,                          /*tp_descr_get*/
		0,                          /*tp_descr_set*/
		0,                          /*tp_dictofnset*/
		0,                          /*tp_init*/
		0,                          /*tp_alloc*/
		0,                          /*tp_new*/
		0,                          /*tp_free*/
		0,                          /*tp_is_gc*/
};

/* --------------------------------------------------------------------- */


/* Function of no arguments returning new Windpower object */

static PyObject *
Windpower_new(PyObject *self, PyObject *args)
{
	WindpowerObject *rv;
	rv = newWindpowerObject(0);
	if (rv == NULL)
		return NULL;
	return (PyObject *)rv;
}

static PyObject *
Windpower_wrap(PyObject *self, PyObject *args)
{
	WindpowerObject *rv;
	long long int ptr = 0;  // 64 bit arch
	if (!PyArg_ParseTuple(args, "L:wrap", &ptr)){
		PyErr_BadArgument();
		return NULL;
	}
	rv = newWindpowerObject((void*)ptr);
	if (rv == NULL)
		return NULL;
	return (PyObject *)rv;
}

static PyObject *
Windpower_default(PyObject *self, PyObject *args)
{
	WindpowerObject *rv;
	char* def = 0;
	if (!PyArg_ParseTuple(args, "s:default", &def)){
		PyErr_BadArgument();
		return NULL;
	}
	rv = newWindpowerObject(0);
	if (rv == NULL)
		return NULL;

	PySAM_load_defaults((PyObject*)rv, rv->x_attr, rv->data_ptr, "Windpower", def);

	return (PyObject *)rv;
}

/* ---------- */


/* List of functions defined in the module */

static PyMethodDef WindpowerModule_methods[] = {
		{"new",             Windpower_new,         METH_VARARGS,
				PyDoc_STR("new() -> Windpower")},
		{"default",             Windpower_default,         METH_VARARGS,
				PyDoc_STR("default(config) -> Windpower\n\nUse financial model-specific default attributes\n"
				"config options:\n\n- \"WindPowerAllEquityPartnershipFlip\"\n- \"WindPowerCommercial\"\n- \"WindPowerCommercialPPA\"\n- \"WindPowerIndependentPowerProducer\"\n- \"WindPowerLCOECalculator\"\n- \"WindPowerLeveragedPartnershipFlip\"\n- \"WindPowerNone\"\n- \"WindPowerResidential\"\n- \"WindPowerSaleLeaseback\"\n- \"WindPowerSingleOwner\"")},
		{"wrap",             Windpower_wrap,         METH_VARARGS,
				PyDoc_STR("wrap(ssc_data_t) -> Windpower\n\nUse existing PySSC data\n\n.. warning::\n\n	Do not call PySSC.data_free on the ssc_data_t provided to ``wrap``")},
		{NULL,              NULL}           /* sentinel */
};

PyDoc_STRVAR(module_doc,
			 "Wind power system with one or more wind turbines");


static int
WindpowerModule_exec(PyObject *m)
{
	/* Finalize the type object including setting type of the new type
	 * object; doing it here is required for portability, too. */

	if (PySAM_load_lib(m) < 0) goto fail;
	if (PySAM_init_error(m) < 0) goto fail;

	Windpower_Type.tp_dict = PyDict_New();
	if (!Windpower_Type.tp_dict) { goto fail; }

	/// Add the AdjustmentFactors type object to Windpower_Type
	PyObject* AdjustmentFactorsModule = PyImport_ImportModule("AdjustmentFactors");
	if (!AdjustmentFactorsModule){
		PyErr_SetImportError(PyUnicode_FromString("Could not import AdjustmentFactors module."), NULL, NULL);
	}

	PyTypeObject* AdjustmentFactors_Type = (PyTypeObject*)PyObject_GetAttrString(AdjustmentFactorsModule, "AdjustmentFactors");
	if (!AdjustmentFactors_Type){
		PyErr_SetImportError(PyUnicode_FromString("Could not import AdjustmentFactors type."), NULL, NULL);
	}
	Py_XDECREF(AdjustmentFactorsModule);

	if (PyType_Ready(AdjustmentFactors_Type) < 0) { goto fail; }
	PyDict_SetItemString(Windpower_Type.tp_dict,
						 "AdjustmentFactors",
						 (PyObject*)AdjustmentFactors_Type);
	Py_DECREF(&AdjustmentFactors_Type);
	Py_XDECREF(AdjustmentFactors_Type);

	/// Add the Resource type object to Windpower_Type
	if (PyType_Ready(&Resource_Type) < 0) { goto fail; }
	PyDict_SetItemString(Windpower_Type.tp_dict,
				"Resource",
				(PyObject*)&Resource_Type);
	Py_DECREF(&Resource_Type);

	/// Add the Turbine type object to Windpower_Type
	if (PyType_Ready(&Turbine_Type) < 0) { goto fail; }
	PyDict_SetItemString(Windpower_Type.tp_dict,
				"Turbine",
				(PyObject*)&Turbine_Type);
	Py_DECREF(&Turbine_Type);

	/// Add the Farm type object to Windpower_Type
	if (PyType_Ready(&Farm_Type) < 0) { goto fail; }
	PyDict_SetItemString(Windpower_Type.tp_dict,
				"Farm",
				(PyObject*)&Farm_Type);
	Py_DECREF(&Farm_Type);

	/// Add the Losses type object to Windpower_Type
	if (PyType_Ready(&Losses_Type) < 0) { goto fail; }
	PyDict_SetItemString(Windpower_Type.tp_dict,
				"Losses",
				(PyObject*)&Losses_Type);
	Py_DECREF(&Losses_Type);

	/// Add the Outputs type object to Windpower_Type
	if (PyType_Ready(&Outputs_Type) < 0) { goto fail; }
	PyDict_SetItemString(Windpower_Type.tp_dict,
				"Outputs",
				(PyObject*)&Outputs_Type);
	Py_DECREF(&Outputs_Type);

	/// Add the Windpower type object to the module
	if (PyType_Ready(&Windpower_Type) < 0) { goto fail; }
	PyModule_AddObject(m,
				"Windpower",
				(PyObject*)&Windpower_Type);

	return 0;
	fail:
	Py_XDECREF(m);
	return -1;
}

static struct PyModuleDef_Slot WindpowerModule_slots[] = {
		{Py_mod_exec, WindpowerModule_exec},
		{0, NULL},
};

static struct PyModuleDef WindpowerModule = {
		PyModuleDef_HEAD_INIT,
		"Windpower",
		module_doc,
		0,
		WindpowerModule_methods,
		WindpowerModule_slots,
		NULL,
		NULL,
		NULL
};

/* Export function for the module */

PyMODINIT_FUNC
PyInit_Windpower(void)
{
	return PyModuleDef_Init(&WindpowerModule);
}