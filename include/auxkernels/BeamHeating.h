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

#ifndef BEAMHEATING_H
#define BEAMHEATING_H

#include "AuxKernel.h"


//Forward Declarations
class BeamHeating;

template<>
InputParameters validParams<BeamHeating>();

/**
 * Coupled auxiliary value
 */
class BeamHeating : public AuxKernel
{
public:

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  BeamHeating(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

  VariableValue & _ionic_heating;
  Real _beam_current;

};

#endif //BEAMHEATING_H
