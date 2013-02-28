/*
 * main.cpp
 *
 *  Created on: 2013-01-21
 *      Author: Hans Dulimarta <dulimarh@cis.gvsu.edu>
 */

#define GL_GLEXT_PROTOTYPES
// The following #define may be required to enable glWindowPos2i
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

glm::vec4 light0_pos (2, 1.4, 1.5, 1);
float light0_diff[] = {1.0, 0.9, 0.05, 1};
float light1_diff[] = {1.0, 1.0, 1.0, 1.0};
float light1_spec[] = {1.0, 0.9, 0.3, 1.0};
glm::mat4 camera_cf, pot_cf, spotlite_cf;

float box_color[] = {0.5, 0.3, 0.0, 1.0};
float material_ambi[] = {195.0/255, 107.0/255, 41.0/255, 1};
float material_diff[] = {0.67, 0.76, 0.36, 1};
float material_spec[] = {0.8, 0.8, 0.0, 1};
float material_none[] = {0.0f, 0.0f, 0.0f , 1.0f};
//float material_emit[] = {0.6, 0.0, 0.0, 1.0};
float teapot_color[] = {0.667, 0.7647, 0.3607, 1.0};

int WIN_HEIGHT;
vector<int> win_ids;
float bgColor[3];
map<int,int> potlist, cf_list, arrow_list, spotlite_list;
//bool use_color_material;
bool in_help_mode = false;
bool show_ambient, show_diffuse, show_specular;
float spot_cutoff = 20;
int selected_light = 0;
GLUquadric* qObj;
void show_help();
void show_text(int, int, const string&);

/********************************************************************/
// Display callback
/********************************************************************/
void render_main()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

void render_scene(const string& title, bool use_ambi, bool use_diff, bool use_spec,
                  bool show_cf)
{
    int win_id = glutGetWindow();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (in_help_mode && win_id == win_ids[1]) {
        show_help();
    }
    else
        show_text (10, 10, title);

    glLightfv(GL_LIGHT0, GL_POSITION, &light0_pos[0]);
    glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(glm::column(spotlite_cf, 3)));
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, &glm::column(spotlite_cf, 2)[0]);

    if (show_cf) {
        glPushAttrib(GL_LIGHTING_BIT);
        glEnable(GL_COLOR_MATERIAL);
        /* use the arrow color as the material property */
        glCallList(cf_list[win_id]);
        glPopAttrib();
    }

    if (glIsEnabled(GL_LIGHT0)) {
        glPushMatrix();
        glPushAttrib(GL_LIGHTING_BIT);
        /* use the light source diffuse component as its emissive light */
        glMaterialfv(GL_FRONT, GL_EMISSION, light0_diff);
        glTranslatef(light0_pos[0], light0_pos[1], light0_pos[2]);
        glutSolidSphere(0.04, 20, 12);
        glPopAttrib();
        glPopMatrix();
    }
    glMaterialfv (GL_FRONT, GL_AMBIENT, use_ambi ? material_ambi : material_none);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, use_diff ? material_diff : material_none);
    glMaterialfv (GL_FRONT, GL_SPECULAR, use_spec ? material_spec : material_none);
    glMaterialf (GL_FRONT, GL_SHININESS, 127);  /* 0-127 */

    if (glIsEnabled(GL_LIGHT1)) {
        glPushMatrix();
        glMultMatrixf (&spotlite_cf[0][0]);
        glCallList(spotlite_list[win_id]);
        glPopMatrix();
    }

    /* render the teapot */
    glPushMatrix();
    glMultMatrixf(&pot_cf[0][0]);
    glCallList(potlist[win_id]);
    glPopMatrix();

    /* render the base */
    glPushAttrib(GL_LIGHTING_BIT);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glTranslatef (0.0f, 0.0f, -.7f);
    glScalef(3.0f, 3.0f, 0.1f);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor3ub (156, 60, 12);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor3ub (0, 0, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopAttrib();

	glutSwapBuffers();
}

void render_all()
{
    render_scene("h: help", show_ambient, show_diffuse, show_specular, true);
}

void render_ambi()
{
    glClearColor(.2, .2, .2, 0.0);
    render_scene("Ambient only", true, false, false, false);
}

void render_diff()
{
    glClearColor(.2, .2, .2, 0.0);
    render_scene("Diffuse only", false, true, false, false);
}

void render_spec()
{
    glClearColor(.2, .2, .2, 0.0);
    render_scene("Specular only", false, false, true, false);
}

void show_help()
{
    static string help_text[] = {
        "0/1: toggle light source",
        "F1/F2: select active light source",
        "x/X/y/Y/z/Z : move the active light source",
        "a/d/s: toggle ambient/diffuse/specular", 
        "p/P: adjust the pan angle of the spotlight",
        "t/T: adjust the tilt angle of the spotlight",
        "Esc: quit"
    };

    const int N = sizeof(help_text) / sizeof(string);
    const int HEIGHT = 20;
    for (int k = 0; k < N; k++) {
        show_text (5, (N - k) * HEIGHT, help_text[k]);
    }
}


/********************************************************************/
// Resize callback
/********************************************************************/
void subresize (int w, int h)
{
    WIN_HEIGHT = h;
	glViewport(0, 0, (GLint) w, (GLint) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(60, (float)w/h, 0.5, 50);

    /* always switch back to MODEVLVIEW matrix mode !!!! */
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
    /* use the default camera placement: eye at origin, 
       the camera is pointed along the NEGATIVE z-axis, 
       and the camera Y-axis (its "up" axis) is parallel to the world Y-axis
     */
    gluLookAt(5, 2.0, 1.5,
              0, 0, 0,
              0, 0, 1);
}

void resize (int w, int h)
{
    glutSetWindow(win_ids[1]);
    glutPositionWindow(0, 0);
    glutReshapeWindow(3*w/4, h);
    subresize(3*w/4, h);

    glutSetWindow(win_ids[2]);
    glutPositionWindow(3*w/4, 0);
    glutReshapeWindow(w/4, h/3);
    subresize(w/4, h/3);

    glutSetWindow(win_ids[3]);
    glutPositionWindow(3*w/4, h/3);
    glutReshapeWindow(w/4, h/3);
    subresize(w/4, h/3);

    glutSetWindow(win_ids[4]);
    glutPositionWindow(3*w/4, 2*h/3);
    glutReshapeWindow(w/4, h/3);
    subresize(w/4, h/3);
}

/********************************************************************/
// Keyboard callback
/********************************************************************/
void keyHandler (unsigned char ch, int x, int y)
{
//    cout << glutGetModifiers() << endl;
    switch (ch)
    {
        case 0x1B: /* escape key */
            exit (0);
            break;
        case '0':
            if (glIsEnabled(GL_LIGHT0))
                glDisable(GL_LIGHT0);
            else
                glEnable(GL_LIGHT0);
            break;
        case '1':
            if (glIsEnabled(GL_LIGHT1))
                glDisable(GL_LIGHT1);
            else
                glEnable(GL_LIGHT1);
            break;
        case 'a': /* toggle show ambient */
            show_ambient ^= true;
            break;
        case 'd': /* toggle show diffuse */
            show_diffuse ^= true;
            break;
        case 's': /* toggle show specular */
            show_specular ^= true;
            break;
        case 'h':
            in_help_mode ^= true;
            break;
        case 'p': /* pan the spotlight */
            spotlite_cf = glm::rotate(spotlite_cf, +10.0f, 1.0f, 0.0f, 0.0f);
            break;
        case 'P':
            spotlite_cf = glm::rotate(spotlite_cf, -10.0f, 1.0f, 0.0f, 0.0f);
            break;
        case 't':
            spotlite_cf = glm::rotate(spotlite_cf, +10.0f, 0.0f, 1.0f, 0.0f);
            break;
        case 'T':
            spotlite_cf = glm::rotate(spotlite_cf, -10.0f, 0.0f, 1.0f, 0.0f);
            break;
        default:
            if (selected_light == 0)
            {
                switch (ch) {
                    case 'x':
                    case 'y':
                    case 'z':
                        light0_pos[ch - 'x'] -= 0.2;
                        break;
                    case 'X':
                    case 'Y':
                    case 'Z':
                        light0_pos[ch - 'X'] += 0.2;
                        break;
                }
            }
            else {
                switch (ch) {
                    case 'x':
                    case 'y':
                    case 'z':
                        spotlite_cf[3][ch - 'x'] -= 0.2;
                        break;
                    case 'X':
                    case 'Y':
                    case 'Z':
                        spotlite_cf[3][ch - 'X'] += 0.2;
                        break;

                    default:
                        break;
                }
            }
    }
    for (int k = 0; k < win_ids.size(); k++)
    {
        glutSetWindow(win_ids[k]);
        glutPostRedisplay();
    }
}

/* Default Teapot orientation:
 * The spout is facing towards the positive-X
 * The axis of the teapot body is the Z-axis
 */
void fkeyHandler (int key, int x, int y)
{
    if (key == GLUT_KEY_F12)
        exit(0);
    int mod = glutGetModifiers();
    if (mod == GLUT_ACTIVE_SHIFT) {
        switch (key) {
            case GLUT_KEY_UP: /* pitch-down */
                pot_cf = glm::rotate(pot_cf, -20.0f, 0.0f, 0.0f, 1.0f);
                break;
            case GLUT_KEY_DOWN: /* pitch-uo */
                pot_cf = glm::rotate(pot_cf, +20.0f, 0.0f, 0.0f, 1.0f);
                break;
            case GLUT_KEY_LEFT:
                pot_cf = glm::rotate(pot_cf, +20.0f, 0.0f, 1.0f, 0.0f);
                break;
            case GLUT_KEY_RIGHT:
                pot_cf = glm::rotate(pot_cf, -20.0f, 0.0f, 1.0f, 0.0f);
                break;
        }
    }
    else {
        switch (key) {
            case GLUT_KEY_F1:
                selected_light = 0;
                break;
            case GLUT_KEY_F2:
                selected_light = 1;
                break;
                
            case GLUT_KEY_UP: /* move forward */
                /* multiply the teapot frame with X-translate */
                pot_cf = glm::translate(pot_cf, 0.5f, 0.0f, 0.0f);
                break;
            case GLUT_KEY_DOWN: /* move backward */
                pot_cf = glm::translate(pot_cf, -0.5f, 0.0f, 0.0f);
                break;
            case GLUT_KEY_LEFT:   /* roll */
                pot_cf = glm::rotate(pot_cf, -20.0f, 1.0f, 0.0f, 0.0f);
                break;
            case GLUT_KEY_RIGHT:  /* roll */
                pot_cf = glm::rotate(pot_cf, +20.0f, 1.0f, 0.0f, 0.0f);
                break;
        }

    }
    for (int k = 0; k < win_ids.size(); k++)
    {
        glutSetWindow(win_ids[k]);
        glutPostRedisplay();
    }
}

void show_text (int x, int y, const string& msg)
{
    /* color must be set BEFORE glWindowPos* !!!!! */
    glColor3f(1,1,1); /* white text */
    /* Use the window coordinates to place the text */
    string m = msg;
#ifdef GL_VERSION_1_5
    glWindowPos2i(x, y);
#else
    m = "Your OpenGL is older than 1.5: " + msg;
#endif
    for (int k = 0; k < m.length(); k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[k]);
}

/********************************************************************/
// Initialization routines
/********************************************************************/
void initStates()
{
    fill (bgColor, bgColor + 3, 0.0);
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);

    glLineWidth(2.0);
    glPointSize(3.0);

    /* render front polygons (CCW) as filled faces */
    glPolygonMode(GL_FRONT, GL_FILL);

    /* render back polygon (CW) as outline */
//    glPolygonMode(GL_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

    glEnable(GL_LIGHT1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
    /* the default of other light sources is BLACK, so we must set its
       properties */
    glLightfv(GL_LIGHT1, GL_DIFFUSE, &light1_diff[0]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, &light1_spec[0]);
    /* enable automatic renormalization of normal vectors */
    glEnable(GL_NORMALIZE);
//    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    show_ambient = show_diffuse = show_specular = true;
}

void initModels()
{
    int win_id = glutGetWindow();
    /* setup the axes */
    arrow_list[win_id] = glGenLists(1);
    glNewList(arrow_list[win_id], GL_COMPILE);
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glScalef(2.0, .06, .06);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, 2.0);
    glutSolidCone(.15, 0.4, 20, 2);
    glPopMatrix();
    glEndList();

    cf_list[win_id] = glGenLists(1);
    glNewList(cf_list[win_id], GL_COMPILE);
    /* draw the x-axis in red */
    glColor3ub(255,0,0);
    glCallList(arrow_list[win_id]);
    /* draw the y-axis in green */
    glColor3ub(0, 255, 0);
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glCallList(arrow_list[win_id]);
    glPopMatrix();

    /* draw the z-axis in blue */
    glColor3ub(18, 168, 212);
    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glCallList(arrow_list[win_id]);
    glPopMatrix();
    glEndList();

    /* Setup the teapot */
    pot_cf = glm::rotate(90.0f, 1.0f, 0.0f, 0.0f);
    pot_cf = glm::rotate(pot_cf, 90.0f, 0.0f, 1.0f, 0.0f);
    potlist[win_id] = glGenLists(1);
    glNewList(potlist[win_id], GL_COMPILE);
    glutSolidTeapot(1.0);
    glEndList();

    /* setup the spotlite cone and coordinate frame */
    qObj = gluNewQuadric();
    /* create a display list for the spot light */
    spotlite_list[win_id] = glGenLists(1);
    glNewList(spotlite_list[win_id],GL_COMPILE);
    glCallList(cf_list[win_id]);
    const float CONE_HEIGHT = 1.0f;
    gluCylinder(qObj, 0, CONE_HEIGHT * tan(spot_cutoff * M_PI/180.0),
                CONE_HEIGHT, 20, 5);
    glEndList();

    spotlite_cf = glm::translate(2, -2, 2);
    spotlite_cf = glm::rotate(spotlite_cf, -130.0f, 0.0f, 1.0f, 0.0f);
    spotlite_cf = glm::rotate(spotlite_cf, -30.0f, 1.0f, 0.0f, 0.0f);

}

void cleanup()
{
    gluDeleteQuadric(qObj);
}

int main (int argc, char** argv)
{
    atexit(cleanup);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
    /* The desired layout: one larger subwindow on the left side
     * of the window that fills the entire height and three
     * smaller subwindows stacked vertically on the right 
     * To create a 4:3 aspect for all the subwindows, the entire
     * window must have a 16:9 aspect ratio.
     */
    glutInitWindowSize (1280, 720);
    win_ids.push_back(glutCreateWindow("Local Lighting Model"));
    /* setup callback functions */
    glutDisplayFunc(render_main);
    glutReshapeFunc(resize);

    /* initial setup */
    initStates();

    win_ids.push_back(glutCreateSubWindow(win_ids[0], 0, 0, 960, 720));
    glutDisplayFunc(render_all);
    glutKeyboardFunc(keyHandler);
    glutSpecialFunc(fkeyHandler);
    initStates();
    initModels();

    win_ids.push_back(glutCreateSubWindow(win_ids[0], 720, 0, 320, 240));
    glutDisplayFunc(render_ambi);
    initStates();
    initModels();

    win_ids.push_back(glutCreateSubWindow(win_ids[0], 720, 240, 320, 240));
    glutDisplayFunc(render_diff);
    initStates();
    initModels();

    win_ids.push_back(glutCreateSubWindow(win_ids[0], 720, 480, 320, 240));
    glutDisplayFunc(render_spec);
    initStates();
    initModels();

    glutSetWindow(win_ids[1]);
    glutMainLoop();
}



