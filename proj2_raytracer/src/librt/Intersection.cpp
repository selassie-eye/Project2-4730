//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Intersection.cpp
// Intersection points - store surface normal, time of intersection
// distance squared, surface
//
// This is used to carry data about the surface for rendering
//------------------------------------------------------------------------------


#include "Intersection.h"
#include "Surface.h"



Intersection::Intersection(void)
    :   distanceSqu         (0),
        surface             (NULL),
        point               (STVector3(0,0,0)),
        normal              (STVector3(0,0,1))
{

}


Intersection::~Intersection(void)
{

}

void Intersection::setDistanceSqu(float d){ distanceSqu = d; }
void Intersection::setPoint(STVector3 p){ point = point; }
void Intersection::setNormal(STVector3 n){ normal = n; }
void Intersection::setSurface(Surface *s){ surface = s; }
