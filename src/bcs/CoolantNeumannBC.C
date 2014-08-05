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

// 

#include "CoolantNeumannBC.h"

template<>
InputParameters validParams<CoolantNeumannBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("T_coolant", "The temperature of the bulk coolant");;
  params.addRequiredCoupledVar("heat_transfer_coefficient", "The heat transfer coefficient of the bulk coolant");

  return params;
}

CoolantNeumannBC::CoolantNeumannBC(const std::string & name, InputParameters parameters)
 :IntegratedBC(name, parameters),
  _T_coolant(coupledValue("T_coolant")),
  _heat_transfer_coefficient(coupledValue("heat_transfer_coefficient"))
  

{}

Real
CoolantNeumannBC::computeQpResidual()
{
  return _heat_transfer_coefficient[_qp] * _test[_i][_qp] * (_u[_qp] - _T_coolant[_qp]);
}
