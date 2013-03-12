import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Frame {
    GLU glu;
    GLUquadric quadric;
    GL2 gl;
    float[][] frameColor;

    public Frame(GLU glu, GL2 gl, float[][] frameColor) {
        this.glu = glu;
        quadric = glu.gluNewQuadric();
        this.gl = gl;
        this.frameColor = frameColor;
    }

    public int createFrameList() {
        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);

        gl.glPushMatrix();

        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_DIFFUSE, frameColor[0], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_AMBIENT, frameColor[1], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_SPECULAR, frameColor[2], 0);
        gl.glMaterialf(GL2.GL_FRONT_AND_BACK, GL2.GL_SHININESS, frameColor[3][0]);

        glu.gluCylinder(quadric, 0.5, 0.5, 10, 10, 5);

        gl.glRotated(90, 1, 0, 0);
        gl.glTranslated(0, -0.5, -0.5);
        glu.gluCylinder(quadric, 0.5, 0.5, 15, 10, 5);
        gl.glTranslated(0, 10.5, 0);
        glu.gluCylinder(quadric, 0.5, 0.5, 15, 10, 5);
        gl.glTranslated(0, -5.25, 15);
        glu.gluDisk(quadric, 10, 0, 50, 10);

        gl.glPopMatrix();
        gl.glEndList();

        return listId;
    }
}