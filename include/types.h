#pragma once

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;

typedef float               f32;
typedef double              f64;

typedef unsigned long int ulong;

typedef unsigned int        usize_t;
//typedef signed int          ssize_t;

//typedef unsigned int        uintptr_t;
//typedef signed int          intptr_t;

typedef __builtin_va_list va_list;
#define va_start(v,l) __builtin_va_start(v,l)
#define va_end(v) __builtin_va_end(v)

using u64 = std::uint64_t;
using s64 = std::int64_t;

enum Direction
{
    RIGHT = 0,
    LEFT  = 1,
    UP    = 2,
    DOWN  = 3
};

struct Rect
{
	float left;
	float bottom;
	float right;
	float top;
};
