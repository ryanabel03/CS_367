#include "Model.h"
#include <iostream>
using namespace std;

Model::Model ()
{
    list_id = -1;
}

Model::~Model ()
{
    if (list_id != -1)
        glDeleteLists (list_id, 1);
}

void Model::draw()
{
    glColor3f(r, g, b);
    if (list_id != -1) glCallList (list_id);
    else cout << "Trying to draw uninstantiated model" << endl;
}
