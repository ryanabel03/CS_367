import javax.media.opengl.*;
import javax.media.opengl.fixedfunc.GLMatrixFunc;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;

public class Bowling extends GLCanvas {
    int pin_list;
    GLU glu;

    public Bowling(GLCapabilities capabilities) {
        super(capabilities);

        this.addGLEventListener(new GLEventListener() {
            public void init(GLAutoDrawable glAutoDrawable) {
                GL2 gl = glAutoDrawable.getGL().getGL2();
                glu = new GLU();

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
                    radius2 = 0.5f;
                    z = 0;
                    x = (float) (radius1 * Math.cos(theta));
                    y = (float) (radius1 * Math.sin(theta));
                    gl.glColor3f(0.4f,0,0.4f);
                    gl.glVertex3f(x, y, z);
                    z += 0.5;

                    x = (float) (radius2 * Math.cos(theta));
                    y = (float) (radius2 * Math.sin(theta));
                    gl.glColor3f(0.9f,0,0);
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
                render(gl, glAutoDrawable.getWidth(), glAutoDrawable.getHeight());
                setCamera(gl, 10);
            }

            public void reshape(GLAutoDrawable glAutoDrawable, int i, int i2, int width, int height) {
                GL2 gl = glAutoDrawable.getGL().getGL2();
                gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
                gl.glLoadIdentity();
            }
        });
    }

    private void render(GL2 gl, int width, int height)
    {
        gl.glPushMatrix();
        gl.glClear(GL.GL_COLOR_BUFFER_BIT);
        gl.glClear(GL.GL_DEPTH_BUFFER_BIT);
        gl.glLoadIdentity();
        gl.glCallList(pin_list);
        gl.glTranslatef(5,5,0);
        gl.glCallList(pin_list);
        gl.glPopMatrix();
    }

    private void setCamera(GL2 gl, float distance)
    {
        gl.glMatrixMode(GL2.GL_PROJECTION);
        gl.glLoadIdentity();

        float widthHeightRatio = (float) getWidth() / (float) getHeight();
        glu.gluPerspective(45, widthHeightRatio, 1, 1000);
        glu.gluLookAt(5,15,distance,0,0,0,0,1,0);

        gl.glMatrixMode(GL2.GL_MODELVIEW);
        gl.glLoadIdentity();
    }
}
