#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Score.h"
#include"Obstacles.h"
#include"Cylinder.h"
#include"DebugCamera.h"
#include"RailCamera.h"
#include <list>
#include <sstream>
#include <fstream>
#include "Player.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	void ObstaclesGeneration(const  Vector3& position,int radian);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// メインカメラ
	ViewProjection viewProjection_;

	Player* player_ = nullptr;
	Model* body_ = nullptr;
	Model* leg_ = nullptr;

	//Model* leg1_ = nullptr;
	//Model* leg2_ = nullptr;



	// プレイヤーの片足
	WorldTransform worldTransforms_[5];

	Score* score_ = nullptr;

	Obstacles* obstacles_ = nullptr;
	std::list<Obstacles*> obstacless_;

	Model* model_ = nullptr;

	Cylinder* cylinder_ = nullptr;
	Model* modelcylinder_ = nullptr;

	RailCamera* railCamera_ = nullptr;

	 // 敵発生コマンド
	std::stringstream enemyPopCommands;

	//デバッグカメラ
	DebugCamera* debugCamera_=nullptr;
	//デバッグカメラ有効
	bool isDebugCameraAcctive_ = false;
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
