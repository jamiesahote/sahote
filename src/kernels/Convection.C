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

#include "Convection.h"

template<>
InputParameters validParams<Convection>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("pressure", "The velocity of the coolant in metres per second.");
  return params;
}

Convection::Convection(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    _velocity(coupledGradient("pressure")),
    _density(getMaterialProperty<Real>("Density")),
    _specific_heat_capacity(getMaterialProperty<Real>("SpecificHeatCapacity"))

{}

Real
Convection::computeQpResidual()
{
_velocity[_qp] = 1e10;

  return -_test[_i][_qp]
    * _density[_qp]
    * _specific_heat_capacity[_qp]
    * _velocity[_qp]
    * _grad_u[_qp];
}

Real
Convection::computeQpJacobian()
{
_velocity[_qp] = 1e10;

  return -_test[_i][_qp]
    * _density[_qp]
    * _specific_heat_capacity[_qp]
    * _velocity[_qp]
    * _grad_phi[_j][_qp];
}
