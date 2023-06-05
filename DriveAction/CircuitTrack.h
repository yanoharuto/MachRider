#pragma once
#include <string>
#include <vector>
class StageWall;
class Rock;
class FirstPositionGetter;
/// <summary>
/// 走る場所
/// </summary>
class CircuitTrack final
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    CircuitTrack(FirstPositionGetter* firstPosGetter);
    ///modelをデリート
    ~CircuitTrack();
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw();
private:

    //コースの外側のmodelのポジション
    const float rockYPos = 20;
    //地面
    int floorModelHandle;
    std::vector<Rock*> rocks;
    StageWall* stageWall;
};