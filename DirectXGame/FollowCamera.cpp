#include "FollowCamera.h"
#include "MyMath.h"
#include <math.h>

void FollowCamera::Initialize() {
	viewProjection_.rotation_.x = -ToRadian(30);
	viewProjection_.translation_;

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//worldTransform_.Initialize();
	//worldTransform_.translation_ = {0.0f, 6.0f, -12.0f};
	//worldTransform_.rotation_ = {ToRadian(30), 0.0f, 0.0f};
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void FollowCamera::Update() {

	//worldTransform_.UpdateMatrix();
	//
	//viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	
	// 追従対象がいれば
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, -15.0f, -50.0f};

		//カメラの角度から回転行列を計算する
		// Y軸回転行列を宣言
		Matrix4x4 matRotY = {0};
		matRotY.m[0][0] = cosf(viewProjection_.rotation_.y);
		matRotY.m[1][1] = 1;
		matRotY.m[0][2] = -sinf(viewProjection_.rotation_.y);
		matRotY.m[2][0] = sinf(viewProjection_.rotation_.y);
		matRotY.m[2][2] = cosf(viewProjection_.rotation_.y);
		matRotY.m[3][3] = 1;

		//オフセットをカメラの回転に合わせて回転させる
		offset = TransformNormal(offset, matRotY);

		// 座標をコピーしてオフセットからずらす
		viewProjection_.translation_ = Add(target_->translation_ , offset);
	}
	// ビュー行列の更新と転送
	viewProjection_.UpdateMatrix();
}
