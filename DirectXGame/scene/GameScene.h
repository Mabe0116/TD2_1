#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <Tree.h>

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
	// メインカメラ
	ViewProjection viewProjection_;

	Player* player_ = nullptr;
	Model* body_ = nullptr;
	Model* leg_ = nullptr;

	//Model* leg1_ = nullptr;
	//Model* leg2_ = nullptr;

	//int count = 0;

	//// プレイヤーの片足
	//WorldTransform worldTransforms_[5];

	//柱
	Model* modelTree_ = nullptr;
	Tree* tree_ = nullptr;

	WorldTransform worldTransform_;

	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
