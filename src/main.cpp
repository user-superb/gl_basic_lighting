#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "init_window.hpp"

#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"

#include "gl_cube.hpp"

const char* WINDOW_TITLE = "New window";

unsigned int SCR_WIDTH = 1920,
             SCR_HEIGHT = 1080;

int main(int argc, char const *argv[])
{   
    GLFWwindow *window = initWindow(WINDOW_TITLE, SCR_WIDTH, SCR_HEIGHT);
    if (!window) {
        return 1;
    }

    // gl: init settings
    // -----------------
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    /***************/
    /* load shader */
    /***************/
    Shader defaultShader("resources/shaders/defaultVertex.vert", "resources/shaders/defaultFragment.frag");
    Shader lightShader("resources/shaders/defaultVertex.vert", "resources/shaders/lightFragment.frag");

    /* load texture: */
    Texture texture("resources/textures/container.jpg", GL_RGB, GL_TEXTURE_2D, GL_TEXTURE0);

    /**********/
    /* Camera */
    /**********/
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f));

    /* Cube */
    Cube    cube(lightShader),
            light(defaultShader);
            
    cube.setPosition(glm::vec3(-2.0f, 0.0f, -2.0f));
    cube.objectColor = glm::vec3(1.0f, 0.8f, 0.0f);

    light.setPosition(glm::vec3(2.0f, 0.0f, -2.0f));
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    light.objectColor = lightColor;

    // Set active default shader
    // defaultShader.use();
    while(!glfwWindowShouldClose(window)) {
        // gl: clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texture.bind();

        // camera: update
        camera.input(window);

        // cube: update
        cube.rotate(glm::radians(0.1f), glm::vec3(0.0f, -1.0f, 1.0f));
        //cube.setPosition(glm::vec3(-5.0f, -2.0f, 0.0f));

        // light: update
        //light.setPosition(glm::vec3(sin(glfwGetTime() * 0.5f) * 5.0f, 0.0f, cos(glfwGetTime() * 0.5f) * 5.0f));
        //light.objectColor = lightColor;

        /* draw */
        camera.update(lightShader, "cameraMatrix");
        lightShader.setVec3("objectColor", cube.objectColor);
        lightShader.setVec3("lightColor", lightColor);
        lightShader.setVec3("lightPos", light.pos);
        lightShader.setVec3("viewPos", camera.position);
        cube.draw();

        camera.update(defaultShader, "cameraMatrix");
        defaultShader.setVec3("objectColor", light.objectColor);
        light.draw();

        // glfw: swap buffers and fetch IO events
        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
