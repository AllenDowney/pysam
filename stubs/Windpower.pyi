class Resource(object):
	def assign(self): 
		pass

	def export(self) -> Dict[Dict]
		pass

	def __init__(self, *args, **kwargs): 
		pass


	weibull_k_factor = float
	weibull_reference_height = float
	weibull_wind_speed = float
	wind_resource_data = dict
	wind_resource_distribution = tuple
	wind_resource_filename = str
	wind_resource_model_choice = float


class Turbine(object):
	def assign(self): 
		pass

	def export(self) -> Dict[Dict]
		pass

	def __init__(self, *args, **kwargs): 
		pass

	def calculate_powercurve(self, turbine_size=double, rotor_diameter=double, elevation=double, max_cp=double, max_tip_speed=double, max_tip_sp_ratio=double, cut_in=double, cut_out=double, drive_train=int):
		pass

	wind_resource_shear = float
	wind_turbine_hub_ht = float
	wind_turbine_max_cp = float
	wind_turbine_powercurve_powerout = tuple
	wind_turbine_powercurve_windspeeds = tuple
	wind_turbine_rotor_diameter = float


class Farm(object):
	def assign(self): 
		pass

	def export(self) -> Dict[Dict]
		pass

	def __init__(self, *args, **kwargs): 
		pass


	system_capacity = float
	wind_farm_wake_model = float
	wind_farm_xCoordinates = tuple
	wind_farm_yCoordinates = tuple
	wind_resource_turbulence_coeff = float


class Losses(object):
	def assign(self): 
		pass

	def export(self) -> Dict[Dict]
		pass

	def __init__(self, *args, **kwargs): 
		pass


	avail_bop_loss = float
	avail_grid_loss = float
	avail_turb_loss = float
	elec_eff_loss = float
	en_icing_cutoff = float
	en_low_temp_cutoff = float
	env_degrad_loss = float
	env_exposure_loss = float
	env_ext_loss = float
	env_icing_loss = float
	icing_cutoff_rh = float
	icing_cutoff_temp = float
	low_temp_cutoff = float
	ops_env_loss = float
	ops_grid_loss = float
	ops_load_loss = float
	ops_strategies_loss = float
	turb_generic_loss = float
	turb_hysteresis_loss = float
	turb_perf_loss = float
	turb_specific_loss = float
	wake_loss = float


class Outputs(object):
	def assign(self): 
		pass

	def export(self) -> Dict[Dict]
		pass

	def __init__(self, *args, **kwargs): 
		pass


	annual_energy = float
	capacity_factor = float
	cutoff_losses = float
	gen = tuple
	kwh_per_kw = float
	monthly_energy = tuple
	pressure = tuple
	temp = tuple
	turbine_output_by_windspeed_bin = tuple
	wind_direction = tuple
	wind_speed = tuple


class Windpower(object):
	def assign(self, dict):
		pass

	def execute(self, int_verbosity):
		pass

	def export(self):
		pass

	def __getattribute__(self, *args, **kwargs):
		pass

	def __init__(self, *args, **kwargs):
		pass

	Resource = Resource
	Turbine = Turbine
	Farm = Farm
	Losses = Losses
	Outputs = Outputs


def default(config) -> Windpower
	pass

def new() -> Windpower
	pass

def wrap(ssc_data_t) -> Windpower
	pass

__loader__ = None 

__spec__ = None
