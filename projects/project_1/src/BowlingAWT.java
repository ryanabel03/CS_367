import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.GLProfile;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.awt.GLCanvas;

import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class BowlingAWT {

    public static void main(String [] args) {
        GLProfile glprofile = GLProfile.getDefault();
        GLCapabilities glcapabilities = new GLCapabilities(glprofile);
        final GLCanvas glcanvas = new GLCanvas(glcapabilities);

        glcanvas.addGLEventListener(new GLEventListener() {
            public void reshape(GLAutoDrawable glautodrawable, int x, int y, int width, int height) {
                Bowling.setup(glautodrawable.getGL().getGL2(), width, height);
            }

            public void init(GLAutoDrawable glautodrawable) {
            }

            public void dispose(GLAutoDrawable glautodrawable) {
            }

            public void display(GLAutoDrawable glautodrawable) {
                Bowling.render(glautodrawable.getGL().getGL2(), glautodrawable.getWidth(), glautodrawable.getHeight());
            }
        });

        final Frame frame = new Frame("Bowling");
        frame.add(glcanvas);
        frame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowevent) {
                frame.remove(glcanvas);
                frame.dispose();
                System.exit(0);
            }
        });

        frame.setSize(600, 600);
        frame.setVisible(true);
    }
}