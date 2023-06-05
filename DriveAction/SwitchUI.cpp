#include "SwitchUI.h"
#include "Utility.h"
#include "Timer.h"
SwitchUI::SwitchUI()
{
    timer = new Timer(span);
}

SwitchUI::~SwitchUI()
{
    SAFE_DELETE(timer);
}

void SwitchUI::Update()
{
}

void SwitchUI::Draw()
{
    
}
