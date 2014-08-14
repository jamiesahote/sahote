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


#include "VelocityAux.h"

template<>
InputParameters validParams<VelocityAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("pressure", "the pressure distribution");
  return params;
}

VelocityAux::VelocityAux(const std::string & name, InputParameters parameters)
  :AuxKernel(name, parameters),
   _grad_P(coupledGradient("pressure"))

{}

Real
VelocityAux::computeValue()
{

// Returns the gradient of the pressure field

    return (_grad_P[_qp](1));   //the minus 1 is to translate the negative gradient into a positive velocity
}
