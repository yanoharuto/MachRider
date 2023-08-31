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
class StageObjectController final : public ActorController
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    StageObjectController();
    ///modelをデリート
    ~StageObjectController() override;
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw()const override;
private:
    //地面
    int floorModelHandle;
    //空
    int skyDomeModelHandle;
    //壁
    StageWall* stageWall;
};