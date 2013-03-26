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
    private Context mCtx;
    private Drawable ferrisWheel;
    private TransformationParams param;
    private final static float lightDir[] = {0, 0, -1f, 0f};
    private final static float lightPos[] = {2.6f, 0.0f, 5.0f, 1f};;

    public GLRenderer(Context parent, TransformationParams p) {

        mCtx = parent;
        ferrisWheel = new FerrisWheel(mCtx);
        param = p;
//        param.transX = param.transY = 0;
        param.texScale = 1.0f;
        param.texTransX = param.texTransY = 0;
//        float[] faceVertexData = {-1f, 1f, 1f,
//                1f, 1f, 1f,
//                1f, -1f, 1f,
//                -1f, -1f, 1f};
//        faceVertexBuff = ByteBuffer.allocateDirect(faceVertexData.length * 4).order(ByteOrder.nativeOrder()).asFloatBuffer();
//        faceVertexBuff.put(faceVertexData);
//        faceVertexBuff.position(0);
//        float[] faceColorData = {1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1};
//        faceColorBuff = ByteBuffer.allocateDirect(faceColorData.length*4).order(ByteOrder.nativeOrder()).asFloatBuffer();
//        faceColorBuff.put(faceColorData);
//        faceColorBuff.position(0);
//        short[] faceOrderData = {0,3,1,1,3,2};
//        faceOrderBuff = ByteBuffer.allocateDirect(faceOrderData.length*4).order(ByteOrder.nativeOrder()).asShortBuffer();
//        faceOrderBuff.put(faceOrderData);
//        faceOrderBuff.position(0);
    }

    /**
     * Display callback
     */
    @Override
    public void onDrawFrame(GL10 gl) {

        gl.glClearColor (0, 0, 0, 1f);
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        gl.glLoadIdentity();
        GLU.gluLookAt(gl, param.eyeX, param.eyeY, param.eyeZ, /* eye */
                param.coa[0], param.coa[1], param.coa[2], /* focal point */
                0, 0, 1f); /* up */
        gl.glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        gl.glPushMatrix();
        gl.glTranslatef(param.litePos[0], param.litePos[1], param.litePos[2]);
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_POSITION, lightPos, 0);
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_SPOT_DIRECTION, lightDir, 0);
        gl.glPopMatrix();

        gl.glPushMatrix();
        ferrisWheel.draw();
        gl.glPopMatrix();
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
