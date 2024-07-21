#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

class Shader
{
public:
    // The program ID
    GLuint ID;
    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // Use/activate the shader
    void Activate();
    // Delete the shader
    void Delete();
};

// Utility function to read shader source code from a file
std::string get_file_contents(const char* filename);

#endif
