# microClipper

Overdrive plugin based on the traditional diode-clipping circuit.

## Specification

- Built using JUCE framework
- Mono input
- Multiple outputs (copies of first channel)
- Four controls:
  - Pre-gain - Controls the gain of the input to the diode-clipper.
  - Distortion - Controls diode ideality factor.
  - Brightness - Controls the stop-band gain of a low-shelf filter.
  - Warmth - Changes the symmetry of the diodes controlling even/odd harmonics.

## Model

The underlying circuit model is a diode clipper featuring a resistor connected to a capacitor and two diodes in parallel. This is modelled using trapezoidal discretisation, with an iterative solver to solver the nonlinearity.

Following the distortion stage is a first order low-shelf filter with a fixed cutoff frequency of 500 Hz. This is implemented as a state-space model, parameterised with stop-band gain and cutoff frequency.

## To do list

- Implement oversampling
- Optimise iterative solver for performance
