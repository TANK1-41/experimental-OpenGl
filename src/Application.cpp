#include<string>
#include<sstream>
#include<fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "texture.h"
#include "VertexBufferLayout.h"


void framebuffer_size_callback(GLFWwindow* window, int width = 640, int height=480)
{
	glViewport(0, 0, width, height);

}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    //sets to core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //sets vsync or monitor refresh rate
    glfwSwapInterval(1);
    //specifies the view of the window -https://learnopengl.com/Getting-started/Hello-Window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /*inits glewInit*/
    if(glewInit() != GLEW_OK)
	    std::cout << "Glew init failed"<<std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        
        float positions[] = {
          //first triangle
          -0.5f,-0.5f, 0.0f,0.0f, //0
          0.5f,-0.5f,1.0f,0.0f,//1
          0.5f,0.5f, 1.0f,1.0f,//2
          //second triangle

          -0.5f,0.5f, 0.0f,1.0f//3

        };

        unsigned int indices[]{
            0,1,2,//first triangle
            2,3,0//second triangle
        };
        //enables blending for textures
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        //create vertex array
        VertexArray va;

        //creating a buffer
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        //vertex buffer layout
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb,layout);

        //creating a index buffer
        IndexBuffer ib(indices, 6);
        
        Shader shader("res/shaders/basic.shader");
        shader.Bind();

        //shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/cherno.png");
        texture.Bind();
        shader.SetUniform4i("u_Texture",0);
        //used to increment the uniform color
        float red = 0.0f;
        float incrementColor = 0.05f;

        Renderer renderer;

        shader.Unbind();
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.clear();

            shader.Bind();
            shader.SetUniform4i("u_Texture",0);
            //shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);
            
            renderer.draw(va,ib,shader);

            //increments color every frame 
            if (red > 1.0f) {
                incrementColor = -0.05f;
            }
            else if (red < 0.0f) {
                incrementColor = 0.05f;
            }
            red += incrementColor;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
