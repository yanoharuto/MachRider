#include "StopWatch.h"
#include "Clock.h"
#include "DxLib.h"
StopWatch::StopWatch()
{
    tempRunTime = 0;
    startTime = 0;
    stopFlag = true;
}

StopWatch::~StopWatch()
{
    tempRunTime = 0;
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
        tempRunTime += Clock::GetNowGameTime() - startTime;
    }
    stopFlag = true;
}

void StopWatch::Reset()
{
    tempRunTime = 0;
}

double StopWatch::GetRunTime()
{
    return tempRunTime + Clock::GetNowGameTime() - startTime;
}
