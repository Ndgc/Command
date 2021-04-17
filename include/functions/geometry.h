#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED
#include <cstddef>

char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x=NULL, float *i_y=NULL);

bool get_line_square_intersection(int line_x0,int line_y0,int line_x1,int line_y1,int square_x,int square_y,int square_w,int square_h);

#endif // GEOMETRY_H_INCLUDED
