#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <cmath>

float s_array[3] = {1};
float m_array[] = {1, 0, 0};
float d_array[3] = {0};
float shiny[] = {64}; //Shiny, captain, Shiny!
float emission[] = {0.0, 0.0, 0.0, 0.0};

float green[] = {0, 1, 0};
float blue[] = {0, 0, 1};
float yellow[] = {1.0, 1.0, 0.0};
float orange[] = {1.0, 0.4, 0.0};
float indigo[] = {0.4, 0.0, 0.4};
float violet[] = {0.4, 0.0, 1.0};

#define WHITE s_array
#define RED m_array
#define BLACK d_array
//#define WHITE_DIFFUSE w_array
#define BLING shiny

#define BLUE blue
#define YELLOW yellow
#define ORANGE orange
#define INDIGO indigo
#define EMISSION emission
#define VIOLET violet

class Sphere
{
    public:
        float x, y, z, radius;
        float xvel, yvel, zvel;
        float resol;
        int stacks;
        int slices;
        Sphere();
        Sphere(float, float);
        Sphere(double, int, int);
        void draw();
        void update();
};

Sphere::Sphere()
{
    x = y = z = 0.0;
    radius = 0.5;
    resol = 0.25;
}

Sphere::Sphere(float m_radius, float m_resol)
{
    x = y = z = 0.0;
    radius = m_radius;
    resol = m_resol;
}

Sphere::Sphere(double m_radius, int m_slices, int m_stacks)
{
    radius = m_radius;
    slices = m_slices;
    stacks = m_stacks;
    x = y = z = 0.0;
}

void Sphere::draw()
{
    float xx, yy, zz;
    float xxp, yyp, zzp;
    glPushMatrix();
    glScalef(radius, radius, radius);  
    glTranslatef(x, y, z);
//        glNormal3d(0, 0, 1);
    for(float angle2 = -3.1416/2; angle2 <= 3.1416/2; angle2 += resol)
    {
        //Builds the sphere by layering (kind of like a 3D printer)
        glBegin(GL_TRIANGLE_STRIP);
        glLoadIdentity();
        //Points direction of lighting 
        for(float angle1 = 0.0; angle1 <= 3.1416*2.0+resol; angle1 += resol)
        {
            yy = sin(angle2);
            xx = cos(angle1)*cos(angle2);
            zz = sin(angle1)*cos(angle2);
            
            yyp = sin(angle2 + resol);
            xxp = cos(angle1)*cos(angle2 + resol);
            zzp = sin(angle1)*cos(angle2 + resol);
           
        glNormal3d(0, 0, 1);
            glVertex3f(xx, yy, zz);
            glVertex3f(xxp, yyp, zzp);
        }
        glEnd();
    }
        
    glPopMatrix();
}

void Sphere::update()
{
    x += sin(x);
    y +=  cos(y);
    z +=  sin(z);
    glRotatef(1, 0, 0, 1);
    //z = z + zvel;
}
