#include "FollowCamera.h"
#include "MyMath.h"

void FollowCamera::Initialize() {

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void FollowCamera::Update() {
	// 追従対象がいれば
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		// 座標をコピーしてオフセットからずらす
		viewProjection_.translation_ = Add(target_->translation_ , offset);
	}
	// ビュー行列の更新と転送
	viewProjection_.UpdateMatrix();
}
