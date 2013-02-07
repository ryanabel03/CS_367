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

    int pin_list, floor_list, gutter_list, ball_list, lanetop_list;
    GLU glu;
    float eyeZ, eyeX, eyeY, refZ, refX, refY, upZ, upX, upY;
    float rShade, gShade, bShade;

    float radius1, radius2, x, y, z;

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

    private void createLaneTopList(GL2 gl) {
        lanetop_list = gl.glGenLists(1);
        gl.glNewList(lanetop_list, GL2.GL_COMPILE);
        genRectangle(gl,GL2.GL_QUADS,3.14f,2,2);
        gl.glEndList();
    }

    private void createFloorList(GL2 gl) {
        floor_list = gl.glGenLists(1);
        gl.glNewList(floor_list, GL2.GL_COMPILE);
        genRectangle(gl,GL2.GL_QUADS,2.6f,.2f,20);
        gl.glEndList();
    }
    private void createGutterList(GL2 gl) {
        float theta;
        radius1 = .27f;
        gutter_list = gl.glGenLists(1);
        gl.glNewList(gutter_list, GL2.GL_COMPILE);
        gl.glBegin(GL2.GL_QUAD_STRIP);
        for(int i = 0; i <= 50; i++)
        {
            theta = (float) (-i / 50.0 * Math.PI);
            x = (float) (radius1 * Math.cos(theta));
            y = (float) (radius1 * Math.sin(theta));
            gl.glColor3f(.5f, .5f, .5f);
            gl.glVertex3f(x, y*.7f, z-10);

            x = (float) (radius1 * Math.cos(theta));
            y = (float) (radius1 * Math.sin(theta));
            gl.glVertex3f(x, y*.7f, z+10);
        }
        gl.glEnd();
        gl.glEndList();
    }
    private void createPinList(GL2 gl) {
        radius1 = 0.15f;
        radius2 = 0.15f;
        z = 0;
        setDrawBaseColor(.5f, .5f, .5f);

        pin_list = gl.glGenLists(1);
        gl.glNewList(pin_list, GL2.GL_COMPILE);
        genCylinder(gl, GL2.GL_POLYGON, 1, 0, 0, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .01f, .002f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 20, .01f, 0f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 37, .01f, -.0035f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 3, .01f, -.0035f, true, .9f, .1f, .1f, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 4, .01f, 0f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 3, .01f, .0025f, true, .9f, .1f, .1f, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 7, .01f, .0025f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 10, .01f, -.002f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 8, .005f, -.005f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 7, .002f, -.002f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 7, .001f, -.0005f, false, rShade, gShade, bShade, .005f);
        genCylinder(gl, GL2.GL_TRIANGLE_FAN, 1, 0, 0, false, rShade, gShade, bShade, .005f);

        setDrawSettings(0.15f, 0.15f, 0, 0, 0);
        gl.glEndList();
    }

    private void createBallList(GL2 gl) {
        setDrawSettings(.1f, .1f, x, y, z);
        resetShading();
        setDrawBaseColor(0,0,.3f);
        ball_list = gl.glGenLists(1);
        gl.glNewList(ball_list, GL2.GL_COMPILE);

        genCylinder(gl, GL2.GL_TRIANGLE_FAN, 1, 0, 0, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, .003f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, .0019f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, .0010f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, .0005f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, .00025f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, .0000f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, -.00025f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, -.0005f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, -.0010f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, -.0019f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_QUAD_STRIP, 40, .0015f, -.003f, false, rShade, gShade, bShade, .001f);
        genCylinder(gl, GL2.GL_TRIANGLE_FAN, 1, 0, 0, false, rShade, gShade, bShade, .001f);


        gl.glEndList();

    }

    private void createLane(GL2 gl)
    {
        gl.glCallList(gutter_list);
        gl.glTranslatef(1.57f,0,0);
        gl.glCallList(floor_list);
        gl.glTranslatef(1.57f,0,0);
        gl.glCallList(gutter_list);
        gl.glTranslatef(-1.57f,0,0);
        gl.glRotatef(-90,1,0,0);
        gl.glTranslatef(-1,9.5f,0);

        gl.glCallList(pin_list); //7
        gl.glTranslatef(.67f, 0, 0);
        gl.glCallList(pin_list); //8
        gl.glTranslatef(.67f, 0, 0);
        gl.glCallList(pin_list); //9
        gl.glTranslatef(.67f, 0, 0);
        gl.glCallList(pin_list); //10
        gl.glTranslatef(-1.67f, -.5f, 0);
        gl.glCallList(pin_list); //4
        gl.glTranslatef(.67f, 0, 0);
        gl.glCallList(pin_list); //5
        gl.glTranslatef(.67f, 0, 0);
        gl.glCallList(pin_list); //6
        gl.glTranslatef(-1, -.5f, 0);
        gl.glCallList(pin_list); //2
        gl.glTranslatef(.67f, 0, 0);
        gl.glCallList(pin_list); //3
        gl.glTranslatef(-.33f, -.5f, 0);
        gl.glCallList(pin_list); //1
        gl.glTranslatef(0, -6f, 0);
        gl.glCallList(ball_list);
    }

    private void resetShading() {
        rShade = 0;
        gShade = 0;
        bShade = 0;
    }

    private void genRectangle(GL2 gl, int connection, float length, float height, float depth)
    {
        float halfLength = length/2;
        float halfDepth = depth/2;
        gl.glBegin(connection);
        gl.glColor3f(.8f, .7f, .5f);
        //bottom face
        gl.glVertex3f(-halfLength,0,-halfDepth);
        gl.glVertex3f(halfLength,0,-halfDepth);
        gl.glVertex3f(halfLength,0,halfDepth);
        gl.glVertex3f(-halfLength,0,halfDepth);
        //top face
        gl.glVertex3f(-halfLength,-height,-halfDepth);
        gl.glVertex3f(halfLength,-height,-halfDepth);
        gl.glVertex3f(halfLength,-height,halfDepth);
        gl.glVertex3f(-halfLength,-height,halfDepth);
        //front face
        gl.glVertex3f(-halfLength,-height,halfDepth);
        gl.glVertex3f(-halfLength,0,halfDepth);
        gl.glVertex3f(halfLength,0,halfDepth);
        gl.glVertex3f(halfLength,-height,halfDepth);
        //back face
        gl.glVertex3f(-halfLength,-height,-halfDepth);
        gl.glVertex3f(-halfLength,0,-halfDepth);
        gl.glVertex3f(halfLength,0,-halfDepth);
        gl.glVertex3f(halfLength,-height,-halfDepth);
        //left face
        gl.glVertex3f(-halfLength,-height,halfDepth);
        gl.glVertex3f(-halfLength,0,halfDepth);
        gl.glVertex3f(-halfLength,0,-halfDepth);
        gl.glVertex3f(-halfLength,-height,-halfDepth);
        //right face
        gl.glVertex3f(halfLength,-height,halfDepth);
        gl.glVertex3f(halfLength,0,halfDepth);
        gl.glVertex3f(halfLength,0,-halfDepth);
        gl.glVertex3f(halfLength,-height,-halfDepth);
        gl.glEnd();
    }

    private void genCylinder(GL2 gl, int connection, float length, float zScale, float radiusScale,
                             boolean overrideShade, float rColor, float gColor, float bColor,
                             float shadeSpeed)
    {
        float theta;
        for (int i = 0; i <= length; i++) {
            gl.glBegin(connection);
            radius1 = radius2;
            z += zScale;
            shadeIncrement(shadeSpeed);
            if(!overrideShade)
            {
                rColor = rShade;
                gColor = gShade;
                bColor = bShade;
            }
            for (float j = 0; j <= 50; j++) {
                theta = (float) (j / 50.0 * 2 * Math.PI);
                x = (float) (radius1 * Math.cos(theta));
                y = (float) (radius1 * Math.sin(theta));
                gl.glColor3f(rColor, gColor, bColor);
                gl.glVertex3f(x, y, z);

                radius2 = radius1 + radiusScale;
                x = (float) (radius2 * Math.cos(theta));
                y = (float) (radius2 * Math.sin(theta));
                gl.glVertex3f(x, y, z+.01f);
            }
            gl.glEnd();
        }
    }

    private void setDrawBaseColor(float rColor, float gColor, float bColor)
    {
        rShade = rColor;
        gShade = gColor;
        bShade = bColor;
    }

    private void setDrawSettings(float rad1, float rad2, float newX, float newY, float newZ)
    {
        radius1 = rad1;
        radius2 = rad2;
        x = newX;
        y = newY;
        z = newZ;
    }

    private void shadeIncrement(float shadeSpeed)
    {
        rShade += shadeSpeed;
        gShade += shadeSpeed;
        bShade += shadeSpeed;
    }

    private void render(GL2 gl, int width, int height) {
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
        gl.glPushMatrix();
        createLane(gl);
        gl.glTranslatef(2.5f,-2,0);
        gl.glRotatef(-270,1,0,0);
        createLane(gl);
        gl.glTranslatef(2.5f,-2,0);
        gl.glRotatef(-270,1,0,0);
        createLane(gl);
        gl.glPopMatrix();
    }

    private void setCamera(GL2 gl) {
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        float widthHeightRatio = (float) getWidth() / (float) getHeight();
        glu.gluPerspective(60, widthHeightRatio, 1, 100);

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

        createFloorList(gl);
        createGutterList(gl);
        createPinList(gl);
        createBallList(gl);
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
