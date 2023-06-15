#pragma once
#include <string>
#include <vector>
#include "ActorController.h"
class StageWall;
class Rock;
class FirstPositionGetter;
/// <summary>
/// 走る場所
/// </summary>
class StageObjectController final:public ActorController
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    StageObjectController(FirstPositionGetter* firstPosGetter);
    ///modelをデリート
    ~StageObjectController() override;
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw()const override;
private:

    //コースの外側のmodelのポジション
    const float rockYPos = 20;
    //地面
    int floorModelHandle;
    int skyDomeModelHandle;
};