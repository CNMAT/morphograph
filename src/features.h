// features.h
// 

#ifndef FEATURES_H
#define FEATURES_H 

#include "FFT.h"
#include "algorithms.h"
#include <cmath>

// spectral descriptors ------------------------------------------------- //

template <typename T>
inline T speccentr(
		const T* amplitudes,
		const T* frequencies,
		int N) {
	return centroid(amplitudes, frequencies, N);
}

template <typename T>
inline T specspread(
		const T* amplitudes,
		const T* frequencies,
		int N,
		T centroid) {
	return std::sqrt(moment<T > (amplitudes, frequencies, N, 2, centroid));
}

template <typename T>
inline T specskew(
		const T* amplitudes,
		const T* frequencies,
		int N,
		T centroid,
		T spread) {

	T delta = std::pow(spread, 3);
	T tmp = moment<T> (amplitudes, frequencies, N, 3, centroid);
	if (delta != 0) {
		tmp /= delta;
	}

	return tmp;
}

template <typename T>
inline T speckurt(
		const T* amplitudes,
		const T* frequencies,
		int N,
		T centroid,
		T spread) {

	T delta = std::pow(spread, 4);
	T tmp = moment<T > (amplitudes, frequencies, N, 4, centroid);
	if (delta != 0) {
		tmp /= delta;
	}

	return tmp;
}

template <typename T>
inline T specflux(T* amplitudes, T* oldAmplitudes, int N) {
	T sf = 0; // spectral flux
	T a = 0;
	for (int i = 0; i < N; ++i) {
		a = (amplitudes[i] - oldAmplitudes[i]);
		oldAmplitudes[i] = amplitudes[i];
		sf += a < 0 ? 0 : a; // rectification
		//sf += a;
	}

	return sf;
}

template <typename T>
inline T specirr(T* amplitudes, int N) {
	if (1 > N) return 0;
	T si = 0; // spectral irregularity
	T a = 0;
	for (int i = 1; i < N; ++i) {
		a = fabs(amplitudes[i] - amplitudes[i - 1]);
		si += a;
	}

	return si;
}

template <typename T>
inline T specdecr(
		const T* amplitudes,
		int N) {
	T decs = 0;
	T den = 0;
	if (N <= 1) return 0;

	for (int index = 1; index < N; ++index) {
		decs += (amplitudes[index] - amplitudes[0]) / (T) (index);
		den += amplitudes[index];
	}

	if (den != 0.0) {
		decs /= den;
	}

	return decs;
}

template <typename T>
inline T specslope(
		const T* amplitudes,
		const T* frequencies,
		int N) {
	T step = 0;
	T sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += amplitudes[i];
	}

	T sl = linreg(amplitudes, frequencies, N, step);

	if (sum != 0.0) {
		sl /= sum;
	}

	return sl;
}

template <typename T>
inline T specflat(
		const T* amplitudes,
		int N) {
	T prod = amplitudes[0];
	T sum = amplitudes[0];
	for (int i = 1; i < N; ++i) {
		sum += amplitudes[i];
		//prod *= (amplitudes[i]);
		prod += log(amplitudes[i]);
	}


	//T geom = pow (prod, 1. / N);
	T geom = std::exp(prod / N);
	T flat = geom;
	if (sum != 0.0) {
		flat /= sum;
	} else flat = 0;

	return flat;
}

template <typename T>
inline T speccrest(
		const T* amplitudes,
		int N) {
	T max = amplitudes[0];
	T sum = amplitudes[0];
	for (int i = 1; i < N; ++i) {
		sum += amplitudes[i];
		if (max < amplitudes[i]) max = amplitudes[i];
	}


	T crest = max;
	if (sum != 0.0) {
		crest /= sum;
	} else crest = 0;

	return crest;
}

template <typename T>
inline T hfc(T* amplitudes, int N) {
	T hfc = 0; // high frequency content
	T a = 0;
	T n = 0;
	for (int i = 0; i < N; ++i) {
		a = amplitudes[i];
		hfc += (a * a) * i;
		n += i;
	}

	return hfc / n;
}

template <typename T>
T inharmonicity(T* amp, T* freq, int size, T f0, T R, T& sumAmpl) {
	if (f0 <= 0) return 0;

	sumAmpl = 0.0;
	T sumVariation = 0.0;
	for (int i = 0; i < size / 2; ++i) {
		T harmo = (i + 1) * f0;
		T variation = std::fabs(freq[i] - harmo);
		sumAmpl += amp[i];
		sumVariation += variation * amp[i];
	}

	T estInharm = 0.;
	if (sumAmpl != 0) {
		estInharm = (2 / f0) * (sumVariation / sumAmpl) / R;
	}

	return estInharm;
}


// temporal descriptors ------------------------------------------------- //

template <typename T>
inline T energy(const T* samples, int N, T winEnergy) {
	T sum = 0.;
	T en = 0.;
	T a = 0.;
	for (int index = 0; index < N; ++index) {
		a = samples[index];
		sum += a * a;
	}

	if (winEnergy > 0) {
		en = std::sqrt(sum / winEnergy);
	}

	return en;
}

template <typename T>
static inline T zcr(const T* samples, int N) {
	T nb_zcr = 0.0;
	int sign1, sign2;

	if (1 > N) return 0;

	sign1 = (samples[0] < 0 ? -1 : 1);
	if (samples[0] == 0) sign1 = 0;

	for (int index = 1; index < N; ++index) {
		sign2 = (samples[index] < 0 ? -1 : 1);
		if (samples[index] == 0) sign2 = 0;

		if (sign1 != sign2) {
			++nb_zcr;
		}

		sign1 = sign2;
	}

	return (T) (nb_zcr / N);
}

#endif	// FEATURES_H

// EOF
