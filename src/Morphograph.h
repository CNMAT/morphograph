// Morphograph.h
// 

#ifndef MORPHOGRAPH_H
#define MORPHOGRAPH_H 

#include "analysis.h"
#include "svg.h"

#define OFFSET 50

struct Layer {
	std::string fname;
	std::string shape;
	Descriptors desc;
};

class Morphograph {
private:
	Morphograph& operator= (Morphograph&);
	Morphograph (const Morphograph&);
public: 
	Morphograph (const std::string& fname, Parameters* p) {
		params = p;
		Dimensions dims (params->width + OFFSET, params->height + OFFSET);
		doc = new Document (fname, Layout(dims, Layout::BottomLeft, params->zoom));
	}
	virtual ~Morphograph () {
		delete doc;
	}
	void add_layer (const std::string& fname, const std::string& shape) {
		Layer l;
		l.fname = fname;
		l.shape = shape;
		analyse (fname, *params, l.desc);
		layers.push_back (l);
	}
	void render () {
		int max_frames = 0;
		for (unsigned i = 0; i < layers.size (); ++i) {
			if (max_frames < layers[i].desc.energy.size ()) {
				max_frames = layers[i].desc.energy.size ();
			}
		}
		double min_freq = params->sr / 2, max_freq = 1; // large mins
		double min_irr = params->sr / 2, max_irr = 1; // large mins
		double min_nrg = params->fft_size, max_nrg = 0;
		double min_zcr = params->sr / 2, max_zcr = 0;
		for (unsigned i = 0; i < layers.size (); ++i) {
			for (unsigned j = 0; j < layers[i].desc.energy.size (); ++j) {
				layers[i].desc.highest_peak_Hz.resize (max_frames, 0);
				layers[i].desc.energy.resize (max_frames, 0);
				layers[i].desc.zcr.resize (max_frames, 0);
			}
			//get_min_max (layers[i].desc.highest_peak_Hz, min_freq, max_freq);
			min_freq = 0;
			max_freq = params->sr / 2;
			// get_min_max (layers[i].desc.irr, min_irr, max_irr);
			// min_irr = 0;
			// max_irr = params->sr / 2;
			get_min_max (layers[i].desc.energy, min_nrg, max_nrg);
			get_min_max (layers[i].desc.zcr, min_zcr, max_zcr);
		}
		for (unsigned i = 0; i < layers.size (); ++i) {
			
			for (unsigned j = 0; j < layers[i].desc.energy.size (); ++j) {
				if (j % 2 == 0) {
					int sz = layers[i].desc.energy.size ();

					double sc_freq = (layers[i].desc.highest_peak_Hz[j] / (max_freq - min_freq)) + min_freq;
					// double sc_irr = (layers[i].desc.irr[j] / (max_irr - min_irr)) + min_irr;
					double sc_nrg = (layers[i].desc.energy[j] / (max_nrg - min_nrg)) + min_nrg;
					// double sc_zcr = (layers[i].desc.zcr[j] / (max_zcr - min_zcr)) + min_zcr;

					if (layers[i].shape == "circles") {
						(*doc) << Circle (Point ((double) j / sz * params->width, sc_freq * params->height), 
								sc_nrg * params->width / 32,  Fill(Color (sc_nrg * 256, sc_nrg * 256, sc_nrg * 256)), 
								Stroke (1, Color (0, 0, 0)));						
					} else if (layers[i].shape == "rectangles") {
						(*doc) << Rectangle(Point ((double) j / sz * params->width, sc_freq * params->height), 
							sc_nrg * params->width / 32, sc_nrg * params->height / 32, Color (sc_nrg * 256, sc_nrg * 256, sc_nrg * 256));
					} else if (layers[i].shape == "letters") {
						int l = rand () % 26;
						char ls = 'a';
						std::stringstream lss;
						lss << (char) (ls + l);
						std::cout << lss.str () << std::endl;
						(*doc) << Text(Point ((double) j / sz * params->width, sc_freq * params->height), 
							lss.str (), Color (sc_nrg * 256, sc_nrg * 256, sc_nrg * 256), Font (sc_nrg * params->height / 16, "Verdana"));
					}
				}
			}
		}
		
		(*doc).save ();
	}

	Document* doc;
	Parameters* params;
	std::vector<Layer> layers;
private:
	void get_min_max (std::vector<double>& vals, double& min_v, double& max_v) {
		if (max<double> (&vals[0], vals.size ()) > max_v) {
			max_v = max<double> (&vals[0], vals.size ());
		}
		if (min<double> (&vals[0], vals.size ()) < min_v) {
			min_v = min<double> (&vals[0], vals.size ());
		}
	}
};

#endif	// MORPHOGRAPH_H 

// EOF
