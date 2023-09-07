#include "SoundPlayer.h"
#include "DxLib.h"
#include "CSVFileLoader.h"
#include "Utility.h"
//サウンドの種類ごとのハンドル
std::map<SoundKind, int> SoundPlayer::soundHandleMap;
//サウンドの種類ごとの初期化パスコンテナ
std::vector <std::string> SoundPlayer::initFilePassData;
/// <summary>
/// 全音のパスを把握
/// </summary>
SoundPlayer::SoundPlayer()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(initSoundFileName);
    initFilePassData = initDataLoader->GeFileStringData();
    SAFE_DELETE(initDataLoader);
}
/// <summary>
/// 音を全部止めて解放
/// </summary>
SoundPlayer::~SoundPlayer()
{
    for (int i = 0; i < SAFE_GET_SIZE(soundHandleMap); i++)
    {
        int success = StopSoundMem((*soundHandleMap.begin()).second);
        success = DeleteSoundMem((*soundHandleMap.begin()).second);
    }
}
/// <summary>
/// 全ての音を止める
/// </summary>
void SoundPlayer::StopAllSound()
{
    for (auto ite = soundHandleMap.begin(); ite != soundHandleMap.end(); ite++)
    {
        StopSound((*ite).first);
    }
}
/// <summary>
/// 効果音を鳴らす
/// </summary>
/// <param name="kind">音の種類</param>
void SoundPlayer::Play2DSE(SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);
    }
}
/// <summary>
/// 3d空間での音を鳴らす
/// </summary>
/// <param name="pos">なっている音の位置</param>
/// <param name="kind">音の種類</param>
void SoundPlayer::Play3DSE(SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);
    }
}
/// <summary>
/// 鳴らしたい音の位置を変える
/// </summary>
/// <param name="pos">なっている音の位置</param>
/// <param name="kind">音の種類</param>
void SoundPlayer::SetPosition3DSound(VECTOR pos, SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        Set3DPositionSoundMem(pos, handleKey);
    }
}
/// <summary>
/// 全ての音を止める
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::PlayBGM(SoundKind kind)
{
    if (soundHandleMap.contains(kind))
    {
        int handleKey = soundHandleMap[kind];
        PlaySoundMem(handleKey, DX_PLAYTYPE_LOOP);
    }
}
/// <summary>
/// 音を止める
/// </summary>
/// <param name="kind">音の種類</param>
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
/// <summary>
/// 音をロードして音量を初期化して使いまわせるようにする
/// </summary>
/// <param name="kind">音の種類</param>
void SoundPlayer::LoadAndInitSound(SoundKind kind)
{
    //音がロードされていないなら
    if (!soundHandleMap.contains(kind))
    {
        int num = static_cast<int>(kind);
        //データ読み取り
        CSVFileLoader* initDataLoader = new CSVFileLoader(initFilePassData[num]);
        std::vector<const char*> initData = initDataLoader->GetFileCharData();
        //読み取った文字列からパスを受け取り音データを所得
        int loadSoundHandleNum = LoadSoundMem(initData[soundPass]);
        //mapに追加
        soundHandleMap.insert(std::make_pair(kind, loadSoundHandleNum));
        //音量を設定
        ChangeVolumeSoundMem(atoi(initData[soundVolume]), loadSoundHandleNum);
        //読み取りクラスの開放
        SAFE_DELETE(initDataLoader);
    }
}
/// <summary>
/// ３Dの音をロードして音量を初期化して使いまわせるようにする
/// </summary>
/// <param name="kind">音の種類</param>
void SoundPlayer::LoadAndInit3DSound(SoundKind kind)
{
    //音がロードされていないなら
    if (!soundHandleMap.contains(kind))
    {
        //ロードと初期化
        LoadAndInitSound(kind);
        int num = static_cast<int>(kind);
        //データ読み取り
        CSVFileLoader* initDataLoader = new CSVFileLoader(initFilePassData[num]);
        //読み取ったデータから聞こえる半径を設定
        auto initStrDataVec = initDataLoader->GeFileStringData();
        Set3DRadiusSoundMem(SAFE_STR_TO_F(initStrDataVec[soundRadius]), soundHandleMap[kind]);
        //読み取りクラスの開放
        SAFE_DELETE(initDataLoader);
    }
}
/// <summary>
/// その音が鳴ってるかどうか調べる
/// </summary>
/// <param name="kind">音の種類</param>>
/// <returns>なってたらTrue</returns>
bool SoundPlayer::IsPlaySound(SoundKind kind)
{
    //1ならなってる-1なってない
    return  CheckSoundMem(soundHandleMap[kind]) == 1;
}
