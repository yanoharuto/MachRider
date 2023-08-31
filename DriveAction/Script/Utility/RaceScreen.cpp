#include "RaceScreen.h"
#include "Utility.h"
int RaceScreen::screen = -1;
/// <summary>
/// •`‰æ‚µ‚½‰æ‘œ‚ğ•Û‘¶‚·‚é
/// </summary>
RaceScreen::RaceScreen()
{
    DeleteGraph(screen);
    screen = -1;
}

RaceScreen::~RaceScreen()
{
    DeleteGraph(screen);
    screen = -1;
}

/// <summary>
/// •`‰æ‚µ‚Ä‚¢‚é‰æ‘œ‚ğXV
/// </summary>
void RaceScreen::ScreenUpdate()
{
    DeleteGraph(screen);
    screen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen);
}

int RaceScreen::GetScreen()
{
    return screen;
}


