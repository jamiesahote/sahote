[Mesh]
## Put your Cubit mesh here
[]

[Variables]
  [./Temperature]
    order = FIRST
    family = LAGRANGE
    initial_condition = 300
  [../]
[]

[AuxVariables]
  [./HeatGeneration]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
[]

[Functions]
  [./HeatGenerationFunction]
    type = PiecewiseLinear
    data_file = ___             ## Put the SRIM energy deposition file here
    format = columns
    axis = 0
  [../]
[]

[Kernels]
  [./HeatConduction-Structure]
    type = MatPropDiffusion
    variable = Temperature
    block = 'Top_Structure Bottom_Structure'
    diffusivity = ThermalConductivity-304SS
  [../]

  [./HeatConduction-Coolant]
    type = MatPropDiffusion
    variable = Temperature
    block = 'Coolant'
    diffusivity = ThermalConductivity-KNO3
  [../]

  [./HeatConduction-Pincers]
    type = MatPropDiffusion
    variable = Temperature
    block = 'Pincers'
    diffusivity = ThermalConductivity-316SS
  [../]

  [./HeatConduction-Sample]
    type = MatPropDiffusion
    variable = Temperature
    block = 'Sample'
    diffusivity = ThermalConductivity-W
  [../]

  [./RadiationHeatSource]
    type = RadiationHeatSource
    variable = Temperature
    PrimarySource = HeatGeneration
  [../]
[]

[AuxKernels]
  [./HeatGenerationRate]
    type = FunctionAux
    variable = HeatGeneration
    function = HeatGenerationFunction
  [../]
[]

[Materials]	## You'll have to write a SahoteMaterial class, copy from mine to start
  [./SahoteMaterial]
    type = SahoteMaterial
  [../]
[]

[BCs]		## You'll have to change these to match your problem
  [./V-Surface]
    type = DirichletBC
    variable = Vacancies
    boundary = 'left'
    value = 0
  [../]

  [./I-Surface]
    type = DirichletBC
    variable = Interstitials
    boundary = 'left'
    value = 0
  [../]

  [./V-right]
    type = DirichletBC
    variable = Vacancies
    boundary = 'right'
    value = 0
  [../]

  [./I-right]
    type = DirichletBC
    variable = Interstitials
    boundary = 'right'
    value = 0
  [../]

  [./Void-right]
    type = DirichletBC
    variable = Voids
    boundary = 'right'
    value = 0
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady

  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'

  l_max_its = 100
  l_tol = 1e-5
  nl_rel_step_tol = 1e-50
  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-11

#  [./Adaptivity]
#    steps = 1
#    refine_fraction = 0.4
#    coarsen_fraction = 0.02
#    max_h_level = 3
#    error_estimator = KellyErrorEstimator
#  [../]

[]

[Outputs]
  file_base = Sahote
  exodus = true
  perf_log = true
  all_var_norms = true
[]


