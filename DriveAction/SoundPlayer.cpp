#include "SoundPlayer.h"
#include "DxLib.h"
#include "CSVFileLoader.h"
#include "Utility.h"
std::map<SoundKind, int> SoundPlayer::soundHandleMap;
std::vector <std::string> SoundPlayer::initFilePassData;
/// <summary>
/// 音を出すやつ
/// </summary>
SoundPlayer::SoundPlayer()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(initSoundFileName);
    initFilePassData = initDataLoader->GetLoadStringData();
    SAFE_DELETE(initDataLoader);
}
/// <summary>
/// デストラクタ
/// </summary>
SoundPlayer::~SoundPlayer()
{
    for (int i = 0; i < soundHandleMap.size(); i++)
    {
        int success = StopSoundMem((*soundHandleMap.begin()).second);
        success = DeleteSoundMem((*soundHandleMap.begin()).second);
    }
}

/// <summary>
/// 全ての音を止める
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::StopAllSound()
{
    for (auto ite = soundHandleMap.begin(); ite != soundHandleMap.end(); ite++)
    {
        StopSound((*ite).first);
    }
}


void SoundPlayer::Play2DSE(SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);
    }
}

void SoundPlayer::Play3DSE(SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);
    }
}


void SoundPlayer::SetPosition3DSound(VECTOR pos, SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        Set3DPositionSoundMem(pos, handleKey);
    }
}

void SoundPlayer::PlayBGM(SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        PlaySoundMem(handleKey, DX_PLAYTYPE_LOOP);
    }
}

void SoundPlayer::StopSound(SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        if (CheckSoundMem(handleKey) == 1)
        {
            StopSoundMem(handleKey);
        }
    }
}

void SoundPlayer::LoadSound(SoundKind kind)
{
    if (!soundHandleMap.contains(kind))
    {

        int num = static_cast<int>(kind);
        //データ読み取り
        CSVFileLoader* initDataLoader = new CSVFileLoader(initFilePassData[num]);
        std::vector<const char*> initData = initDataLoader->GetLoadCharData();
        int loadSoundHandleNum = LoadSoundMem(initData[soundPass]);

        soundHandleMap.insert(std::make_pair(kind, loadSoundHandleNum));
        ChangeVolumeSoundMem(atoi(initData[soundVolume]), loadSoundHandleNum);
        SAFE_DELETE(initDataLoader);
    }
}

void SoundPlayer::Load3DSound(SoundKind kind)
{
    if (!soundHandleMap.contains(kind))
    {
        LoadSound(kind);
        int num = static_cast<int>(kind);
        //データ読み取り
        CSVFileLoader* initDataLoader = new CSVFileLoader(initFilePassData[num]);
        std::vector<const char*> initData = initDataLoader->GetLoadCharData();
        Set3DRadiusSoundMem(atoi(initData[soundRadius]), soundHandleMap[kind]);
        SAFE_DELETE(initDataLoader);
    }
}

bool SoundPlayer::IsPlaySound(SoundKind kind)
{
    //1ならなってる-1なってない
    return  CheckSoundMem(soundHandleMap[kind]) == 1;
}
