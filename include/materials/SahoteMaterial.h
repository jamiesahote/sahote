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

#ifndef SAHOTEMATERIAL_H
#define SAHOTEMATERIAL_H

#include "Material.h"

//Forward Declarations
class SahoteMaterial;

template<>
InputParameters validParams<SahoteMaterial>();

class SahoteMaterial : public Material
{
public:
  SahoteMaterial(const std::string & name,
                  InputParameters parameters);

protected:
//  virtual void initQpStatefulProperties();
  virtual void computeQpProperties();

private:

  /**
   * These variables will hold key values from the
   * input file for material property calculation.
   */

// Simple parameters to be used all over
  VariableValue & _temperature;

  

  /**
   * This is the member reference that will hold the
   * computed values from this material class.
   */

  // Parameters specifying material properties used for both structural/sample materials and cooling fluids
  MaterialProperty<Real> & _density;
  //MaterialProperty<Real> & _elemental composition;
  MaterialProperty<Real> & _specific_heat_capacity;
  MaterialProperty<Real> &  _thermal_conductivity;

  // Parameters used for structural/sample material only
  //MaterialProperty<Real> & _grain_size;

  // Paramaters used for cooling fluids only
  MaterialProperty<Real> & _boiling_point;
  MaterialProperty<Real> & _melting_point;
  MaterialProperty<Real> & _dynamic_viscosity;
  MaterialProperty<Real> & _surface_tension;
  MaterialProperty<Real> & _latent_heat_of_vapourisation;

  MooseEnum _material_type;


  // Coupled variables used in calculation (TBD)
//  VariableValue & _T;

};

#endif //SAHOTEMATERIAL_H

