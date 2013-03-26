package com.example.project_3;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

/**
 * Created with IntelliJ IDEA.
 * User: Alex
 * Date: 3/25/13
 * Time: 4:57 PM
 * To change this template use File | Settings | File Templates.
 */
public class GLRenderer implements GLSurfaceView.Renderer {
    FloatBuffer faceVertexBuff;
    FloatBuffer faceColorBuff;
    ShortBuffer faceOrderBuff;

    public GLRenderer(Context parent) {
        float[] faceVertexData = {-1f, 1f, 1f,
                1f, 1f, 1f,
                1f, -1f, 1f,
                -1f, -1f, 1f};
        faceVertexBuff = ByteBuffer.allocateDirect(faceVertexData.length * 4).order(ByteOrder.nativeOrder()).asFloatBuffer();
        faceVertexBuff.put(faceVertexData);
        faceVertexBuff.position(0);
        float[] faceColorData = {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1};
        faceColorBuff = ByteBuffer.allocateDirect(faceColorData.length*4).order(ByteOrder.nativeOrder()).asFloatBuffer();
        faceColorBuff.put(faceColorData);
        faceColorBuff.position(0);
        short[] faceOrderData = {0,3,1,1,3,2};
        faceOrderBuff = ByteBuffer.allocateDirect(faceOrderData.length*4).order(ByteOrder.nativeOrder()).asShortBuffer();
        faceOrderBuff.put(faceOrderData);
        faceOrderBuff.position(0);
    }

    /**
     * Display callback
     */
    @Override
    public void onDrawFrame(GL10 gl) {
		 /* Clear the buffer, clear the matrix */
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);

        GLU.gluLookAt(gl, 0, 0, -2, 0, 0, 0, 0, 1, 0);

        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
//	     gl.glEnableClientState(GL10.GL_NORMAL_ARRAY);
        gl.glEnableClientState(GL10.GL_COLOR_ARRAY);

        gl.glVertexPointer(3, GL10.GL_FLOAT, 0, faceVertexBuff);
        gl.glColorPointer(4, GL10.GL_FLOAT, 0, faceColorBuff);
        //gl.glNormalPointer(GL10.GL_FLOAT, 0, faceOrderBuff);

        gl.glDrawElements(GL10.GL_TRIANGLES, 6, GL10.GL_UNSIGNED_SHORT, faceOrderBuff);

        gl.glFlush();
    }


    /**
     * Resized callback
     */
    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        gl.glViewport(0, 0, width, height);
        gl.glMatrixMode(GL10.GL_PROJECTION);
        gl.glLoadIdentity();
        GLU.gluPerspective(gl, 45f, (float) width / (float) height, 0.1f, 100f);
        //gl.glOrthof(-2, 2, -2, 2,-2, 2);
        gl.glMatrixMode(GL10.GL_MODELVIEW);
    }


    /**
     * Location for init() code
     */
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        gl.glClearColor(.5f, 1.0f, 0, 1.0f);
        gl.glShadeModel(GL10.GL_SMOOTH);
//	     gl.glEnable(GL10.GL_CULL_FACE);
        gl.glEnable(GL10.GL_DEPTH_TEST);
    }

}
