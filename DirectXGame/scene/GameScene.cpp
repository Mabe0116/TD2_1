#include "GameScene.h"
#include "ImGuiManager.h"
#include "MyMath.h"
#include "TextureManager.h"
#include <cassert>


GameScene::GameScene() {}

GameScene::~GameScene() {
	delete score_;
	for (Obstacles* obstacles : obstacless_) {
         delete obstacles;
	}
	delete debugCamera_;
	delete railCamera_;
	delete player_;
	delete modelTree_;
	delete body_;
	delete leg_;
	delete tree_;
	delete model_;
	delete followCamera_;
	delete modelSkydome_;
}


void GameScene::Initialize() {

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	model_ = Model::Create();


	
	score_ = new Score();
	score_->Initialize();


	LoadEnemyPopData();

	railCamera_ = new RailCamera();
	const float kCameraSpeed = -0.0f;
	Vector3 Cameravelocity = {0.0f, kCameraSpeed, 0.0f};
	Vector3 translation = {0.0f, 0.0f, -50.0f};
	Vector3 rotation = {0.0f, 0.0f, 0.0f};
	railCamera_->Initialize(Cameravelocity, translation, rotation);

	viewProjection_.Initialize();
	worldTransform_.Initialize();
	

	player_ = new Player();
	player_->Initialize();
	//自キャラの生成と初期化処理
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 柱の初期化
	modelTree_ = Model::CreateFromOBJ("tree", true);
	Vector3 position_(0, 0, 0);
	tree_ = new Tree();
	tree_->Initialize(modelTree_, position_);
	player_->SetParent(&tree_->GetWorldTransform());
	//スコア
	TextureHandle_[0] = TextureManager::Load("UI/score/0.png");
	TextureHandle_[1] = TextureManager::Load("UI/score/1.png");
	TextureHandle_[2] = TextureManager::Load("UI/score/2.png");
	TextureHandle_[3] = TextureManager::Load("UI/score/3.png");
	TextureHandle_[4] = TextureManager::Load("UI/score/4.png");
	TextureHandle_[5] = TextureManager::Load("UI/score/5.png");
	TextureHandle_[6] = TextureManager::Load("UI/score/6.png");
	TextureHandle_[7] = TextureManager::Load("UI/score/7.png");
	TextureHandle_[8] = TextureManager::Load("UI/score/8.png");
	TextureHandle_[9] = TextureManager::Load("UI/score/9.png");
	//メートル
	TextureHandle_[10] = TextureManager::Load("UI/score/meter.png");
	//HP
	TextureHandle_[11] = TextureManager::Load("UI/HP.png");

	//スコアの配置
	sprite0 = Sprite::Create(TextureHandle_[1], {950.0f, 50.0f});
	sprite1 = Sprite::Create(TextureHandle_[1], {1000.0f, 50.0f});
	sprite2 = Sprite::Create(TextureHandle_[1], {1050.0f, 50.0f});
	sprite3 = Sprite::Create(TextureHandle_[1], {1100.0f, 50.0f});
	sprite4 = Sprite::Create(TextureHandle_[10], {1150.0f, 50.0f});

	//ライフの配置
	sprite5 = Sprite::Create(TextureHandle_[11], {10.0f, 50.0f});
	sprite6 = Sprite::Create(TextureHandle_[11], {40.0f, 50.0f});
	sprite7 = Sprite::Create(TextureHandle_[11], {80.0f, 50.0f});

	// 追従カメラの生成
	followCamera_ = new FollowCamera;
	// 追従カメラの初期化
	followCamera_->Initialize();
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	//Skydome
	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
	skydome_->Update();
	followCamera_->SetTarget(&tree_->GetWorldTransform());

	soundDataHandle_ = audio_->LoadWave("BGM//BGM2.mp3");
	audio_->PlayWave(soundDataHandle_, true);

	soundDataHandle2_ = audio_->LoadWave("SE//SE.wav");

	
}

void GameScene::Update() {
#ifdef _DEBUG
	isSceneEnd_ = false;
	if (input_->TriggerKey(DIK_S)) {
		isDebugCameraAcctive_ = true;
	}
	if (isDebugCameraAcctive_) {

		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// 追従カメラの更新
		followCamera_->SetRotationY(tree_->GetRotationY());
		followCamera_->Update();
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		// ビュープロジェクション行列の更新と転送
		// viewProjection_.UpdateMatrix();
	}
#endif

	player_->Update();
	tree_->Update();
	
	if (input_->TriggerKey(DIK_S)) {
		audio_->StopWave(soundDataHandle_);
	}
	
	for (Obstacles* obstacles : obstacless_) {
		obstacles->Update();
	}
	obstacless_.remove_if([](Obstacles* obstacle) {
		if (obstacle->IsDead()) {
			delete obstacle;
			return true;
		}
		return false;
	});

	//cylinder_->Update();
	
	// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();

	UpdateEnemyPopCommands();
	CheckAllCollisions();

	if (player_->IsDead()) {
		isSceneEnd_ = true;
	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>



	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	/*tree_->Draw(viewProjection_);

	player_->Draw(viewProjection_);*/

	tree_->Draw(viewProjection_);
	player_->Draw(viewProjection_);

	/*leg1_->Draw(worldTransforms_[0],viewProjection_ );
	leg2_->Draw(worldTransforms_[1],viewProjection_ );
	leg1_->Draw(worldTransforms_[2],viewProjection_ );
	leg2_->Draw(worldTransforms_[3],viewProjection_ );
	leg1_->Draw(worldTransforms_[4], viewProjection_);*/

	for (Obstacles* obstacles : obstacless_) {
		obstacles->Draw(viewProjection_);
	}

	skydome_->Draw(viewProjection_);

	//cylinder_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);
	
	//スコアの変動
	int32_t Meter = tree_->GetMeter();

	// 1000の位
	eachNumber[0] = Meter / 1000;
	Meter = Meter % 1000;

	// 100の位
	eachNumber[1] = Meter / 100;
	Meter = Meter % 100;

	//10の位
	eachNumber[2] = Meter / 10;
	Meter = Meter % 10;

	//1の位
	eachNumber[3] = Meter;
	

		// 1000の位
		sprite0->SetTextureHandle(TextureHandle_[eachNumber[0]]);
		if (eachNumber[0] == 0) {
			sprite0->SetTextureHandle(TextureHandle_[0]);
		} else if (eachNumber[0] == 1) {
			sprite0->SetTextureHandle(TextureHandle_[1]);
		} else if (eachNumber[0] == 2) {
			sprite0->SetTextureHandle(TextureHandle_[2]);
		} else if (eachNumber[0] == 3) {
			sprite0->SetTextureHandle(TextureHandle_[3]);
		} else if (eachNumber[0] == 4) {
			sprite0->SetTextureHandle(TextureHandle_[4]);
		} else if (eachNumber[0] == 5) {
			sprite0->SetTextureHandle(TextureHandle_[5]);
		} else if (eachNumber[0] == 6) {
			sprite0->SetTextureHandle(TextureHandle_[6]);
		} else if (eachNumber[0] == 7) {
			sprite0->SetTextureHandle(TextureHandle_[7]);
		} else if (eachNumber[0] == 8) {
			sprite0->SetTextureHandle(TextureHandle_[8]);
		} else if (eachNumber[0] == 9) {
			sprite0->SetTextureHandle(TextureHandle_[9]);
		}

		// 100の位
		sprite1->SetTextureHandle(TextureHandle_[eachNumber[1]]);
		if (eachNumber[1] == 0) {
			sprite1->SetTextureHandle(TextureHandle_[0]);
		} else if (eachNumber[1] == 1) {
			sprite1->SetTextureHandle(TextureHandle_[1]);
		} else if (eachNumber[1] == 2) {
			sprite1->SetTextureHandle(TextureHandle_[2]);
		} else if (eachNumber[1] == 3) {
			sprite1->SetTextureHandle(TextureHandle_[3]);
		} else if (eachNumber[1] == 4) {
			sprite1->SetTextureHandle(TextureHandle_[4]);
		} else if (eachNumber[1] == 5) {
			sprite1->SetTextureHandle(TextureHandle_[5]);
		} else if (eachNumber[1] == 6) {
			sprite1->SetTextureHandle(TextureHandle_[6]);
		} else if (eachNumber[1] == 7) {
			sprite1->SetTextureHandle(TextureHandle_[7]);
		} else if (eachNumber[1] == 8) {
			sprite1->SetTextureHandle(TextureHandle_[8]);
		} else if (eachNumber[1] == 9) {
			sprite1->SetTextureHandle(TextureHandle_[9]);
		}

		// 10の位
		sprite2->SetTextureHandle(TextureHandle_[eachNumber[2]]);
		if (eachNumber[2] == 0) {
			sprite2->SetTextureHandle(TextureHandle_[0]);
		} else if (eachNumber[2] == 1) {
			sprite2->SetTextureHandle(TextureHandle_[1]);
		} else if (eachNumber[2] == 2) {
			sprite2->SetTextureHandle(TextureHandle_[2]);
		} else if (eachNumber[2] == 3) {
			sprite2->SetTextureHandle(TextureHandle_[3]);
		} else if (eachNumber[2] == 4) {
			sprite2->SetTextureHandle(TextureHandle_[4]);
		} else if (eachNumber[2] == 5) {
			sprite2->SetTextureHandle(TextureHandle_[5]);
		} else if (eachNumber[2] == 6) {
			sprite2->SetTextureHandle(TextureHandle_[6]);
		} else if (eachNumber[2] == 7) {
			sprite2->SetTextureHandle(TextureHandle_[7]);
		} else if (eachNumber[2] == 8) {
			sprite2->SetTextureHandle(TextureHandle_[8]);
		} else if (eachNumber[2] == 9) {
			sprite2->SetTextureHandle(TextureHandle_[9]);
		}

		// 1の位
		sprite3->SetTextureHandle(TextureHandle_[eachNumber[3]]);

		if (eachNumber[3] == 0) {
			sprite3->SetTextureHandle(TextureHandle_[0]);
		} else if (eachNumber[3] == 1) {
			sprite3->SetTextureHandle(TextureHandle_[1]);
		} else if (eachNumber[3] == 2) {
			sprite3->SetTextureHandle(TextureHandle_[2]);
		} else if (eachNumber[3] == 3) {
			sprite3->SetTextureHandle(TextureHandle_[3]);
		} else if (eachNumber[3] == 4) {
			sprite3->SetTextureHandle(TextureHandle_[4]);
		} else if (eachNumber[3] == 5) {
			sprite3->SetTextureHandle(TextureHandle_[5]);
		} else if (eachNumber[3] == 6) {
			sprite3->SetTextureHandle(TextureHandle_[6]);
		} else if (eachNumber[3] == 7) {
			sprite3->SetTextureHandle(TextureHandle_[7]);
		} else if (eachNumber[3] == 8) {
			sprite3->SetTextureHandle(TextureHandle_[8]);
		} else if (eachNumber[3] == 9) {
			sprite3->SetTextureHandle(TextureHandle_[9]);
		}
	
	sprite0->Draw();
	sprite1->Draw();
	sprite2->Draw();
	sprite3->Draw();
	sprite4->Draw();

	//ライフ変動
	if (player_->GetLife() == 3) {
		sprite5->Draw();
		sprite6->Draw();
		sprite7->Draw();
	} else if (player_->GetLife() == 2) {
		sprite5->Draw();
		sprite6->Draw();
	} else if (player_->GetLife() == 1) {
		sprite5->Draw();
	}

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::ObstaclesGeneration(const Vector3& position, int radian) {

	Obstacles* obstacles = new Obstacles();
	
	const float kObstaclesSpeed = 0.5f;
	Vector3 velocity = {0.0f, kObstaclesSpeed, 0.0f};
	modelobstacles_ = Model::CreateFromOBJ("nuts", true);
	obstacles->Initialize(modelobstacles_, ToRadian(radian), position, velocity);
	
	obstacless_.push_back(obstacles);
}

void GameScene::LoadEnemyPopData() {

	// ファイルを開く
	std::ifstream file;
	std::string filename = "Resources//nuts//obstaclesPop.csv";
	file.open(filename);
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {
	bool iswait = false;
	int32_t waitTimer = 0;

	// 待機処理
	if (iswait) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			iswait = false;
		}
		return;
	}
	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくなる
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行は飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			int radian = rand() % 360;

			// 敵を発生させる
			ObstaclesGeneration(Vector3(x, y, z), radian);
		}

		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			iswait = true;
			waitTimer = waitTime;

			// コマンドループを抜ける
			break;
		}
	}
}

void GameScene::CheckAllCollisions() {

	//判定対象AとBの座標
	Vector3 posA, posB;

	//障害物リストの取得
	//const std::list<Obstacles*>& GetObstacles = obstacles_->GetObstacles();

	#pragma region
	#pragma endregion

	//自キャラの座標
	posA = player_->GetWorldPosition();

	//自キャラと障害物全ての当たり判定
	for (Obstacles* obstacles : obstacless_) {
		// obstacless_[0]
		
		// 障害物の座標
		posB = obstacles->GetWorldPosition();

		// 球と球の交差判定
		float Distance = Length(Subtract(posA, posB));
		if (Distance < 4.0f + 4.0f) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 障害物の衝突時コールバックを呼び出す
			obstacles->OnCollision();

			audio_->PlayWave(soundDataHandle2_);
		}
	}


}







