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

        int list_id = gl.glGenLists(1);
        gl.glNewList(list_id, GL2.GL_COMPILE);
        glu.gluCylinder(quadric, 10, 10, 1, 1, 1);
        gl.glEndList();

        return list_id;
    }
}
