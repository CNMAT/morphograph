// morphograph.cpp
// 

#include "Morphograph.h"
#include "analysis.h"
#include "parser.h"

#include <stdexcept>
#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
	try {
		srand (time (NULL));
		cout << "[morphograph, ver. 0.1]" << endl << endl;
		cout << "sound scores; inspired by Linda Bouchard" << endl;
		cout << "(c) 2021, www.carminecella.com" << endl << endl;

		Parameters p;
		p.fft_size = 4096;
		p.hop_size = 512;
		p.sr = 44100;
		p.width = 600;
		p.height = 600;
		p.zoom = 3;

		Morphograph g ("test.svg", &p);
		g.add_layer ("../../samples/Brahms_4.wav", "rectangles");
		g.add_layer ("../../samples/Koonitz.wav", "circles");
		//g.add_layer ("../../samples/drops.wav", "letters");
		g.render ();

	} catch (exception& e) {
		cout << "Error: " << e.what () << endl;
	} catch (...) {
		cout << "Fatal error: unknown exception" << endl;
	}
	return 0;
}

// EOF

