#ifndef GAME_STATE
#define GAME_STATE

#include <iostream>

#include <application.hpp>
#include <states/game.cpp>
#include <states/menu.cpp>
#include <vector>
using std::vector;

class GameApp : public gameTemp::Application
{
    gameTemp::WindowConfiguration getWindowConfiguration() override
    {
        return {"Game State", {1280, 720}, false};
    }

    void onInitialize() override
    {
        nextState = new MenuState(this);
        glClearColor(0, 0, 0, 0);
    }

    void goToState(State *newState)
    {
        if (currState)
            currState->onExit();

        currState = newState;
        nextState = nullptr;
        currState->onEnter();
    };

    void onDraw(double deltaTime) override
    {
        if (nextState)
        {
            goToState(nextState);
        }

        if (currState)
            currState->onDraw(deltaTime);

        if (keyboard.justPressed(GLFW_KEY_ENTER))
        {
            if (currState->getName() == "MenuState")
            {
                goToState(new GameState(this));
            }
        }

        if (keyboard.justPressed(GLFW_KEY_ESCAPE))
        {
            if (currState->getName() == "GameState")
            {
                goToState(new MenuState(this));
            }
            else
            {
                if (currState)
                    currState->onExit();

                currState = nullptr;
            }
        }
    }

    void onDestroy() override
    {
    }
};

#endif