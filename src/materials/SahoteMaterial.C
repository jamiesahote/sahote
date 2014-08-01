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
  //params.addRequiredParam<Real>("velocity", "the velocity of the coolant");
  MooseEnum material_type("316SS, 304SS, 308LSS, 347SS, LAS, CS, Stellite, CuNi9010, Titanium, Inconel, Incoloy, Hastelloy, SA230, Graphite, T91, PE16, Na, Pb, Pb-Bi, KNO3, KCSN, Hg, Rb, Cs, Glycerine,");
  params.addParam<MooseEnum>("material_type",material_type,"This string specifies the material to return properties."); 

  // Many material properties scale with temperature (to be implemented later)
//  params.addRequiredCoupledVar("temperature", "Temperature of the CRUD for viscosity calculation (water temperature)");

  return params;
}

SahoteMaterial::SahoteMaterial(const std::string & name,
                           InputParameters parameters)
    :Material(name, parameters),

     // Get simple parameters from the input fil
     _temperature(coupledValue("temperature")),
     //_velocity(getParam<Real>("velocity")),
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
     //_heat_transfer_coefficient(declareProperty<Real>("HeatTransferCoefficient")),
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
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "304SS")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.1333333333 * _temperature[_qp] + 433.6; //in J/kgK
     _thermal_conductivity[_qp] = 21.5; // at 773 K //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "308LSS")
  {
     _density[_qp] = 0.0011 * _temperature[_qp] + 7.0697; //in g/cm^2
     _specific_heat_capacity[_qp] = 477; //in J/kgK
     _thermal_conductivity[_qp] = 0.06 * _temperature[_qp] - 9.38; //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "347SS")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 500; //in J/kgK
     _thermal_conductivity[_qp] = 21.5; //at 773 K //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "LAS")
  {
     _density[_qp] = 7.72; // at 673 K //in g/cm^2
     _specific_heat_capacity[_qp] = 0.5 * _temperature[_qp] + 288.5; //in J/kgK
     _thermal_conductivity[_qp] = 25.5; // at 773 K //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "CS")
  {
     _density[_qp] = 7.85; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.5033333333 * _temperature[_qp] + 285.59; //in J/kgK
     _thermal_conductivity[_qp] = -0.011 * _temperature[_qp] + 53.503; //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "Stellite")
  {
     _density[_qp] = 7.99; //in g/cm^2
     _specific_heat_capacity[_qp] = 548; //in J/kgK
     _thermal_conductivity[_qp] = 21.4; //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "CuNi9010")
  {
     _density[_qp] = 8.9; //in g/cm^2
     _specific_heat_capacity[_qp] = 377; //in J/kgK
     _thermal_conductivity[_qp] = 50; // at 573 K //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "Titanium")
  {
     _density[_qp] = 4.51; //in g/cm^2
     _specific_heat_capacity[_qp] = 670; //at 813 K //in J/kgK
     _thermal_conductivity[_qp] = 0.0013333333 * _temperature[_qp] + 18.636; //in W/mK
    // _heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "Inconel")
  {
     _density[_qp] = 8.47; //in g/cm^2
     _specific_heat_capacity[_qp] = 444; //in J/kgK
     _thermal_conductivity[_qp] = 0.0163333333 * _temperature[_qp] + 9.641; //in W/mK
    // _heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "Incoloy")
  {
     _density[_qp] = 7.94; //in g/cm^2
     _specific_heat_capacity[_qp] = 460; //between 273-373 K //in J/kgK
     _thermal_conductivity[_qp] = 0.016 * _temperature[_qp] + 7.132; //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "Hastelloy")
  {
     _density[_qp] = 8.22; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.28 * _temperature[_qp] + 337.56; //in J/kgK
     _thermal_conductivity[_qp] = 0.0223333333 * _temperature[_qp] + 1.303; //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "SA230")
  {
     _density[_qp] = 8.97; //at 298 K //in g/cm^2
     _specific_heat_capacity[_qp] = 397; //at 298 K //in J/kgK
     _thermal_conductivity[_qp] = 8.97; //at 298 K //in W/mK
    // _heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "Graphite")
  {
     _density[_qp] = 1.76; //in g/cm^2
     _specific_heat_capacity[_qp] = 2.1493333333 * _temperature[_qp] - 494.368; //in J/kgK
     _thermal_conductivity[_qp] = 81.4; // at 673 K //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "T91")
  {
     _density[_qp] = -0.0003 * _temperature[_qp] + 7.8119; //in g/cm^2
     _specific_heat_capacity[_qp] = 0.6073333333 * _temperature[_qp] + 212.298; //in J/kgK
     _thermal_conductivity[_qp] = -0.0009966777 * _temperature[_qp] + 29.4110963455; //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "PE16")
  {
     _density[_qp] = 8.0; //in g/cm^2
     _specific_heat_capacity[_qp] = 544; //between 20-400 deg C HOW?? //in J/kgK
     _thermal_conductivity[_qp] = 2.3788666667 * _temperature[_qp] - 1334.2506; //in W/mK
     //_heat_transfer_coefficient[_qp] = 0;
  }
  else if (_material_type == "Na")
  {
     _density[_qp] = 0.845; //in g/cm^2
     _specific_heat_capacity[_qp] = 1269; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] = 68.88; //at 723 K //in W/mK
     _boiling_point[_qp] = 1156; // in K
     _melting_point[_qp] = 371; //in K
     _dynamic_viscosity[_qp] = 0.3; //at 723 K //in mPa-s
     _surface_tension[_qp] = 163; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 3871; //in kJ/kg
     //_heat_transfer_coefficient[_qp] = -156.0388387064 * _velocity * _velocity + 8912.90292955163 * _velocity + 4024.9331520837;
  }
  else if (_material_type == "Pb")
  {
     _density[_qp] = 10.52; //at 723 K //in g/cm^2
     _specific_heat_capacity[_qp] = 147300; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] =17.1; //at 723 K //in W/mK
     _boiling_point[_qp] = 1745; // in K
     _melting_point[_qp] = 327.4; //in K
     _dynamic_viscosity[_qp] = 0.19; //at 723 K //in mPa-s
     _surface_tension[_qp] = 480; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 856.8; //in kJ/kg
     //_heat_transfer_coefficient[_qp] = -2747.1377887 * _velocity * _velocity + 156915.885291833 * _velocity + 122.9514881055;
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
     //_heat_transfer_coefficient[_qp] = -4.7665903249 * _velocity * _velocity + 272.2665545663 * _velocity + 122.9514881055; 
  }
else if (_material_type == "Bi")
  {
     _density[_qp] = 9.85; //at 723 K//in g/cm^2
     _specific_heat_capacity[_qp] = 150000; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] = 14.2; //at 723 K //in W/mK
     _boiling_point[_qp] = 1552; // in K
     _melting_point[_qp] = 271.4; //in K
     _dynamic_viscosity[_qp] = 0.13; //at 723 K //in mPa-s
     _surface_tension[_qp] = 370; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 852; //in kJ/kg
     //_heat_transfer_coefficient[_qp] = -3073.9812210367 * _velocity * _velocity + 160689.67565352 * _velocity + 67320.4187749379;
  }
else if (_material_type == "Pb-Bi")
  {
     _density[_qp] = 10.15; //at 723 K //in g/cm^2
     _specific_heat_capacity[_qp] = 146000; //at 723 K //in J/kgK
     _thermal_conductivity[_qp] = 14.2; //at 723 K //in W/mK
     _boiling_point[_qp] = 1670; // in K
     _melting_point[_qp] = 125;//in K
     _dynamic_viscosity[_qp] = 0.14; //at 723 K //in mPa-s
     _surface_tension[_qp] = 392; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 852; //in kJ/kg
     //_heat_transfer_coefficient[_qp] = -2712.8765609881 * _velocity * _velocity + 154958.891759794 * _velocity + 69977.1088938927;
  }
else if (_material_type == "Hg")
  {
     _density[_qp] = 13.53; //in g/cm^2
     _specific_heat_capacity[_qp] = 135.25; //in J/kgK
     _thermal_conductivity[_qp] = 10.05; //at 673 K //in W/mK
     _boiling_point[_qp] = 629.62; // in K
     _melting_point[_qp] = 507.17;//in K
     _dynamic_viscosity[_qp] = 0.85; //at 723 K //in mPa-s
     _surface_tension[_qp] = 424.8; //at 523 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 58.2; //literature value give up to 59.2, lower value is taken //in kJ/kg
     //_heat_transfer_coefficient[_qp] = -115.7725627711 * _velocity * _velocity + 6612.9024376516 * _velocity + 2986.2874516524;
  }
else if (_material_type == "Glycerine")
  {
     _density[_qp] = 1.060; //in g/cm^2
     _specific_heat_capacity[_qp] = 2407.4; //at 553 K- literatue values give up to 2426.3, lower value is taken //in J/kgK
     _thermal_conductivity[_qp] = 0.285; //at 353 K //in W/mK
     _boiling_point[_qp] = 563; // in K
     _melting_point[_qp] = 291.2; //in K
     _dynamic_viscosity[_qp] = 14.8; //at 373 k //in mPa-s
     _surface_tension[_qp] = 634; //in mN/m
     _latent_heat_of_vapourisation[_qp] = 652.59;//in kJ/kg
    // _heat_transfer_coefficient[_qp] = 2123.6513547203;

  }
else if (_material_type == "KCSN")
  {
     _density[_qp] = 1.88; //in g/cm^2
     _specific_heat_capacity[_qp] = 910; //at 298.15 K //in J/kgK
     _thermal_conductivity[_qp] = 1; // no value found in literature for KCSN //in W/mK
     _boiling_point[_qp] = 773 ; // in K
     _melting_point[_qp] = 446; //in K
     _dynamic_viscosity[_qp] = 11.8; //at 723 K //in mPa-s
     _surface_tension[_qp] = 91.87; //at 723 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 6.07;//in kJ/kg
    // _heat_transfer_coefficient[_qp] = 1;
  }
else if (_material_type == "Rb")
  {
     _density[_qp] = 1.53; //in g/cm^2
     _specific_heat_capacity[_qp] = 363; ///in J/kgK
     _thermal_conductivity[_qp] = 58.2; //in W/mK
     _boiling_point[_qp] = 815; // in K
     _melting_point[_qp] = 312.3;//in deg C
     _dynamic_viscosity[_qp] = 0.143; //at 815 K //in mPa-s
     _surface_tension[_qp] = 51; //at 823 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 887.46;//in kJ/kg
     //_heat_transfer_coefficient[_qp] = -210.22314878 * _velocity * _velocity + 12007.8983979054 * _velocity + 5422.586624326;
  }
else if (_material_type == "Cs")
  {
     _density[_qp] = 1.873; //in g/cm^2
     _specific_heat_capacity[_qp] = 237.78; //at 571 K and above //in J/kgK
     _thermal_conductivity[_qp] = 21.53; //at 773 K //in W/mK
     _boiling_point[_qp] = 944; // in K
     _melting_point[_qp] = 301.5; //in K
     _dynamic_viscosity[_qp] = 0.28; //at 773 K //in mPa-s
     _surface_tension[_qp] = 50.98; //at 811 K //in mN/m
     _latent_heat_of_vapourisation[_qp] = 494.321; //at 944 K //in kJ/kg
    // _heat_transfer_coefficient[_qp] = -80.502811267 * _velocity * _velocity + 4595.3022585233 * _velocity + 2076.5242589016;
  }

}
