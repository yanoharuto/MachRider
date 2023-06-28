#include "RaceScreen.h"
#include "Utility.h"
int RaceScreen::screen = -1;
/// <summary>
/// �`�悵���摜��ۑ�����
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
/// �`�悵�Ă���摜���X�V
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


