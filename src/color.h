#ifndef ACCELERINE_COLOR_PALETTE_H
#define ACCELERINE_COLOR_PALETTE_H

#define m_color(r, g, b, a) (a) << 24 | (r) << 16 | (g) << 8 | (b)
#define COL_SKYBLUE m_color(135, 206, 235, 255)
#define COL_GRASSGREEN m_color(50, 205, 50, 255)
#define COL_BRICKRED m_color(178, 34, 34, 255)
#define COL_BLACK m_color(0, 0, 0, 255)

#define alpha(rgba) ((rgba) >> 24)
#define red(rgba) (((rgba) >> 16) & ((1 << 8) - 1))
#define green(rgba) (((rgba) >> 8) & ((1 << 8) - 1))
#define blue(rgba) ((rgba) & ((1 << 8) - 1))

#endif // ACCELERINE_COLOR_PALETTE_H