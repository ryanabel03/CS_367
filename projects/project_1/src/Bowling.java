import javax.media.opengl.*;
import javax.media.opengl.glu.*;
import javax.media.opengl.awt.GLCanvas;

public class Bowling extends GLCanvas {
    int pin_list;

    public Bowling(GLCapabilities capabilities) {
        super(capabilities);

        this.addGLEventListener(new GLEventListener() {
            public void init(GLAutoDrawable glAutoDrawable) {
                GL2 gl = glAutoDrawable.getGL().getGL2();

                pin_list = gl.glGenLists(1);
            }

            public void dispose(GLAutoDrawable glAutoDrawable) {
                //To change body of implemented methods use File | Settings | File Templates.
            }

            public void display(GLAutoDrawable glAutoDrawable) {
                //To change body of implemented methods use File | Settings | File Templates.
            }

            public void reshape(GLAutoDrawable glAutoDrawable, int i, int i2, int width, int height) {
                Bowling.setup(glAutoDrawable.getGL().getGL2(), width, height);            }
        }

        );
    }

    protected static void setup(GL2 gl, int width, int height) {
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        // coordinate system origin at lower left with width and height same as the window
        GLU glu = new GLU();
        glu.gluOrtho2D(0.0f, width, 0.0f, height);

        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();

        gl.glViewport(0, 0, width, height);
    }

    protected static void render(GL2 gl, int width, int height) {
        gl.glLoadIdentity();
    }
}
