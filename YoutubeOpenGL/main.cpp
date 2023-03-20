#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<shader.h>
#include<stb_image.h>
#include<glm-0.9.9.8/glm/glm.hpp>
#include<glm-0.9.9.8/glm/gtc/matrix_transform.hpp>
#include<glm-0.9.9.8/glm/gtc/type_ptr.hpp>
#include <iostream>
#include<cmath>
#include<time.h>

float cameraSpeedf = 0.09f;
float cameraSpeeds = 0.09f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 960;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lightPos = cameraPos;

void assign(glm::vec3 arr[]) {
    //time_t t;
    //srand((unsigned)time(&t));
    for (int i = 0; i < 24; i++)
    {
        float x, z;
        z = -30.0f + rand() % 15; 
        for (int j = 0; j < 6; j++)
        {
            x = -5.0f + rand() % 10;
            arr[i] = glm::vec3(x, 0.0f, z);
            printf("\n%f\t%f", x, z);
        }
        
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourshader("texture.vs", "texture.fs");  
    glEnable(GL_DEPTH_TEST);
    

    float vertices[] = {//infinite ground plane
        //position                  //color
         7.5f, -0.5f, -600.0f,    0.145f, 0.796f, 0.250f,   //rght far                          
         7.5f, -0.5f,   10.0f,    0.145f, 0.796f, 0.250f,   //rght behind                           
       - 7.5f, -0.5f,   10.0f,    0.145f, 0.796f, 0.250f,   //left behind                           
       - 7.5f, -0.5f, -600.0f,    0.145f, 0.796f, 0.250f    //left far
    };


    unsigned int indices[] = {      //for green ground plane
        0, 1, 3,
        3, 1, 2
    };
    
    
    float cube_vert[] = {//objects 
        -0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,

        -0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,

        -0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,

         0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,

        -0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
         0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f, -0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f, -0.5f, -0.5f,        0.039f, 0.321f, 0.082f,

        -0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
         0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f,  0.5f,  0.5f,        0.039f, 0.321f, 0.082f,
        -0.5f,  0.5f, -0.5f,        0.039f, 0.321f, 0.082f,
    };

    unsigned int cube_int[] = {
        0, 1, 3,
        3, 1, 2
    };

    glm::vec3 arr[24];
    assign(arr);
      
    
    
    unsigned int VBO[2], VAO[2], EBO[2], lightVAO;
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);
    glGenVertexArrays(1, &lightVAO);

    glBindVertexArray(VAO[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vert), cube_vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_int), cube_int, GL_STATIC_DRAW);

    ourshader.use();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(30.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(ourshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window))
    {
        
        //cameraPos.z -= 0.02f;
        processInput(window);
        glClearColor(0.133f, 0.305f, 0.945f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(ourshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(ourshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
              

        ourshader.use();
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        for (int i = 0; i < 24; i++)
        {
            glBindVertexArray(VAO[1]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            model = glm::translate(model,arr[i]);
            glUniformMatrix4fv(glGetUniformLocation(ourshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
        while (cameraPos.z < -600.0f)
        {
            cameraPos.z = 0.0f;
            cameraSpeedf += 0.01f;
            assign(arr);
        }
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    
    // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeedf * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeeds * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeeds;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeeds;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && (cameraPos.y < 1.5f))    
        cameraPos += cameraSpeeds * cameraUp;    
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && cameraPos.y>0.5f)
        cameraPos -= cameraSpeeds * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}