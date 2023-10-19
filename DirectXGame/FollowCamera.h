#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>
class FollowCamera {
public:
	void Initialize();

	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	void SetRotationY(float rotation) { 
		viewProjection_.rotation_.y = rotation;

	}

	 void SetParent(const WorldTransform* parent) {
		worldTransform_.parent_ = parent;
		 worldTransform_.UpdateMatrix();
	}


private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールド変換データ
	WorldTransform worldTransform_;
	//追従対象
	const WorldTransform* target_ = nullptr;
	//キーボード入力
	Input* input_ = nullptr;
};
