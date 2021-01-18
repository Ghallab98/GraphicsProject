#ifndef MENU_STATE_CPP
#define MENU_STATE_CPP

#include <states/state.cpp>
#include "../texture/texture2D.hpp"

class MenuState : public State
{
    gameTemp::Mouse &mouse = app->getMouse();
    gameTemp::Keyboard &keyboard = app->getKeyboard();

    GLuint vertex_array = 0;
    glm::vec2 mousePos = glm::vec2(mouse.getMousePosition().x, mouse.getMousePosition().y);
    GLuint texture;
    Texture text;
    int level_of_detail = 0;
    float zoom = 1.45;

public:
    MenuState(Application *app = nullptr) : State(app)
    {
        name = "MenuState";
    }

    void onEnter() override
    {
        programs["Start"].create();
        programs["Start"].attach("assets/shaders/pic/fullscreen_triangle.vert", GL_VERTEX_SHADER);
        programs["Start"].attach("assets/shaders/pic/texel_fetch.frag", GL_FRAGMENT_SHADER);
        programs["Start"].link();
        glGenVertexArrays(1, &vertex_array);
        texture = text.getTexture();
        glGenTextures(1, &texture);
        text.create(true, 0, 0, 0, 0, "assets/images/DSC100668434.jpg");
        glUseProgram(programs["Start"]);
    }

    void onDraw(double deltaTime) override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        texture = text.getTexture();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        programs["Start"].set("sampler", 0);

        programs["Start"].set("lod", level_of_detail);
        programs["Start"].set("zoom", zoom);

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    void onExit() override
    {
        glDeleteVertexArrays(1, &vertex_array);
        text.destroy();
        State::onExit();
    }
};

#endif
