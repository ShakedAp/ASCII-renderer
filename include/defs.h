#ifndef __DEFS_H
#define __DEFS_H
#include <ncurses.h>
#include "vec3.h"

#define PI (3.14159265358979323846264338327950288)
#define DEG_TO_RAD(d) (d * PI / 180)

#define MAX(a, b) (((a)>(b))? (a) : (b))
#define MIN(a, b) (((a)<(b))? (a) : (b))

#define WH (LINES)
#define WW (COLS)

#endif