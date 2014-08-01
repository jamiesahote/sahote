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

#ifndef MATERIALHEATAUX_H
#define MATERIALHEATAUX_H

#include "AuxKernel.h"


//Forward Declarations
class MaterialHeatAux;

template<>
InputParameters validParams<MaterialHeatAux>();

/**
 * Coupled auxiliary value
 */
class MaterialHeatAux : public AuxKernel
{
public:

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  MaterialHeatAux(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

  Real _velocity;
  MooseEnum  _material_type;  

};

#endif //MATERIALHEATAUX_H
