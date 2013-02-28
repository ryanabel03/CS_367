#ifndef HANS_MODEL_H
#define HANS_MODEL_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Model {
public:
    Model();
    virtual ~Model();

    virtual void newInstance() = 0;
    virtual void draw();
    void setColor (float r,float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

protected:
    GLint list_id;
    float r,g,b;
};
#endif
