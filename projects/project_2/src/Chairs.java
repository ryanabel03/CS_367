import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Chairs {
    GLU glu;
    GLUquadric quadric;
    GL2 gl;

    public Chairs(GLU glu, GL2 gl) {
        this.glu = glu;
        this.quadric = glu.gluNewQuadric();
        this.gl = gl;
    }

    public int createChairs() {
        int NUM_CHAIRS = 6;

        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);

        gl.glRotated(-270, 1, 0, 0);
        gl.glTranslated(0, -2, 0);

        double alpha = Math.PI * 2 / NUM_CHAIRS;
        for(int i = 0; i < NUM_CHAIRS; i++) {
            gl.glPushMatrix();

            double theta = alpha * i;
            gl.glTranslated(Math.cos(theta) * 10, 0, Math.sin(theta) * 10);
            glu.gluCylinder(quadric, 2.5, 1, 3, 50, 5);

            gl.glPopMatrix();
        }


        gl.glEndList();
        return listId;
    }

}
