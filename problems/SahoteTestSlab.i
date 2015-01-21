[Mesh]
  type = FileMesh
  file = SlabStructure.e
[]

[Variables]
  [./Temperature]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0
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
[]

[Functions]
  [./HeatGenerationFunction]
    type = PiecewiseMultilinear
    data_file = IonBeamEnergy40CuslabTi.txt  //for the slab
  [../]
[]

[Kernels]
  [./HeatConduction]
    type = MatPropDiffusion
    variable = Temperature
    block = 'Sample CopperSlab'
    diffusivity = ThermalConductivity
  [../]
  [./RadiationHeatSource]
    type = RadiationHeatSource
    variable = Temperature
    block = 'Sample CopperSlab'
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
    beam_current = 1e-6 # Specify your total beam current in Amps
    beam_radius = 0.003 # Specify your beam radius in metres
  [../]
[]

[Materials]
  [./Slab]
    type = SahoteMaterial
    block = 'CopperSlab'
    temperature = Temperature
    material_type = Titanium
  [../]
  [./Sample]
    type = SahoteMaterial
    block = 'Sample'
    temperature = Temperature
    material_type = Titanium
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
[]

[VectorPostprocessors]
  [./SampleTemperature]
    type = LineValueSampler
    variable = Temperature
    num_points = 25
    start_point = '0 0 0.00250000011874363'
    end_point = '0 0 -0.00200000011874363'
    sort_by = id
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
  file_base = slabTi40
  exodus = true
  csv = true
  print_linear_residuals = true
  print_perf_log = true
  [./Console]
    type = Console
    all_variable_norms = true
  [../]
[]

