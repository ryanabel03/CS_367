import javax.media.opengl.GL;
import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;

public class Bowling {
    protected static void setup(GL2 gl2, int width, int height) {
        gl2.glMatrixMode(GL2.GL_PROJECTION);
        gl2.glLoadIdentity();

        // coordinate system origin at lower left with width and height same as the window
        GLU glu = new GLU();
        glu.gluOrtho2D(0.0f, width, 0.0f, height);

        gl2.glMatrixMode(GL2.GL_MODELVIEW);
        gl2.glLoadIdentity();

        gl2.glViewport(0, 0, width, height);
    }

    protected static void render(GL2 gl2, int width, int height) {
        gl2.glClear(GL.GL_COLOR_BUFFER_BIT);

        gl2.glLoadIdentity();
        gl2.glBegin(GL.GL_LINE_LOOP);
        gl2.glVertex2f(200, 100);
        gl2.glVertex2f(180, 200);
        gl2.glVertex2f(180, 210);
        gl2.glVertex2f(200, 240);
        gl2.glVertex2f(200, 250);
        gl2.glVertex2f(195, 265);
        gl2.glVertex2d(195, 280);
        gl2.glVertex2d(200, 295);
        gl2.glVertex2d(230, 295);
        gl2.glVertex2d(235, 280);
        gl2.glVertex2d(235, 265);
        gl2.glVertex2f(230, 250);
        gl2.glVertex2f(230, 240);
        gl2.glVertex2f(250, 210);
        gl2.glVertex2f(250, 200);
        gl2.glVertex2f(230, 100);
        gl2.glEnd();
    }
}