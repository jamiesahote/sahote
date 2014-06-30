/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "SahoteMaterial.h"

template<>
InputParameters validParams<SahoteMaterial>()
{
  InputParameters params = validParams<Material>();
  // These parameters are simple constants from the input file
  params.addRequiredCoupledVar("temperature", "The temperature for the simulation");
  MooseEnum material_type("316SS, 304SS, 308LSS, 347SS, LAS, CS, Stellite, CuNi9010, Titanium, Inconel, Incoloy, Hastelloy, SA230, Graphite, T91, PE16, Na, Pb, ");
  params.addParam<MooseEnum>("material_type",material_type,"This string specifies the material to return properties."); 

  // Many material properties scale with temperature (to be implemented later)
//  params.addRequiredCoupledVar("temperature", "Temperature of the CRUD for viscosity calculation (water temperature)");

  return params;
}

SahoteMaterial::SahoteMaterial(const std::string & name,
                           InputParameters parameters)
    :Material(name, parameters),

     // Get simple parameters from the input fil
     _temperature(coupledValue("Temperature")),

     // Parameters specifying material properties used for both structural/sample materials and cooling fluids
     _density(declareProperty<Real>("Density")),
     //_elemental composition(declareProperty<Real>("ElementalComposition")),
     _specific_heat_capacity(declareProperty<Real>("SpecificHeatCapacity")),
     _thermal_conductivity(declareProperty<Real>("ThermalConductivity")),

     // Parameters used for structural/sample material only
     // _grain_size(getParam<Real>("GrainSize")),

     // Paramaters used for cooling fluids only
     _boiling_point(declareProperty<Real>("BoilingPoint")),
     _melting_point(declareProperty<Real>("MeltingPoint")),
     _dynamic_viscosity(declareProperty<Real>("DynamicViscosity")),
     _surface_tension(declareProperty<Real>("SurfaceTension")),
     _latent_heat_of_vapourisation(declareProperty<Real>("LatentHeatOfVapuorisation")),
     _material_type(getParam<MooseEnum>("material_type"))



     // Bring in any coupled variables needed to calculate material properties
//     _T(coupledValue("temperature"))

{
}

void
SahoteMaterial::computeQpProperties()
{
  if (_material_type == "316SS")
  {
     _density[_qp] = 7.99; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.12666667 * _temperature[_qp] + 475.42; //in J/kgK
     _thermal_conductivity[_qp] = 21.4; // at 773 K //in W/mK
  }
  else if (_material_type == "304SS")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.1333333333 * _temperature[_qp] + 433.6; //in J/kgK
     _thermal_conductivity[_qp] = 21.5; // at 773 K //in W/mK
  }
  else if (_material_type == "308LSS")
  {
     _density[_qp] = 0.0011 * _temperature[_qp] + 7.0697; //in g/cm^2
     _specific_heat_capacity[_qp] = 477; //in J/kgK
     _thermal_conductivity[_qp] = 0.06 * _temperature[_qp] - 9.38; //in W/mK
  }
  else if (_material_type == "347SS")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 500; //in J/kgK
     _thermal_conductivity[_qp] = 21.5; //at 773 K //in W/mK
  }
  else if (_material_type == "LAS")
  {
     _density[_qp] = 7.72; // at 673 K //in g/cm^2
     _specific_heat_capacity[_qp] = 0.5 * _temperature[_qp] + 288.5; //in J/kgK
     _thermal_conductivity[_qp] = 25.5; // at 773 K //in W/mK
  }
  else if (_material_type == "CS")
  {
     _density[_qp] = 7.85; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.5033333333 * _temperature[_qp] + 285.59; //in J/kgK
     _thermal_conductivity[_qp] = -0.011 * _temperature[_qp] + 53.503; //in W/mK
  }
  else if (_material_type == "Stellite")
  {
     _density[_qp] = 7.99; //in g/cm^2
     _specific_heat_capacity[_qp] = 548; //in J/kgK
     _thermal_conductivity[_qp] = 21.4; //in W/mK
  }
  else if (_material_type == "CuNi9010")
  {
     _density[_qp] = 8.9; //in g/cm^2
     _specific_heat_capacity[_qp] = 377; //in J/kgK
     _thermal_conductivity[_qp] = 50; // at 573 K //in W/mK
  }
  else if (_material_type == "Titanium")
  {
     _density[_qp] = 4.51; //in g/cm^2
     _specific_heat_capacity[_qp] = 670; //at 813 K //in J/kgK
     _thermal_conductivity[_qp] = 0.0013333333 * _temperature[_qp] + 18.636; //in W/mK
  }
  else if (_material_type == "Inconel")
  {
     _density[_qp] = 8.47; //in g/cm^2
     _specific_heat_capacity[_qp] = 444; //in J/kgK
     _thermal_conductivity[_qp] = 0.0163333333 * _temperature[_qp] + 9.641; //in W/mK
  }
  else if (_material_type == "Incoloy")
  {
     _density[_qp] = 7.94; //in g/cm^2
     _specific_heat_capacity[_qp] = 460; //between 273-373 K //in J/kgK
     _thermal_conductivity[_qp] = 0.016 * _temperature[_qp] + 7.132; //in W/mK
  }
  else if (_material_type == "Hastelloy")
  {
     _density[_qp] = 8.22; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.28 * _temperature[_qp] + 337.56; //in J/kgK
     _thermal_conductivity[_qp] = 0.0223333333 * _temperature[_qp] + 1.303; //in W/mK
  }
  else if (_material_type == "SA230")
  {
     _density[_qp] = 8.97; //at room temp //in g/cm^2
     _specific_heat_capacity[_qp] = 397; //at room temp //in J/kgK
     _thermal_conductivity[_qp] = 8.97; //at room temp //in W/mK
  }
  else if (_material_type == "Graphite")
  {
     _density[_qp] = 1.76; //in g/cm^2
     _specific_heat_capacity[_qp] = 737.2; //-1382 between 300-600 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 81.4; // at 400 deg C //in W/mK
  }
  else if (_material_type == "T91")
  {
     _density[_qp] = 7.64; //-7.55 between 300-600 deg C HOW??//in g/cm^2
     _specific_heat_capacity[_qp] = 560.3; //-742.5 between 300-600 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 28.84; //-28.54 between 300-600 deg C HOW?? //in W/mK
  }
  else if (_material_type == "PE16")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
  }
  else if (_material_type == "Na")
  {
     _density[_qp] = 0.845; //in g/cm^2
     _specific_heat_capacity[_qp] = 1269; //at 450 deg C //in J/kgK
     _thermal_conductivity[_qp] = 68.88; //at 450 deg C //in W/mK
     _boiling_point[_qp] = 883; // in deg C
     _melting_point[_qp] = 98; //in deg C
     _dynamic_viscosity[_qp] = 0.3; //at 450 deg C //in mPa-s
     _surface_tension[_qp] = 163; //at 450 deg C //in mN/m
     _latent_heat_of_vapourisation[_qp] = 3871; //in kJ/kg
  }
  else if (_material_type == "Pb")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1; // in deg C
     _melting_point[_qp] = 1; //in deg C
     _dynamic_viscosity[_qp] = 1; //in mPa-s
     _surface_tension[_qp] = 1; //in mN/m
     _latent_heat_of_vapourisation[_qp] = 1; //in kJ/kg
  }
else if (_material_type == "KNO3")
  {
     _density[_qp] = 2.105; //in g/cm^2
     _specific_heat_capacity[_qp] = 1328.9; //in J/kgK
     _thermal_conductivity[_qp] = 0.376; //at 447 deg C //in W/mK
     _boiling_point[_qp] = 400; // in deg C
     _melting_point[_qp] = 334;  //in deg C
     _dynamic_viscosity[_qp] = 1.4596; //at 492 deg C //in mPa-s
     _surface_tension[_qp] = 111; //between 340-550 deg C //in mN/m
     _latent_heat_of_vapourisation[_qp] = 50.6; //in kJ/kg
  }
else if (_material_type == "Na")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1;// in deg C
     _melting_point[_qp] = 1;//in deg C
     _dynamic_viscosity[_qp] = 1;//in mPa-s
     _surface_tension[_qp] = 1;//in mN/m
     _latent_heat_of_vapourisation[_qp] = 1;//in kJ/kg
  }
else if (_material_type == "Na")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1; // in deg C
     _melting_point[_qp] = 1;//in deg C
     _dynamic_viscosity[_qp] = 1;//in mPa-s
     _surface_tension[_qp] = 1;//in mN/m
     _latent_heat_of_vapourisation[_qp] = 1;//in kJ/kg
  }
else if (_material_type == "Na")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1;// in deg C
     _melting_point[_qp] = 1;//in deg C
     _dynamic_viscosity[_qp] = 1;//in mPa-s
     _surface_tension[_qp] = 1;//in mN/m
     _latent_heat_of_vapourisation[_qp] = 1;//in kJ/kg
  }
else if (_material_type == "Na")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1;// in deg C
     _melting_point[_qp] = 1;//in deg C
     _dynamic_viscosity[_qp] = 1;//in mPa-s
     _surface_tension[_qp] = 1;//in mN/m
     _latent_heat_of_vapourisation[_qp] = 1;//in kJ/kg
  }
else if (_material_type == "Na")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1;// in deg C
     _melting_point[_qp] = 1;//in deg C
     _dynamic_viscosity[_qp] = 1;//in mPa-s
     _surface_tension[_qp] = 1;//in mN/m
     _latent_heat_of_vapourisation[_qp] = 1;//in kJ/kg
  }
else if (_material_type == "Na")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1;// in deg C
     _melting_point[_qp] = 1;//in deg C
     _dynamic_viscosity[_qp] = 1;//in mPa-s
     _surface_tension[_qp] = 1;//in mN/m
     _latent_heat_of_vapourisation[_qp] = 1;//in kJ/kg
  }
else if (_material_type == "Na")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 16.75; //-21.35 between 300-600 deg C HOW?? //in W/mK
     _boiling_point[_qp] = 1;// in deg C
     _melting_point[_qp] = 1;//in deg C
     _dynamic_viscosity[_qp] = 1;//in mPa-s
     _surface_tension[_qp] = 1;//in mN/m
     _latent_heat_of_vapourisation[_qp] = 1;//in kJ/kg
  }
}
