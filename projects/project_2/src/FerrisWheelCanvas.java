import javax.media.opengl.*;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.fixedfunc.GLMatrixFunc;
import javax.media.opengl.glu.GLU;
import java.awt.*;
import java.awt.event.*;

public class FerrisWheelCanvas extends GLCanvas implements GLEventListener, KeyListener, MouseMotionListener, MouseWheelListener {
    /* SETTINGS */
    final static float KEY_SPEED = 0.5F;
    final static float SCROLL_SPEED = 0.3F;
    final static float MOUSE_SPEED = .01F;

    boolean wireframeOn;
    GLU glu;
    float eyeZ, eyeX, eyeY, refZ, refX, refY, upZ, upX, upY;
    int wheelList;
    Wheel wheel;

    public FerrisWheelCanvas(GLCapabilities capabilities) {
        super(capabilities);
        glu = new GLU();
        setDefault();

        this.addGLEventListener(this);
        this.addKeyListener(this);
        this.addMouseMotionListener(this);
        this.addMouseWheelListener(this);
    }

    private void initializeModels(GL2 gl) {
        wheel = new Wheel(10, 1, glu, gl);
        wheelList = wheel.createWheelList();
    }

    private void setDefault() {
        eyeZ = 20;
        eyeX = 5;
        eyeY = 0;
        refZ = 0;
        refX = 0;
        refY = 0;
        upZ = 0;
        upX = 0;
        upY = 1;
    }

    private void render(GL2 gl, int width, int height) {
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
        gl.glPushMatrix();
        gl.glCallList(wheelList);
        gl.glTranslated(0,0,5);
        gl.glCallList(wheelList);
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
            case KeyEvent.VK_Q:
                if(wireframeOn)
                    wireframeOn = false;
                else
                    wireframeOn = true;
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

        initializeModels(gl);

        gl.glEnable(GL.GL_DEPTH_TEST);
        gl.glDepthFunc(GL.GL_LEQUAL);
    }

    public void dispose(GLAutoDrawable glAutoDrawable) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public void display(GLAutoDrawable glAutoDrawable) {
        GL2 gl = glAutoDrawable.getGL().getGL2();
        if(wireframeOn)
            gl.glPolygonMode(GL2.GL_FRONT_AND_BACK, GL2.GL_LINE);
        else
            gl.glPolygonMode(GL2.GL_FRONT_AND_BACK, GL2.GL_FILL);

        setCamera(gl);
        render(gl, glAutoDrawable.getWidth(), glAutoDrawable.getHeight());
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