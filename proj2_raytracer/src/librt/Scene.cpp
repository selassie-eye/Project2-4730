//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.cpp
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#include "Scene.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Intersection.h"
#include "Surface.h"
#include "Light.h"
#include "Sphere.h"



Scene::Scene(void)
    : m_background(RGBR_f(0, 0, 0, 1))
 {
    // init camera
    m_pCamera = new Camera();

}


Scene::~Scene()
{
}


void Scene::SetBackgroundColor(RGBR_f color)
{
    m_background = color;
}


RGBR_f Scene::GetBackgroundColor(void)
{
    return(m_background);
}


void Scene::AddLight(Light lightin)
{
    m_lights.push_back(lightin);
}


void Scene::AddSurface(Surface *pSurfacein)
{
    m_surfaceList.push_back(pSurfacein);
}


Camera *Scene::GetCamera(void)
{
    return(m_pCamera);
}


// computes the direction of the light in the scene
// and returns it
STVector3 Scene::GetLightDirection(void)
{
    STVector3 lightDirection;

    // TO DO: Proj2 raytracer
    //          - Compute light direction.
    // 1. Return the direction of the light in the scene
    //---------------------------------------------------------
    Light light = m_lights.front();
    lightDirection = light.GetPosition();
    //---------------------------------------------------------

    return(lightDirection);
}


// Select the closest intersection and return the number of points
// very close to this one
int Scene::SelectClosest(IntersectionList *pIntersectionList, Intersection *pIntersection)
{

    int numPoints = 0;

    // TO DO: Proj2 raytracer
    //          - Find the closest intersection.
    // 1. Find the closest (over all objects) intersection and update pIntersection
    // 2. return the number of really close points if there is a cluster
    //---------------------------------------------------------

    //---------------------------------------------------------

    return(numPoints);
}


//-----------------------------------------------------
// Find the intersection of the ray with objects in the scene
// Return the closest intersection
//-----------------------------------------------------
int Scene::FindClosestIntersection(Ray ray, Intersection *pIntersection)
{
    int numPoints = 0;
    numPoints = FindIntersection(ray, pIntersection, false);
    return(numPoints);
}


//-----------------------------------------------------
// Find the intersection of the ray with objects in the scene
// Checks for the closest intersections and retuns the number
// of close intersections found
// Updates the pIntersection
//   -if bAny is true, return the first intersection found
//   - if bAny is false, return the closest intersection
//
//-----------------------------------------------------
int Scene::FindIntersection(Ray ray, Intersection *pIntersection, bool bAny)
{
    //std::cout << "Scene.FindIntersection started." << std::endl;
    bool bFound = false;
    int numPoints = 0;

    IntersectionList intersectionList;

    SurfaceList::const_iterator iter = m_surfaceList.begin();
    SurfaceList::const_iterator end  = m_surfaceList.end();
    //std::cout << "SurfaceList iterators initialized" << std::endl;

    for (; iter != end; ++iter) {
        // TO DO: Proj2 raytracer
        //          - Find Intersections.
        // 1. Find intersections with objects in the scene
        // 2. If bAny is true, return as soon as you find one
        //    Do not forget to update the pIntersection before returning
        // 3. Othersize just add to the list of intersections
        //---------------------------------------------------------
        bFound = (*iter)->FindIntersection(ray, pIntersection);
        intersectionList.push_back(*pIntersection);
        if (bFound){
          //std::cout << "Intersection found" << std::endl;
          numPoints++;
          if (bAny) return numPoints;
        }
        else return 0;
    }

    // TO DO: Proj2 raytracer
    //          - Find Intersections.
    // 1. Find the closest intersection along the ray in the list
    //---------------------------------------------------------
    IntersectionList::const_iterator iterr = intersectionList.begin();
    IntersectionList::const_iterator endd  = intersectionList.end();
    Intersection closest = intersectionList.front();
    for (; iterr != endd; ++iterr) {
      if (closest.distanceSqu <= iterr->distanceSqu) closest = *iterr;
    }
    *pIntersection = closest;

    //---------------------------------------------------------

    return(numPoints);
}


//-----------------------------------------------------
// clear the scene by removing surfaces
//-----------------------------------------------------
void Scene::Clear(void)
{
    SurfaceList::iterator iter = m_surfaceList.begin();
    SurfaceList::iterator end  = m_surfaceList.end();

    // delete objects
    for (; iter != end; ++iter) {
        delete *iter;
        *iter = NULL;
    }

    // clean up
    m_surfaceList.clear();
}
