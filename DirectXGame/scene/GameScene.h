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

#include"DebugCamera.h"
#include"RailCamera.h"
#include <list>
#include <sstream>
#include <fstream>
#include "Player.h"
#include <Tree.h>
#include "DebugCamera.h"
#include "FollowCamera.h"

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
	// モデル
	Model* model_ = nullptr;
	// メインカメラ
	ViewProjection viewProjection_;
	WorldTransform worldTransform_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	Player* player_ = nullptr;
	Model* body_ = nullptr;
	Model* leg_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//追従カメラ, カメラの親がプレイヤー、プレイヤーの親が円柱
	FollowCamera* followCamera_ = nullptr;

	Score* score_ = nullptr;

	//stacles* obstacles_ = nullptr;
	std::list<Obstacles*> obstacless_;
	Model* modelobstacles_ = nullptr;

	
	Model* modelcylinder_ = nullptr;

	RailCamera* railCamera_ = nullptr;

	 // 敵発生コマンド
	std::stringstream enemyPopCommands;

	//デバッグカメラ有効
	bool isDebugCameraAcctive_ = false;
	

	//柱
	Model* modelTree_ = nullptr;
	Tree* tree_ = nullptr;


		

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
