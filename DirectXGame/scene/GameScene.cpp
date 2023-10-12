#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { delete score_;
	delete obstacles_;
	delete cylinder_;
	delete debugCamera_;
	delete railCamera_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	model_ = Model::Create();

	score_ = new Score();
	score_->Initialize();
	/*Vector3 position = {0.0f, 0.0f, 0.0f};
	ObstaclesGeneration(position);*/
	LoadEnemyPopData();

	cylinder_ = new Cylinder();
	modelcylinder_ = Model::CreateFromOBJ("cylinder", true);
	const float kRotSpeed = 0.1f;
	Vector3 velocity = {0.0f, kRotSpeed, 0.0f};
	
	Vector3 CylinderPosition = {0.0f, 0.0f, 50.0f};
	cylinder_->Initialize(modelcylinder_,velocity,CylinderPosition);
	

	railCamera_ = new RailCamera();
	const float kCameraSpeed = -0.0f;
	Vector3 Cameravelocity = {0.0f,kCameraSpeed, 0.0f};
	Vector3 translation = {0.0f, 0.0f, -50.0f};
	Vector3 rotation = {0.0f, 0.0f, 0.0f};
	railCamera_->Initialize(Cameravelocity,translation,rotation);

	viewProjection_.Initialize();


	// 円柱とレールカメラの親子関係を結ぶ
	cylinder_->SetParent(&railCamera_->GetWorldTransform());
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() { //score_->Update();
	for (Obstacles* obstacles : obstacless_)
	{
		obstacles->Update();
	}
	
	cylinder_->Update();
	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraAcctive_ = true;
	}
	if (isDebugCameraAcctive_) {

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
#endif
	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();

	railCamera_->Update();

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
	for (Obstacles* obstacles : obstacless_) {
		obstacles->Draw(viewProjection_);
	}
	
	cylinder_->Draw(viewProjection_);

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

void GameScene::ObstaclesGeneration(const Vector3& position)
{
	
	
	Obstacles* obstacles = new Obstacles();
	float radian = rand()/static_cast<float>(1);
	const float kObstaclesSpeed = 0.5f;
	Vector3 velocity = {0.0f, kObstaclesSpeed, 0.0f};
	obstacles->Initialize(model_,(float)radian,position,velocity);
	//obstacles->SetGameScene(this);
	//obstacles->SetCylinder(cylinder_);
	//obstacles->SetParent(&railCamera_->GetWorldTransform());
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

			// 敵を発生させる
			ObstaclesGeneration(Vector3(x, y, z));
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
