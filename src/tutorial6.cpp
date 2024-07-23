#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
//#include "stb/stb_image.h"  // Ensure this path matches the structure
//#include "C:/Users/jackp/vcpkg/tutorial2/libs/stb/stb_image.h" 
#include "stb_image.h"  // Use the relative path now that the include directory is set

// Rest of your code



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};



int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);
    std::cout << "Viewport set successfully" << std::endl;

    // Print current working directory
    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;

    // Check if the shader files exist
    std::string vertexPath = "C:/Users/jackp/vcpkg/tutorial2/resource/default.vert";
    std::string fragmentPath = "C:/Users/jackp/vcpkg/tutorial2/resource/default.frag";

    if (std::filesystem::exists(vertexPath)) {
        std::cout << "Vertex shader file exists at: " << vertexPath << std::endl;
    } else {
        std::cout << "Vertex shader file NOT found at: " << vertexPath << std::endl;
    }

    if (std::filesystem::exists(fragmentPath)) {
        std::cout << "Fragment shader file exists at: " << fragmentPath << std::endl;
    } else {
        std::cout << "Fragment shader file NOT found at: " << fragmentPath << std::endl;
    }

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram(vertexPath.c_str(), fragmentPath.c_str());
    std::cout << "Shader Program created successfully" << std::endl;


    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();
    std::cout << "VAO generated and bound successfully" << std::endl;

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    std::cout << "VBO generated and bound successfully" << std::endl;

    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));
    std::cout << "EBO generated and bound successfully" << std::endl;

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 6 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    std::cout << "VAO, VBO, and EBO unbound successfully" << std::endl;

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // gl Text....

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    shaderProgram.Activate();
    glUniform1i(tex0Uni, 0);


    // Main while loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f);
        glBindTexture(GL_TEXTURE_2D, texture);
      //  std::cout << "Shader Program activated successfully" << std::endl;
        VAO1.Bind();
        //std::cout << "VAO bound successfully" << std::endl;
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //std::cout << "Primitives drawn successfully" << std::endl;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    glDeleteTextures(1, &texture);
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
