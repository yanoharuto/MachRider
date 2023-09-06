#pragma once
class StageDataEditor;
/// <summary>
/// Editor�Ŏg���G�t�F�N�g
/// </summary>
class EditorEffect
{
public:
    /// <summary>
    /// �G�t�F�N�g�ǂݍ���
    /// </summary>
    EditorEffect();
    /// <summary>
    /// �G�t�F�N�g�I��
    /// </summary>
    ~EditorEffect();
    /// <summary>
    /// �G�t�F�N�g�̌����ƈʒu�̕ύX
    /// </summary>
    /// <param name="editor">���ҏW���Ă���Editor</param>
    void Update(StageDataEditor* const editor);
private:
    //�z�u���̃I�u�W�F�N�g�̌�����������G�t�F�N�g�̃T�C�Y
    const float dirEffectSize = 5.0f;
    //�ҏW���̈ʒu�̕�����₷���Ȃ�G�t�F�N�g
    int posEffect = -1;
    //������������₷���Ȃ�G�t�F�N�g
    int dirEffect = -1;
};