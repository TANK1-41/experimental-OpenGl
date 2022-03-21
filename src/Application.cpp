#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "texture.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void framebuffer_size_callback(GLFWwindow *window, int width = 640, int height = 480) {
    glViewport(0, 0, width, height);
}

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //sets to core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window) {
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
    if (glewInit() != GLEW_OK)
        std::cout << "Glew init failed" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {

        float positions[] = {
                //first triangle
                -50.f, -50.f, 0.0f, 0.0f,//0
                 50.f, -50.f, 1.0f, 0.0f,//1
                 50.f, 50.f, 1.0f, 1.0f,//2
                //second triangle

                -50.f, 50.f, 0.0f, 1.0f//3

        };

        unsigned int indices[]{
                0, 1, 2,//first triangle
                2, 3, 0 //second triangle
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
        va.AddBuffer(vb, layout);

        //creating a index buffer
        IndexBuffer ib(indices, 6);
        //math for aspect ratio
        glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
        //camera view
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
        //model matrix translation used in game loop
        glm::vec3 translationA(200,200,0);
        glm::vec3 translationB(400,200,0);


        Shader shader("res/shaders/basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);


        Texture texture("res/textures/cherno.png");
        texture.Bind();
        shader.SetUniform4i("u_Texture", 0);
        //used to increment the uniform color
        float red = 0.0f;
        float incrementColor = 0.05f;

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
        //imgui sample window vars


        shader.Unbind();
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.clear();

            ImGui_ImplGlfwGL3_NewFrame();

            shader.Bind();
            {
                //model matrixA
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.draw(va, ib, shader);
            }

            {
                //model matrixB
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.draw(va, ib, shader);
            }

            shader.SetUniform4i("u_Texture", 0);
            //increments color every frame
            if (red > 1.0f) {
                incrementColor = -0.05f;
            } else if (red < 0.0f) {
                incrementColor = 0.05f;
            }
            red += incrementColor;



            // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
            {
                ImGui::SliderFloat3("translationA", &translationA.x, 0.0f, 960.f);
                ImGui::SliderFloat3("translationB", &translationB.x, 0.0f, 960.f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    glfwTerminate();
    return 0;
}
