#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*inits glewInit*/
    if(glewInit() != GLEW_OK)
	    std::cout << "Glew init failed"<<std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
       -0.5f,-0.5f,
        0.0f,0.05f,
        0.5f,-0.5f
    };
    //creating a buffer
    unsigned int buffer{ 0 };
    glGenBuffers(1,&buffer);

    //select the buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    
    //specify the data
    glBufferData(GL_ARRAY_BUFFER, 6* sizeof(float),positions,GL_STATIC_DRAW);

    //
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float) *2,0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}