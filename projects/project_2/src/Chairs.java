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
        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);

        gl.glTranslated(0, -2, 0);

        glu.gluCylinder(quadric, 2.5, 1, 3, 50, 5);

        gl.glEndList();
        return listId;
    }

}
