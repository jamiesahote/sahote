yyy/****************************************************************/
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
 

  if (_material_type == "Na")
  {
     
     value = -156.0388387064 * _velocity * _velocity + 8912.90292955163 * _velocity + 4024.9331520837;
  }
 
else 
  {
     value=1;
  }
    return value;

}
