#ifndef MYDFINE_H
#define MYDEFINE_H

//各種定義をこっちに記載する

/*画面解像度*/
const int ScreenWidth = 960; //横画面サイズ
const int ScreenHeight = 540; //縦画面サイズ

/*マップデータ*/
const int Width = 1000;
const int Height = 17;
const int CellSize = 32;
const float ScrollSpeed = 1.5f;

/*数学関連*/
const float Sprt2 = 1.41421356237f;  // ルート2

const float PI = 3.14159265359f;	// 円周率
const float Deg2Rad = PI / 180.0f; // 度からラジアンに変換する定数
const float Rad2Deg = 180.0f / PI; // ラジアンから度に変換する定数

float radius = 100.0f;

/*自機構造体*/
struct Player {
    float v;// 移動速度
    float x;// x座標
    float y;// y座標
    float collisionRadius;//当たり判定の半径
    int isDead;//死亡フラグ（1:未使用 0:使用）
    int life;// 耐久力
    int invincible;// 残り無敵時間。0以下なら無敵じゃないってこと
    int type; // 自機タイプ
    int ImageHandle; // イメージハンドル
};

const int PlayerMax = 2; // プレイヤー最大数

const float PlayerInitPosX = 100; //x座標の初期地点
const float PlayerInitPosY = 540 / 2; //y座標の初期地点
const float PlayerMoveSpeed = 6.0f; //自機の速度

const float PlayerCollisionRadius = 3.0f; //プレイヤーの当たり判定の半径

const int PlayerInitLife = 20;   // 自機ライフ
const int InvincibleTime = 120; // 無敵時間

const float PlayerImageSizeX = 64.0f;
const float PlayerImageSizeY = 64.0f;

/*敵構造体*/
struct Enemy
{
    float speed; // 移動速度
    float x; // x座標
    float y; // y座標
    float vx; // x方向移動速度
    float vy; // y方向移動速度
    float collisionRadius; //当たり判定の半径
    float isDead; // 死亡フラグ（1:未使用 0:使用）
    float angle = 0.0f; // 角度
    int life; //耐久
    int type;
    int ImageHandle; //イメージハンドル
    int counter;
    int AttackCount; //攻撃回数
    int state; //状態
};

const int enemyMax = 100; //敵数のMAX
const int enemyMaxNumber = 9;

//敵の当たり判定の半径
const float EnemyCollisionRadius = 32.0f;

/*敵ボス構造体*/
enum BossState
{
    Standby,	// 待機
    Appear,	// 登場
    Normal,	// 通常時
    Swoon,	// 気絶時
    Angry,	// 発狂モード
    Dying,	// 死亡
};

//ボス
struct BOSS
{
    Enemy enemy;			// Enemy構造体
    int swoonTime;			// 残り気絶時間
    int dyingTime;			// 死亡時のアニメーション時間
    int explositonWaitCnt;        // 死んだ時爆発出すウエイト時間
    float centerX;			// 中心座標X
    float centerY;			// 中心座標Y
    int normalTime;			// 通常時の時間
    int angryTime;			// 発狂モード時の時間
    float restartX;			// リスタート地点のX座標
    float restartY;			// リスタート地点のY座標
};

const int   BossLife = 100;               // ボスライフ
const float BossCollisionRadius = 90.0f;  // ボス当たり判定半径
const int SwoonTime = 120;                // 気絶時間
const int DyingTime = 160;                // 死亡時のアニメーション時間

/*自機弾構造体*/
struct PlayerBullet{
    float speed; // 移動速度
    float x; // x座標
    float y; // y座標
    float vx; // x方向移動速度
    float vy; // y方向移動速度
    float collisionRadius; // 当たり判定の半径
    int isDead = 1; // 死亡フラグ（1:未使用 0:使用）
    float angle = 0.0f; // 角度
    int enemyControl;
};

/*自機弾構造体*/
struct PlayerPeasBullet {
    float speed; // 移動速度
    float x; // x座標
    float y; // y座標
    float vx; // x方向移動速度
    float vy; // y方向移動速度
    float collisionRadius; // 当たり判定の半径
    int isDead = 1; // 死亡フラグ（1:未使用 0:使用）
    float angle = 0.0f; // 角度
};

const int PlayerBulletMax = 100; // 自機の弾数MAX

const int PlayerPeasBulletMax = 1000; // 自機の豆鉄砲弾数MAX

const float PlayerBulletCollisionRadius = 16.0f; // 自機弾当たり判定の半径

int count = 0;

/*敵弾構造体*/
struct EnemyBullet
{
    float speed; // 移動速度
    float x; // x座標
    float y; // y座標
    float vx; // x方向移動速度
    float vy; // y方向移動速度
    float collisionRadius; // 当たり判定の半径
    int isDead = 1; // 死亡フラグ（1:未使用 0:使用）
    int ImageHandle; //イメージハンドル
    float angle = 0.0f;
    int type;
    int counter;
};

const int EnemyBulletMax = 10000;

//敵弾の当たり判定の半径
const float EnemyBulletCollisionRadius = 8.0f;

/*爆発構造体*/
struct Explosion
{
    float x;// x座標
    float y;// y座標
    float isDead;// 死亡フラグ
    int timer;// 時間を計るための変数
    int number;// 表示すべき画像の番号
};

const int ExplosionMax = 100; // 爆発エフェクトMAX
const int ExplosionChipSize = 64; //爆破エフェクトサイズ

// ゲーム状態
enum State {
    Title,  //タイトル
    Select, //キャラ選択
    Play,   //プレイ
    Over,   //ゲームオーバー
    Clear,  //ゲームクリア
};

/*画像ハンドル*/
enum {
    ePLAYERBULLET, //自機弾
    ePLAYERPEASBULLET, // 豆鉄砲

    ePLAYER00, //プレイヤー0～3
    ePLAYER01,
    ePLAYER02,
    ePLAYER03,

    eENEMY00, //敵ザコ１～9
    eENEMY01,
    eENEMY02,
    eENEMY03,
    eENEMY04,
    eENEMY05,
    eENEMY06,
    eENEMY07,
    eENEMY08,
    eENEMY09,
    eBOSS_NORMAL = 100, // ボス(通常)
    eBOSS_SWOON, // ボス(気絶)
    eBOSS_ANGRY, // ボス(怒り)
    eENEMYBULLET, //敵弾

    eEXPLOSION, //爆破エフェクト

    eIMAGE_MAX
};

//効果音ハンドル
enum SE
{
    eShotSE,
};

enum BGM
{
    eBGM1,
};

#endif // !MYDFINE_H
