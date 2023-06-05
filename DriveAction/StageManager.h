#pragma once
#include <string>
class CircuitTrack;
class SkyDome;
class FirstPositionGetter;
/// <summary>
/// コースのロードや描画とか当たり判定とかする
/// </summary>
class StageManager
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    StageManager();
    ~StageManager();
    void Update();
    void Draw()const;
    
private:
    CircuitTrack* circuit;
    SkyDome* skyDome;
    FirstPositionGetter* firstPositionGeneratetor;

};