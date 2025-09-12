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
	f32 x, y;
} v2;
typedef struct {
	i32 x, y;
} v2i;

typedef struct {
	f32 x, y, z;
} v3;
typedef struct {
	i32 x, y, z;
} v3i;


#ifdef SHORTTYPE
i32 clampi(i32 in, i32 min, i32 max) {
	if (in > max) return max;
	if (in < min) return min;
	return in;
}
f32 clampf(f32 in, f32 min, f32 max) {
	if (in > max) return max;
	if (in < min) return min;
	return in;
}


v2 v2_norm(v2 v) {
	f32 h = (v.x > v.y) ? v.x : v.y;
	if (!h) h = 0.00000001;
	return (v2) {
		v.x/h,
		v.y/h
	};
}

v2 v2_rot(v2 v, f32 a) {
	f32 sa = sin(a);
	f32 ca = cos(a);
	return (v2) {
		 v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca
	};
}
v2i v2i_rot(v2i v, f32 a) {
	f32 sa = sin(a);
	f32 ca = cos(a);
	return (v2i) {
		 v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca
	};
}
f32 v2_dis(v2 v) {
	return sqrt(
		(v.x * v.x) + (v.y * v.y)
	);
}

f32 lerpf(f32 in, f32 target, f32 factor) {
	return in * (1.0f - factor) + (target * factor);
}

// v3 v3_norm(v3 v) {
	// f32 h = (v.x > v.y) ? v.x : v.y;
	// if (h < v.z) h = v.z;
	// return (v3) {
		// v.x/h,
		// v.y/h,
		// v.z/h
	// };
// }
/*v3 v3_rotx(v3 v, f32 a) {
	f32 sa = sin(a);
	f32 ca = cos(a);
	
	return (v3) {
		v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca,
		0
	};
}
v3 v3_roty(v3 v, f32 a) {
	f32 sa = sin(a);
	f32 ca = cos(a);
	
	return (v3) {
		v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca,
		0
	};
}*/
v3 v3_rotz(v3 v, f32 a) {
	f32 sa = sin(a);
	f32 ca = cos(a);
	
	return (v3) {
		v.x * ca - v.y * sa,
		-v.x * sa - v.y * ca,
		0
	};
}
#else
i32 clampi(i32 in, i32 min, i32 max);
f32 clampf(f32 in, f32 min, f32 max);
f32 lerpf(f32 in, f32 target, f32 factor);

v2 v2_norm(v2 v);
v2 v2_rot(v2 v, f32 a);
f32 v2_dis(v2 v);
v3 v3_norm(v3 v);
v3 v3_rotx(v3 v, f32 a);
v3 v3_roty(v3 v, f32 a);
v3 v3_rotz(v3 v, f32 a);
v2i v2i_rot(v2i v, f32 a);


#endif

#endif