import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Frame {
    GLU glu;
    GLUquadric quadric;
    GL2 gl;

    public Frame(GLU glu, GL2 gl) {
        this.glu = glu;
        quadric = glu.gluNewQuadric();
        this.gl = gl;
    }

    public int createFrameList() {
        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);

        gl.glPushMatrix();
        glu.gluCylinder(quadric, 0.5, 0.5, 8, 10, 5);
        gl.glPopMatrix();
        gl.glEndList();

        return listId;
    }
}