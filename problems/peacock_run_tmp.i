[Mesh]
  type = FileMesh
  file = Structure.e
[]

[Variables]
  [./Temperature]
    order = FIRST
    family = LAGRANGE
    initial_condition = 298
  [../]
[]

[AuxVariables]
  [./HeatGenerationPerIon]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 456
  [../]
  [./HeatGeneration]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 456
  [../]
[]

[Functions]
  # [./HeatGenerationFunction]
  # type = ConstantFunction
  # value = 5
  # [../]
  [./HeatGenerationFunction]
    type = PiecewiseMultilinear
    data_file = IonBeamEnergy.txt
  [../]
[]

[Kernels]
  [./HeatConduction-Structure]
    type = MatPropDiffusion
    variable = Temperature
    block = 'Top_Structure Bottom_Structure'
    diffusivity = ThermalConductivity
  [../]
  [./HeatConduction-Coolant]
    type = MatPropDiffusion
    variable = Temperature
    block = Coolant
    diffusivity = ThermalConductivity
  [../]
  [./HeatConduction-Pincers]
    type = MatPropDiffusion
    variable = Temperature
    block = Pincers
    diffusivity = ThermalConductivity
  [../]
  [./HeatConduction-Sample]
    type = MatPropDiffusion
    variable = Temperature
    block = Sample
    diffusivity = ThermalConductivity
  [../]
  [./RadiationHeatSource]
    type = RadiationHeatSource
    variable = Temperature
    PrimarySource = HeatGeneration
  [../]
[]

[AuxKernels]
  [./IonicHeatGenerationRate]
    type = FunctionAux
    variable = HeatGenerationPerIon
    function = HeatGenerationFunction
  [../]
  [./HeatGenerationRate]
    type = BeamHeating
    variable = HeatGeneration
    ionic_heating = HeatGenerationPerIon
    beam_current = 2e-4 # Specify your total beam current in Amps
    beam_radius = 0.003 # Specify your beam radius in metres
  [../]
[]

[Materials]
  [./TopStructure]
    type = SahoteMaterial
    block = 2
    temperature = Temperature
    material_type = 316SS
  [../]
  [./Coolant]
    type = SahoteMaterial
    block = 1
    temperature = Temperature
    material_type = KNO3
  [../]
  [./Pincers]
    type = SahoteMaterial
    block = 4
    temperature = Temperature
    material_type = 316SS
  [../]
  [./Sample]
    type = SahoteMaterial
    block = 5
    temperature = Temperature
    material_type = 304SS
  [../]
  [./BottomStructure]
    type = SahoteMaterial
    block = 3
    temperature = Temperature
    material_type = 316SS
  [../]
[]

[BCs]
  [./StructureAir]
    type = CRUDCoolantNeumannBC
    variable = Temperature
    boundary = Structure-Air
    T_coolant = 300
    h_convection_coolant = 50
  [../]
  [./StructureCoolant]
    type = CRUDCoolantNeumannBC
    variable = Temperature
    boundary = Structure-Coolant
    T_coolant = 600
    h_convection_coolant = 12000
  [../]
  [./CoolantSample]
    type = CRUDCoolantNeumannBC
    variable = Temperature
    boundary = Coolant-Pincer
    T_coolant = 600
    h_convection_coolant = 12000
  [../]
  [./CoolantPincer]
    type = CRUDCoolantNeumannBC
    variable = Temperature
    boundary = Coolant-Sample
    T_coolant = 600
    h_convection_coolant = 12000
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  # [./Adaptivity]
  # steps = 1
  # refine_fraction = 0.4
  # coarsen_fraction = 0.02
  # max_h_level = 3
  # error_estimator = KellyErrorEstimator
  # [../]
  type = Steady
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  l_max_its = 3
  l_tol = 1e-3
  nl_rel_step_tol = 1e-50
  nl_rel_tol = 1e-2
  nl_abs_tol = 1e1
[]

[Outputs]
  file_base = Sahote
  exodus = true
  print_linear_residuals = true
  print_perf_log = true
  [./Console]
    type = Console
    all_variable_norms = true
  [../]
[]

