// utilities.h
//


#ifndef UTILITIES_H
#define UTILITIES_H

#include <dirent.h>

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include <deque>
#include <cmath>

// -----------------------------------------------------------------------------
std::string removePath (const std::string& in) {
	size_t pos = std::string::npos;
	pos = in.find_last_of ("/");
	if (pos != std::string::npos) {
		return in.substr (pos + 1, in.size () - pos);
	} else return in;
}

std::string removeExtension (const std::string& in) {
	size_t pos = std::string::npos;
	pos = in.find_last_of (".");
	if (pos != std::string::npos) {
		return in.substr (0, pos);
	} else return in;
}

std::string trim (std::string const& source,
	char const* delims = " \t\r\n") {
	std::string result (source);
	std::string::size_type index = result.find_last_not_of (delims);
	if (index != std::string::npos)
		result.erase (++index);

	index = result.find_first_not_of (delims);
	if (index != std::string::npos)
		result.erase (0, index);
	else
		result.erase ();
	return result;
}

void erase_substring (std::string & mainStr, const std::string & toErase) {
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);

	if (pos != std::string::npos) {
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}



std::vector<std::string> split_by_pipe (const std::string& input) {
    std::istringstream ss(input);
    std::string token;

    std::vector<std::string> res;
    while(std::getline(ss, token, '|')) {
        res.push_back(token);
    }

    return res;
}

// -----------------------------------------------------------------------------
// search for regexp at beginning of text
bool match_star (int c, char *regexp, char *text);
bool match_here (char* regexp, char* text) {
    if (regexp[0] == '\0') return true;
    if (regexp[1] == '*') return match_star (regexp[0], regexp + 2, text);
    if (regexp[0] == '$' && regexp[1] == '\0') return *text == '\0';
    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) {
        return match_here (regexp + 1, text + 1);
    }
    return false;
}

// leftmost longest search for c*regexp */
bool match_star (int c, char *regexp, char *text) {
    char *t;

    for (t = text; *t != '\0' && (*t == c || c == '.'); t++)
        ;
    do {    /* * matches zero or more */
        if (match_here(regexp, t)) return true;
    } while (t-- > text);
    return false;
}

// search for regexp anywhere in text
bool match (char* regexp, char* text) {
    if (regexp[0] == '^')
        return match_here (regexp + 1, text);
    do {
        if (match_here (regexp, text)) return true;
    } while (*text++ != '\0');
    return false;
}
// -----------------------------------------------------------------------------
template <typename T>
void save_vector (const char* file, const std::vector<T>& v) {
	std::ofstream out (file);
	if (!out.good ()) {
		throw std::runtime_error ("cannot create output file");
	}

	for (unsigned i = 0; i < v.size (); ++i) {
		out << v[i] << " ";
	}
	out.close ();
}

// -----------------------------------------------------------------------------
template <typename T>
void interleave (T* stereo, const T* l, const T* r, int n) {
	for (int i = 0; i < n; ++i) {
		stereo[2 * i] = l[i];
		stereo[2 * i + 1] = r[i];
	}
}

template <typename T>
void deinterleave (const T* stereo, T* l, T* r, int n) {
	for (int i = 0; i < n; ++i) {
		l[i] = stereo[2 * i];
		r[i] = stereo[2 * i + 1];
	}
}

// -----------------------------------------------------------------------------

template <typename T>
T cents_to_ratio (int cents) {
	T c = cents;
	c /= 1200.;
	return std::pow (2., c);
}

long pitch_buffer_to_midi (char *pitch_string) {
    int base = 0;
    char *cur = pitch_string;
    switch (*cur) {
        case 'c':
        case 'C':
            base = 0;
            break;
        case 'd':
        case 'D':
            base = 2;
            break;
        case 'e':
        case 'E':
            base = 4;
            break;
        case 'f':
        case 'F':
            base = 5;
            break;
        case 'g':
        case 'G':
            base = 7;
            break;
        case 'a':
        case 'A':
            base = 9;
            break;
        case 'b':
        case 'B':
            base = 11;
            break;
        default:
            // possibily throw error
            return 0;
    }
    cur++;

    bool alt = 0;
    if (*cur == '#') {
        alt = 1;
        cur++;
    }

    return (atoi(cur)+1)*12+base+alt;
}

long pitch_buffer_to_cents (char *pitch_string) {
    return pitch_buffer_to_midi(pitch_string)*100;
}

inline bool file_exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

// inframes contains INTERLEAVED samples for all channels
template <typename T>
long resample(T* inframes, long nsamps, std::vector<T>& outframes, double old_sr,
	double new_sr, double fmax, double window_width, long num_channels) {
    double factor = new_sr / old_sr;
    long num_in_frames = nsamps / num_channels;
    long num_out_frames = (long)ceil(num_in_frames * factor);
    
    // clear and initialize output vector
    outframes.clear();
    for (long i = 0; i < num_out_frames; i++)
        outframes.push_back(0.);
    
    for (long ch = 0; ch < num_channels; ch++) {
        for (long s = 0; s < num_out_frames; s++) {
            long i, j;
            double x = s / factor;
            double r_w, r_a, r_snc;
            double r_g = 2 * fmax / new_sr; // Calc gain correction factor
            double r_y = 0;
            for (i = -window_width/2; i < window_width/2; i++) { // For 1 window width
                j = (long)(x + i); // Calc input sample index
                //rem calculate von Hann Window. Scale and calculate Sinc
                r_w     = 0.5 - 0.5 * cos (2. * M_PI * (0.5 + (j - x) / window_width));
                r_a     = 2. * M_PI * (j - x)*fmax/new_sr;
                r_snc   = (r_a != 0 ? r_snc = sin(r_a)/r_a : 1);
                if (j >= 0 && j < num_in_frames) {
                    r_y   = r_y + r_g * r_w * r_snc * inframes[num_channels * j + ch];
                }
            }
            outframes[num_channels * s + ch] = r_y; // Return new filtered sample
        }
    }
    return num_out_frames * num_channels;
}

#endif	// UTILITIES_H

// EOF
