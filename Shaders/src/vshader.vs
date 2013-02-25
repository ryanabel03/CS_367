void main()
{
    if (gl_Vertex.x * gl_Vertex.y * gl_Vertex.z > 0.0)
        gl_FrontColor = vec4 (0.3529, 0.745, 0.3529, 1.0);
    else
        gl_FrontColor = vec4 (0.9333, 0.412, 0.124, 1.0);
    
    /* multiply each vertex with the ModelView Matrix and
       Projection Matrix */
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}