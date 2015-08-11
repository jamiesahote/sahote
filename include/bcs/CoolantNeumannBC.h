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

#include "IntegratedBC.h"

#ifndef COOLANTNEUMANNBC_H
#define COOLANTNEUMANNBC_H

//Forward Declarations
class CoolantNeumannBC;

template<>
InputParameters validParams<CoolantNeumannBC>();

/**
 * Implements a simple constant Neumann BC where grad(u)=alpha * v on the boundary.
 * Uses the term produced from integrating the diffusion operator by parts.
 */
class CoolantNeumannBC : public IntegratedBC
{
public:

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  CoolantNeumannBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  
private:

  VariableValue & _T_coolant;
  VariableValue & _heat_transfer_coefficient;

};

#endif //COOLANTNEUMANNBC_H
