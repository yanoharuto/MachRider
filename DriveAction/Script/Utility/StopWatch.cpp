#include "StopWatch.h"
#include "Clock.h"
#include "DxLib.h"
StopWatch::StopWatch()
{
    runTime = 0;
    startTime = 0;
    stopFlag = true;
}

StopWatch::~StopWatch()
{
    runTime = 0;
    startTime = 0;
}

void StopWatch::Run()
{
    startTime = Clock::GetNowGameTime();
    stopFlag = false;
}

void StopWatch::Stop()
{
    if (!stopFlag)
    {
        runTime += Clock::GetNowGameTime() - startTime;
    }
    stopFlag = true;
}

void StopWatch::Reset()
{
    runTime = 0;
}

double StopWatch::GetRunTime()
{
    return runTime + Clock::GetNowGameTime() - startTime;
}
