import javax.swing.*;
import javax.media.opengl.*;

public class Driver {
    public Driver(FerrisWheelCanvas canvas) {
        JFrame frame = new JFrame("Project 2");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        frame.add(canvas);
        frame.setSize(700, 700);
        frame.setVisible(true);
        canvas.requestFocus();
    }

    public static void main(String[] args) {
        GLProfile glprofile = GLProfile.getDefault();
        GLCapabilities capabilities = new GLCapabilities(glprofile);
        FerrisWheelCanvas canvas = new FerrisWheelCanvas(capabilities);

        Driver instance = new Driver(canvas);
    }
}