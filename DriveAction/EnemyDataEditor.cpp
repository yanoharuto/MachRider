#include "EnemyDataEditor.h"
#include "UserInput.h"
#include "EditorObject.h"
#include "Utility.h"
#include "EditorModelViewer.h"
#include "CircleFlyShipViewer.h"


/// <summary>
/// �G�̕ҏW�N���X
/// </summary>
EnemyDataEditor::EnemyDataEditor()
    :StageDataEditor("enemyData.csv")
{
    nowEditEne = new EditorObject(nowEditKind);
    //�e�G�l�~�[�̕`��S����
    using enum ObjectInit::InitObjKind;
    eneViewerMap.insert(std::make_pair(saw, new EditorModelViewer(saw)));
    eneViewerMap.insert(std::make_pair(upDownLaserShip, new EditorModelViewer(upDownLaserShip)));
    eneViewerMap.insert(std::make_pair(circleLaserShip, new CircleFlyShipViewer()));
    eneViewerMap.insert(std::make_pair(bomberShip, new EditorModelViewer(bomberShip)));
    eneViewerMap.insert(std::make_pair(moveSaw, new EditorModelViewer(moveSaw)));
}
/// <summary>
/// �������݂�Delete
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
/// �X�V
/// </summary>
void EnemyDataEditor::Update()
{
    if (isEndEdit || isSelectEditedEne)//�ҏW������Ȃ��Ȃ�
    {
        //�ҏW����G�l�~�[��I��
        SelectEnemy();
        //�X�y�[�X�L�[����������ҏW���[�h��
        if (UserInput::GetInputState(Space) == Push)
        {
            isSelectEditedEne = false;
            isEndEdit = false;
        }
        else//�����ĂȂ�
        {
            //�ߋ��̃G�l�~�[��I��r���Ȃ�܂��X�V��������
            isSelectEditedEne = selectEditedEneNum != -1;
            isEndEdit = !isSelectEditedEne;
        }
    }
    else //�ҏW��
    {
        EditSelectEnemy();
    }
    //�J�����Ɍ���ׂ��I�u�W�F�N�g��`����
    nowEditObjData = nowEditEne->GetEditObjectData();
    //�G�t�F�N�g�̈ʒu�Ȃǂ��X�V
    UpdateEffect();
}
/// <summary>
/// �ҏW�ς݂̃I�u�W�F�N�g��`��
/// </summary>
void EnemyDataEditor::DrawAllEditedObject() const
{
    if (!editDataVec.empty())//�R���e�i���̃I�u�W�F�N�g�S�ĕ`��
    {
        int size = editDataVec.size();
        for (int i = 0; i < size; i++)
        {
            //�`�悷��I�u�W�F�N�g�̎��
            auto drawKind = static_cast<ObjectInit::InitObjKind>(editDataVec[i].objKind);
            eneViewerMap.find(drawKind)->second->Draw(editDataVec[i]);
        }
    }
}
/// <summary>
/// ���ݕҏW���Ă��镨��`��
/// </summary>
void EnemyDataEditor::DrawNowEditObject() const
{
    //���ҏW���Ă���G�l�~�[�̕`��S�����ɕ`�悵�Ă��炤
    eneViewerMap.find(nowEditKind)->second->SelectDraw(nowEditEne->GetEditObjectData());
}
/// <summary>
/// ������`��
/// </summary>
void EnemyDataEditor::DrawEditString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), GetColor(0, 0, 0));
}
/// <summary>
/// �I������Ă���Ƃ��̕�����`��
/// </summary>
void EnemyDataEditor::DrawSelectString() const
{
    DrawString(0, drawStrY, drawEditString.c_str(), selectColor);
}
/// <summary>
/// �ҏW����G�l�~�[��I��
/// </summary>
void EnemyDataEditor::SelectEnemy()
{
    //�ߋ��̃G�l�~�[���đI��
    SelectEditedEnemy();

    using enum ObjectInit::InitObjKind;
    ObjectInit::InitObjKind prevKind = nowEditKind;
    auto nowEditData = nowEditEne->GetEditObjectData();
    //���E�L�[�Ŏ�ޕύX
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
    //�z�u���ꂽ���ނ�ύX���ꂽ��model��ύX����
    if (nowEditKind != prevKind)
    {
        SAFE_DELETE(nowEditEne);
        nowEditData.objKind = nowEditKind;
        nowEditEne = new EditorObject(nowEditData);
    }
}
/// <summary>
/// �ҏW�����ߋ��̃G�l�~�[���ĕҏW�ł���悤�ɂ���
/// </summary>
void EnemyDataEditor::SelectEditedEnemy()
{
    //���łɕҏW�������Ƃ�����Ȃ�
    if (!editDataVec.empty())
    {
        //Up��Down�L�[�������Ă���ύX
        const int prevNum = selectEditedEneNum;
        //�㉺�L�[�ōĕҏW������̂�ύX
        if (UserInput::GetInputState(Down) == Push)selectEditedEneNum++;
        
        if (UserInput::GetInputState(Up) == Push)selectEditedEneNum--;
        //�㉺�L�[�������đΏۂ�ύX������-1�ȏ�ɂȂ�
        if (selectEditedEneNum > -1 && selectEditedEneNum != prevNum)
        {
            if (selectEditedEneNum >= editDataVec.size())
            {
                //�ߋ��ɕҏW�����G�l�~�[�̐���菭�Ȃ��Ȃ��Ă��邩
                selectEditedEneNum = editDataVec.size() - 1;
            }
            //�ߋ��ɕҏW�����G�l�~�[������
            auto editedData = editDataVec[selectEditedEneNum];
            nowEditKind = static_cast<ObjectInit::InitObjKind>(editedData.objKind);
            //�o�Ă���^�C�~���O�������ɂ���
            missionNum = editedData.missionNum;
            missionNum = missionNum > collectNum ? collectNum : missionNum;
            SAFE_DELETE(nowEditEne);
            nowEditEne = new EditorObject(editedData);
        }
        else if(selectEditedEneNum < -1)//-1��������V������낤�Ƃ��Ă���
        {
            selectEditedEneNum = -1;
        }
    }
}

/// <summary>
/// �I�������G�l�~�[�̕ҏW
/// </summary>
void EnemyDataEditor::EditSelectEnemy()
{
    //�ړ���]
    nowEditEne->Update();
    //�ҏW�I��
    if (UserInput::GetInputState(Space) == Push)
    {
        //�ҏW�����^�C�~���O�̃~�b�V���������L�^
        auto saveData = nowEditEne->GetEditObjectData();
        saveData.missionNum = missionNum;
        //�ߋ��̃A�C�e����I�����Ă�����
        if (!isEndEdit && selectEditedEneNum != -1)
        {
            //�ߋ��̃A�C�e�����Ĕ[�i
            editDataVec[selectEditedEneNum] = saveData;
            selectEditedEneNum = -1;
        }
        else
        {
            //�ҏW�I���R���e�i�ɔ[�i
            editDataVec.push_back(saveData);
        }
        isEndEdit = true;
    }
    //�j�����ďI��
    else if (UserInput::GetInputState(DKey) == Push)
    {
        if (selectEditedEneNum != -1)//�̕ҏW�������̂��폜
        {
            EraceEndEditData(selectEditedEneNum);
            selectEditedEneNum = -1;
        }
        isEndEdit = true;
    }
}
