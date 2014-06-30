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

// This file computes the true porosity of the CRUD, by starting
// with the skeletal porosity handed down from MAMBA-MACRO. This
// skeletal porosity is the porosity of the insoluble skeleton of
// iron and nickel oxides.
//
// The porosity then decreases to a smaller value once soluble
// species (such as HBO2) fill up the pores.

#include "BeamHeating.h"

template<>
InputParameters validParams<BeamHeating>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("ionic_heating", "The local concentration of metaboric acid for porosity calculation");
  params.addParam<Real>("beam_current", 1e-6, "Ion beam current in Amps");
  return params;
}

BeamHeating::BeamHeating(const std::string & name, InputParameters parameters)
  :AuxKernel(name, parameters),
   _ionic_heating(coupledValue("ionic_heating")),
   _beam_current(getParam<Real>("beam_current"))

{}

Real
BeamHeating::computeValue()
{

// Take the heating per ion, multiply by beam current, which is _beam_current divided by the charge of an electron

    return _ionic_heating[_qp] * _beam_current / 1.6e-19;

}
