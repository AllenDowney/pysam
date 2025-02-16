#ifndef SAM_PVWATTSV5_H_
#define SAM_PVWATTSV5_H_

#include "visibility.h"
#include "SAM_api.h"


#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

	//
	// Pvwattsv5 Technology Model
	//

	/** 
	 * Create a Pvwattsv5 variable table.
	 * @param def: the set of financial model-dependent defaults to use (None, Residential, ...)
	 * @param[in,out] err: a pointer to an error object
	 */

	SAM_EXPORT typedef void * SAM_Pvwattsv5;

	SAM_EXPORT SAM_Pvwattsv5 SAM_Pvwattsv5_construct(const char* def, SAM_error* err);

	/// verbosity level 0 or 1. Returns 1 on success
	SAM_EXPORT int SAM_Pvwattsv5_execute(SAM_Pvwattsv5 data, int verbosity, SAM_error* err);

	SAM_EXPORT void SAM_Pvwattsv5_destruct(SAM_Pvwattsv5 system);


	//
	// LocationAndResource parameters
	//

	/**
	 * Set solar_resource_data: Weather data
	 * options: dn,df,tdry,wspd,lat,lon,tz
	 * constraints: None
	 * required if: ?
	 */
	SAM_EXPORT void SAM_Pvwattsv5_LocationAndResource_solar_resource_data_tset(SAM_Pvwattsv5 ptr, SAM_table tab, SAM_error *err);

	/**
	 * Set solar_resource_file: Weather file path
	 * options: None
	 * constraints: None
	 * required if: ?
	 */
	SAM_EXPORT void SAM_Pvwattsv5_LocationAndResource_solar_resource_file_sset(SAM_Pvwattsv5 ptr, const char* str, SAM_error *err);


	//
	// SystemDesign parameters
	//

	/**
	 * Set array_type: Array type [0/1/2/3/4]
	 * options: Fixed OR,Fixed Roof,1Axis,Backtracked,2Axis
	 * constraints: MIN=0,MAX=4,INTEGER
	 * required if: *
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_array_type_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set azimuth: Azimuth angle [deg]
	 * options: E=90,S=180,W=270
	 * constraints: MIN=0,MAX=360
	 * required if: array_type<4
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_azimuth_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set batt_simple_enable: Enable Battery [0/1]
	 * options: None
	 * constraints: BOOLEAN
	 * required if: ?=0
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_batt_simple_enable_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set dc_ac_ratio: DC to AC ratio [ratio]
	 * options: None
	 * constraints: POSITIVE
	 * required if: ?=1.1
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_dc_ac_ratio_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set gcr: Ground coverage ratio [0..1]
	 * options: None
	 * constraints: MIN=0,MAX=3
	 * required if: ?=0.4
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_gcr_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set inv_eff: Inverter efficiency at rated power [%]
	 * options: None
	 * constraints: MIN=90,MAX=99.5
	 * required if: ?=96
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_inv_eff_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set losses: System losses [%]
	 * options: Total system losses
	 * constraints: MIN=-5,MAX=99
	 * required if: *
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_losses_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set module_type: Module type [0/1/2]
	 * options: Standard,Premium,Thin film
	 * constraints: MIN=0,MAX=2,INTEGER
	 * required if: ?=0
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_module_type_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set shading:azal: Azimuth x altitude beam shading loss [%]
	 * options: None
	 * constraints: None
	 * required if: ?
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_shading_azal_mset(SAM_Pvwattsv5 ptr, double* mat, int nrows, int ncols, SAM_error *err);

	/**
	 * Set shading:diff: Diffuse shading loss [%]
	 * options: None
	 * constraints: None
	 * required if: ?
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_shading_diff_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set shading:mxh: Month x Hour beam shading loss [%]
	 * options: None
	 * constraints: None
	 * required if: ?
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_shading_mxh_mset(SAM_Pvwattsv5 ptr, double* mat, int nrows, int ncols, SAM_error *err);

	/**
	 * Set shading:timestep: Time step beam shading loss [%]
	 * options: None
	 * constraints: None
	 * required if: ?
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_shading_timestep_mset(SAM_Pvwattsv5 ptr, double* mat, int nrows, int ncols, SAM_error *err);

	/**
	 * Set system_capacity: System size (DC nameplate) [kW]
	 * options: None
	 * constraints: None
	 * required if: *
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_system_capacity_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);

	/**
	 * Set tilt: Tilt angle [deg]
	 * options: H=0,V=90
	 * constraints: MIN=0,MAX=90
	 * required if: array_type<4
	 */
	SAM_EXPORT void SAM_Pvwattsv5_SystemDesign_tilt_nset(SAM_Pvwattsv5 ptr, double number, SAM_error *err);


	/**
	 * LocationAndResource Getters
	 */

	SAM_EXPORT SAM_table SAM_Pvwattsv5_LocationAndResource_solar_resource_data_tget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT const char* SAM_Pvwattsv5_LocationAndResource_solar_resource_file_sget(SAM_Pvwattsv5 ptr, SAM_error *err);


	/**
	 * SystemDesign Getters
	 */

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_array_type_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_azimuth_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_batt_simple_enable_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_dc_ac_ratio_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_gcr_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_inv_eff_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_losses_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_module_type_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_SystemDesign_shading_azal_mget(SAM_Pvwattsv5 ptr, int* nrows, int* ncols, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_shading_diff_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_SystemDesign_shading_mxh_mget(SAM_Pvwattsv5 ptr, int* nrows, int* ncols, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_SystemDesign_shading_timestep_mget(SAM_Pvwattsv5 ptr, int* nrows, int* ncols, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_system_capacity_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_SystemDesign_tilt_nget(SAM_Pvwattsv5 ptr, SAM_error *err);


	/**
	 * Outputs Getters
	 */

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_ac_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_ac_annual_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_ac_monthly_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_annual_energy_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_aoi_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_capacity_factor_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT const char* SAM_Pvwattsv5_Outputs_city_sget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_dc_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_dc_monthly_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_df_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_dn_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_elev_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_gh_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_inverter_efficiency_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_inverter_model_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_kwh_per_kw_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_lat_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT const char* SAM_Pvwattsv5_Outputs_location_sget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_lon_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_monthly_energy_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_poa_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_poa_monthly_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_shad_beam_factor_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_solrad_annual_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_solrad_monthly_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT const char* SAM_Pvwattsv5_Outputs_state_sget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_sunup_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_system_use_lifetime_output_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_tamb_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_tcell_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_tpoa_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_ts_shift_hours_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double SAM_Pvwattsv5_Outputs_tz_nget(SAM_Pvwattsv5 ptr, SAM_error *err);

	SAM_EXPORT double* SAM_Pvwattsv5_Outputs_wspd_aget(SAM_Pvwattsv5 ptr, int* length, SAM_error *err);

#ifdef __cplusplus
} /* end of extern "C" { */
#endif

#endif