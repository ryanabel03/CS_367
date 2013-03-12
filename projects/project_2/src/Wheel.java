import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Wheel {
    GLU glu;
    GLUquadric quadric;
    GL2 gl;
    float[][] wheelColor;
    float[][] spokeColor;

    public Wheel(GLU glu, GL2 gl, float[][] wheelColor, float[][] spokeColor) {
        this.glu = glu;
        quadric = glu.gluNewQuadric();
        this.gl = gl;
        this.wheelColor = wheelColor;
        this.spokeColor = spokeColor;
    }

    public int createWheelList() {
        int NUM_SPOKES = 6;

        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);
        gl.glPushMatrix();
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_DIFFUSE, wheelColor[0], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_AMBIENT, wheelColor[1], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_SPECULAR, wheelColor[2], 0);
        gl.glMaterialf(GL2.GL_FRONT_AND_BACK, GL2.GL_SHININESS, wheelColor[3][0]);

        glu.gluCylinder(quadric, 10, 10, 0.5, 50, 5);
        gl.glRotated(-270, 1, 0, 0);
        gl.glTranslated(0, 0.25, 0);

        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_DIFFUSE, spokeColor[0], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_AMBIENT, spokeColor[1], 0);
        gl.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_SPECULAR, spokeColor[2], 0);
        gl.glMaterialf(GL2.GL_FRONT_AND_BACK, GL2.GL_SHININESS, spokeColor[3][0]);

        for(int i = 0; i < NUM_SPOKES; i++) {
            double angle = i * 360.0 / NUM_SPOKES;
            gl.glPushMatrix();
            gl.glRotated(angle, 0, 1, 0);
            glu.gluCylinder(quadric, 0.2, 0.2, 9.92, 10, 5);
            gl.glPopMatrix();
        }

        gl.glPopMatrix();
        gl.glEndList();

        return listId;
    }
}
