#pragma once

#include "Audio.h"
#include "Cylinder.h"
#include "DebugCamera.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "FollowCamera.h"
#include "Input.h"
#include "Model.h"
#include "Obstacles.h"
#include "Player.h"
#include "RailCamera.h"
#include "SafeDelete.h"
#include "Score.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Tree.h>
#include <fstream>
#include <list>
#include <sstream>
#include <Skydome.h>

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

	void ObstaclesGeneration(const Vector3& position, int radian);

	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// モデル
	Model* model_ = nullptr;
	// メインカメラ
	ViewProjection viewProjection_;
	WorldTransform worldTransform_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	Player* player_ = nullptr;
	Model* body_ = nullptr;
	Model* leg_ = nullptr;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// 追従カメラ, カメラの親がプレイヤー、プレイヤーの親が円柱
	FollowCamera* followCamera_ = nullptr;

	Score* score_ = nullptr;

	Obstacles* obstacles_ = nullptr;
	// 障害物リスト
	std::list<Obstacles*> obstacless_;

	Cylinder* cylinder_ = nullptr;
	Model* modelcylinder_ = nullptr;

	RailCamera* railCamera_ = nullptr;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	// デバッグカメラ有効
	bool isDebugCameraAcctive_ = false;

	// 柱
	Model* modelTree_ = nullptr;
	Tree* tree_ = nullptr;

	Sprite* sprite = nullptr;

	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
