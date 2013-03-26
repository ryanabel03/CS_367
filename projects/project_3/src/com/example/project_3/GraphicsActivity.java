package com.example.project_3;

import android.app.Activity;
import android.content.Context;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.*;

public class GraphicsActivity extends Activity {
    private GLView mView;
    private GLRenderer render;
    private SensorManager sm;
    private Display myDisplay;

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        mView = new GLView(this);
        mView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

        sm = (SensorManager) getSystemService(SENSOR_SERVICE);
        myDisplay = getWindowManager().getDefaultDisplay();

        setContentView(R.layout.main);

        /* replace Textview with GLView */
        View dummy = findViewById(R.id.GraphicsView);
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
            render = new GLRenderer(context);

            setRenderer(render);
            setRenderMode(RENDERMODE_CONTINUOUSLY);
        }
    }
}
