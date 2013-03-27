//
//  Shader.h
//  Shaders
//
//  Created by Hans Dulimarta on 02/24/13.
//
//

#ifndef __Shaders__Shader__
#define __Shaders__Shader__

#include <string>
using namespace std;
class Shader {
public:
    void load (const string& file_name, int shader_type);
    int id() const { return sh_id; }
private:
    int sh_id;
};
#endif /* defined(__Shaders__Shader__) */
