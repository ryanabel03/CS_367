import javax.media.opengl.*;
import javax.media.opengl.fixedfunc.GLMatrixFunc;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;
import java.awt.event.*;
import java.awt.Point;

public class Bowling extends GLCanvas implements GLEventListener, KeyListener, MouseMotionListener, MouseWheelListener {
    /* SETTINGS */
    final static float KEY_SPEED = 0.2F;
    final static float SCROLL_SPEED = 0.1F;
    final static float MOUSE_SPEED = .003F;

    int pin_list;
    GLU glu;
    float eyeZ, eyeX, eyeY, refZ, refX, refY, upZ, upX, upY;
    float rShade, gShade, bShade;

    public Bowling(GLCapabilities capabilities) {
        super(capabilities);
        glu = new GLU();
        setDefault();

        this.addGLEventListener(this);
        this.addKeyListener(this);
        this.addMouseMotionListener(this);
        this.addMouseWheelListener(this);
    }

    private void setDefault() {
        eyeZ = 5;
        eyeX = 0;
        eyeY = 0;
        refZ = 0;
        refX = 0;
        refY = 0;
        upZ = 0;
        upX = 0;
        upY = 1;
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

        for (float i = 0; i <= 50; i++) {
            gl.glBegin(GL2.GL_TRIANGLE_FAN);/* f1: front */
            theta = (float) (i / 50.0 * 2 * Math.PI);
            x = (float) (radius1 * Math.cos(theta));
            y = (float) (radius1 * Math.sin(theta));
            gl.glColor3f(rShade, gShade, bShade);
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
        gl.glCallList(pin_list); //7
        gl.glTranslatef(.67f,0,0);
        gl.glCallList(pin_list); //8
        gl.glTranslatef(.67f,0,0);
        gl.glCallList(pin_list); //9
        gl.glTranslatef(.67f,0,0);
        gl.glCallList(pin_list); //10
        gl.glTranslatef(-1.67f,-.5f,0);
        gl.glCallList(pin_list); //4
        gl.glTranslatef(.67f,0,0);
        gl.glCallList(pin_list); //5
        gl.glTranslatef(.67f,0,0);
        gl.glCallList(pin_list); //6
        gl.glTranslatef(-1,-.5f,0);
        gl.glCallList(pin_list); //2
        gl.glTranslatef(.67f,0,0);
        gl.glCallList(pin_list); //3
        gl.glTranslatef(-.33f,-.5f,0);
        gl.glCallList(pin_list); //1
        gl.glPopMatrix();
    }

    private void setCamera(GL2 gl) {
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        float widthHeightRatio = (float) getWidth() / (float) getHeight();
        glu.gluPerspective(90, widthHeightRatio, 1, 100);

        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();
        glu.gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ);
    }

    /* KeyListener */
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        switch (keyCode) {
            case KeyEvent.VK_UP:
                eyeY += KEY_SPEED;
                refY += KEY_SPEED;
                break;
            case KeyEvent.VK_DOWN:
                eyeY -= KEY_SPEED;
                refY -= KEY_SPEED;
                break;
            case KeyEvent.VK_LEFT:
                eyeX -= KEY_SPEED;
                refX -= KEY_SPEED;
                break;
            case KeyEvent.VK_RIGHT:
                eyeX += KEY_SPEED;
                refX += KEY_SPEED;
                break;
            case KeyEvent.VK_W:
                refY += KEY_SPEED;
                break;
            case KeyEvent.VK_A:
                refX -= KEY_SPEED;
                break;
            case KeyEvent.VK_S:
                refY -= KEY_SPEED;
                break;
            case KeyEvent.VK_D:
                refX += KEY_SPEED;
                break;
            case KeyEvent.VK_EQUALS:
                eyeZ -= KEY_SPEED;
                refZ -= KEY_SPEED;
                break;
            case KeyEvent.VK_MINUS:
                eyeZ += KEY_SPEED;
                refZ += KEY_SPEED;
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

    /* MouseMotionListener */
    public void mouseDragged(MouseEvent e)
    {
    }

    public void mouseMoved(MouseEvent e)
    {
        Point p = e.getPoint();
        refX = (float)p.getX() * MOUSE_SPEED;
        refY = -(float)p.getY() * MOUSE_SPEED;

        display();
    }

    /* MouseWheelListener */
    public void mouseWheelMoved(MouseWheelEvent e)
    {
        float notches = e.getWheelRotation();
        eyeZ += notches * SCROLL_SPEED;
    }
}