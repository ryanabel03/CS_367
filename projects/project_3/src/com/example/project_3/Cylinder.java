package com.example.project_3;

import android.opengl.GLES20;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * Created with IntelliJ IDEA.
 * User: Alex
 * Date: 3/25/13
 * Time: 5:13 PM
 * To change this template use File | Settings | File Templates.
 */
public class Cylinder implements Drawable {
    private FloatBuffer vertexBuffer;
    private final int mProgram;
    private int mPositionHandle;
    private final int COORDS_PER_VERTEX = 3;
    private int mColorHandle;
    private int numCoordinates;

    float color[] = { 0.63671875f, 0.76953125f, 0.22265625f, 1.0f };

    public Cylinder(float length, float radius1, float radius2, int resolution) {
        numCoordinates = (int) resolution * 2 * 3;
        float[] coordinateArray = new float[numCoordinates];

        float theta, x, y;

        for(int i = 0; i < numCoordinates; i += 6) {
            theta = (float) (i / 50.0 * 2 * Math.PI);
            x = (float) (radius1 * Math.cos(theta));
            y = (float) (radius1 * Math.sin(theta));
            coordinateArray[i] = x;
            coordinateArray[i+1] = y;
            coordinateArray[i+2] = 0f;

            x = (float) (radius2 * Math.cos(theta));
            y = (float) (radius2 * Math.sin(theta));
            coordinateArray[i+3] = x;
            coordinateArray[i+4] = y;
            coordinateArray[i+5] = length;
        }

        // initialize vertex byte buffer for shape coordinates
        ByteBuffer bb = ByteBuffer.allocateDirect(
            // (number of coordinate values * 4 bytes per float)
            coordinateArray.length * 4);
        // use the device hardware's native byte order
        bb.order(ByteOrder.nativeOrder());

        // create a floating point buffer from the ByteBuffer
        vertexBuffer = bb.asFloatBuffer();
        // add the coordinates to the FloatBuffer
        vertexBuffer.put(coordinateArray);
        // set the buffer to read the first coordinate
        vertexBuffer.position(0);

        mProgram = GLES20.glCreateProgram();             // create empty OpenGL ES Program
        GLES20.glLinkProgram(mProgram);                  // creates OpenGL ES program executables
    }

    @Override
    public void draw(Object... data) {
        // Add program to OpenGL ES environment
        GLES20.glUseProgram(mProgram);

        // get handle to vertex shader's vPosition member
        mPositionHandle = GLES20.glGetAttribLocation(mProgram, "vPosition");

        // Enable a handle to the thing's vertices
        GLES20.glEnableVertexAttribArray(mPositionHandle);

        // Prepare the triangle coordinate data
        GLES20.glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX,
                GLES20.GL_FLOAT, false,
                1, vertexBuffer);

        // get handle to fragment shader's vColor member
        mColorHandle = GLES20.glGetUniformLocation(mProgram, "vColor");

        // Set color for drawing the thing
        GLES20.glUniform4fv(mColorHandle, 1, color, 0);

        // Draw the thing
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, numCoordinates);
    }
}
