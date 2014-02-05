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

Display                     *dpy;
Window                      root;
GLint                       att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo                 *vi;
Colormap                    cmap;
XSetWindowAttributes        swa;
Window                      win;
GLXContext                  glc;
XWindowAttributes           gwa;
XEvent                      xev;
XKeyEvent                   xkev;
KeySym                      key;

Sphere bally(0.5, 0.0625);
//Sphere bally(0.75, 0.5);
Sphere small(0.25, 0.125);
bool keyStates[65536] = {0};
void keyDown(XEvent);
void keyUp(XEvent);
void move();

int main(int argc, char *argv[])
{
    
    bool running = true;
    //small.z = -0.03125;
    dpy = XOpenDisplay(NULL);

    if(dpy == NULL)
    {
        printf("\n\tcannot connect to X server\n\n");
        exit(0);
    }

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy, 0, att);

    if(vi == NULL)
    {
        printf("\n\tno appropriate visual found\n\n");
        exit(0);
    }
    else
    {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid);
    }

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 1024, 1024, 0, vi->depth, InputOutput, vi->visual,
                        CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Remington's Renderer");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    glEnable(GL_DEPTH_TEST);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        float lightpos[] = {0.0, 0.0 , 0.0, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    while(1)
    {
        XNextEvent(dpy, &xev);

        if(xev.type == Expose)
        {
            XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);

            //glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

           glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
            glLightfv(GL_LIGHT0, GL_AMBIENT, BLACK);
            //glLightfv(GL_LIGHT0, GL_DIFFUSE, BLUE);

            glMaterialfv(GL_FRONT, GL_SHININESS, BLING);
            glMaterialfv(GL_FRONT, GL_EMISSION, EMISSION);

            bally.draw();
            if(running)
            {
                small.update();
                //small.draw();
            }

            small.draw();
            
            glXSwapBuffers(dpy, win);

            usleep(500);
         }
         else if(xev.type == KeyPress)
         {
            
            keyDown(xev); 
            //keyUp(xev);

            XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
            

           // glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
            glLightfv(GL_LIGHT0, GL_AMBIENT, BLACK);
            //glLightfv(GL_LIGHT0, GL_DIFFUSE, BLUE); 
            
            glMaterialfv(GL_FRONT, GL_SHININESS, BLING);
            glMaterialfv(GL_FRONT, GL_EMISSION, EMISSION);
            
            bally.draw();
            if(running)
            {
                small.update();
                //small.draw();
            }
            small.draw();
            
            
            glXSwapBuffers(dpy, win);
            
            keyUp(xev);

            //If Esc key is pressed Exit Window
            if(keyStates[XK_Escape] )
            {
                glXMakeCurrent(dpy, None, NULL);
                glXDestroyContext(dpy, glc);
                XDestroyWindow(dpy, win);
                XCloseDisplay(dpy);
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
            //bally.zvel = 0.0;
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
