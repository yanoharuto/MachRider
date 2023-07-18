#pragma once
class StopWatch
{
public:
    StopWatch();
    ~StopWatch();
    void Run();
    void Stop();
    void Reset();
    double GetRunTime();
private:
    bool stopFlag;
    double runTime;
    double startTime;
};