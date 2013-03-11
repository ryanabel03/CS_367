import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Wheel {
    float radius;
    float tire_thickness;
    GLU glu;
    GLUquadric quadric;
    GL2 gl;

    public Wheel(float radius, float tire_thickness, GLU glu, GL2 gl) {
        this.glu = glu;
        this.radius = radius;
        this.tire_thickness = tire_thickness;
        quadric = glu.gluNewQuadric();
        this.gl = gl;
    }

    public int createWheelList() {
        int NUM_SPOKES = 6;

        int listId = gl.glGenLists(1);
        gl.glNewList(listId, GL2.GL_COMPILE);
        gl.glPushMatrix();
        glu.gluCylinder(quadric, 10, 10, 1, 50, 5);
        gl.glPopMatrix();
        gl.glEndList();

        return listId;
    }
}
