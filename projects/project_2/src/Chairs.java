import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Chairs {
    GLU glu;
    GLUquadric quadric;
    GL2 gl;
    float[][] chairColor;

    public Chairs(GLU glu, GL2 gl, float[][] chairColor) {
        this.glu = glu;
        this.quadric = glu.gluNewQuadric();
        this.gl = gl;
        this.chairColor = chairColor;
    }

    public int createChairs() {
        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);

        gl.glTranslated(0, -2, 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_DIFFUSE, chairColor[0], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_AMBIENT, chairColor[1], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_SPECULAR, chairColor[2], 0);
        gl.glMaterialf(GL2.GL_FRONT_AND_BACK, GL2.GL_SHININESS, chairColor[3][0]);

        glu.gluCylinder(quadric, 2.5, 1.8, 3, 50, 5);
        glu.gluDisk(quadric, 2.5, 2, 20, 1);
        gl.glTranslated(0, 0, 3);
        glu.gluDisk(quadric, 1.8, 0, 20, 1);

        gl.glEndList();
        return listId;
    }

}
