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


#include "MaterialHeatAux.h"

template<>
InputParameters validParams<MaterialHeatAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("velocity", "the velocity of the coolant");
  MooseEnum material_type("316SS, 304SS, 308LSS, 347SS, LAS, CS, Stellite, CuNi9010, Titanium, Inconel, Incoloy, Hastelloy, SA230, Graphite, T91, PE16, Na, Pb, Pb-Bi, KNO3, KCSN, Hg, Rb, Cs, Glycerine,");
  params.addParam<MooseEnum>("material_type",material_type,"This string specifies the material to return properties.");
  return params;
}

MaterialHeatAux::MaterialHeatAux(const std::string & name, InputParameters parameters)
  :AuxKernel(name, parameters),
     _velocity(coupledValue("velocity")),
     _material_type(getParam<MooseEnum>("material_type"))


{}

Real
MaterialHeatAux::computeValue()
{
    double value = 3000;  
 

  if (_material_type == "Na")
  {
     
     value = -156.0388387064 * _velocity[_qp] * _velocity[_qp] + 8912.90292955163 * _velocity[_qp] + 4024.9331520837;
  }

else if (_material_type == "Pb")
  {
     
     value = -2747.1377887 * _velocity[_qp] * _velocity[_qp] + 156915.885291833 * _velocity[_qp] + 122.9514881055;
  }
else if (_material_type == "KNO3")
  {
     
     value = -4.7665903249 * _velocity[_qp] * _velocity[_qp] + 272.2665545663 * _velocity[_qp] + 122.9514881055; 
  }
else if (_material_type == "Bi")
  {
     
     value = -3073.9812210367 * _velocity[_qp] * _velocity[_qp] + 160689.67565352 * _velocity[_qp] + 67320.4187749379;
  }
else if (_material_type == "Pb-Bi")
  {
     
     value = -2712.8765609881 * _velocity[_qp] * _velocity[_qp] + 154958.891759794 * _velocity[_qp] + 69977.1088938927;
  }
else if (_material_type == "Hg")
  {
     
     value = -115.7725627711 * _velocity[_qp] * _velocity[_qp] + 6612.9024376516 * _velocity[_qp] + 2986.2874516524;
  }
else if (_material_type == "Glycerine")
  {
     
     value = 2123.6513547203;

  }
else if (_material_type == "KCSN")
  {
     
     value = 1;
  }
else if (_material_type == "Rb")
  {
     
     value = -210.22314878 * _velocity[_qp] * _velocity[_qp] + 12007.8983979054 * _velocity[_qp] + 5422.586624326;
  }
else if (_material_type == "Cs")
  {
     
     value = -80.502811267 * _velocity[_qp] * _velocity[_qp] + 4595.3022585233 * _velocity[_qp] + 2076.5242589016;
  } 
 
else 
  {
     value=1;
  }
    return value;

}
