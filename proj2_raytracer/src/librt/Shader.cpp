//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

#include "Shader.h"
#include <assert.h>
#include "Intersection.h"



Shader::Shader(void)
    : m_mode          (LAMBERTIAN)
{
}


void Shader::SetMode(RenderMode mode)
{
    m_mode = mode;
}


// Runs the shader according to the specified render mode
RGBR_f Shader::Run(Intersection *pIntersection, STVector3 *lightDirection)
{
    RGBR_f color;

    if (pIntersection->isNull()){
      color = RGBR_f(0, 0, 0, 255);
      return color;
    }

    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection);
            break;
        case PHONG:
            color = Phong(pIntersection, lightDirection);
            break;
        default:
            color = Lambertian(pIntersection, lightDirection);
            break;
        }

    // TO DO: Proj2 raytracer
    //          - Add special effects.
    // 1. Add calls to your new special effects function to the switch statement
    // 2. Update the RenderMode structure in def.h to flag these
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 *lightDirection)
{
    assert(pIntersection);
    assert(lightDirection);

    STVector3 normal = pIntersection->normal;
    STVector3 lightDir = *lightDirection;
    RGBR_f color;
    float albedo = .1;

    // TO DO: Proj2 raytracer
    //          - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
    //    normal and light direction
    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------
    float lambert = STVector3::Dot(normal, lightDir);
    color = RGBR_f(0, 255*lambert*albedo, 0, 255);
    //---------------------------------------------------------

    return(color);
}


// Implements diffuse shading using the lambertian lighting model
RGBR_f Shader::Phong(Intersection *pIntersection, STVector3 *lightDirection)
{

    assert(pIntersection);
    assert(lightDirection);

    RGBR_f color;

    // TO DO: Proj2 raytracer
    //          - Add Phong shading.
    // 1. Implement the phong shading equation here
    // 2. Remember to add any attributes you might need for shading to
    //    your surface objects as they are passed in with the pIntersection
    //---------------------------------------------------------
    //---------------------------------------------------------

    return(color);
}


Shader::~Shader()
{
}


// TO DO: Proj2 raytracer
//          - Add shading functions for special effects.
// 1. Declare functions for your special effects in the .h file
// 2. See the Run function to see when each shading function is called
//---------------------------------------------------------
//---------------------------------------------------------
