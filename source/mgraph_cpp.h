//
//  morphograph_cpp.h
//  max-sdk
//
//  Created by Jeff Lubow on 1/13/23.
//

#ifndef morphograph_cpp_h
#define morphograph_cpp_h

#include <vector>
#include <string>
#include "mgraph.h"
#include "cella/svg.h"



struct Descriptors {
    std::vector<double> highest_peak_Hz;
    //implemented in features.h
    std::vector<double> energy;
    std::vector<double> zcr;
    std::vector<double> speccentr;
    std::vector<double> specspread;
    std::vector<double> specskew;
    std::vector<double> speckurt;
    std::vector<double> specflux;
    std::vector<double> specirr;
    std::vector<double> specdecr;
    std::vector<double> specslope;
    std::vector<double> specflat;
    std::vector<double> speccrest;
    std::vector<double> hfc;
    std::vector<double> inharmonicity;
};

struct Layer {
    std::string fname;
    std::string shape;
    Descriptors desc;
};

struct Parameters {
    double sr;
    long fft_size;
    long hop_size;
    long width;
    long height;
    long zoom;
};


#endif /* morphograph_cpp_h */

