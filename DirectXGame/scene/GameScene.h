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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* leg1_ = nullptr;
	Model* leg2_ = nullptr;



	// プレイヤーの片足
	WorldTransform worldTransforms_[5];

	Score* score_ = nullptr;

	Obstacles* obstacles_ = nullptr;

	Model* model_ = nullptr;

	Cylinder* cylinder_ = nullptr;
	Model* modelcylinder_ = nullptr;

	ViewProjection viewProjection_;
	//デバッグカメラ
	DebugCamera* debugCamera_=nullptr;
	//デバッグカメラ有効
	bool isDebugCameraAcctive_ = false;
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
