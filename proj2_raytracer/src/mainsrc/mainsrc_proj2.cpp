//--------------------------------------------------------
// Computer Graphics
// University of Florida
// Copyright 2015 Corey Toler-Franklin
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#ifndef GLEW_STATIC
    #define GLEW_STATIC 1
#endif
#include "stglew.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include "Scene.h"
#include "RayTracer.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "defs.h"


// globals
//---------------------------------
// scene
Scene       *pScene = NULL;     // scene geometry and lights
RayTracer   *pRayTracer = NULL; // runs ray tracing algorithm


// mouse
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;

// Window size, kept for screenshots
static int gWindowSizeX = 0;
static int gWindowSizeY = 0;


// Function Prototypes
// TO DO: Proj2 raytracer
// Nothing to do here but note:
// These are not actually used in this
// app unless you were to create a glut
// window loop in the main and add a display callback
// You do not need this but it is available
//--------------------------------------
void MouseMotionCallback(int x, int y);
void MouseCallback(int button, int state, int x, int y);
void KeyCallback(unsigned char key, int x, int y);
void SpecialKeyCallback(int key, int x, int y);
void ReshapeCallback(int w, int h);
void Setup(void);
void EnvironmentMapping(void);









//---------------------------------------------------------------------
// Scene functions
//---------------------------------------------------------------------
// Creates the scene
//
void Setup(void)
{

    // init the scene
    pScene = new Scene();

    // TO DO: Proj2 raytracer
    // Set up your scene.
    // Use the variable pScene to set parameters
    // See Scene.h/cpp for function descriptions that you can call to set these scene parameters
    // 1. change background color
    // 2. add lights - I suggest at least two light and an additional ambient light
    // 3. add objects - e.g. a sphere, a triangle
    // 4. add translation and rotation operations to place objects
    //   (OR make sure you define your objects so they are scene by the camera)
    //------------------------------------------------
    pScene->SetBackgroundColor(RGBR_f(0,0,0,0));
    Light *light1 = new Light(STVector3(1,1,1), RGBR_f(1,1,1,1), "light1");
    pScene->AddLight(*light1);
    Surface *sphere = new Sphere();
    pScene->AddSurface(sphere);
    //------------------------------------------------

    // init a ray tracer object
    pRayTracer = new RayTracer();

}


//
// Reshape the window and record the size so
// that we can use it for screenshots.
//
void ReshapeCallback(int w, int h)
{
	gWindowSizeX = w;
    gWindowSizeY = h;

    glViewport(0, 0, gWindowSizeX, gWindowSizeY);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	// Set up a perspective projection
    float aspectRatio = (float) gWindowSizeX / (float) gWindowSizeY;
	gluPerspective(30.0f, aspectRatio, .1f, 10000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void SpecialKeyCallback(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            pScene->GetCamera()->Strafe(10,0);
            break;
        case GLUT_KEY_RIGHT:
            pScene->GetCamera()->Strafe(-10,0);
            break;
        case GLUT_KEY_DOWN:
            pScene->GetCamera()->Strafe(0,-10);
            break;
        case GLUT_KEY_UP:
            pScene->GetCamera()->Strafe(0,10);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void KeyCallback(unsigned char key, int x, int y)
{

    switch(key) {
    case 's': {
            //
            // Take a screenshot, and save as screenshot.jpg
            //
            STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
            screenshot->Read(0,0);
            screenshot->Save("../../data/images/screenshot.jpg");
            delete screenshot;
        }
        break;
    case 'r':
        pScene->GetCamera()->Reset();
        break;
    case 'u':
        pScene->GetCamera()->ResetUp();
        break;
	case 'q':
		exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}


/**
 * Mouse event handler
 */
void MouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON
        || button == GLUT_RIGHT_BUTTON
        || button == GLUT_MIDDLE_BUTTON)
    {
        gMouseButton = button;
    } else
    {
        gMouseButton = -1;
    }

    if (state == GLUT_UP)
    {
        gPreviousMouseX = -1;
        gPreviousMouseY = -1;
    }
}


/**
 * Mouse active motion callback (when button is pressed)
 */
void MouseMotionCallback(int x, int y)
{
    if (gPreviousMouseX >= 0 && gPreviousMouseY >= 0)
    {
        //compute delta
        float deltaX = x-gPreviousMouseX;
        float deltaY = y-gPreviousMouseY;
        gPreviousMouseX = x;
        gPreviousMouseY = y;

        //orbit, strafe, or zoom
        if (gMouseButton == GLUT_LEFT_BUTTON)
        {
            pScene->GetCamera()->Rotate(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_MIDDLE_BUTTON)
        {
            pScene->GetCamera()->Strafe(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_RIGHT_BUTTON)
        {
            pScene->GetCamera()->Zoom(deltaY);
        }

    } else
    {
        gPreviousMouseX = x;
        gPreviousMouseY = y;
    }

}



// If the commandline input is incorrect, notifies the user.
void usage(const char *myname)
{
    fprintf(stderr, "Usage: %s\nmodes:\n1 Lambertian\n2 Phong\n3 Mirror\n4 Environment Map\n5 Effect_1\n6 Effect_2\n7 Effect_3", myname);
    exit(0);
}


// Parses the input arguments
// The input to the program is a single
// integer value to specify the render mode
RenderMode parseArgs(int argc, char **argv)
{
    if(!(argc == 2))
        usage(argv[0]);

    RenderMode mode = (RenderMode)(atoi(argv[1]));

    if(! ((mode == LAMBERTIAN) ||
        (mode == PHONG) ||
        (mode == MIRROR) ||
        (mode == ENVIRONMENTMAP) ||
        (mode == EFFECT_1) ||
        (mode == EFFECT_2) ||
        (mode == EFFECT_3))) {
            usage(argv[0]);
    }

    return(mode);
}



//-----------------------------------------------
// Proj2 Ray Tracer
// This function follows the main
// logic of your rendering program.
// The commandline input is a single integer that specifies the render mode.
// The render modes are defined in the RenderMode enum in file Defs.h
// Example
// >> proj2_raytracer 1
//
//-----------------------------------------------
int main(int argc, char** argv)
{

    // TO DO: Proj2 raytracer
    // Set the render mode.
    // 1. Here, we read in the render mode.
    //    The render modes are defined in the RenderMode enum in file Defs.h
    //    If you make any changes to RenderMode or input parameters, you have to
    //    update parseArgs(int argc, char **argv).
    //------------------------------------------------
    RenderMode mode = parseArgs(argc, argv);
    //------------------------------------------------

    // Initializes the scene
    Setup();

    // run the ray tracer
    pRayTracer->Run(pScene, "output.png", mode);


    return 0;
}


#pragma endregion
