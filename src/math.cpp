#include <math.h>

struct Point {
    double x;
    double y;
};

Point invert(Point original) 
{
    double inversionRadius = 5.0;
    Point inversionCenter = Point({5.0,5.0});
    if (original.x == inversionCenter.x && original.y == inversionCenter.y)
    {
        return original;
    }
    double homothetyFactor = pow(inversionRadius, 2.0) / ( pow(original.x - inversionCenter.x, 2.0) + pow(original.y - inversionCenter.y, 2.0) );
    Point invertedPoint = Point 
    ( {
        (original.x - inversionCenter.x) * homothetyFactor + inversionCenter.x,
        (original.y - inversionCenter.y) * homothetyFactor + inversionCenter.y
    } );
    return invertedPoint;
}