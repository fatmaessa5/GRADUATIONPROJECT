//Header Guard File

# ifndef STD_TYPES_H
# define STD_TYPES_H

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

typedef signed char     s8;
typedef signed short    s16;
typedef signed int      s32;

typedef float           f32;
typedef double          f64;

typedef unsigned long long int u64;
typedef signed long long int s64;

#define NULL		((void *)0x00)

#define LIB_SREG     (*(volatile u8 *)0x5F)
#endif 

