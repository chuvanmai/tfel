The `@Stress` let the user specifiy the inital value of the stresses.

This keyword is followed by an array. The size of this array must be
equal to the number of components of symmetric tensors for the
modelling hypothesis considered (see the `@ModellingHypothesis`
keyword).

## Example

~~~~ {.cpp}
@Stress {'YoungModulus*EXX0',
         '-PoissonRatio*YoungModulus*EXX0',
         '-PoissonRatio*YoungModulus*EXX0',
         0.,0.,0.};
~~~~
