import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Wheel {
    GLU glu;
    GLUquadric quadric;
    GL2 gl;

    public Wheel(GLU glu, GL2 gl) {
        this.glu = glu;
        quadric = glu.gluNewQuadric();
        this.gl = gl;
    }

    public int createWheelList() {
        int NUM_SPOKES = 6;

        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);
        gl.glPushMatrix();
        glu.gluCylinder(quadric, 10, 10, 1, 50, 5);
        gl.glRotated(-270, 1, 0, 0);
        gl.glTranslated(0, 0.5, 0);

        for(int i = 0; i < NUM_SPOKES; i++) {
            double angle = i * 360.0 / NUM_SPOKES;
            gl.glPushMatrix();
            gl.glRotated(angle, 0, 1, 0);
            glu.gluCylinder(quadric, 0.2, 0.2, 9.9, 10, 5);
            gl.glPopMatrix();
        }

        gl.glPopMatrix();
        gl.glEndList();

        return listId;
    }
}
