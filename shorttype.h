/*
This is a library designed to help you write programs in c, using concise syntax and some abstractions and utility
contributions welcome.

please credit if any of this code is used
by Hasan Sabri, DO NOT REMOVE CREDIT
*/
#ifndef SHORTTYPE_H
#define SHORTTYPE_H

#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

#define f32 float
#define f64 double

#define ch char
#define bo bool

#define con const
#define sta static

typedef struct {
	double x, y;
} v2;
typedef struct {
	int x, y;
} v2i;

typedef struct {
	double x, y, z;
} v3;
typedef struct {
	int x, y, z;
} v3i;


#ifdef SHORTTYPE
int clampi(int in, int min, int max) {
	if (in > max) return max;
	if (in < min) return min;
	return in;
}
double clampf(double in, double min, double max) {
	if (in > max) return max;
	if (in < min) return min;
	return in;
}


v2 v2_norm(v2 v) {
	double h = (v.x > v.y) ? v.x : v.y;
	if (!h) h = 0.00000001;
	return (v2) {
		v.x/h,
		v.y/h
	};
}

v2 v2_rot(v2 v, double a) {
	double sa = sin(a);
	double ca = cos(a);
	return (v2) {
		 v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca
	};
}
v2i v2i_rot(v2i v, double a) {
	double sa = sin(a);
	double ca = cos(a);
	return (v2i) {
		 v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca
	};
}
double v2_dis(v2 v) {
	return sqrt(
		(v.x * v.x) + (v.y * v.y)
	);
}

double lerpf(double in, double target, double factor) {
	return in * (1.0f - factor) + (target * factor);
}

// v3 v3_norm(v3 v) {
	// double h = (v.x > v.y) ? v.x : v.y;
	// if (h < v.z) h = v.z;
	// return (v3) {
		// v.x/h,
		// v.y/h,
		// v.z/h
	// };
// }
/*v3 v3_rotx(v3 v, double a) {
	double sa = sin(a);
	double ca = cos(a);
	
	return (v3) {
		v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca,
		0
	};
}
v3 v3_roty(v3 v, double a) {
	double sa = sin(a);
	double ca = cos(a);
	
	return (v3) {
		v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca,
		0
	};
}*/
v3 v3_rotz(v3 v, double a) {
	double sa = sin(a);
	double ca = cos(a);
	
	return (v3) {
		v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca,
		0
	};
}
#else
int clampi(int in, int min, int max);
double clampf(double in, double min, double max);
double lerpf(double in, double target, double factor);

v2 v2_norm(v2 v);
v2 v2_rot(v2 v, double a);
double v2_dis(v2 v);
v3 v3_norm(v3 v);
v3 v3_rotx(v3 v, double a);
v3 v3_roty(v3 v, double a);
v3 v3_rotz(v3 v, double a);
v2i v2i_rot(v2i v, double a);


#endif

#endif