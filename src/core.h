#ifndef ACCELERINE_CORE_H
#define ACCELERINE_CORE_H

#include <stdio.h>
#include <stdlib.h>

/* Math */
#define HANDMADE_MATH_NO_SIMD
#define HANDMADE_MATH_USE_DEGREES
#include <HandmadeMath/HandmadeMath.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* SDL2 */
#include <SDL2/SDL.h>

#endif // ACCELERINE_CORE_H
