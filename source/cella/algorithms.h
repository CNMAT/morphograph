// algorithms.h
// 

#ifndef ALGORITHMS_H
#define ALGORITHMS_H 

#include <vector>
#include <cmath>

#define P0 (1 / (std::pow (2.0, 32.) / 2 - 1))
#define LOG2 log (2.)
#define LOG2OF10 3.32192809488736234787

// numerical/statistic -------------------------------------------------- //
template <typename T>
inline T logTwo (const T& x) {
	return LOG2OF10 * std::log10 ((T) x);
}

template <typename T>
void normalize (const T* data, T* result, int N) {
	T min = data[0];
	T max = data[0];
	T mean = 0;

	for (int i = 0; i < N; ++i) {
		if (max < data[i]) max = data[i];
		if (min > data[i]) min = data[i];
	}	
	
	T fmin = fabs (min);
	for (int i = 0; i < N; ++i) {
		result[i] = (data[i] + fmin) / (max + fmin);
	}	
}

template <typename T>
void scale (const T* buff, T* out, int len, T factor) {
	for (int i = 0; i < len; ++i) {
		out[i] = buff[i] * factor;
	}
}

template <typename T>
void swapElem (T& a, T& b) { 
	T t = (a); (a) = (b); (b) = t;
} 

template <typename T>
T kth_smallest (T a[], int n, int k) { 
	int i, j, l, m; 
	T x ; 
	l = 0 ; m = n - 1 ; 
	while (l < m) { 
		x = a[k]; 
		i = l; 
		j= m; 
		do { 
			while (a[i] < x) i++; 
			while (x < a[j]) j--; 
			if (i <= j) { 
				swapElem (a[i], a[j]); 
				i++; j--; 
			} 
		} while (i <= j) ; 
		if (j < k) l = i; 
		if (k < i) m = j; 
	} 
	return a[k] ; 
} 

template <typename T>
T median (T a[], int n) {
	return kth_smallest (a, n, (((n) & 1) ? ((n) / 2):(((n) / 2) -1)));
}

template <typename T>
T sum (
	const T* values, 
	int N) {
	if (1 > N) return 0;
	
	T sum = 0.;
	for (int i = 0; i < N; ++i) {
		sum += values[i];
	}
	
	return sum;
}

template <typename T>
T mean (
	const T* values, 
	int N) {
	if (1 > N) return 0;
	
	return sum (values, N) / N;
}
	
template <typename T>
T min (
	const T* values, 
	int N) {
	if (1 > N) return 0;
	
	T m = values[0];
	for (int i = 0; i < N; ++i) {
		if (m > values[i]) {
			m = values[i];
		}
	}
	
	return m;
}

template <typename T>
T max (
	const T* values, int N) {
        if (1 > N) return 0;
	
	T m = values[0];
	for (int i = 0; i < N; ++i) {
		if (m < values[i]) {
			m = values[i];
		}
	}
	
	return m;
}

template <typename T>
T centroid (
	const T* weights,
	const T* values, 
	int N) {
	T sumWeigth = 0;
	T sumWeigthDistance = 0;
	T distance = 0;
	T weigth = 0;
	T weigthDistance = 0;

	T maxAmp = weights[0];
	for (int index = 0; index < N; ++index) {
		distance = values[index];
		weigth = weights[index] / N;
		weigthDistance = weigth * distance;
		sumWeigth += weigth;
		sumWeigthDistance += weigthDistance;
		if (maxAmp < weights[index]) {
			maxAmp = weights[index];
		}
	}
	return (sumWeigth > .1 ? sumWeigthDistance / sumWeigth : 0);
}

template <typename T>
T stddev (const T* weights, const T* values, T mean, int N) {
	if (N <= 0) return 0;

	T max = weights[0];
	for (int f = 0; f < N; ++f) {
		if (weights[f] >= max) max = weights[f];
	}
	T scaledMax = 0.3 * max;

	T sumWeight = 0.0;
	T sumDistance = 0.0;
	for (int index = 0; index < N; index++) {
		T tmp = values[index] - mean;
		T value = tmp * tmp;
		T weight = weights[index];
		if (weight <= scaledMax) weight = 0;
		T distance  = value * weight;

		sumWeight += weight;
		sumDistance += distance;
	}

	T sd = 0.0;
	if (0 != sumWeight) {
		sd = sumDistance / sumWeight;
	} else {
		sd = 0.;

	}
	return std::sqrt (sd);
}

template <typename T>
T moment (
	const T* weights,
	const T* values,
	int N,
	int order,
	T centroid) {
	T sumWeigth = 0;
	T sumWeigthDistance = 0;
	T distance = 0;
	T weigth = 0;
	T weigthDistance = 0;

	for (int index = 0; index < N; ++index) {
		distance = values[index];
		distance -= centroid;
		distance = std::pow (distance, order);
		weigth = weights[index];
		weigthDistance = weigth * distance;
		sumWeigth += weigth;
		sumWeigthDistance += weigthDistance;
	}

	return (sumWeigth != 0 ? sumWeigthDistance / sumWeigth : 0);
}

template <typename T>
T linreg (
	const T* weights,
	const T* values,
	int N,
	T& step) {
	int index;
	int nbValue = N;

	T Xk = 0;
	T Yk = 0;
	T Xk2 = 0;
	T XkYk = 0;

	T sumXk = 0;
	T sumYk = 0;
	T sumXk2 = 0;
	T sumXkYk = 0;
	
	T slope = 0;

	for (index = 0; index < nbValue; index++) {
		Xk = values[index];
		Yk = weights[index];
		Xk2 = Xk * Xk;
		XkYk = Xk * Yk;

		sumXk += Xk;
		sumYk += Yk;
		sumXkYk += XkYk;
		sumXk2 += Xk2;
	}

	T numSlope = ((T) nbValue) * sumXkYk - (sumXk * sumYk);
	T numStep = sumXk2 * sumYk - sumXk * sumXkYk;
	T denSlope = ((T) nbValue) * sumXk2 - std::pow (sumXk, 2.0);

	if (0 != denSlope) {
		slope = numSlope / denSlope;
		step  = numStep / denSlope;
	} else {
		slope = 0;
		step = 0;
	}
	return slope;
}

// dsp ------------------------------------------------------------------ //


template <typename T>
void conv (T* X, T* Y, T* Z, int lenx, int leny, T scale) {
	T *zptr, s, *xp, *yp;
	int i, n, n_lo, n_hi;
	int lenz = lenx + leny - 1;

	zptr = Z;
	for (i = 0; i < lenz; i++) {
		s=0.0;
		n_lo= 0 > (i - leny + 1) ? 0 : i - leny + 1;
		n_hi = lenx - 1 < i ? lenx - 1 : i;
		xp = X + n_lo;
		yp = Y + i-n_lo;
		for (n = n_lo; n <= n_hi; n++) {
			s += *xp * *yp;
			xp++;
			yp--;
		}
	*zptr = s * scale;
	zptr++;
	}
}

template <typename T>
T amp2db (const T& input) {
	// sound pressure level (minimum 32 bits)
	if (input < P0) return 0;
	T f = 20. * std::log10 ((T) (input / P0));
	return f;
}

#endif	// ALGORITHMS_H 

// EOF
