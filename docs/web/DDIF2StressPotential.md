% The `DDIF2` stress potential
% Bruno Michel, Thomas Helfer
% 12/2017

This page describes the `DDIF2` stress potential.

The `DDIF2` behaviour is used to describe the brittle nature of
nuclear fuel ceramics and is usually coupled with a description of the
viscoplasticity of those ceramics (See for example
[@monerie_overall_2006,@salvo_experimental_2015;@salvo_experimental_2015-1]).

Internally the `DDIF2` stress potential is derived from the `Hooke`
stress potential, so the definition of the elastic properties follows
the same rules.

# Local coordinate

This description is currently limited to initially isotropic
behaviours, but the damage is described in three orthogonal
directions. Those directions are currently fixed with respect to the
global system. For \(2D\) and \(3D\) modelling hypotheses, those
directions are determined by a material property, which external name
is `AngularCoordinate`, giving the angular coordinate in a cylindrical
system.

# Material properties associated with damage

The description of damage is based on the following material
properties:

- the fracture stresses in each direction. Two options can be used to
  described them:
    - if the `fracture_stress` option is used, the fracture stresses
	  are equal in each directions.
	- otherwise, the `fracture_stresses` keyword can be used to
      describe the fracture stresses in each of the three directions.
- the softening slopes stresses in each direction. Two options can be
  used to described them:
    - if the `softening_slope` option is used, the softening slopes
	  are equal in each directions.
	- otherwise, the `softening_slopes` keyword can be used to
      describe the softening slopes in each of the three directions.

In each case, a material property must be given as a value or as an
external `MFront` file.

## Fracture energies

Following Hillerborg approach (see @hillerborg_analysis_1976),
softening slopes can be related to fracture energies by the mesh
size. Thus, rather than the softening slopes, the user can provide the
fracture energies through one the `fracture_energy` or
`fracture_energies` options. In this case, an array of three material
properties, which external name is `ElementSize`, is automatically
declared.

# External pressure effect

The effect of external pressure on the crack surface can be taken into
account using the option `handle_pressure_on_crack_surface`. If this
option is true, an external state variable called `pr`, which external
name is `PressureOnCrackSurface`, is automatically declared.

# References
