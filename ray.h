#ifndef RAYH
#define RAYH
#include "vec3.h"

/**
 * Ray classes are use to represent rays of light. It requires an origin and a direction vector.
 * Along the ray, if it come across a surface, or more accurately, from that surface and calculate what rays come across it, we can determine what color this ray of light should create on that surface.
 * 
 * **/
class ray
{
    public:
    ray(){}
    ray(const vec3& a, const vec3& b){A=a; B=b;}
    vec3 origin() const {return A;}
    vec3 direction() const {return B;}
    vec3 point_at_parameter(float t) const {return A + t*B;}

    vec3  A;
    vec3 B;
};

#endif