#ifndef ACCELERINE_CORE_H
#define ACCELERINE_CORE_H

#include <stdlib.h>
#include <stdio.h>

/* Math */
#define HANDMADE_MATH_NO_SIMD
#include <HandmadeMath/HandmadeMath.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/* SDL2 */
#include <SDL2/SDL.h>

#endif // ACCELERINE_CORE_H