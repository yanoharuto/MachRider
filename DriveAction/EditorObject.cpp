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
EditorObject::EditorObject(ObjectInit::InitObjKind kind)
    :Actor(kind)
{
    objKind = kind;
}
/// <summary>
/// 位置や方向を変更した状態で
/// </summary>
/// <param name="editData"></param>
EditorObject::EditorObject(EditArrangementData editData)
    :Actor(static_cast<ObjectInit::InitObjKind>(editData.objKind))
{
    objKind = static_cast<ObjectInit::InitObjKind>(editData.objKind);
    position = VGet(editData.posX, 0, editData.posZ);
    direction = VGet(editData.dirX, 0, editData.dirZ);
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
/// オブジェクトの位置や回転などを渡す
/// </summary>
/// <returns></returns>
EditArrangementData EditorObject::GetEditObjectData() const
{
    EditArrangementData data;
    data.dirX = direction.x;
    data.dirZ = direction.z;
    data.posX = position.x;
    data.posZ = position.z;
    data.objKind = objKind;
    return data;
}
/// <summary>
/// 入力を反映して移動と回転を更新
/// </summary>
void EditorObject::ReflectInput()
{
    if (UserInput::GetInputState(WKey) == Hold)//ｗキーを押してたら回転モード
    {
        float rotate = 0;
        if (UserInput::GetInputState(Left) == Hold)rotate = -rotaSpeed;
        else if (UserInput::GetInputState(Right) == Hold)rotate = +rotaSpeed;
        
        direction = OriginalMath::GetYRotateVector(direction, rotate);

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
