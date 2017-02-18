//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
//
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"



// contructor
Triangle::Triangle(void)
        : Surface()
{
  m_a = STVector3(2, 1, 5);
  m_b = STVector3(4, 0, 7);
  m_c = STVector3(1, 4, 4);
}


// clean up
Triangle::~Triangle()
{

}



//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    LinearSolver L;
    bool bFoundSolution = false;

    // TO DO: Proj2 raytracer
    //          - Solve for intersections.
    // 1. Use barycentric coordinates and linear equations to solve for intersections
    // 2. If a solution is found return true, otherwise, return false
    // 3. If a solution is found, u, v and w are updated; otherwise they are useless
    //------------------------------------------------

    //------------------------------------------------------

    return(bFoundSolution);
}



//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;

    // TO DO: Proj2 raytracer
    //          - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    //    Use barycentric coordinates and linear equations
    // 2. Store the results of the intersection
    // 3. If found return true, otherwise, return false
    // NOTE: The Intersection pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------
    STVector3 normal = ComputeNormalVector()
    float d = STVector3::Dot(normal, m_a);
    float t = -(STVector3::Dot(normal, ray.Origin() + d)/STVector3::Dot(normal, ray.Direction());
    if (t < 0) return false;
    STVector3 p = ray.Origin() + (t * ray.Direction());

    pIntersection->setDistanceSqu(t);
    //std::cout << "Intersection distance added" << std::endl;
    pIntersection->point = p;
    //std::cout << "Intersection point added" << std::endl;
    pIntersection->normal = normal;
    //std::cout << "Intersection normal added" << std::endl;
    pIntersection->surface = this;
    //------------------------------------------------------

    return(bFound);
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal(0,0,1);

    // TO DO: Proj2 raytracer
    //          - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------
    normal = STVector3::Cross((m_a - m_b) (m_b - m_c));
    normal.Normalize();
    //---------------------------------------------------

    return(normal);
}


// TO DO: Proj2 raytracer
//          - Add object specific properties.
// 1. Add any object specific properties you need
//    to create your special effects (e.g. specularity, transparency...)
// 2. Remember to declare these in your .h file
//
//---------------------------------------------------------
//---------------------------------------------------------
