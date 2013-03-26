package com.example.project_3;

import android.content.Context;

import static android.opengl.GLES10.*;

public class FerrisWheel implements Drawable {


    private MeshObject ferrisWheel;

    public FerrisWheel(Context context) {
        ferrisWheel = new MeshObject(context, "ferris_wheel.off");
    }
    @Override
    public void draw(Object... data) {

        glPushMatrix();
        glTranslatef(0, 0, 2.2f);
        glScalef(1.7f, 1.7f, 1.6f);
        ferrisWheel.draw();
        glPopMatrix();
    }

}
