#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
#include"Result.h"

class GameClear {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameClear();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameClear();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	///< summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kTitle; }
	

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isSceneEnd_ = false;

	Result* result_ = nullptr;

	
	// 画像
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
};
