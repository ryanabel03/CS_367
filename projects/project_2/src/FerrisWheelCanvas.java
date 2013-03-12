import com.jogamp.opengl.util.Animator;

import javax.media.opengl.*;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.fixedfunc.GLLightingFunc;
import javax.media.opengl.fixedfunc.GLMatrixFunc;
import javax.media.opengl.glu.GLU;
import java.awt.*;
import java.awt.event.*;

public class FerrisWheelCanvas extends GLCanvas implements GLEventListener, KeyListener, MouseMotionListener, MouseWheelListener {
    /* SETTINGS */
    final static float KEY_SPEED = 0.5F;
    final static float SCROLL_SPEED = 0.3F;
    final static float MOUSE_SPEED = .01F;
    final static int NUM_CHAIRS = 6;

    private double rotateSpeed;
    private boolean wireframeOn;
    private GLU glu;
    private GL2 gl;
    private Animator animator;

    private float eyeZ, eyeX, eyeY, refZ, refX, refY, upZ, upX, upY;

    private Chairs chairs;
    private Wheel wheel;
    private Frame frame;
    private int chairList, wheelList, frameList;

    private double currentRotationAngle = 0;
    private double previousChairAngle = 0;
    private double previousChairPosition = 0;
    private boolean swingDirection = true;

    private boolean lightZeroEnabled = false;
    private boolean lightOneEnabled = false;
    private float[] lightZeroPos;

    //chrome
    private float[] chromeDiffuse, chromeAmbient, chromeSpecular, chromeShiny;
    private float[][] chrome;

    //polished gold
    private float[] pGoldDiffuse, pGoldAmbient, pGoldSpecular, pGoldShiny;
    private float[][] pGold;

    //emerald
    private float[] emeraldDiffuse, emeraldAmbient, emeraldSpecular, emeraldShiny;
    private float[][] emerald;

    //ruby
    private float[] rubyDiffuse, rubyAmbient, rubySpecular, rubyShiny;
    private float[][] ruby;

    //turquoise
    private float[] turquoiseDiffuse, turquoiseAmbient, turquoiseSpecular, turquoiseShiny;
    private float[][] turquoise;

    public FerrisWheelCanvas(GLCapabilities capabilities) {
        super(capabilities);
        glu = new GLU();
        setDefault();

        this.addGLEventListener(this);
        this.addKeyListener(this);
        this.addMouseMotionListener(this);
        this.addMouseWheelListener(this);

        animator = new Animator(this);
        animator.add(this);
        animator.start();

        setMaterialColors();
    }

    private void setMaterialColors() {
        chromeDiffuse = new float[]{0.25f, 0.25f, 0.25f, 1};
        chromeAmbient = new float[]{0.4f, 0.4f, 0.4f, 1};
        chromeSpecular = new float[]{0.774597f, 0.774597f, 0.774597f, 1};
        chromeShiny = new float[]{76.800003f};
        chrome = new float[][]{chromeDiffuse, chromeAmbient, chromeSpecular, chromeShiny};

        pGoldDiffuse = new float[]{0.24725f, 0.2245f, 0.0645f, 1};
        pGoldAmbient = new float[]{0.34615f, 0.3143f, 0.0903f, 1};
        pGoldSpecular = new float[]{0.797357f, 0.723991f, 0.208006f, 1};
        pGoldShiny = new float[]{83.199997f};
        pGold = new float[][]{pGoldDiffuse, pGoldAmbient, pGoldSpecular, pGoldShiny};

        emeraldDiffuse = new float[]{0.0215f, 0.1745f, 0.0215f, 0.55f};
        emeraldAmbient = new float[]{0.07568f, 0.61424f, 0.07568f, 0.55f};
        emeraldSpecular = new float[]{0.633f, 0.727811f, 0.633f, 0.55f};
        emeraldShiny = new float[]{76.800003f};
        emerald = new float[][]{emeraldDiffuse, emeraldAmbient, emeraldSpecular, emeraldShiny};

        rubyDiffuse = new float[]{0.1745f, 0.01175f, 0.01175f, 0.55f};
        rubyAmbient = new float[]{0.61424f, 0.04136f, 0.04136f, 0.55f};
        rubySpecular = new float[]{0.727811f, 0.626959f, 0.626959f, 0.55f};
        rubyShiny = new float[]{76.800003f};
        ruby = new float[][]{rubyDiffuse, rubyAmbient, rubySpecular, rubyShiny};

        turquoiseDiffuse = new float[]{0.1f, 0.18725f, 0.1745f, 0.8f};
        turquoiseAmbient = new float[]{0.396f, 0.74151f, 0.69102f, 0.8f};
        turquoiseSpecular = new float[]{0.297254f, 0.30829f, 0.306678f, 0.8f};
        turquoiseShiny = new float[]{12.8f};
        turquoise = new float[][]{turquoiseDiffuse, turquoiseAmbient, turquoiseSpecular, turquoiseShiny};
    }

    private void initializeModels() {
        initializeLights();
        wheel = new Wheel(glu, gl, turquoise, chrome);
        wheelList = wheel.createWheelList();
        chairs = new Chairs(glu, gl, ruby);
        chairList = chairs.createChairs();
        frame = new Frame(glu, gl, emerald);
        frameList = frame.createFrameList();
    }

    private void initializeLights() {
        gl.glEnable(GLLightingFunc.GL_LIGHTING);
        gl.glEnable(GLLightingFunc.GL_LIGHT0);
        gl.glEnable(GLLightingFunc.GL_LIGHT1);

        lightZeroEnabled = true;
        lightOneEnabled = true;

        float[] light0Color = {0.5f, 0.5f, 0.5f, 1f};
        float[] light1Color = {0.1f, 0.1f, 0.1f, 1f};
        lightZeroPos = new float[]{ -1, 0, 0, 0 };
        gl.glLightfv(GLLightingFunc.GL_LIGHT0, GLLightingFunc.GL_POSITION, lightZeroPos, 0);
        gl.glLightfv(GLLightingFunc.GL_LIGHT0, GLLightingFunc.GL_DIFFUSE, light0Color, 0);
        gl.glLightfv(GLLightingFunc.GL_LIGHT0, GLLightingFunc.GL_AMBIENT, light0Color, 0);
        gl.glLightfv(GLLightingFunc.GL_LIGHT0, GLLightingFunc.GL_SPECULAR, light0Color, 0);

        float[] lightPos1 = { 1, 0, 0, 0 };
        gl.glLightfv(GLLightingFunc.GL_LIGHT1, GLLightingFunc.GL_POSITION, lightPos1, 0);
        gl.glLightfv(GLLightingFunc.GL_LIGHT1, GLLightingFunc.GL_DIFFUSE, light1Color, 0);
        gl.glLightfv(GLLightingFunc.GL_LIGHT1, GLLightingFunc.GL_AMBIENT, light1Color, 0);
        gl.glLightfv(GLLightingFunc.GL_LIGHT1, GLLightingFunc.GL_SPECULAR, light1Color, 0);
    }

    private void setDefault() {
        eyeX = 15;
        eyeY = -7.5f;
        eyeZ = 28;
        refX = 1.65f;
        refY = -1.8f;
        refZ = 0.5f;
        upX = 0;
        upY = 1;
        upZ = 0;
    }

    private void render(int width, int height) {
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);

        gl.glPushMatrix();
        gl.glDisable(GLLightingFunc.GL_LIGHTING);
        gl.glTranslatef(lightZeroPos[0], lightZeroPos[1], lightZeroPos[2]);
        glu.gluSphere(glu.gluNewQuadric(), 1, 20, 10);
        gl.glEnable(GLLightingFunc.GL_LIGHTING);
        gl.glPopMatrix();

        gl.glPushMatrix();
        gl.glCallList(frameList);
        gl.glPopMatrix();

        gl.glTranslatef(0, 0, 2);

        gl.glPushMatrix();
        gl.glRotated(-rotateSpeed, 0, 0, 1);
        gl.glCallList(wheelList);
        gl.glTranslated(0, 0, 5.5);
        gl.glCallList(wheelList);

        //render each chair
        double alpha = Math.PI * 2 / NUM_CHAIRS;
        gl.glRotated(-270, 1 , 0, 0);
        gl.glTranslated(0, -0.5, 0);

        currentRotationAngle += 0.2;
        currentRotationAngle = currentRotationAngle % 360;

        for(int i = 0; i < NUM_CHAIRS; i++) {
            gl.glPushMatrix();

            //swing
            if(swingDirection) {
                if(previousChairAngle < 10) {
                    previousChairAngle += .03;
                } else {
                    swingDirection = false;
                }
            } else {
                if(previousChairAngle > -10) {
                    previousChairAngle -= .05;
                } else {
                    swingDirection = true;
                }
            }

            gl.glRotated(currentRotationAngle, 0, 1, 0);
            double theta = ((alpha * i) + previousChairPosition) % 360;
            gl.glTranslated(Math.cos(theta) * 10, 0, Math.sin(theta) * 10);

            gl.glTranslated(0,0,0.5f);
            gl.glRotated(previousChairAngle, 0, 1, 0);
            gl.glTranslated(0,0,-0.5f);
            gl.glCallList(chairList);
            gl.glPopMatrix();
        }
        previousChairPosition += .0035f;

        gl.glPopMatrix();
    }

    private void update() {
        rotateSpeed += 0.2;
    }

    private void setCamera() {
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
            case KeyEvent.VK_Q:
                wireframeOn = (!wireframeOn);
                break;
            case KeyEvent.VK_1:
                lightZeroEnabled = (!lightZeroEnabled);
                break;
            case KeyEvent.VK_2:
                lightOneEnabled = (!lightOneEnabled);
                break;
            case KeyEvent.VK_SPACE:
                rotateSpeed += 0.2 * 12;
                currentRotationAngle += 0.2 * 12;
                previousChairPosition += 0.0035 * 12;
                break;
            case KeyEvent.VK_BACK_SPACE:
                rotateSpeed -= 0.2 * 14;
                currentRotationAngle -= 0.2 * 14;
                previousChairPosition -= 0.0035 * 14;
                break;
            case KeyEvent.VK_P:
                if(animator.isPaused())
                    animator.resume();
                else
                    animator.pause();
            case KeyEvent.VK_I:
                lightZeroPos[1] += KEY_SPEED;
                break;
            case KeyEvent.VK_K:
                lightZeroPos[1] -= KEY_SPEED;
                break;
            case KeyEvent.VK_J :
                lightZeroPos[0] -= KEY_SPEED;
                break;
            case KeyEvent.VK_L:
                lightZeroPos[0] += KEY_SPEED;
                break;
            case KeyEvent.VK_U:
                lightZeroPos[2] -= KEY_SPEED;
                break;
            case KeyEvent.VK_O:
                lightZeroPos[2] += KEY_SPEED;
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
        gl = glAutoDrawable.getGL().getGL2();

        gl.setSwapInterval(1);
        initializeModels();

        gl.glEnable(GL.GL_DEPTH_TEST);
        gl.glDepthFunc(GL.GL_LEQUAL);
    }

    public void dispose(GLAutoDrawable glAutoDrawable) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public void display(GLAutoDrawable glAutoDrawable) {
        GL2 gl = glAutoDrawable.getGL().getGL2();

        gl.glLightfv(GLLightingFunc.GL_LIGHT0, GLLightingFunc.GL_POSITION, lightZeroPos, 0);

        if(wireframeOn)
            gl.glPolygonMode(GL2.GL_FRONT_AND_BACK, GL2.GL_LINE);
        else
            gl.glPolygonMode(GL2.GL_FRONT_AND_BACK, GL2.GL_FILL);

        if(lightZeroEnabled)
            gl.glEnable(GLLightingFunc.GL_LIGHT0);
        else
            gl.glDisable(GLLightingFunc.GL_LIGHT0);

        if(lightOneEnabled)
            gl.glEnable(GLLightingFunc.GL_LIGHT1);
        else
            gl.glDisable(GLLightingFunc.GL_LIGHT1);

        setCamera();
        update();
        render(glAutoDrawable.getWidth(), glAutoDrawable.getHeight());
    }

    public void reshape(GLAutoDrawable glAutoDrawable, int i, int i2, int width, int height) {
        GL2 gl = glAutoDrawable.getGL().getGL2();
        gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
        gl.glLoadIdentity();
    }

    /* MouseMotionListener */
    public void mouseDragged(MouseEvent e) {
    }

    public void mouseMoved(MouseEvent e) {
        if(animator.isPaused())
            return;

        Point p = e.getPoint();
        refX = (float) p.getX() * MOUSE_SPEED;
        refY = -(float) p.getY() * MOUSE_SPEED;

        display();
    }

    /* MouseWheelListener */
    public void mouseWheelMoved(MouseWheelEvent e) {
        float notches = e.getWheelRotation();
        eyeZ += notches * SCROLL_SPEED;
    }
}
