#ifndef SOURCE
#define SOURCE

#include <application.hpp>
#include "./states/menu.cpp"
#include "./states/game.cpp"

using namespace std;

int main(int argc, char **argv)
{
    MenuState *MS = new MenuState();
    GameState *GS = new GameState();

    int currentState = MS->run(MENU_STATE_ID);
    while (MS->GetNextStateID() != -1 && GS->GetNextStateID() != -1)
    {
        if (currentState == GAME_STATE_ID)
        {
            currentState = GS->run(GAME_STATE_ID);
            if (GS->GetNextStateID() == MENU_STATE_ID)
            {
                currentState = MS->run(MENU_STATE_ID);
            }
        }
        else if (currentState == MENU_STATE_ID)
        {
            if (MS->GetNextStateID() == GAME_STATE_ID)
            {
                currentState = GS->run(GAME_STATE_ID);
            }
        }
    }
    return 0;
}
#endif