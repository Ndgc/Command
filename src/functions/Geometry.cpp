#include <cstddef>

//line_intersection from https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x=NULL, float *i_y=NULL)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}

//return true if the line intersects the square
bool get_line_square_intersection(int line_x0,int line_y0,int line_x1,int line_y1,int square_x,int square_y,int square_w,int square_h)
{
    //top edge
    if (get_line_intersection(line_x0,line_y0,line_x1,line_y1,square_x,square_y,square_x+square_w,square_y))
    {
        return true;
    }
    //left edge
    if (get_line_intersection(line_x0,line_y0,line_x1,line_y1,square_x,square_y,square_x,square_y+square_h))
    {
        return true;
    }
    //bottom edge
    if (get_line_intersection(line_x0,line_y0,line_x1,line_y1,square_x,square_y+square_h,square_x+square_w,square_y+square_h))
    {
        return true;
    }
    //right edge
    if (get_line_intersection(line_x0,line_y0,line_x1,line_y1,square_x+square_w,square_y,square_x+square_w,square_y+square_h))
    {
        return true;
    }
return false;
}
