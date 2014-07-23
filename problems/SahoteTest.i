[Mesh]
  type = FileMesh
  file = Structure.e
[]

[Variables]
  [./Temperature]
    order = FIRST
    family = LAGRANGE
    initial_condition = 700
  [../]
[]

[AuxVariables]
  [./HeatGenerationPerIon]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0
  [../]
  [./HeatGeneration]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0
  [../]
##  [./Pressure]
##    order = FIRST
##    family = LAGRANGE
##      initial_condition = 100000
  [../]
[]

[Functions]
  [./HeatGenerationFunction]
    type = PiecewiseMultilinear
    data_file = IonBeamEnergy.txt
  [../]
##  [./PressureFunction]
##    type = ParsedFunction
##    value = -467.0720000001 * p + 100000
##    vars = p
##  [../]
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
  [./Convection-Coolant]
    type = Convection
    variable = Temperature
    block = Coolant
    some_variable = Pressure
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
    beam_current = 2e-6 # Specify your total beam current in Amps
    beam_radius = 0.003 # Specify your beam radius in metres
  [../]
##  [./PressureAux]
##    type = FunctionAux
##    variable = Pressure
##    function = PressureFunction
##  [../]
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
    velocity = 1
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
    h_convection_coolant = 100
  [../]
  [./CoolantSample]
    type = CRUDCoolantNeumannBC
    variable = Temperature
    boundary = Coolant-Pincer
    T_coolant = 700
    h_convection_coolant = 100
  [../]
  [./CoolantPincer]
    type = CRUDCoolantNeumannBC
    variable = Temperature
    boundary = Coolant-Sample
    T_coolant = 700
    h_convection_coolant = 100
  [../]
  [./CoolantEntry]
    type = DirichletBC
    variable = Temperature
    boundary = Coolant-Entry
    value = 650
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
  l_max_its = 10
  l_tol = 1e-2
  nl_rel_step_tol = 1e-50
  nl_rel_tol = 1e-3
[]

[Outputs]
  file_base = Sahote
  exodus = true
  [./Console]
    type = Console
    linear_residuals = true
    all_variable_norms = true
    perf_log = true
  [../]
[]

