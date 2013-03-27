//
//  Shader.cpp
//  Shaders
//
//  Created by Hans Dulimarta on 02/24/13.
//
//
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#endif
#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include "Shader.h"

void Shader::load(const string& fname, int shader_type)
{
    ifstream sh_file (fname.c_str());
    string code;
    if (sh_file.is_open()) {
        while (sh_file)
        {
            string s;
            sh_file >> s;
            code.append(" " + s);
        }
//        cout << "Code is : " << code << endl;
        const char *code_str = code.c_str();
        sh_file.close();
        sh_id = glCreateShader(shader_type);
        glShaderSource(sh_id, 1, &code_str, NULL);
        glCompileShader(sh_id);
        int status;
        glGetShaderiv(sh_id, GL_COMPILE_STATUS, &status);
        if (!status) {
            GLint len;
            glGetShaderiv(sh_id, GL_INFO_LOG_LENGTH, &len);
            char *log = new char[len];
            glGetShaderInfoLog(sh_id, len, &len, log);
            cout << log << endl;
            delete [] log;
        }
    }
    else
        cerr << "File not found: " << fname << endl;
}
