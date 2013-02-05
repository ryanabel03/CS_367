import com.jogamp.opengl.util.awt.TextRenderer;

import java.awt.Font;

import javax.media.opengl.*;
import javax.media.opengl.fixedfunc.GLMatrixFunc;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Bowling extends GLCanvas implements GLEventListener, KeyListener {
    final static float UNIT = 0.2F;
    int pin_list;
    GLU glu;
    float z, x, y, refz, refx, refy;
    float rShade, gShade, bShade;

    public Bowling(GLCapabilities capabilities) {
        super(capabilities);
        glu = new GLU();
        setDefault();

        this.addGLEventListener((GLEventListener) this);
        this.addKeyListener(this);
    }

    private void setDefault() {
        z = 3;
        x = 0;
        y = 0;
        refz = 0;
        refx = 0;
        refy = 0;
    }

    private void createPinList(GL2 gl) {
        float theta, radius1, radius2, x, y, z;
        radius1 = 0.15f;
        radius2 = 0.15f;
        z = 0;

        pin_list = gl.glGenLists(1);
        gl.glNewList(pin_list, GL2.GL_COMPILE);
        gl.glBegin(GL2.GL_POLYGON);
        for (float i = 0; i <= 50; i++) {
            theta = (float) (i / 50.0 * 2 * Math.PI);
            x = (float) (radius1 * Math.cos(theta));
            y = (float) (radius1 * Math.sin(theta));
            gl.glColor3f(rShade, gShade, bShade);
            gl.glVertex3f(x, y, z);
        }
        gl.glEnd();

        for (float i = 0; i <= 40; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .01f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 + .002f;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 20; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .01f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                gl.glVertex3f(x, y, z);

                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 40; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .01f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                if(i > 37)
                    gl.glColor3f(0.9f,0.1f,0.1f);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 - .0035f;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 4; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .01f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                gl.glVertex3f(x, y, z);

                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 10; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .01f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                if(i < 3)
                    gl.glColor3f(0.9f,0.1f,0.1f);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 + .0025f;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 10; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .01f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 - .002f;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 8; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .005f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 - .005f;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 7; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .002f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 - .002f;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        for (float i = 0; i <= 7; i++) {
            gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
            radius1 = radius2;
            z += .001f;
            shadeIncrement();
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rShade, gShade, bShade);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 - .0005f;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }

        gl.glColor3f(rShade, gShade, bShade);
        for (float i = 0; i <= 50; i++) {
            theta = (float) (i / 50.0 * 2 * Math.PI);
            x = (float) (radius1 * Math.cos(theta));
            y = (float) (radius1 * Math.sin(theta));
            gl.glVertex3f(x, y, z);
        }
        gl.glEnd();

        gl.glEndList();
    }

    private void shadeIncrement()
    {
        rShade += .007f;
        gShade += .007f;
        bShade += .007f;
    }

    private void render(GL2 gl, int width, int height) {
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
        gl.glPushMatrix();
        gl.glTranslatef(0,-1,0);
        gl.glRotatef(-90,1,0,0);
        gl.glCallList(pin_list);
        gl.glTranslatef(1,0,0);
        gl.glCallList(pin_list);
        gl.glTranslatef(1,0,0);
        gl.glCallList(pin_list);
        gl.glTranslatef(-1.33f,-1,0);
        gl.glCallList(pin_list);
        gl.glTranslatef(0.67f,0,0);
        gl.glCallList(pin_list);
        gl.glPopMatrix();
    }

    private void setCamera(GL2 gl) {
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        float widthHeightRatio = (float) getWidth() / (float) getHeight();
        glu.gluPerspective(90, widthHeightRatio, 1, 100);

        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();
        glu.gluLookAt(x, y, z, refx, refy, refz, 0, 1, 0);
    }

    /* KeyListener */
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        switch (keyCode) {
            case KeyEvent.VK_UP:
                y += UNIT;
                refy += UNIT;
                break;
            case KeyEvent.VK_DOWN:
                y -= UNIT;
                refy -= UNIT;
                break;
            case KeyEvent.VK_LEFT:
                x -= UNIT;
                refx -= UNIT;
                break;
            case KeyEvent.VK_RIGHT:
                x += UNIT;
                refx += UNIT;
                break;
            case KeyEvent.VK_W:
                refy += UNIT;
                break;
            case KeyEvent.VK_A:
                refx -= UNIT;
                break;
            case KeyEvent.VK_S:
                refy -= UNIT;
                break;
            case KeyEvent.VK_D:
                refx += UNIT;
                break;
            case KeyEvent.VK_EQUALS:
                z -= UNIT;
                break;
            case KeyEvent.VK_MINUS:
                z += UNIT;
                break;
            case KeyEvent.VK_1:
                z += UNIT;
                refz += UNIT;
                break;
            case KeyEvent.VK_2:
                z -= UNIT;
                refz -= UNIT;
                break;
            case KeyEvent.VK_R:
                setDefault();
                break;
        }
        display();
    }

    public void keyReleased(KeyEvent e) {
    }

    public void keyTyped(KeyEvent e) {
    }

    /* GLEventListener */
    public void init(GLAutoDrawable glAutoDrawable) {
        GL2 gl = glAutoDrawable.getGL().getGL2();

        gl.glEnable(GL.GL_DEPTH_TEST);
        gl.glDepthFunc(GL.GL_LEQUAL);

        createPinList(gl);
    }

    public void dispose(GLAutoDrawable glAutoDrawable) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public void display(GLAutoDrawable glAutoDrawable) {
        GL2 gl = glAutoDrawable.getGL().getGL2();
        setCamera(gl);
        render(gl, glAutoDrawable.getWidth(), glAutoDrawable.getHeight());
    }

    public void reshape(GLAutoDrawable glAutoDrawable, int i, int i2, int width, int height) {
        GL2 gl = glAutoDrawable.getGL().getGL2();
        gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
        gl.glLoadIdentity();
    }
}