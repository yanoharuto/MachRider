#include "EnemyDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorModelViewer.h"
#include "CircleFlyShipViewer.h"


/// <summary>
/// 敵の編集クラス
/// </summary>
EnemyDataEditor::EnemyDataEditor()
    :StageDataEditor("enemyData.csv")
{
    nowEditEne = new EditorObject(nowEditKind);
    //各エネミーの描画担当役
    using enum ObjectInit::InitObjKind;
    eneViewerMap.insert(std::make_pair(saw, new EditorModelViewer(saw)));
    eneViewerMap.insert(std::make_pair(upDownLaserShip, new EditorModelViewer(upDownLaserShip)));
    eneViewerMap.insert(std::make_pair(circleLaserShip, new CircleFlyShipViewer()));
    eneViewerMap.insert(std::make_pair(bomberShip, new EditorModelViewer(bomberShip)));
    eneViewerMap.insert(std::make_pair(moveSaw, new EditorModelViewer(moveSaw)));
}
/// <summary>
/// 書き込みとDelete
/// </summary>
EnemyDataEditor::~EnemyDataEditor()
{
    int size = editDataVec.size();
    for (int i = 0; i < size; i++)
    {
        SaveEditObjectData(editDataVec[i]);
    }
    
    for (auto itr = eneViewerMap.begin(); itr!=eneViewerMap.end(); itr++)
    {
        SAFE_DELETE((*itr).second);
    }
    SAFE_DELETE(nowEditEne);
}
/// <summary>
/// 更新
/// </summary>
void EnemyDataEditor::Update()
{
    if (isEndEdit || isSelectEditedEne)//編集中じゃないなら
    {
        //編集するエネミーを選択
        SelectEnemy();
        //スペースキーを押したら編集モードに
        if (UserInput::GetInputState(Space) == Push)
        {
            isSelectEditedEne = false;
            isEndEdit = false;
        }
        else//押してない
        {
            //過去のエネミーを選択途中ならまだ更新し続ける
            isSelectEditedEne = selectEditedEneNum != -1;
            isEndEdit = !isSelectEditedEne;
        }
    }
    else //編集中
    {
        EditSelectEnemy();
    }
    //カメラに見るべきオブジェクトを伝える
    nowEditObjData = nowEditEne->GetEditObjectData();
    //エフェクトの位置などを更新
    UpdateEffect();
}
/// <summary>
/// 編集済みのオブジェクトを描画
/// </summary>
void EnemyDataEditor::DrawAllEditedObject() const
{
    if (!editDataVec.empty())//コンテナ内のオブジェクト全て描画
    {
        int size = editDataVec.size();
        for (int i = 0; i < size; i++)
        {
            //描画するオブジェクトの種類
            auto drawKind = static_cast<ObjectInit::InitObjKind>(editDataVec[i].objKind);
            eneViewerMap.find(drawKind)->second->Draw(editDataVec[i]);
        }
    }
}
/// <summary>
/// 現在編集している物を描画
/// </summary>
void EnemyDataEditor::DrawNowEditObject() const
{
    //今編集しているエネミーの描画担当役に描画してもらう
    eneViewerMap.find(nowEditKind)->second->SelectDraw(nowEditEne->GetEditObjectData());
}
/// <summary>
/// 文字を描画
/// </summary>
void EnemyDataEditor::DrawEditString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), GetColor(0, 0, 0));
}
/// <summary>
/// 選択されているときの文字を描画
/// </summary>
void EnemyDataEditor::DrawSelectString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), selectColor);
}
/// <summary>
/// 編集するエネミーを選択
/// </summary>
void EnemyDataEditor::SelectEnemy()
{
    //過去のエネミーを再選択
    SelectEditedEnemy();

    using enum ObjectInit::InitObjKind;
    ObjectInit::InitObjKind prevKind = nowEditKind;
    auto nowEditData = nowEditEne->GetEditObjectData();
    //左右キーで種類変更
    if (UserInput::GetInputState(Right) == Push)
    {
        switch (nowEditKind)
        {
        case saw:
            nowEditKind = moveSaw;
            break;
        case upDownLaserShip:
            nowEditKind = saw;
            break;
        case circleLaserShip:
            nowEditKind = upDownLaserShip;
            break;
        case bomberShip:
            nowEditKind = circleLaserShip;
            break;
        case moveSaw:
            nowEditKind = bomberShip;
            break;
        }
    }
    else if (UserInput::GetInputState(Left) == Push)
    {
        switch (nowEditKind)
        {
        case saw:
            nowEditKind = upDownLaserShip;
            break;
        case upDownLaserShip:
            nowEditKind = circleLaserShip;
            break;
        case circleLaserShip:
            nowEditKind = bomberShip;
            break;
        case bomberShip:
            nowEditKind = moveSaw;
            break;
        case moveSaw:
            nowEditKind = saw;
        }
    }
    //配置されたり種類を変更されたらmodelを変更する
    if (nowEditKind != prevKind)
    {
        SAFE_DELETE(nowEditEne);
        nowEditData.objKind = nowEditKind;
        nowEditEne = new EditorObject(nowEditData);
    }
}
/// <summary>
/// 編集した過去のエネミーを再編集できるようにする
/// </summary>
void EnemyDataEditor::SelectEditedEnemy()
{
    //すでに編集したことがあるなら
    if (!editDataVec.empty())
    {
        //UpかDownキーを押してたら変更
        const int prevNum = selectEditedEneNum;
        //上下キーで再編集するものを変更
        if (UserInput::GetInputState(Down) == Push)selectEditedEneNum++;
        
        if (UserInput::GetInputState(Up) == Push)selectEditedEneNum--;
        //上下キーを押して対象を変更したら-1以上になる
        if (selectEditedEneNum > -1 && selectEditedEneNum != prevNum)
        {
            if (selectEditedEneNum >= editDataVec.size())
            {
                //過去に編集したエネミーの数より少なくなっているか
                selectEditedEneNum = editDataVec.size() - 1;
            }
            //過去に編集したエネミーを所得
            auto editedData = editDataVec[selectEditedEneNum];
            nowEditKind = static_cast<ObjectInit::InitObjKind>(editedData.objKind);
            //出てくるタイミングも同じにする
            missionNum = editedData.missionNum;
            missionNum = missionNum > collectNum ? collectNum : missionNum;
            SAFE_DELETE(nowEditEne);
            nowEditEne = new EditorObject(editedData);
        }
        else if(selectEditedEneNum < -1)//-1だったら新しく作ろうとしている
        {
            selectEditedEneNum = -1;
        }
    }
}

/// <summary>
/// 選択したエネミーの編集
/// </summary>
void EnemyDataEditor::EditSelectEnemy()
{
    //移動回転
    nowEditEne->Update();
    //編集終了
    if (UserInput::GetInputState(Space) == Push)
    {
        //編集したタイミングのミッション数を記録
        auto saveData = nowEditEne->GetEditObjectData();
        saveData.missionNum = missionNum;
        //過去のアイテムを選択していたら
        if (!isEndEdit && selectEditedEneNum != -1)
        {
            //過去のアイテムを再納品
            editDataVec[selectEditedEneNum] = saveData;
            selectEditedEneNum = -1;
        }
        else
        {
            //編集終了コンテナに納品
            editDataVec.push_back(saveData);
        }
        isEndEdit = true;
    }
    //破棄して終了
    else if (UserInput::GetInputState(DKey) == Push)
    {
        if (selectEditedEneNum != -1)//昔編集したものを削除
        {
            EraceEndEditData(selectEditedEneNum);
            selectEditedEneNum = -1;
        }
        isEndEdit = true;
    }
}
