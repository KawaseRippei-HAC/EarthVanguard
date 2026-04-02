// playerのtypeが1の時豆鉄砲が発射されないのですが原因は何が考えられますか？

#define _CRT_SECURE_NO_WARNINGS
#include <GSgameLIght.h>
#include "myUtil.h"
#include "myDfine.h"

class MyGame : public gslib::Game {

	//ステージ初期状態にする
	void Reset()
	{
		// 自機弾データの初期化を追加
		for (int i = 0; i < PlayerBulletMax; i++) {
			playerBullets[i].collisionRadius = PlayerBulletCollisionRadius;
			playerBullets[i].isDead = 1;
			playerBullets[i].enemyControl = 1;
		}
		// 豆鉄砲(自機弾)データの初期化を追加
		for (int i = 0; i < PlayerPeasBulletMax; i++){
			playerPeasBullets[i].collisionRadius = PlayerBulletCollisionRadius;
			playerPeasBullets[i].isDead = 1;
		}

		// 敵弾データの初期化を追加
		for (int i = 0; i < EnemyBulletMax; i++) {
			enemyBullets[i].collisionRadius = EnemyBulletCollisionRadius;
			enemyBullets[i].isDead = 1;
		}
			player.v = PlayerMoveSpeed;
			player.x = PlayerInitPosX;
			player.y = PlayerInitPosY;
			player.collisionRadius = PlayerCollisionRadius; //プレイヤーの半径
			player.isDead = 0; //プレイヤーの生死判定
			player.life = PlayerInitLife;//プレイヤーの初期ライフ設定
			player.invincible = 0;//プレイヤーの無敵時間初期化
			player.type = 0;
		

		//敵の初期化
		for (int i = 0; i < enemyMax; i++) {
			//ザコ敵
			enemys[i].vx = -0.5f;
			enemys[i].vy = -0.5f;
			enemys[i].collisionRadius = EnemyCollisionRadius;
			enemys[i].isDead = 1;
			enemys[i].angle = 0;
			enemys[i].life = 1;
			enemys[i].type = 0;
			enemys[i].ImageHandle = eENEMY00 + enemys[i].type;
			enemys[i].counter = 0;

		}


		for (int i = 0; i < ExplosionMax; i++) {
			explosion[i].isDead = 1;
			explosion[i].timer = 0;
			explosion[i].number = 0;
		}

		position = 0;

		gsPlayBGM(eBGM1);
	}

	/*自機の関数*/
	//更新処理
	void UpdatePlayer(float delta_time)
	{
		
		if (player.isDead)return; //プレイヤーが死んでたら何もしない

		//無敵時間カウント減らす
		if (player.invincible != 0) player.invincible--;

		switch (player.type)
		{
		case 0:
			// Zボタン押下で自機弾を発射
			if (gsGetKeyState(GKEY_Z) && count % 10 == 0) {
				float speed = 10;
				float bulletvx = speed;
				float bulletvy = 0;
				ShotBullet(player.x, player.y, speed, bulletvx, bulletvy);
				gsPlaySE(eShotSE);
			}
			// Xボタン押下で自機弾を発射
			if (gsGetKeyState(GKEY_X) && count % 5 == 0) {
				float speed = 10;
				float bulletvx = speed;
				float angle = 10 * Deg2Rad;
				ShotBullet(player.x, player.y, speed, angle);
				angle = -10 * Deg2Rad;
				ShotBullet(player.x, player.y, speed, angle);
				gsPlaySE(eShotSE);
			}
			break;
		case 1:
			// Zボタン押下で自機弾を発射
			// Zボタン押下で自機弾を発射
			if (gsGetKeyState(GKEY_Z) && count % 10 == 0) {
				float speed = 10;
				float bulletvx = speed;
				float bulletvy = 0;
				ShotBullet(player.x, player.y, speed, bulletvx, bulletvy);
				gsPlaySE(eShotSE);
			}
			// Xボタン押下で自機弾を発射
			if (gsGetKeyState(GKEY_X) && count % 5 == 0) {
				float speed = 10;
				float bulletvx = speed;
				float bulletvy = 0;
				ShotPeasBullet(player.x, player.y, speed, bulletvx, bulletvy);
				gsPlaySE(eShotSE);
			}
			break;
		default:
			break;
		}
			// 斜め移動も同じ速度になるように調整、
			// 実際に位置を動かすを追加
			float vx = 0.0f;
			float vy = 0.0f;

			if (gsGetKeyState(GKEY_UP) && player.y - player.v > 32) {
				vy -= player.v;
			}
			if (gsGetKeyState(GKEY_LEFT) && player.x - player.v > 32) {
				vx -= player.v;
			}
			if (gsGetKeyState(GKEY_DOWN) && player.y + player.v < ScreenHeight - 32) {
				vy += player.v;
			}
			if (gsGetKeyState(GKEY_RIGHT) && player.x + player.v < ScreenWidth - 32) {
				vx += player.v;
			}

			if (vx != 0 && vy != 0) {
				vx /= Sprt2;
				vy /= Sprt2;
			}

			player.x += vx;
			player.y += vy;

			//if (vx == 0 && vy == 0 && count % 10 == 0) {
			//	float speed = 10;
			//	float bulletvx = speed;
			//	float bulletvy = 0;
			//	ShotBullet(player.x, player.y, speed, bulletvx, bulletvy);
			//}
	}

	//描画
	void DrawPlayer()
	{
		if (player.isDead)return;
		//stateがSelectのとき
		if (state == Select) {
			GSvector2 playerPos = { ScreenWidth / 2,ScreenHeight / 2 };
			GSvector2 playerCenter = { 32,32 };

			gsDrawSprite2D(ePLAYER00 + player.type, &playerPos, NULL, &playerCenter, NULL, NULL, NULL);
		}

		// 無敵中は2フレームに1回描画（点滅）
		if (player.invincible % 3 == 0 && state == Play) {

			GSvector2 playerPos = { player.x,player.y };
			GSvector2 playerCenter = { 32,32 };

			gsDrawSprite2D(ePLAYER00 + player.type, &playerPos, NULL, &playerCenter, NULL, NULL, NULL);
		}
	}

	//ダメージ
	void PlayerTakeDamage()
	{
		player.life--;
		if (player.life <= 0) {
			SetExplosion(player.x, player.y);
			player.isDead = 1;
			state = Over;
		}
		else {
			player.invincible = InvincibleTime;
		}
	}

	/*自機弾の関数*/

	//更新
	void UpdatePlayerBullets(float delta_time) {

		for (int i = 0; i < PlayerBulletMax; i++) {

			//移動
			if (playerBullets[i].isDead)continue;
			playerBullets[i].x += playerBullets[i].vx;
			playerBullets[i].y += playerBullets[i].vy;

			//削除
			if (playerBullets[i].x > ScreenWidth || //左右
				playerBullets[i].x < 0 ||
				playerBullets[i].y > ScreenHeight || //上下
				playerBullets[i].y < 0) {

				playerBullets[i].isDead = 1;
			}
		}
	}

	//更新
	void UpdatePlayerPeasBullets(float delta_time) {

		for (int i = 0; i < PlayerPeasBulletMax; i++) {

			//移動
			if (playerPeasBullets[i].isDead)continue;
			playerPeasBullets[i].x += playerPeasBullets[i].vx;
			playerPeasBullets[i].y += playerPeasBullets[i].vy;

			//削除
			if (playerPeasBullets[i].x > ScreenWidth || //左右
				playerPeasBullets[i].x < 0 ||
				playerPeasBullets[i].y > ScreenHeight || //上下
				playerPeasBullets[i].y < 0) {

				playerPeasBullets[i].isDead = 1;
			}
		}
	}

	//生成1(直線)
	void ShotBullet(float x, float y, float speed, float vx, float vy)
	{
		// 各種メンバの設定
		PlayerBullet pb;

		pb.speed = speed;
		pb.x = x;
		pb.y = y;
		pb.vx = vx;
		pb.vy = vy;
		pb.isDead = 0;
		pb.collisionRadius = PlayerBulletCollisionRadius;

		// 自機弾配列の空いている場所に登録
		for (int i = 0; i < PlayerBulletMax; i++) {
			if (playerBullets[i].isDead) {
				playerBullets[i] = pb;
				break;
			}
		}

	}
	//生成2(角度指定)
	void ShotBullet(float x, float y, float speed, float angle)
	{
		// 各種メンバの設定
		PlayerBullet pb;

		pb.x = x;
		pb.y = y;
		pb.vx = cosf(angle) * speed;
		pb.vy = sinf(angle) * speed;
		pb.isDead = 0;
		pb.collisionRadius = PlayerBulletCollisionRadius;
		pb.angle = angle;

		// 自機弾配列の空いている場所に登録
		for (int i = 0; i < PlayerBulletMax; i++) {
			if (playerBullets[i].isDead) {
				playerBullets[i] = pb;
				break;
			}
		}

	}

	//生成3(豆鉄砲)
	void ShotPeasBullet(float x, float y, float speed, float vx, float vy)
	{
		// 各種メンバの設定
		PlayerPeasBullet pp;

		pp.speed = speed;
		pp.x = x;
		pp.y = y;
		pp.vx = vx;
		pp.vy = vy;
		pp.isDead = 0;
		pp.collisionRadius = PlayerBulletCollisionRadius;

		// 自機弾配列の空いている場所に登録
		for (int i = 0; i < PlayerPeasBulletMax; i++) {
			if (playerPeasBullets[i].isDead) {
				playerPeasBullets[i] = pp;
				break;
			}
		}
	}

	//描画
	void DrawPlayerBullet() {
		for (int i = 0; i < PlayerBulletMax; i++) {
			if (playerBullets[i].isDead)continue;

			GSvector2 playerBulletPos = { playerBullets[i].x,playerBullets[i].y };
			GSvector2 playerBulletcenter = { 16.0f,16.0f };

			gsDrawSprite2D(ePLAYERBULLET, &playerBulletPos, NULL, &playerBulletcenter, NULL, NULL, playerBullets[i].angle * (180 / PI));


		}
	}

	//描画
	void DrawPlayerPeasBullet() {
		for (int i = 0; i < PlayerPeasBulletMax; i++) {
			if (playerPeasBullets[i].isDead)continue;

			GSvector2 playerPeasBulletPos = { playerPeasBullets[i].x,playerPeasBullets[i].y };
			GSvector2 playerPeasBulletcenter = { 2.0f,10.0f };

			gsDrawSprite2D(ePLAYERPEASBULLET, &playerPeasBulletPos, NULL, &playerPeasBulletcenter, NULL, NULL, playerBullets[i].angle * (180 / PI));

		}
	}

	/*敵の関数*/
	//更新
	void UpdateEnemys(float delta_time)
	{
		//enemyCount++;
		//timer = enemyCount % (60 * 5);
		enemyTime += delta_time / 5;

		// 敵配列の移動処理
		for (int i = 0; i < enemyMax; i++) {
			if (enemys[i].isDead != 0) continue;
			enemys[i].counter++;
			// 秒数
			int seconds = enemys[i].counter / 60; // 1秒
			// 5秒ごとに時計回りと反時計周りを切り替えるフラグ
			bool clockWise = (seconds / 5) % 2 == 0; // trueなら時計回り、falseなら反時計回り
			switch (enemys[i].type)
			{
			case 0:
				//直進(横)
				enemys[i].x += enemys[i].vx;
				break;
			case 1:
				//上下移動(横)
				enemys[i].x += enemys[i].vx;
				enemys[i].y -= cos(enemyTime * 0.3f) * 5.0f;
				break;
			case 2:
				//直進(縦)
				enemys[i].y += enemys[i].vy;
				break;
			case 3:
				//上下移動(縦)
				enemys[i].x += enemys[i].vx;
				enemys[i].y -= cos(enemyTime * 0.3f) * 5.0f;

				// 自機狙いばらまき弾
				if (enemys[i].counter % 10 == 0)
				{
					// 発射角度を度数で求める
					float angle = PointToPointAngle(enemys[i].x, enemys[i].y, player.x, player.y) * Rad2Deg;
					float shakeAngle = RandomPlusMinus(15.0f);
					ShotEnemyBullet(enemys[i].x, enemys[i].y, 6.0f, angle + shakeAngle, enemys[i].type);
				}
				break;
			case 4:
				// 横移動
				enemys[i].x += enemys[i].vx;
				/*enemys[i].y -= cos(enemyTime * 0.3f) * 5.0f;*/

				// 登場から0.5秒たつまでの間、時計回りする
				if (enemys[i].counter > 30)
			{
					// ぐるぐるグネグネバー
					if (enemys[i].counter % 5 == 0) {
						if (clockWise) {
							ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, -enemys[i].counter, enemys[i].type);
							ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, -enemys[i].counter + 90.0f, enemys[i].type);
							ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, -enemys[i].counter + 180.0f, enemys[i].type);
							ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, -enemys[i].counter + 270.0f, enemys[i].type);
						}else{
							// ぐるぐるグネグネバー
							if (enemys[i].counter % 5 == 0) {
								ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, enemys[i].counter, enemys[i].type);
								ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, enemys[i].counter + 90.0f, enemys[i].type);
								ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, enemys[i].counter + 180.0f, enemys[i].type);
								ShotEnemyBullet(enemys[i].x, enemys[i].y, 7.0f, enemys[i].counter + 270.0f, enemys[i].type);
						}
					}
				}
			}
				break;
			case 5:
				enemys[i].x += enemys[i].vx;

				//自機狙い弾
				if (enemys[i].counter % 50 == 0)
				{

					float angle = PointToPointAngle(enemys[i].x, enemys[i].y, player.x, player.y) / PI * 180.0f;
					float shakeAngle = RandomPlusMinus(15.0f) * Deg2Rad;
					ShotEnemyBullet(enemys[i].x, enemys[i].y, 8.0f, angle + shakeAngle, enemys[i].type);
				}
				break;
			case 6:
				//全方位に弾を撃つ + ワープ
				if (enemys[i].AttackCount < 5) {
					if (enemys[i].counter % 250 == 30) {
						for (int j = 0; j < 360; j += 20) {
							ShotEnemyBullet(enemys[i].x, enemys[i].y, 2.0, j, enemys[i].type);
						}
						enemys[i].x = RandomRangef(0 + EnemyCollisionRadius, ScreenWidth - EnemyCollisionRadius);
						enemys[i].y = RandomRangef(0 + EnemyCollisionRadius, ScreenHeight - EnemyCollisionRadius);

						enemys[i].AttackCount++;
					}
				}
				else {
					enemys[i].isDead = 1;
				}
				break;
			case 7:
				///直進(横)
				enemys[i].x += enemys[i].vx;
				break;
			case 8:
				enemys[i].x += enemys[i].vx;
				//自機狙い弾 + 拡散
				if (enemys[i].counter % 120 == 0) {
					float angle = PointToPointAngle(enemys[i].x, enemys[i].y, player.x, player.y) / PI * 180.0f;
					float shakeAngle = RandomPlusMinus(15.0f) * Deg2Rad;

					ShotEnemyBullet(enemys[i].x, enemys[i].y, 5.0f, angle + shakeAngle, enemys[i].type);


				}
				break;
			case 9:
				//自機に向かってくる + 自爆
				float angleToPlayer = PointToPointAngle(enemys[i].x, enemys[i].y, player.x, player.y);
				float speed = 3.0f;
				enemys[i].x += (float)cos(angleToPlayer) * speed;
				enemys[i].y += (float)sin(angleToPlayer) * speed;
				if (enemys[i].counter > 300) {
					for (int j = 0; j < 20; j++) {
						SetExplosion(enemys[i].x + RandomPlusMinus(EnemyCollisionRadius + 30),
							enemys[i].y + RandomPlusMinus(EnemyCollisionRadius + 30));
					}
					if (CircleCircleIntersection(player.x, player.y, 32,
						enemys[i].x, enemys[i].y, enemys[i].collisionRadius + 32)) {
						PlayerTakeDamage();
					}
					enemys[i].isDead = 1;
				}
				break;
				//default:
				//	enemys[i].x += enemys[i].vx;
				//	break;
			}
			// 画面外に行ったときに消す
			if (enemys[i].x + enemys[i].collisionRadius < 0 - EnemyCollisionRadius * 4 ||
				enemys[i].y + enemys[i].collisionRadius < 0 - EnemyCollisionRadius * 4 ||
				enemys[i].x > ScreenWidth + EnemyCollisionRadius * 4 ||
				enemys[i].y > ScreenHeight + EnemyCollisionRadius * 4)
			{
				enemys[i].isDead = 1;
			}
		}

	}

	//描画
	void DrawEnemy()
	{

		for (int i = 0; i < enemyMax; i++) {
			if (enemys[i].isDead)continue;
			GSvector2 enemyPos = { enemys[i].x,enemys[i].y };
			GSvector2 enemycenter = { 32.0f,32.0f };

			if (enemys[i].type == 9 && enemys[i].counter > 120) {
				if (enemys[i].counter % 20 < 10) {
					gsDrawSprite2D(enemys[i].ImageHandle, &enemyPos, NULL, &enemycenter, NULL, NULL, NULL);
				}
			}
			else {
				gsDrawSprite2D(enemys[i].ImageHandle, &enemyPos, NULL, &enemycenter, NULL, NULL, NULL);
			}
		}

		//GSvector2 enemyBossPos = { enemyBoss.x,enemyBoss.y };
		//GSvector2 enemyBossCenter = { 32.0f,32.0f };

		//gsDrawSprite2D(eENEMY01, &enemyBossPos, NULL, &enemyBossCenter, NULL, NULL, NULL);
	}

	//敵生成
	void AddEnemy(float x, float y, int type)
	{
		Enemy enemy;
		enemy.x = x;
		enemy.y = y;
		enemy.type = type;
		enemy.ImageHandle = eENEMY00 + type;
		enemy.vx = -1;
		enemy.vy = -1;
		enemy.life = 1;
		enemy.collisionRadius = EnemyCollisionRadius;
		enemy.counter = 0;
		enemy.isDead = 0;

		switch (type)
		{
		case 2:
			enemy.vx = 0;
			flg = RandomRange(0, 1);
			if (flg == 0) {
				enemy.y = 0;
				enemy.vy = 1;
			}
			else if (flg == 1) {
				enemy.y = ScreenHeight + EnemyCollisionRadius;
				enemy.vy = -1;
			}
			enemy.x = RandomRangef(150 + EnemyCollisionRadius, ScreenWidth - 150 - EnemyCollisionRadius);
			enemy.life = 3;
			break;
		case 3:
			flg = RandomRange(0, 1);
			if (flg == 0) {
				/*enemy.y = 0;*/
				enemy.vy = 1;
			}
			else if (flg == 1) {
				/*enemy.y = ScreenHeight + EnemyCollisionRadius;*/
				enemy.vy = -1;
			}
			/*	enemy.x = RandomRangef(150 + EnemyCollisionRadius, ScreenWidth - 150 - EnemyCollisionRadius);*/
			enemy.life = 1;
			break;
		case 4:
			enemy.life = 999;
			break;
		case 5:
			enemy.life = 10;
			break;
		case 6:
			enemy.x = RandomRangef(0 + EnemyCollisionRadius, ScreenWidth - EnemyCollisionRadius);
			enemy.y = RandomRangef(0 + EnemyCollisionRadius, ScreenHeight - EnemyCollisionRadius);
			enemy.life = 3;
			enemy.AttackCount = 0;
			break;
		case 7:
			enemy.life = 3;
			break;
		default:
			break;
		}
		for (int i = 0; i < enemyMax; i++) {
			if (enemys[i].isDead != 1) continue;

			enemys[i] = enemy;
			break;

		}
	}

	//自機生成
	void AddPlayer(float x, float y, int type)
	{
		switch (type)
		{
		case 0:
			player.life = 3;
			player.collisionRadius;
			break;
		case 1:
			player.life = 10;
			player.collisionRadius;
			break;
		default:
			break;
		}
		player.isDead = 0;
	}

	/*ボス*/
	//更新
	void UpdateBoss()
	{
		float rushMotionTheta = 0.0f;
		if (boss.enemy.isDead) return;

		//ボスの状態によって処理変える
		switch (boss.enemy.state)
		{
			//出現時
		case Appear:
			boss.enemy.x -= 1; // 左へ移動

			if (boss.enemy.x <= 750) // x座標が750以下になったら
			{
				boss.enemy.state = Normal; // 通常状態へ移行
				boss.restartX = boss.enemy.x;
				boss.restartY = boss.enemy.y;
				boss.enemy.vx = 0.0f;
				boss.enemy.vy = 2.0f;
			}
			break;

			//通常時
		case Normal:
			boss.normalTime++;
			boss.enemy.x += boss.enemy.vx;
			boss.enemy.y += boss.enemy.vy;
			if (boss.normalTime % 90 == 0) {
				for (int i = 0; i < 90; i += 18) {
					int angle = 45 - i;
					ShotEnemyBullet(boss.enemy.x, boss.enemy.y, 5.0f, 180.0f + angle, 7);
				}
			}
			if (boss.enemy.y >= 500)
			{
				boss.enemy.y = 500;
				boss.enemy.vy = -boss.enemy.vy;
			}
			else if (boss.enemy.y <= 50)
			{
				boss.enemy.y = 50;
				boss.enemy.vy = -boss.enemy.vy;
			}
			break;

			//気絶時
		case Swoon:
			boss.swoonTime--; // タイマー減少
			//気絶タイマーがリセット前なら
			if (boss.swoonTime > 40)
			{
				boss.enemy.x += boss.enemy.vx;
				boss.enemy.y += boss.enemy.vy;
				boss.enemy.vx *= 0.995f;
				boss.enemy.vy *= 0.995f;
			}
			//リスタート中だったら
			else
			{
				const float Agility = 0.07f;
				boss.enemy.x = boss.enemy.x + (boss.restartX - boss.enemy.x) * Agility;
				boss.enemy.y = boss.enemy.y + (boss.restartY - boss.enemy.y) * Agility;
			}
			if (boss.swoonTime <= 0) // タイマーが0になったら
			{
				boss.enemy.state = Angry; // 発狂モードへ
				boss.enemy.x = boss.restartX;
				boss.enemy.y = boss.restartY;
				boss.centerX = boss.enemy.x;
				boss.centerY = boss.enemy.y;
				boss.angryTime = 0;
			}
			break;

			//怒り時
		case Angry:
			boss.angryTime++;
			//突進運動
			rushMotionTheta = 1.0f * boss.angryTime * Deg2Rad;
			boss.enemy.x = boss.centerX + 300.0f * ((float)cos(2.0f * rushMotionTheta) - 1.0f);
			boss.enemy.y = boss.centerY + 150.0f * ((float)sin(rushMotionTheta));
			if (boss.angryTime % 10 == 0) {
				ShotEnemyBullet(boss.enemy.x, boss.enemy.y, 4.0f, 180.0f + RandomPlusMinus(15.0f), 0);
			}
			break;

			//死亡時
		case Dying:
			boss.enemy.y++;
			boss.explositonWaitCnt++;
			boss.enemy.angle += 0.1f * Deg2Rad;
			float vibrationTheta = 2.8f * boss.dyingTime * Deg2Rad;
			boss.enemy.x = boss.centerX + 3.0f * (float)cos(17.0f * vibrationTheta);
			boss.enemy.y = boss.centerY + 3.0f * (float)sin(23.0f * vibrationTheta);
			boss.centerY += 0.5f;
			if (boss.explositonWaitCnt % 10 == 0) {
				SetExplosion(boss.enemy.x + RandomPlusMinus(boss.enemy.collisionRadius),
					boss.enemy.y + RandomPlusMinus(boss.enemy.collisionRadius));
			}

			boss.dyingTime--; // タイマー減少

			if (boss.dyingTime <= 0) // タイマーが0になったら
			{
				for (int i = 0; i < 30; i++) {
					SetExplosion(boss.enemy.x + RandomPlusMinus(boss.enemy.collisionRadius),
						boss.enemy.y + RandomPlusMinus(boss.enemy.collisionRadius));
				}
				boss.enemy.isDead = true;   //完全に消滅
			}
			break;
		}
	}

	//描画
	void DrawBoss()
	{
		if (boss.enemy.isDead || boss.enemy.state == Standby) return;

		int image = eBOSS_NORMAL;
		switch (boss.enemy.state)
		{
			//出現時とノーマル時
		case Appear:
		case Normal:
			image = eBOSS_NORMAL;
			break;
			//気絶時
		case Swoon:
			image = eBOSS_SWOON;
			break;
			//怒り時
		case Angry:
			image = eBOSS_ANGRY;
			break;
			//死亡時
		case Dying:
			image = eBOSS_SWOON;
			break;
		}
		GSvector2 pos = { boss.enemy.x, boss.enemy.y };
		GSvector2 center = { boss.enemy.collisionRadius,
						   boss.enemy.collisionRadius };
		gsDrawSprite2D(image, &pos, NULL, &center, NULL,
			NULL, boss.enemy.angle * (180.0f / PI));
	}

	// 初期化
	void InitBoss(float x, float y)
	{
		boss.enemy.state = Appear;
		boss.enemy.life = BossLife; // ライフ
		boss.enemy.collisionRadius = BossCollisionRadius; // 当たり判定半径
		boss.enemy.x = x;
		boss.enemy.y = y;
		boss.enemy.isDead = false;
	}

	/*敵弾の関数*/
	//更新
	void UpdateEnemyBullets(float delta_time)
	{
		for (int i = 0; i < EnemyBulletMax; i++) {
			//死んでたら何もしない
			if (enemyBullets[i].isDead)continue;

			// 速度の分だけ移動
			switch (enemyBullets[i].type)
			{
			case 7:
				enemyBullets[i].counter++;
				enemyBullets[i].x += enemyBullets[i].vx;
				enemyBullets[i].y += enemyBullets[i].vy;

				if (enemyBullets[i].counter % 30 == 0) {
					for (int j = 0; j < 360; j += 40) {
						ShotEnemyBullet(enemyBullets[i].x, enemyBullets[i].y, 2.0f, j, 0);
					}
					enemyBullets[i].isDead = 1;
				}

				break;
			default:
				enemyBullets[i].x += enemyBullets[i].vx;
				enemyBullets[i].y += enemyBullets[i].vy;
				break;
			}

			// 画面外に出たら死亡フラグを立てる
			if (enemyBullets[i].x > ScreenWidth || //左右
				enemyBullets[i].x < 0 ||
				enemyBullets[i].y > ScreenHeight || //上下
				enemyBullets[i].y < 0) {

				enemyBullets[i].isDead = 1;

			}
		}
	}

	//生成(角度指定)
	void ShotEnemyBullet(float x, float y, float speed, float angle, int type)
	{
		// 各種メンバの設定
		EnemyBullet eb;

		eb.x = x;
		eb.y = y;
		eb.speed = speed;
		eb.vx = cosf(angle * Deg2Rad) * speed;
		eb.vy = sinf(angle * Deg2Rad) * speed;
		eb.isDead = 0;
		eb.collisionRadius = EnemyBulletCollisionRadius;
		eb.angle = angle;
		eb.type = type;
		eb.counter = 0;

		//switch (type)
		//{
		//default:
		//	break;
		//}

		// 敵弾配列の空いている場所に登録
		for (int i = 0; i < EnemyBulletMax; i++) {
			if (enemyBullets[i].isDead) {
				enemyBullets[i] = eb;
				break;
			}
		}

	}

	//描画
	void DrawEnemyBullet()
	{
		for (int i = 0; i < EnemyBulletMax; i++)
		{
			if (enemyBullets[i].isDead) continue;
			GSvector2 pos = { enemyBullets[i].x, enemyBullets[i].y };
			GSvector2 center = { enemyBullets[i].collisionRadius, enemyBullets[i].collisionRadius };
			gsDrawSprite2D(eENEMYBULLET, &pos, NULL, &center, NULL, NULL, NULL);
		}
	}
	/*爆破エフェクトの関数*/
	//更新
	void UpdateExplosion(float delta_time)
	{
		for (int i = 0; i < ExplosionMax; i++) {

			//時間を計るための変数を使って表示する画像を切り替えていく
			//表示すべき画像の番号を変えていくという事
			if (explosion[i].timer % 3 == 2) {
				++explosion[i].number;
			}

			if (explosion[i].number > 15) {
				explosion[i].isDead = 1;
			}
			else {
				explosion[i].timer++;
			}

		}
	}

	//爆発エフェクトを発生させる
	void SetExplosion(float x, float y)
	{
		//弾の発生と同様にエフェクトを発生させる処理を書く

		// 各種メンバの設定
		Explosion pb;

		pb.x = x;
		pb.y = y;
		pb.isDead = 0;
		pb.timer = 0;
		pb.number = 0;

		// 
		for (int i = 0; i < ExplosionMax; i++) {
			if (explosion[i].isDead) {
				explosion[i] = pb;
				break;
			}
		}
	}

	//描画
	void DrawExplosion()
	{
		for (int i = 0; i < ExplosionMax; i++) {
			if (explosion[i].isDead != 0)continue;
			//表示すべき画像の番号を使って描画する絵を切り替える

			int explosionID = explosion[i].number / 8;

			//イライラ棒でやったように画像データの一部分だけを描画する方法を使う
			GSvector2 pos = { explosion[i].x,explosion[i].y };
			GSvector2 center = { 32.0f,32.0f };
			GSrect src = { (GSfloat)explosion[i].number * ExplosionChipSize, //左上のx座標
						  (GSfloat)explosionID * ExplosionChipSize, //左上のy座標
						  (GSfloat)explosion[i].number * ExplosionChipSize + ExplosionChipSize, //右下のx座標
						  (GSfloat)explosionID * ExplosionChipSize + ExplosionChipSize }; //右下のy座標
			gsDrawSprite2D(eEXPLOSION, &pos, &src, &center, NULL, NULL, 0.0f);

		}
	}

	/*その他の関数*/
	//当たり判定
	void CollisionDetection()
	{
		// 通常弾の処理
		for (int i = 0; i < PlayerBulletMax; i++) {
			if (playerBullets[i].isDead)continue; //使用してない弾は判定しない

			for (int k = 0; k < enemyMax; k++) {
				if (enemys[k].isDead)continue;

				//自機弾と敵が重なっているか
				if (CircleCircleIntersection(playerBullets[i].x, playerBullets[i].y,
					playerBullets[i].collisionRadius,
					enemys[k].x, enemys[k].y,
					enemys[k].collisionRadius)
					) {
					if (enemys[k].life <= 0) {
						SetExplosion(enemys[k].x, enemys[k].y);
						enemys[k].isDead = 1;
					}
					else {
						enemys[k].life--;
					}

					playerBullets[i].isDead = 1;
				}
			}
			if (playerBullets[i].isDead || boss.enemy.isDead) continue;
			// 自機弾とボスが重なっているか？
			if (CircleCircleIntersection(
				playerBullets[i].x + playerBullets[i].collisionRadius / 2,
				playerBullets[i].y + playerBullets[i].collisionRadius / 2,
				playerBullets[i].collisionRadius,
				boss.enemy.x + boss.enemy.collisionRadius / 2,
				boss.enemy.y + boss.enemy.collisionRadius / 2,
				boss.enemy.collisionRadius))
			{
				// 登場時、気絶時、死亡時は被弾しても何もしない
				if (boss.enemy.state == Appear ||
					boss.enemy.state == Swoon || boss.enemy.state == Dying)
					return;


				boss.enemy.life--;
				if (boss.enemy.life <= 0)
				{
					// ライフが無くなったら、すぐ消滅するのではなく、死亡状態へ移行
					boss.enemy.state = Dying;
					boss.dyingTime = DyingTime;
					boss.centerX = boss.enemy.x;
					boss.centerY = boss.enemy.y;
				}
				else if (boss.enemy.state == Normal && boss.enemy.life <= 50)
				{
					// 通常状態でライフが50以下になったら、気絶する
					boss.enemy.state = Swoon;
					boss.swoonTime = SwoonTime;
					//気絶時の初速度を決める
					boss.enemy.vx = 1.2f;
					boss.enemy.vy = 1.2f;
				}
				playerBullets[i].isDead = true;
			}
		}
		// 豆鉄砲の処理
		for (int i = 0; i < PlayerPeasBulletMax; i++) {
			if (playerPeasBullets[i].isDead)continue; //使用してない弾は判定しない

			for (int k = 0; k < enemyMax; k++) {
				if (enemys[k].isDead)continue;

				//自機弾と敵が重なっているか
				if (CircleCircleIntersection(playerPeasBullets[i].x, playerPeasBullets[i].y,
					playerPeasBullets[i].collisionRadius,
					enemys[k].x, enemys[k].y,
					enemys[k].collisionRadius)
					) {
					if (enemys[k].life <= 0) {
						SetExplosion(enemys[k].x, enemys[k].y);
						enemys[k].isDead = 1;
					}
					else {
						enemys[k].life -= 0.5;
					}

					playerPeasBullets[i].isDead = 1;
				}
			}
			if (playerPeasBullets[i].isDead || boss.enemy.isDead) continue;
			// 自機弾とボスが重なっているか？
			if (CircleCircleIntersection(
				playerPeasBullets[i].x + playerPeasBullets[i].collisionRadius / 2,
				playerPeasBullets[i].y + playerPeasBullets[i].collisionRadius / 2,
				playerPeasBullets[i].collisionRadius,
				boss.enemy.x + boss.enemy.collisionRadius / 2,
				boss.enemy.y + boss.enemy.collisionRadius / 2,
				boss.enemy.collisionRadius))
			{
				// 登場時、気絶時、死亡時は被弾しても何もしない
				if (boss.enemy.state == Appear ||
					boss.enemy.state == Swoon || boss.enemy.state == Dying)
					return;


				boss.enemy.life -= 0.5;
				if (boss.enemy.life <= 0)
				{
					// ライフが無くなったら、すぐ消滅するのではなく、死亡状態へ移行
					boss.enemy.state = Dying;
					boss.dyingTime = DyingTime;
					boss.centerX = boss.enemy.x;
					boss.centerY = boss.enemy.y;
				}
				else if (boss.enemy.state == Normal && boss.enemy.life <= 50)
				{
					// 通常状態でライフが50以下になったら、気絶する
					boss.enemy.state = Swoon;
					boss.swoonTime = SwoonTime;
					//気絶時の初速度を決める
					boss.enemy.vx = 1.2f;
					boss.enemy.vy = 1.2f;
				}
				playerPeasBullets[i].isDead = true;
			}
		}

		//自機が生きているときだけする処理
		for (int i = 0; i < PlayerMax; i++)
		{
			if (!player.isDead) {
				for (int i = 0; i < enemyMax; i++) {
					//敵が死んでたらスキップ
					if (enemys[i].isDead)continue;

					//自機と敵の重なり
					if (CircleCircleIntersection(player.x, player.y,
						player.collisionRadius,
						enemys[i].x, enemys[i].y,
						enemys[i].collisionRadius)
						) {
						//無敵じゃなければ
						if (player.invincible == 0) {
							PlayerTakeDamage();
							SetExplosion(enemys[i].x, enemys[i].y);
							enemys[i].isDead = 1;
						}
					}
				}
				for (int i = 0; i < EnemyBulletMax; i++) {
					if (enemyBullets[i].isDead)continue;

					if (CircleCircleIntersection(player.x, player.y,
						player.collisionRadius,
						enemyBullets[i].x, enemyBullets[i].y,
						enemyBullets[i].collisionRadius)
						) {
						if (player.invincible == 0) {
							PlayerTakeDamage();
							enemyBullets[i].isDead = 1;
						}
					}
				}
			}
		}
	}

	//敵配置データcsv読み込み
	void LoadEnemyPos(const char* filePath)
	{
		FILE* fp;

		char fname[256];

		snprintf(fname, 256, filePath);

		char line[Width * 4];
		fp = fopen(fname, "r");

		if (fp == NULL) {
			printf("%s file not open!\n", filePath);
			return;
		}

		int y = 0;
		while (fgets(line, sizeof(line), fp) != NULL) {
			printf("%s", line);
			char* p1;
			int x = 0;
			p1 = strtok(line, ",");

			//分割する文字がなくなるまで繰り返す
			while (p1 != NULL) {
				enemyData[y][x] = atoi(p1);
				p1 = strtok(NULL, ",");

				x++;
			}
			y++;
		}
		fclose(fp);
	}

	//画面スクロールして敵を生成処理
	void Scroll(float delta)
	{
		// スクロールする前の、画面右端のセルの列番号（x）
		x1 = (position + ScreenWidth) / CellSize;

		// スクロールする
		position += delta;

		// スクロールした後の、画面右端のセルの列番号（x）
		x2 = (position + ScreenWidth) / CellSize;

		// スクロールした後の画面右端のセルがマップの範囲外に出ちゃったら何もしないで終了
		if (x2 > Width)return;

		// スクロールする前と後で、画面右端のセルが同じ場合は、何もしないで終了
		if (x1 == x2)return;

		// 画面右端のセルの左端のx座標
		CellX = x2 * CellSize - position;

		// 
		// 上端のセルから下端のセルまで舐めて、敵データが配置されていたら、敵を生成する
		for (int i = 0; i < Height; i++) {
			// 番号に応じて敵を生成する
			if (enemyData[i][x2] < 0) continue;

			CellY = CellSize * i;
			if (enemyData[i][x2] != 100) {
				AddEnemy(CellX, CellY, enemyData[i][x2]);
			}
			else {
				InitBoss(CellX + 90, CellY + 32); // ボスは横幅180pxだから90px右に生成
			}
		}
	}

public:

	MyGame() :gslib::Game{ ScreenWidth,ScreenHeight }{}

private:

	//変数宣言
	int enemyCount = 0;
	int timer;
	float enemyTime;

	int x1, x2;
	float CellX = 0.0f;
	float CellY = 0.0f;

	int flg;

	// 自機の宣言
	Player player; // プレイヤー配列
	PlayerBullet playerBullets[PlayerBulletMax]; //自機弾配列の宣言
	PlayerPeasBullet playerPeasBullets[PlayerPeasBulletMax]; // 豆鉄砲配列の宣言
	/*PlayerBullet playerPeasBullets*/

	//敵の宣言
	Enemy enemys[enemyMax]; //敵解列の宣言
	BOSS boss; //敵(ボス)の宣言
	EnemyBullet enemyBullets[EnemyBulletMax]; //敵弾配列の宣言

	State state;

	Explosion explosion[ExplosionMax];// 爆発エフェクト配列宣言

	//マップデータ
	int enemyData[Height][Width]; // 敵配置データ
	float position; // 現在の位置（画面左端の座標）

	// 開始
	void start() override {
		gsLoadTexture(ePLAYER00, "Image/player.png");
		gsLoadTexture(ePLAYER01, "Image/player01.png");
		gsLoadTexture(ePLAYERBULLET, "Image/player_bullet.png");
		gsLoadTexture(ePLAYERPEASBULLET, "Image/player_peasbullet.png");
		gsLoadTexture(eENEMY00, "Image/zako0.png");
		gsLoadTexture(eENEMY01, "Image/zako1.png");
		gsLoadTexture(eENEMY02, "Image/zako2.png");
		gsLoadTexture(eENEMY03, "Image/zako3.png");
		gsLoadTexture(eENEMY04, "Image/zako4.png");
		gsLoadTexture(eENEMY05, "Image/zako5.png");
		gsLoadTexture(eENEMY06, "Image/zako6.png");
		gsLoadTexture(eENEMY07, "Image/zako7.png");
		gsLoadTexture(eENEMY08, "Image/zako8.png");
		gsLoadTexture(eENEMY09, "Image/zako9.png");
		gsLoadTexture(eENEMYBULLET, "Image/enemy_bullet_16.png");
		gsLoadTexture(eEXPLOSION, "Image/explosion.png");
		gsLoadTexture(eBOSS_NORMAL, "Image/boss1.png");
		gsLoadTexture(eBOSS_SWOON, "Image/boss2.png");
		gsLoadTexture(eBOSS_ANGRY, "Image/boss3.png");

		gsLoadSE(eShotSE, "Sound/ショット.wav", 1, GWAVE_DEFAULT);

		gsLoadBGM(eBGM1, "Sound/Dance_With_Powder.ogg", GS_TRUE);

		LoadEnemyPos("Map/stage1.csv");

		gsFontParameter(GS_FONT_NORMAL, 48, "MSゴシック");
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		state = Title;

		Reset();

	}

	//更新
	void update(float delta_time) override {
		//タイトル
		if (state == Title) {
			if (gsGetKeyTrigger(GKEY_A)) {
				state = Select;
			}
		}
		//キャラ選択
		else if (state == Select) {
			{
				if (gsGetKeyTrigger(GKEY_LEFT) && player.type > 0) {
					player.type--;
				}
				if (gsGetKeyTrigger(GKEY_RIGHT) && player.type < 3) {
					player.type++;
				}

				if (gsGetKeyTrigger(GKEY_A)) {
					AddPlayer(player.x, player.y, player.type);
					state = Play;
				}
			}
		}
		//ゲームプレイ
		else if (state == Play) {
			if (gsGetKeyTrigger(GKEY_A)) {
				state = Over;
			}
			count++;
			//プレイヤー更新処理
			UpdatePlayer(delta_time);

			//プレイヤー弾更新処理
			UpdatePlayerBullets(delta_time);

			// 豆鉄砲更新処理
			UpdatePlayerPeasBullets(delta_time);

			//敵の動き
			UpdateEnemys(delta_time);

			UpdateBoss();

			UpdateEnemyBullets(delta_time);

			//爆発エフェクト更新処理
			UpdateExplosion(delta_time);

			// 衝突判定
			CollisionDetection();

			// マップ（敵）データをスクロール
			Scroll(ScrollSpeed);
		}
		//ゲームオーバー
		else if (state == Over) {
			if (gsGetKeyTrigger(GKEY_A)) {
				state = Clear;
			}
		}
		//ゲームクリア
		else if (state == Clear) {
			if (gsGetKeyTrigger(GKEY_A)) {
				state = Title;
			}
		}
	}

	// 描画
	void draw() override {
		if (state == Title) {
			DrawString("タイトル", 0, 0);
		}
		else if (state == Select) {
			for (int i = 0; i < PlayerMax; i++)
			{
				DrawString("キャラ選択", 0, 0);

				char Type[20];
				snprintf(Type, 64, "プレイヤー%d", player.type);
				DrawString(Type, 360, 180);

				// プレイヤーの描画
				DrawPlayer();
			}
		}
		else if (state == Play)
		{
			DrawString("プレイ", 0, 0);
			// プレイヤーの描画
			DrawPlayer();

			//敵の描画
			DrawEnemy();

			DrawBoss();

			// 自機弾の描画関数を呼ぶを追加
			DrawPlayerBullet();

			// 豆鉄砲の描画関数を呼ぶ
			DrawPlayerPeasBullet();

			//敵弾の描画
			DrawEnemyBullet();

			//爆発エフェクト描画処理
			DrawExplosion();

			char life[20];
			/*snprintf(life, 64, "ゲージ:%d/100", player.charge);*/
			DrawString(life, 690, 0);

		}
		else if (state == Over) {
			DrawString("ゲームオーバー", 0, 0);
		}
		else if (state == Clear) {
			DrawString("ゲームクリア", 0, 0);
		}
	}

	// 終了
	void end() override {
	}

};

// メイン関数
int main() {
	return MyGame().run();
}