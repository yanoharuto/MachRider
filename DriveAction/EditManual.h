#pragma once
#include <string>
class StageDataEditor;
/// <summary>
/// �ҏW���̑������
/// </summary>
class EditManual
{
public:
    /// <summary>
    /// �t�H���g�T�C�Y�ƕ\���ʒu�̒���
    /// </summary>
    EditManual();
    /// <summary>
    /// ��������\��
    /// </summary>
    /// <param name="editor">���ҏW���������Ă��炤</param>
    void Draw(StageDataEditor* const editor);
private:
    //�\���ҏW��
    const std::string selectCrossKeyAction="�\���L�[�ҏW���ύX";
    //�\���I��
    const std::string editCrossAction="�\���L�[�ҏW���ړ�";
    //SpaceKey�I��
    const std::string selectSpaceKeyAction="space�ŕҏW�J�n";
    //SpaceKey�ҏW��
    const std::string editSpaceKeyAction="space�Ŕz�u";
    //DKey
    const std::string dKeyAction="D�ō폜";
    //WKey
    const std::string wKeyAction="�����ύX";
    //AKey
    const std::string aKeyAction="A�Ə\���ŃJ��������";
    //SKey
    const std::string sKeyAction="S�Ə\���ŏo�Ă��鎞����ύX";
    //�\���ʒu�̍���
    int screenHeight;

    //�`�悷�镶���̃T�C�Y
    const int fontSize = 24;
    //������̋���Y
    const int strBetweenY = 50;
    //������̋���X
    const int strBetweenX = 300;
};

