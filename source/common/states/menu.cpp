#ifndef MENUSTATE
#define MENUSTATE

#include <application.hpp>
#include <shader.hpp>

#include<iostream>
class GameState;

class MenuState : public gameTemp::Application
{
    gameTemp::ShaderProgram programS, programH, programP, programG;

    gameTemp::Mouse &mouse = this->getMouse();
    gameTemp::Keyboard &keyboard = this->getKeyboard();
    GLuint vertex_array = 0;

    glm::vec2 mousePos = glm::vec2(mouse.getMousePosition().x, mouse.getMousePosition().y);
    int shapeNum = 1;

    gameTemp::WindowConfiguration getWindowConfiguration() override
    {
        return {"Game", {1280, 720}, false};
    }

    void onInitialize() override
    {
        programS.create();
        programS.attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programS.attach("assets/shaders/Smiley/smiley.frag", GL_FRAGMENT_SHADER);
        programS.link();

        programH.create();
        programH.attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programH.attach("assets/shaders/Heart/heart.frag", GL_FRAGMENT_SHADER);
        programH.link();

        programP.create();
        programP.attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programP.attach("assets/shaders/Pacman/pacman.frag", GL_FRAGMENT_SHADER);
        programP.link();

        programG.create();
        programG.attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programG.attach("assets/shaders/G/g.frag", GL_FRAGMENT_SHADER);
        programG.link();

        glGenVertexArrays(1, &vertex_array);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glUseProgram(programS);
    }

    void onDraw(double deltaTime) override
    {
        
        glClear(GL_COLOR_BUFFER_BIT);

        GLuint mouse_uniform_location = glGetUniformLocation(programS, "mouseCoord");
        glUniform2f(mouse_uniform_location, mouse.getMousePosition().x, mouse.getMousePosition().y);
        GLuint mouse_uniform_location1 = glGetUniformLocation(programH, "mouseCoord");
        glUniform2f(mouse_uniform_location1, mouse.getMousePosition().x, mouse.getMousePosition().y);
        GLuint mouse_uniform_location2 = glGetUniformLocation(programP, "mouseCoord");
        glUniform2f(mouse_uniform_location2, mouse.getMousePosition().x, mouse.getMousePosition().y);
        GLuint mouse_uniform_location3 = glGetUniformLocation(programG, "mouseCoord");
        glUniform2f(mouse_uniform_location3, mouse.getMousePosition().x, mouse.getMousePosition().y);

        if (keyboard.isPressed(GLFW_KEY_A))
        {
            glUseProgram(programS);
        }
        else if (keyboard.isPressed(GLFW_KEY_S))
        {
            glUseProgram(programH);
        }
        else if (keyboard.isPressed(GLFW_KEY_D))
        {
            glUseProgram(programP);
        }
        else if (keyboard.isPressed(GLFW_KEY_W))
        {
            glUseProgram(programG);
        }
        else if (keyboard.isPressed(GLFW_KEY_ENTER))
        {
            this->nextStateId = GAME_STATE_ID;
        }
        /*else if (keyboard.isPressed(GLFW_KEY_ESCAPE))
        {
            this->nextStateId = -1;
        }*/
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void onDestroy() override
    {
        programS.destroy();
        programH.destroy();
        programP.destroy();
        programG.destroy();
        glDeleteVertexArrays(1, &vertex_array);

    }

};

#endif

