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
     _velocity(coupledGradient("velocity")),
     _material_type(getParam<MooseEnum>("material_type"))


{}

Real
MaterialHeatAux::computeValue()
{
    double value = 3000;  
    _velocity[_qp] /= 1000 * -1;	// This is us faking out the velocity divided by 1000, because the "pressure" kernel needs something to do & to turn the negative velocity into a positive number???
 

  if (_material_type == "Na")
  {
     
     value = -179.2415573376 * _velocity[_qp](1) * _velocity[_qp](1) + 10238.2369628439 * _velocity[_qp](1) + 4623.4340907715;
  }

else if (_material_type == "Pb")
  {
     
     value = -3155.6326588782 * _velocity[_qp](1) * _velocity[_qp](1) + 180249.019307632 * _velocity[_qp](1) + 81397.7507767655;
  }
else if (_material_type == "KNO3")
  {
     
     value = -5.4753744652 * _velocity[_qp](1) * _velocity[_qp](1) + 312.752143351 * _velocity[_qp](1) + 141.2341721312; 
  }
else if (_material_type == "Bi")
  {
     
     value = -3531.0771718966 * _velocity[_qp](1) * _velocity[_qp](1) + 184583.966088206 * _velocity[_qp](1) + 77330.8543044832;
  }
else if (_material_type == "Pb-Bi")
  {
     
     value = -3116.2768429171 * _velocity[_qp](1) * _velocity[_qp](1) + 178001.024056639 * _velocity[_qp](1) + 80382.5898738632;
  }
else if (_material_type == "Hg")
  {
     
     value = -132.987752409 * _velocity[_qp](1) * _velocity[_qp](1) + 7596.2301518863 * _velocity[_qp](1) + 2986.2874516524;
  }
else if (_material_type == "Glycerine")
  {
     
     value = 1891.9582696973;

  }
else if (_material_type == "KCSN")
  {
     
     value = 1;
  }
else if (_material_type == "Rb")
  {
     
     value = -241.482984839 * _velocity[_qp](1) * _velocity[_qp](1) + 13793.4531366455 * _velocity[_qp](1) + 6228.9163351921;
  }
else if (_material_type == "Cs")
  {
     
     value = -92.4734468751 * _velocity[_qp](1) * _velocity[_qp](1) + 5282.0622401449 * _velocity[_qp](1) + 2285.3000003117;
  } 
 
else 
  {
     value=1;
  }
    return value;

}
