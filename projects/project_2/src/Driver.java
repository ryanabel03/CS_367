import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLProfile;
import javax.swing.*;

public class Driver {

    public Driver(YoyoAnimation canvas) {
        JFrame frame = new JFrame("Project 2");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        frame.add(canvas);
        frame.setSize(700, 700);
        frame.setVisible(true);
        canvas.requestFocus();
    }

    public static void main(String[] args) {
        GLProfile glProfile = GLProfile.getDefault();
        GLCapabilities capabilities = new GLCapabilities(glProfile);


    }
}

