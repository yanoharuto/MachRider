#include "EditorObject.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "EditorCamera.h"
//移動速度
const int EditorObject::moveSpeed;
//回転速度
const int EditorObject::rotaSpeed;

/// <summary>
/// エディタ上で使用するオブジェクト
/// </summary>
EditorObject::EditorObject()
    :Object()
{
    position = {};
    direction = VGet(1, 0, 0);
}

EditorObject::~EditorObject()
{
}
/// <summary>
/// 各オブジェクトを動かしたり回転させたりする
/// </summary>
void EditorObject::Update()
{
    ReflectInput();
}
/// <summary>
/// 描画に必要な構造体を渡す
/// </summary>
/// <returns>位置と向きと描画したいオブジェクトの種類</returns>
PlacementData EditorObject::GePlacementData() const
{
    PlacementData data;
    //向き
    data.dirX = direction.x;
    data.dirZ = direction.z;
    //ポジション
    data.posX = position.x;
    data.posZ = position.z;
    return data;
}
/// <summary>
/// 引数の配置を引き継ぎ位置を変える
/// </summary>
/// <param name="setData">配置</param>
void EditorObject::SetArrangementData(PlacementData setData)
{
    position = VGet(setData.posX, 0, setData.posZ);
    direction = VGet(setData.dirX, 0, setData.dirZ);
}
/// <summary>
/// 入力を反映して移動と回転を更新
/// </summary>
void EditorObject::ReflectInput()
{
    if (UserInput::GetInputState(WKey) == Hold)//ｗキーを押してたら回転モード
    {
       
        //左右キーを押すと回転する
        if (UserInput::GetInputState(Left) == Hold)
        {
           direction = OriginalMath::GetYRotateVector(direction, -rotaSpeed);
        }
        else if (UserInput::GetInputState(Right) == Hold)
        {
            direction = OriginalMath::GetYRotateVector(direction, rotaSpeed);
        }
    }
    else //押してなかったら移動モード
    {
        //カメラの向きに合わせて移動
        VECTOR cameraDir = EditorCamera::GetNormDirection();

        if (UserInput::GetInputState(Left) == Hold)//左移動
        {
            cameraDir = VCross(cameraDir, VGet(0, 1, 0));
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
        else if (UserInput::GetInputState(Right) == Hold)//右移動
        {
            cameraDir = VCross(cameraDir, VGet(0, -1, 0));
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
        if (UserInput::GetInputState(Up) == Hold)//前移動
        {
            cameraDir = VScale(cameraDir, moveSpeed);
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
        else if (UserInput::GetInputState(Down) == Hold)//後ろ移動
        {
            cameraDir = VScale(cameraDir, -moveSpeed);
            position = VAdd(position, VScale(cameraDir, moveSpeed));
        }
    }
}
