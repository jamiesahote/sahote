[Mesh]
  type = FileMesh
  file = Structure.e
[]

[Variables]
  [./Temperature]
    order = FIRST
    family = LAGRANGE
    initial_condition = 500
  [../]
  [./convected]
    order = FIRST
    family = LAGRANGE
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
  [./HeatAux]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 1
  [../]

[]

[Functions]
  [./HeatGenerationFunction]
    type = PiecewiseMultilinear
    data_file = IonBeamEnergy.txt
  [../]
  [./VelocityFunction]
    type = ParsedFunction
    vals = 2  ## velocity of the coolant
    value = -0.0262136001 * a * a + 2.08902489084122* exp -011 * a + 100000
    vars = a
  [../]

[]

[Kernels]
  [./Velocity-Field]
    type = Diffusion
    variable = convected
  [../]

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
    velocity = 2
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
    beam_current = 1e-7 # Specify your total beam current in Amps
    beam_radius = 0.003 # Specify your beam radius in metres
  [../]
  [./HeatAux]
    type = MaterialHeatAux
    variable = HeatAux
    velocity = convected
    material_type = KNO3
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
    material_type = Titanium
  [../]
  [./BottomStructure]
    type = SahoteMaterial
    block = 3
    temperature = Temperature
    material_type = 316SS
  [../]
[]

[BCs]
  [./bottom_convected]
    type = DirichletBC
    variable = convected
    boundary = 'Coolant-Entry'
    value = 1e5		## Enter inlet pressure in Pa
  [../]
  [./top_convected]
    type = FunctionDirichletBC
    variable = convected
    boundary = 'Coolant-Exit'
    function = VelocityFunction
  [../]
  [./StructureAir]
    type = CRUDCoolantNeumannBC
    variable = Temperature
    boundary = Structure-Air
    T_coolant = 300
    h_convection_coolant = 50
  [../]
  [./StructureCoolant]
    type = CoolantNeumannBC
    variable = Temperature
    boundary = Structure-Coolant
    T_coolant = Temperature
    heat_transfer_coefficient = HeatAux
  [../]
  [./CoolantSample]
    type = CoolantNeumannBC
    variable = Temperature
    boundary = Coolant-Pincer
    T_coolant = Temperature
    heat_transfer_coefficient = HeatAux
  [../]
  [./CoolantPincer]
    type = CoolantNeumannBC
    variable = Temperature
    boundary = Coolant-Sample
    T_coolant = Temperature
    heat_transfer_coefficient = HeatAux
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
  l_max_its = 20
  l_tol = 1e-3
  nl_rel_step_tol = 1e-50
  nl_rel_tol = 1e-4
[]

[Outputs]
  file_base = 1e-
  exodus = true
  [./Console]
    type = Console
    linear_residuals = true
    all_variable_norms = true
    perf_log = true
  [../]
[]

