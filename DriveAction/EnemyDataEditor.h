#pragma once
#include "StageDataEditor.h"
#include <unordered_map>
#include <vector> 
/// <summary>
/// �G�̕ҏW�N���X
/// </summary>
class EnemyDataEditor :
    public StageDataEditor
{
public:
    /// <summary>
/// �G�̕ҏW�N���X
/// </summary>
    EnemyDataEditor(InitObjKind enemyKind);
private:
    //�ǂݍ��ޔz�u���̏����Ă���t�@�C���̃p�X
    static const std::string loadEditFilePath;
};