#include <fstream>
#include <string>
#include "StageDataEditor.h"
#include "UserInput.h"
#include "EditObjectData.h"
#include "UserInput.h"
#include "OriginalMath.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
//今編集しているオブジェクトのポジション
EditArrangementData StageDataEditor::nowEditObjData = {};
/// 収集アイテムの数
int StageDataEditor::collectNum = 0;

/// 収集アイテムを取ったどのタイミングで出てくるか
int StageDataEditor::missionNum = 0;
//選択している物の位置を表す
int StageDataEditor::selectAura = -1;
//選択している物の向きを表す
int StageDataEditor::dirEffect = -1;
/// <summary>
///ステージに配置するオブジェクトの位置などを保存する
/// </summary>
/// <param name="setFileName">どのファイルに保存するか教えて</param>
StageDataEditor::StageDataEditor(std::string setFileName)
{
    saveFileName = setFileName;
    missionNum = 0;
    collectNum = 0;
    //選択エフェクト
    if (selectAura == -1)
    {
        EffectManager::LoadEffect(collectAura);
        EffectManager::LoadEffect(compass);
        selectAura = EffectManager::GetPlayEffect3D(collectAura);
        dirEffect = EffectManager::GetPlayEffect3D(compass);
    }
    //もしすでにファイルがあるならデータを取ってくる
    editDataVec = FirstPositionGetter::CSVConvertFirstData(setFileName);
    //一度ファイルを削除
    remove(saveFileName.c_str());
}

StageDataEditor::~StageDataEditor()
{
}
/// <summary>
/// 今編集しているオブジェクトのポジション
/// </summary>
/// <returns></returns>
VECTOR StageDataEditor::GetEditObjPos()
{
    return  VGet(nowEditObjData.posX,0,nowEditObjData.posZ);
}
/// <summary>
/// 何番目のミッションか変更する
/// </summary>
void StageDataEditor::ChangeMissionNum()
{
    if (UserInput::GetInputState(SKey) == Hold)
    {
        if (UserInput::GetInputState(Up) == Push)
        {
            //収集アイテムの数より多くならない
            if (missionNum + 1 > collectNum)
            {
                missionNum = collectNum;
            }
            else
            {
                missionNum++;
            }
        }
        else if (UserInput::GetInputState(Down) == Push)
        {
            //0より少なくならない
            if (missionNum - 1 < 0)
            {
                missionNum = 0;
            }
            else
            {
                missionNum--;
            }
        }
    }
}
/// <summary>
/// 編集済みデータの削除
/// </summary>
/// <param name="eraceNum">削除するのは先頭から何番目か</param>
void StageDataEditor::EraceEndEditData(int eraceNum)
{
    auto editData = editDataVec.begin();
    editData += eraceNum;
    editDataVec.erase(editData);
}

/// <summary>
/// 引数の情報を書き込む
/// </summary>
/// <param name="data"></param>
void StageDataEditor::SaveEditObjectData(EditArrangementData data)const
{
    std::ofstream writing_file;
    // ファイルを開いて
    writing_file.open(saveFileName, std::ios::app);
    //区切り文字
    std::string colon = ",";
    //オブジェクトの種類と
    writing_file << std::to_string(data.objKind) + colon << std::endl;
    //何番目のミッションの時か
    writing_file << std::to_string(data.missionNum) + colon << std::endl;
    //位置
    writing_file << std::to_string(data.posX) + colon << std::endl;
    writing_file << std::to_string(data.posZ) + colon << std::endl;
    //向き
    writing_file << std::to_string(data.dirX) + colon << std::endl;
    writing_file << std::to_string(data.dirZ) + colon << std::endl;
    writing_file.close();
}
/// <summary>
/// 選択物の向きと位置がわかるエフェクトの更新
/// </summary>
void StageDataEditor::UpdateEffect()
{
    VECTOR dir = VGet(nowEditObjData.dirX, 0, nowEditObjData.dirZ);
    //選択した物の方向が分かるエフェクトを回転する
    float degree = OriginalMath::GetDegreeMisalignment(VGet(1,0,0),dir);
    if (VCross(VGet(1, 0, 0),dir).y < 0)
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, -degree * RAGE, 0);
    }
    else
    {
        SetRotationPlayingEffekseer3DEffect(dirEffect, 0, degree * RAGE, 0);
    }
    //選択した物のポジションが分かるエフェクト
    SetPosPlayingEffekseer3DEffect(selectAura, nowEditObjData.posX, 0, nowEditObjData.posZ);
    SetPosPlayingEffekseer3DEffect(dirEffect, nowEditObjData.posX, 0, nowEditObjData.posZ);
}