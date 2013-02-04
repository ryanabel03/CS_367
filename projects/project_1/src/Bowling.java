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

    public Bowling(GLCapabilities capabilities) {
        super(capabilities);
        glu = new GLU();
        setDefault();

        this.addGLEventListener((GLEventListener)this);
        this.addKeyListener(this);
    }

    private void setDefault()
    {
        z = 3;
        x = 0;
        y = 0;
        refz = 0;
        refx = 0;
        refy = 0;
    }

    private void render(GL2 gl, int width, int height)
    {
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
        gl.glPushMatrix();
        gl.glCallList(pin_list);
        gl.glTranslatef(5,5,0);
        gl.glCallList(pin_list);
        gl.glPopMatrix();
    }

    private void setCamera(GL2 gl)
    {
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        float widthHeightRatio = (float) getWidth() / (float) getHeight();
        glu.gluPerspective(90, widthHeightRatio, 1, 100);

        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();
        glu.gluLookAt(x,y,z,refx,refy,refz,0,1,0);
    }

    /* KeyListener */
    public void keyPressed(KeyEvent e)
    {
        int keyCode = e.getKeyCode();
        switch(keyCode) {
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
            case KeyEvent.VK_RIGHT :
                x += UNIT;
                refx += UNIT;
                break;
            case KeyEvent.VK_W:
                refy -= UNIT;
                break;
            case KeyEvent.VK_A:
                refx -= UNIT;
                break;
            case KeyEvent.VK_S :
                refy += UNIT;
                break;
            case KeyEvent.VK_D :
                refx += UNIT;
                break;
            case KeyEvent.VK_EQUALS:
                z -= UNIT;
                break;
            case KeyEvent.VK_MINUS:
                z += UNIT;
                break;
            case KeyEvent.VK_R:
                setDefault();
                break;
        }
        display();
    }

    public void keyReleased(KeyEvent e)
    {
    }

    public void keyTyped(KeyEvent e)
    {
    }

    /* GLEventListener */
    public void init(GLAutoDrawable glAutoDrawable) {
        GL2 gl = glAutoDrawable.getGL().getGL2();

        gl.glEnable(GL.GL_DEPTH_TEST);
        gl.glDepthFunc(GL.GL_LEQUAL);

        pin_list = gl.glGenLists(1);
        gl.glNewList(pin_list, GL2.GL_COMPILE);
        gl.glBegin(GL2.GL_QUAD_STRIP);/* f1: front */
        float theta, radius1, radius2, x, y, z;
        for(float i = 0; i <= 50; i++)
        {
            theta = (float) (i / 50.0 * 2 * Math.PI);
            radius1 = 0.5f;
            z = 0;
            x = (float) (radius1 * Math.cos(theta));
            y = (float) (radius1 * Math.sin(theta));
            gl.glColor3f(0.1f,0.3f,0.4f);
            gl.glVertex3f(x, y, z);
            z += 0.5;

            radius2 = 0.1f;
            x = (float) (radius2 * Math.cos(theta));
            y = (float) (radius2 * Math.sin(theta));
            gl.glColor3f(0,0.5f,0);
            gl.glVertex3f(x, y, z);
        }
        gl.glEnd();
        gl.glEndList();
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