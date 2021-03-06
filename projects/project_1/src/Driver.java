import javax.swing.*;
import javax.media.opengl.*;

public class Driver {
    public Driver(Bowling canvas) {
        JFrame frame = new JFrame("Project 1");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        frame.add(canvas);
        frame.setSize(700, 700);
        frame.setVisible(true);
        canvas.requestFocus();
    }

    public static void main(String[] args) {
        GLProfile glprofile = GLProfile.getDefault();
        GLCapabilities capabilities = new GLCapabilities(glprofile);
        Bowling canvas = new Bowling(capabilities);

        Driver instance = new Driver(canvas);
    }
}
