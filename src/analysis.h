// analysis.h
// 

#ifndef ANALYSIS_H
#define ANALYSIS_H 

#include "WavFile.h"
#include "utilities.h"
#include "parser.h"
#include "FFT.h"
#include "features.h"

#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

struct Descriptors {
    std::vector<double> highest_peak_Hz;
    std::vector<double> irr;
    std::vector<double> energy;
    std::vector<double> zcr;
};

void analyse (const std::string& fname, Parameters& p, Descriptors& d) {
    WavInFile in (fname.c_str ());
    if (in.getSampleRate () != p.sr) {
        std::stringstream err;
        err << "invalid sampling rate in " << fname << ": " << in.getSampleRate () << " vs" << p.sr;
        throw std::runtime_error (err.str ());
    }
    int nsamps = in.getNumSamples ();

    std::vector<double> samples (nsamps);
    if (in.getNumChannels () == 1) {
        in.read (&samples[0], nsamps);    
    } else if (in.getNumChannels () == 2) {
        std::vector<double> stereo_samples (nsamps * 2);
        in.read (&stereo_samples[0], nsamps);   
        for (unsigned i = 0; i < nsamps; ++i) {
            samples[i] = .5 * stereo_samples[2 * i] + .5 * stereo_samples[2 * i +1];
        }
    } else {
        std::stringstream err;
        err << "invalid number of channels in << " << fname << "(mono or stereo only)"; 
        throw std::runtime_error (err.str ());
    }

    std::vector<double> buffer (p.fft_size * 2); // complex
    std::vector<double> window (p.fft_size);
    makeWindow<double> (&window[0], p.fft_size, .5, .5, 0); // hanning
    double winEnergy = 0;
    for (unsigned i = 0; i < p.fft_size; ++i) {
        winEnergy += window[i] * window[i];
    }
    std::vector<double> amps (p.fft_size / 2); // discard symmetry
    std::vector<double> freqs (p.fft_size / 2); // discard symmetry
    for (unsigned i = 0; i < p.fft_size / 2; ++i) {
        freqs[i] = p.sr / p.fft_size * i;
    }
    int ptr = 0;
    while (ptr < nsamps) {
        if (p.fft_size + ptr > nsamps) break; // discard incomplete frame

        memset (&buffer[0], 0, sizeof (double) * 2 * p.fft_size);
        for (unsigned i = 0; i < p.fft_size; ++i) {
            buffer[2 * i] = window[i] * samples[i + ptr];
        }
        fft (&buffer[0], p.fft_size, -1);

        // double max_peak = 0;
        // int max_pos = 0;
        // for (unsigned i = 0; i < p.fft_size; ++i) {
        //     double r = buffer[2 * i];
        //     double im = buffer[2 * i + 1];
        //     double a = sqrt (r * r + im * im);
        //     if (a > max_peak) {
        //         max_peak = a;
        //         max_pos = i;
        //     }
        // }
        // d.highest_peak_Hz.push_back ((p.sr / p.fft_size) * max_pos);

        for (unsigned i = 0; i < p.fft_size / 2; ++i) {
            double r = buffer[2 * i];
            double im = buffer[2 * i + 1];
            double a = sqrt (r * r + im * im);
            amps[i] = a;
        }
        double c = speccentr (&amps[0], &freqs[0], p.fft_size / 2);
        d.highest_peak_Hz.push_back (c);

        double irr = specirr (&amps[0], p.fft_size / 2);
        d.irr.push_back (irr);

        double z = zcr<double> (&samples[ptr], p.fft_size);
        d.zcr.push_back (z);

        double sum = 0;
        for (int i = 0; i < p.fft_size; ++i) {
		    double a = samples[i + ptr];
		    sum += a * a;
	    }
        d.energy.push_back (std::sqrt (sum / p.fft_size));
        
        ptr += p.hop_size;
    }    
}

#endif	// ANALYSIS_H 

// EOF
