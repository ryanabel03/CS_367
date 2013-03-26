package com.example.project_3;

import android.app.Activity;
import android.content.Context;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.os.Bundle;
import android.view.*;

import javax.microedition.khronos.opengles.GL10;

public class GraphicsActivity extends Activity {
    private GLView mView;
    private GLRenderer render;
    private SensorManager sm;
    private Display myDisplay;
    private TransformationParams par;

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        par = new TransformationParams();
        par.eyeX = 3f;
        par.eyeY = -4f;
        par.eyeZ = 3f;
        par.litePos[0] = 0f;
        par.litePos[1] = 0f;
        par.litePos[2] = 3f;
        par.droid_x = 2.0f;
        par.droid_y = 1.0f;

        requestWindowFeature(Window.FEATURE_NO_TITLE);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        mView = new GLView(this);
        mView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

        sm = (SensorManager) getSystemService(SENSOR_SERVICE);
        myDisplay = getWindowManager().getDefaultDisplay();

        setContentView(R.layout.main);

        /* replace Textview with GLView */
        View dummy = findViewById(R.id.dummy);
        ViewGroup top = (ViewGroup) dummy.getParent();

        mView.setLayoutParams(dummy.getLayoutParams());

        int index = top.indexOfChild(dummy);
        top.removeViewAt(index);
        top.addView(mView, index);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    public class GLView extends GLSurfaceView {
        public GLView(Context context) {
            super(context);
            render = new GLRenderer(context, par);

            setRenderer(render);
            setRenderMode(RENDERMODE_CONTINUOUSLY);
        }
    }
}
