// Title:   lowShelf
// Author:  Ben Holmes
// Date:    2017/12/19
// License: GPL v3.0

// A class that implements low-shelf filter in state-space topology.

#ifndef lowShelf_h
#define lowShelf_h

#include <cmath>

template<class T>
class lowShelf{
    
public:
    // Default constructor
    lowShelf():lowShelf(48e3,0.1778,500){ };
    
    // Destructor
    ~lowShelf() { };
    
    // Constructor with sampling frequency
    lowShelf(T samplingFrequency):
    lowShelf(samplingFrequency,0.1778,500){ };
    
    // Constructor for all parameters
    lowShelf(T samplingFrequency, T stopBandGain, T cutoffFrequency):
    sFreq(samplingFrequency), cutoff(cutoffFrequency)
    {
        setGain(stopBandGain);
        deriveStateSpace();
    }
    
    // Run a single sample through the filter.
    T run(const T input)
    {
        T y = Cy*state + Dy*input;
        state = Ax*state + Bx*input;
        
        return y;
    }
    
    // Setter for gain
    void setGain(const T stopBandGain)
    {
        gain = std::pow(10,0.05*stopBandGain);
        deriveStateSpace();
    }
    
    // Setter for cutoff
    void setCutoff(const T cutoffFrequency)
    {
        cutoff = cutoffFrequency;
        deriveStateSpace();
    }
    
private:
    
    // Update values of the state space coefficients
    void deriveStateSpace()
    {
        // Common terms
        T gainCutoff = 2*PI*gain*cutoff;
        T piCutoff = 2*PI*cutoff;
        T gainSample = gain*2.*sFreq;
        T denom = piCutoff + gainSample - gainCutoff;
        
        // Update state-space matrices
        Ax = -(2.*gain*gainSample*((gain - 1)/gain - 1))/denom - 1;
        
        Bx = -(4.*sFreq*(gain - 1))/denom;
        
        Cy = (gainCutoff*(gain - 1))/denom;
        
        Dy = (gain*((2.*sFreq) + piCutoff - gainCutoff))/denom;
    }
    
    // Constants
    const double PI = 3.14159;
    const T sFreq;  // sampling frequency
    
    // Parameters
    T gain;
    T cutoff;
    
    // State of discretised capacitor
    T state = 0;
    
    // State space matrices
    T Ax;
    T Bx;
    T Cy;
    T Dy;
};


#endif /* lowShelf_h */
