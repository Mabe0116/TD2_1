#pragma once
#include <Input.h>
#include <Model.h>
#include <cassert>

class Tree {

public:
	// デストラクタ
	~Tree();
	// 初期化
	void Initialize(Model* model, const Vector3& position);
	// 更新
	void Update();
	// 描画
	void Draw(const ViewProjection& viewProjection_);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
};
