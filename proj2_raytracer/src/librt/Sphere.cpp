//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "defs.h"
#include <tgmath.h>

// constructor
Sphere::Sphere(void)
    : m_radius(0.5)
{
      m_center = STVector3(0,0,5);
}

Sphere::Sphere(float r)
{     m_radius = r;
      m_center = STVector3(0,0,float(rand() % 5 + 1));
}


// clean up here
Sphere::~Sphere()
{

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection)
{
    //std::cout << "Sphere.FindIntersection started" << std::endl;
    bool bFound = false;
    Intersection *temp = new Intersection();

    // TO DO: Proj2 raytracer
    //          - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    // 2. Store the results of the intersection
    // 3. if found and return true, otherwise, return false
    // NOTE: The IntersectionPoint pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------
    STVector3 l = m_center - ray.Origin();
    //std::cout << "Length vector: ";
    //l.Print();
    float tca = STVector3::Dot(l, ray.Direction());
    //std::cout << "tca: " << tca << std::endl;
    if (tca < 0){
      //std::cout << "No intersection" << std::endl;
      return false;
    }
    float d = sqrtf((STVector3::Dot(l, l) - (tca*tca)));
    //std::cout << "d: " << d << std::endl;
    if (d > m_radius) {
      //std::cout << "No intersection" << std::endl;
      return false;
    }
    float thc = sqrtf((m_radius * m_radius) - (d*d));
    //std::cout << "thc: " << thc << std::endl;


    float t0 = tca - thc;
    //std::cout << "t0: " << t0 << std::endl;
    float t1 = tca + thc;
    //std::cout << "t1: " << t1 << std::endl;


    float t = (t0 < t1 ? t0 : t1);
    //std::cout << "t: " << t << std::endl;


    STVector3 p = ray.Origin() + (t * ray.Direction());
    //std::cout << "p: ";
    //p.Print();

    STVector3 norm = p - m_center;
    norm.Normalize();
    //std::cout << "norm: ";
    //norm.Print();


    pIntersection->setDistanceSqu(t);
    //std::cout << "Intersection distance added" << std::endl;
    pIntersection->point = p;
    //std::cout << "Intersection point added" << std::endl;
    pIntersection->normal = norm;
    //std::cout << "Intersection normal added" << std::endl;
    pIntersection->surface = this;
    //std::cout << "Intersection surface added" << std::endl;
    //std::cout << "Intersection object created" << std::endl;

   //------------------------------------------------------


   return(true);
}
