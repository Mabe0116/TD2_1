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
	delete tree_;
	delete debugCamera_;
	delete followCamera_;
	delete model_;
	delete modelobstacles_;
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
	// 柱の初期化
	modelTree_ = Model::CreateFromOBJ("tree", true);
	Vector3 position_(0, 0, 0);
	tree_ = new Tree();
	tree_->Initialize(modelTree_, position_);
	player_->SetParent(&tree_->GetWorldTransform());

	

	// 追従カメラの生成
	followCamera_ = new FollowCamera;
	// 追従カメラの初期化
	followCamera_->Initialize();
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
}

void GameScene::Update() {
#ifdef _DEBUG
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
		followCamera_->Update();
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		// ビュープロジェクション行列の更新と転送
		// viewProjection_.UpdateMatrix();
	}
#endif

	player_->Update();
	tree_->Update();

	
	for (Obstacles* obstacles : obstacless_) {
		obstacles->Update();
	}

	//cylinder_->Update();

	// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();

	UpdateEnemyPopCommands();
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

	//cylinder_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::ObstaclesGeneration(const Vector3& position, int radian) {

	Obstacles* obstacles = new Obstacles();
	
	const float kObstaclesSpeed = 1.0f;
	Vector3 velocity = {0.0f, kObstaclesSpeed, 0.0f};
	modelobstacles_ = Model::CreateFromOBJ("nuts", true);
	obstacles->Initialize(modelobstacles_, ToRadian(radian), position, velocity);
	
	obstacless_.push_back(obstacles);
}

void GameScene::LoadEnemyPopData() {

	// ファイルを開く
	std::ifstream file;
	std::string filename = "Resources//obstaclesPop.csv";
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

			int radian = rand() % 361;

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
