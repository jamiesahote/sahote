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
  params.addRequiredCoupledVar("temperature", "The temperature for the simulation");
  MooseEnum material_type("316SS, 304SS, 308LSS, 347SS, LAS, CS, Stellite, CuNi9010, Titanium, Inconel, Incoloy, Hastelloy, SA230, Graphite, T91, PE16, W, Cu, Na, Pb, Pb-Bi, KNO3, KCSN, Hg, Rb, Cs, Glycerine,");
  params.addParam<MooseEnum>("material_type",material_type,"This string specifies the material to return properties."); 


  return params;
}

SahoteMaterial::SahoteMaterial(const InputParameters & parameters)
    :Material(parameters),

     // Get simple parameters from the input fil
     _temperature(coupledValue("temperature")),
     // Parameters specifying material properties used for both structural/sample materials and cooling fluids
     _density(declareProperty<Real>("Density")),
     _specific_heat_capacity(declareProperty<Real>("SpecificHeatCapacity")),
     _thermal_conductivity(declareProperty<Real>("ThermalConductivity")),


     // Paramaters used for cooling fluids only
     _boiling_point(declareProperty<Real>("BoilingPoint")),
     _melting_point(declareProperty<Real>("MeltingPoint")),
     _dynamic_viscosity(declareProperty<Real>("DynamicViscosity")),
     _surface_tension(declareProperty<Real>("SurfaceTension")),
     _latent_heat_of_vapourisation(declareProperty<Real>("LatentHeatOfVapuorisation")),
     _material_type(getParam<MooseEnum>("material_type"))
     




{
}

void
SahoteMaterial::computeQpProperties()
{
  if (_material_type == "316SS")
  {
     _density[_qp] = 7990; //in kg/m^3
     _specific_heat_capacity[_qp] = 0.12666667 * _temperature[_qp] + 475.42; //in J/kgK
     _thermal_conductivity[_qp] = 21.4; // at 773 K //in W/mK
  }
  else if (_material_type == "304SS")
  {
     _density[_qp] = 8000; //in kg/m^3
     _specific_heat_capacity[_qp] = 0.1333333333 * _temperature[_qp] + 433.6; //in J/kgK
     _thermal_conductivity[_qp] = 21.5; // at 773 K //in W/mK
  }
  else if (_material_type == "308LSS")
  {
     _density[_qp] = 0.0011 * _temperature[_qp] + 7.0697 * 1000; //in kg/m^3
     _specific_heat_capacity[_qp] = 477; //in J/kgK
     _thermal_conductivity[_qp] = 0.06 * _temperature[_qp] - 9.38; //in W/mK
  }
  else if (_material_type == "347SS")
  {
     _density[_qp] = 8000; //in kg/m^3
     _specific_heat_capacity[_qp] = 500; //in J/kgK
     _thermal_conductivity[_qp] = 21.5; //at 773 K //in W/mK
  }
  else if (_material_type == "LAS")
  {
     _density[_qp] = 7720; // at 673 K //in kg/m^3
     _specific_heat_capacity[_qp] = 0.5 * _temperature[_qp] + 288.5; //in J/kgK
     _thermal_conductivity[_qp] = 25.5; // at 773 K //in W/mK
  }
  else if (_material_type == "CS")
  {
     _density[_qp] = 7850; //in kg/m^3
     _specific_heat_capacity[_qp] = 0.5033333333 * _temperature[_qp] + 285.59; //in J/kgK
     _thermal_conductivity[_qp] = -0.011 * _temperature[_qp] + 53.503; //in W/mK
  }
  else if (_material_type == "Stellite")
  {
     _density[_qp] = 7990; //in kg/m^3
     _specific_heat_capacity[_qp] = 548; //in J/kgK
     _thermal_conductivity[_qp] = 21.4; //in W/mK
  }
  else if (_material_type == "CuNi9010")
  {
     _density[_qp] = 8900; //in kg/m^3
     _specific_heat_capacity[_qp] = 377; //in J/kgK
     _thermal_conductivity[_qp] = 50; // at 573 K //in W/mK
  }
  else if (_material_type == "Titanium")
  {
     _density[_qp] = 4510; //in kg/m^3
     _specific_heat_capacity[_qp] = 670; //at 813 K //in J/kgK
     _thermal_conductivity[_qp] = 0.0013333333 * _temperature[_qp] + 18.636; //in W/mK
  }
  else if (_material_type == "Inconel")
  {
     _density[_qp] = 8470; //in kg/m^3
     _specific_heat_capacity[_qp] = 444; //in J/kgK
     _thermal_conductivity[_qp] = 0.0163333333 * _temperature[_qp] + 9.641; //in W/mK
  }
  else if (_material_type == "Incoloy")
  {
     _density[_qp] = 7940; //in kg/m^3
     _specific_heat_capacity[_qp] = 460; //between 273-373 K //in J/kgK
     _thermal_conductivity[_qp] = 0.016 * _temperature[_qp] + 7.132; //in W/mK
  }
  else if (_material_type == "Hastelloy")
  {
     _density[_qp] = 8220; //in kg/m^3
     _specific_heat_capacity[_qp] = 0.28 * _temperature[_qp] + 337.56; //in J/kgK
     _thermal_conductivity[_qp] = 0.0223333333 * _temperature[_qp] + 1.303; //in W/mK
  }
  else if (_material_type == "SA230")
  {
     _density[_qp] = 8970; //at 298 K //in kg/m^3
     _specific_heat_capacity[_qp] = 397; //at 298 K //in J/kgK
     _thermal_conductivity[_qp] = 8.97; //at 298 K //in W/mK
  }
  else if (_material_type == "Graphite")
  {
     _density[_qp] = 1760; //in kg/m^3
     _specific_heat_capacity[_qp] = 2.1493333333 * _temperature[_qp] - 494.368; //in J/kgK
     _thermal_conductivity[_qp] = 81.4; // at 673 K //in W/mK
  }
  else if (_material_type == "T91")
  {
     _density[_qp] = -0.0003 * _temperature[_qp] + 7.8119 * 1000; //in kg/m^3
     _specific_heat_capacity[_qp] = 0.6073333333 * _temperature[_qp] + 212.298; //in J/kgK
     _thermal_conductivity[_qp] = -0.0009966777 * _temperature[_qp] + 29.4110963455; //in W/mK
  }
  else if (_material_type == "PE16")
  {
     _density[_qp] = 8000; //in kg/m^3
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C //in J/kgK
     _thermal_conductivity[_qp] = 2.3788666667 * _temperature[_qp] - 1334.2506; //in W/mK
  }
  else if (_material_type == "W")
  {
     _density[_qp] = 19300; //in kg/m^3
     _specific_heat_capacity[_qp] = 134; //in J/kgK
     _thermal_conductivity[_qp] = 128; ///at 600 deg C //in W/mK
  }
  else if (_material_type == "Cu")
  {
     _density[_qp] = 8950; //in kg/m^3
     //_specific_heat_capacity[_qp] = 544; //between 20-400 deg C //in J/kgK
     _thermal_conductivity[_qp] = 391; //in W/mK
  }
  else if (_material_type == "Na")
  {
     _density[_qp] = 845; //in kg/m^3
     _specific_heat_capacity[_qp] = 1269; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] = 68.88; //at 723 K //in W/mK
     _boiling_point[_qp] = 1156; // in K
     _melting_point[_qp] = 371; //in K
     _dynamic_viscosity[_qp] = 0.0003; //at 723 K //in mPa-s
     _surface_tension[_qp] = 163; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 3871; //in kJ/kg
  }
  else if (_material_type == "Pb")
  {
     _density[_qp] = 10520; //at 723 K //in kg/m^3
     _specific_heat_capacity[_qp] = 147300; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] =17.1; //at 723 K //in W/mK
     _boiling_point[_qp] = 1745; // in K
     _melting_point[_qp] = 327.4; //in K
     _dynamic_viscosity[_qp] = 0.00019; //at 723 K //in mPa-s
     _surface_tension[_qp] = 480; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 856.8; //in kJ/kg
  }
else if (_material_type == "KNO3")
  {
     _density[_qp] = 2105; //in kg/m^3
     _specific_heat_capacity[_qp] = 1328.9; //in J/kgK
     _thermal_conductivity[_qp] = 0.376; //at 447 deg C //in W/mK
     _boiling_point[_qp] = 400; // in deg C
     _melting_point[_qp] = 334;  //in deg C
     _dynamic_viscosity[_qp] = 0.0014596; //at 492 deg C //in mPa-s
     _surface_tension[_qp] = 111; //between 340-550 deg C //in mN/m
     _latent_heat_of_vapourisation[_qp] = 50.6; //in kJ/kg
  }
else if (_material_type == "Bi")
  {
     _density[_qp] = 9850; //at 723 K//in kg/m^3
     _specific_heat_capacity[_qp] = 150000; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] = 14.2; //at 723 K //in W/mK
     _boiling_point[_qp] = 1552; // in K
     _melting_point[_qp] = 271.4; //in K
     _dynamic_viscosity[_qp] = 0.00013; //at 723 K //in mPa-s
     _surface_tension[_qp] = 370; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 852; //in kJ/kg
  }
else if (_material_type == "Pb-Bi")
  {
     _density[_qp] = 10150; //at 723 K //in kg/m^3
     _specific_heat_capacity[_qp] = 146000; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] = 14.2; //at 723 K //in W/mK
     _boiling_point[_qp] = 1670; // in K
     _melting_point[_qp] = 125;//in K
     _dynamic_viscosity[_qp] = 0.00014; //at 723 K //in mPa-s
     _surface_tension[_qp] = 392; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 852; //in kJ/kg
  }
else if (_material_type == "Hg")
  {
     _density[_qp] = 13530; //in kg/m^3
     _specific_heat_capacity[_qp] = 135.25; //in J/kgK
     _thermal_conductivity[_qp] = 10.05; //at 673 K //in W/mK
     _boiling_point[_qp] = 629.62; // in K
     _melting_point[_qp] = 507.17;//in K
     _dynamic_viscosity[_qp] = 0.00085; //at 723 K //in mPa-s
     _surface_tension[_qp] = 424.8; //at 523 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 58.2; //literature value give up to 59.2, lower value is taken //in kJ/kg
  }
else if (_material_type == "Glycerine")
  {
     _density[_qp] = 1060; //in kg/m^3
     _specific_heat_capacity[_qp] = 2407.4; //at 553 K- literatue values give up to 2426.3, lower value is taken //in J/kgK
     _thermal_conductivity[_qp] = 0.285; //at 353 K //in W/mK
     _boiling_point[_qp] = 563; // in K
     _melting_point[_qp] = 291.2; //in K
     _dynamic_viscosity[_qp] = 0.0148; //at 373 k //in mPa-s
     _surface_tension[_qp] = 634; //in mN/m
     _latent_heat_of_vapourisation[_qp] = 652.59;//in kJ/kg

  }
else if (_material_type == "KCSN")
  {
     _density[_qp] = 1880; //in kg/m^3
     _specific_heat_capacity[_qp] = 910; //at 298.15 K //in J/kgK
     _thermal_conductivity[_qp] = 1; // no value found in literature for KCSN //in W/mK
     _boiling_point[_qp] = 773 ; // in K
     _melting_point[_qp] = 446; //in K
     _dynamic_viscosity[_qp] = 0.0118; //at 723 K //in mPa-s
     _surface_tension[_qp] = 91.87; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 6.07;//in kJ/kg
  }
else if (_material_type == "Rb")
  {
     _density[_qp] = 1530; //in kg/m^3
     _specific_heat_capacity[_qp] = 363; ///in J/kgK
     _thermal_conductivity[_qp] = 58.2; //in W/mK
     _boiling_point[_qp] = 815; // in K
     _melting_point[_qp] = 312.3;//in deg C
     _dynamic_viscosity[_qp] = 0.000143; //at 815 K //in mPa-s
     _surface_tension[_qp] = 51; //at 823 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 887.46;//in kJ/kg
  }
else if (_material_type == "Cs")
  {
     _density[_qp] = 1873; //in kg/m^
     _specific_heat_capacity[_qp] = 237.78; //at 571 K and above //in J/kgK
     _thermal_conductivity[_qp] = 21.53; //at 773 K //in W/mK
     _boiling_point[_qp] = 944; // in K
     _melting_point[_qp] = 301.5; //in K
     _dynamic_viscosity[_qp] = 0.00028; //at 773 K //in mPa-s
     _surface_tension[_qp] = 50.98; //at 811 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 494.321; //at 944 K //in kJ/kg
  }

}
