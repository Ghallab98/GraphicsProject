#ifndef MENU_STATE_CPP
#define MENU_STATE_CPP

#include <states/state.cpp>

class MenuState : public State
{
    gameTemp::Mouse &mouse = app->getMouse();
    gameTemp::Keyboard &keyboard = app->getKeyboard();

    GLuint vertex_array = 0;
    glm::vec2 mousePos = glm::vec2(mouse.getMousePosition().x, mouse.getMousePosition().y);

public:
    MenuState(Application *app = nullptr) : State(app)
    {
        name = "MenuState";
    }

    void onEnter() override
    {
        programs["Smiley"].create();
        programs["Smiley"].attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programs["Smiley"].attach("assets/shaders/Smiley/smiley.frag", GL_FRAGMENT_SHADER);
        programs["Smiley"].link();

        programs["Heart"].create();
        programs["Heart"].attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programs["Heart"].attach("assets/shaders/Heart/heart.frag", GL_FRAGMENT_SHADER);
        programs["Heart"].link();

        programs["Pacman"].create();
        programs["Pacman"].attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programs["Pacman"].attach("assets/shaders/Pacman/pacman.frag", GL_FRAGMENT_SHADER);
        programs["Pacman"].link();

        programs["G"].create();
        programs["G"].attach("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
        programs["G"].attach("assets/shaders/G/g.frag", GL_FRAGMENT_SHADER);
        programs["G"].link();

        glGenVertexArrays(1, &vertex_array);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glUseProgram(programs["Smiley"]);
    }

    void onDraw(double deltaTime) override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        GLuint mouse_uniform_location = glGetUniformLocation(programs["Smiley"], "mouseCoord");
        glUniform2f(mouse_uniform_location, mouse.getMousePosition().x, mouse.getMousePosition().y);

        GLuint mouse_uniform_location1 = glGetUniformLocation(programs["Heart"], "mouseCoord");
        glUniform2f(mouse_uniform_location1, mouse.getMousePosition().x, mouse.getMousePosition().y);

        GLuint mouse_uniform_location2 = glGetUniformLocation(programs["Pacman"], "mouseCoord");
        glUniform2f(mouse_uniform_location2, mouse.getMousePosition().x, mouse.getMousePosition().y);

        GLuint mouse_uniform_location3 = glGetUniformLocation(programs["G"], "mouseCoord");
        glUniform2f(mouse_uniform_location3, mouse.getMousePosition().x, mouse.getMousePosition().y);

        if (keyboard.isPressed(GLFW_KEY_A))
        {
            glUseProgram(programs["Smiley"]);
        }
        else if (keyboard.isPressed(GLFW_KEY_S))
        {
            glUseProgram(programs["Heart"]);
        }
        else if (keyboard.isPressed(GLFW_KEY_D))
        {
            glUseProgram(programs["Pacman"]);
        }
        else if (keyboard.isPressed(GLFW_KEY_W))
        {
            glUseProgram(programs["G"]);
        }

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void onExit() override
    {
        glDeleteVertexArrays(1, &vertex_array);
        State::onExit();
    }
};

#endif
