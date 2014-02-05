//followed: www.opengl.org/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib
//followed: cs.lmu.edu/~ray/notes/openglexamples/
//followed: www.youtube.com/watch?v=gBlk-14SIMI
//OpenGL (GLX) in C/Linux Tutorial #005 - Creating Simple Sphere Youtube
//followed: www.sbin.org/doc/Xlib/chapt_09.html     KeyboardInput
//followed: www.swiftless.com/tutorials/opengl/material_lighting.html
//followed: www.cse.msu.edu/~cse872/tutorial3.html

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <unistd.h>
#include "Geometry.h"
#include "Shoji.h"

Shoji shoji;
Sphere bally(0.5, 0.0625);
Sphere small(0.25, 0.125);

bool keyStates[65536] = {0};
void keyDown(XEvent);
void keyUp(XEvent);
void update();
void move();
void initialize();
void draw();

int main(int argc, char *argv[])
{
    
    initialize(); 

    while(1)
    {
        shoji.Draw();

        if(shoji.getEvent().type == Expose)
        {
            draw();
            usleep(500);
        }
        else if(shoji.getEvent().type == KeyPress)
        {
            keyDown(shoji.getEvent());
            update();
            draw();
            usleep(500);
            if(keyStates[XK_Escape] )
            {
                shoji.Close();
                exit(0);
            }
        }
    }


    return 0;
}

void keyDown(XEvent keyEvent)
{
    switch(XLookupKeysym(&keyEvent.xkey, 0))
    {
        case XK_Escape:
            keyStates[XK_Escape] = true;
            //printf("KeyDown Escape\n");
            break;
        case XK_Left:
            keyStates[XK_Left] = true;
            //printf("KeyDown Left\n");
            break;
        case XK_Right:
            keyStates[XK_Right] = true;
            //printf("KeyDown Right\n");
            break;
        case XK_Up:
            keyStates[XK_Up] = true;
            //printf("KeyDown Up\n");
            break;
        case XK_Down:
            keyStates[XK_Down] = true;
            //printf("KeyDown Down\n");
            break;
        //Increase Z position
        case XK_a:
        case XK_A:
            keyStates[XK_a] = true;
            keyStates[XK_A] = true;
            break;
        //Decrease Z position
        case XK_d:
        case XK_D:
            keyStates[XK_d] = true;
            keyStates[XK_D] = true;
            break;
    }
    move();
}

void keyUp(XEvent keyEvent)
{

    switch(XLookupKeysym(&keyEvent.xkey, 0))
    {
        case XK_Left:
            keyStates[XK_Left] = false;
            break;
        case XK_Right:
            keyStates[XK_Right] = false;
            break;
        case XK_Up:
            keyStates[XK_Up] = false;
            break;
        case XK_Down:
            keyStates[XK_Down] = false;
            break;
        case XK_a:
        case XK_A:
            keyStates[XK_a] = false;
            keyStates[XK_A] = false;
            //bally.zvel = 0.0;
            break;
        //Decrease Z position
        case XK_d:
        case XK_D:
            keyStates[XK_d] = false;
            keyStates[XK_D] = false;
    }
}


void move()
{
    float max_vel = 0.03125;
    if(keyStates[XK_Left])
    {
        bally.x = bally.x-0.03125;
        //bally.xvel = -max_vel;
    }
    if(keyStates[XK_Right])
    {
        bally.x = bally.x+0.03125;
        //bally.xvel = max_vel;
    }
    if(keyStates[XK_Up])
    {
        bally.y = bally.y + 0.03125;
        //bally.yvel = max_vel;
    }
    if(keyStates[XK_Down])
    {
        bally.y = bally.y - 0.03125;
        //bally.yvel = -max_vel;
    }
    if(keyStates[XK_a] || keyStates[XK_A])
    {
        bally.z = bally.z + 0.03125;
        bally.radius+=0.03125;
        //bally.zvel = max_vel;
    }
    if(keyStates[XK_d] || keyStates[XK_D])
    {
        bally.z = bally.z - 0.03125;
        bally.radius -= 0.03125;
        //bally.zvel = -max_vel;
    }

}

void initialize()
{
    shoji.Initialize();

    glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        float lightpos[] = {0.0, 0.0 , 0.0, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

}

void draw()
{
    shoji.View();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, BLACK);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, BLUE);

    glMaterialfv(GL_FRONT, GL_SHININESS, BLING);
    glMaterialfv(GL_FRONT, GL_EMISSION, EMISSION);

    bally.draw();
    small.draw();
    
    shoji.Buffer();
}

void update()
{
    small.update();
}
