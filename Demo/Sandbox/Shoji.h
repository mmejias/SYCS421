//Oh you thought I downloaded this.
//Nope, a custom header for all your windowing needs on Linux
//BAKOW
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <unistd.h>

class Shoji
{
    public:
       Shoji();
       Shoji(int, int);
       XEvent getEvent();
       void View();
       void Initialize();
       void Draw();
       void Close();
       void Buffer();
    private:
       int width, height;
       Display*                 dpy;
       Window                   root;
       GLint*                   att;
       XVisualInfo*             vi;
       Colormap                 cmap;
       XSetWindowAttributes     swa;
       Window                   win;
       GLXContext               glc;
       XWindowAttributes        gwa;
       XEvent                   xev;
};

Shoji::Shoji()
{
    width = 1000;
    height = 1000;
    att = new GLint[5];
    att[0] = GLX_RGBA;
    att[1] = GLX_DEPTH_SIZE;
    att[2] = 24;
    att[3] = GLX_DOUBLEBUFFER;
    att[4] = None;
    //{ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
}

Shoji::Shoji(int m_width, int m_height)
{
    width = m_width;
    height = m_height;
}

XEvent Shoji::getEvent()
{
    return xev;
}

void Shoji::View()
{ 
    XGetWindowAttributes(dpy, win, &gwa);
    glViewport(0, 0, gwa.width, gwa.height);
}

void Shoji::Initialize()
{
    dpy = XOpenDisplay(NULL);
    if(dpy == NULL)
    {
        printf("\n\tcannot connect to X Server\n\n");
        printf("Bee Boop...Closing program\n");
        exit(0);
    }
    root = DefaultRootWindow(dpy);
    vi = glXChooseVisual(dpy, 0, att);
    
    if(vi == NULL)
    {
        printf("\n\tNo appropriate visual found\n\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid);
    }

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
                        CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Remington's Window");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

}

void Shoji::Draw()
{
    XNextEvent(dpy, &xev);

    //XGetWindowAttributes(dpy, win, &gwa);
    //glViewport(0, 0, gwa.width, gwa.height);
    
    //glXSwapBuffers(dpy, win);

    //Draw, View, Spheres, Buffer 
}

void Shoji::Close()
{
    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, glc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    exit(EXIT_SUCCESS);
}

void Shoji::Buffer()
{
    glXSwapBuffers(dpy, win);
    usleep(500);
}
