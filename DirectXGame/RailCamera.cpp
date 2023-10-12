#include "RailCamera.h"

void RailCamera::Initialize(
    const Vector3& velocity, const Vector3& position, const Vector3& rotation) {

	// ワールドトランスフォームの初期設定
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;
	//worldTransform_.translation_ = {0.0f, 0.0f, -100.0f};
	

	velocity_ = velocity;
	worldTransform_.Initialize();

	//viewprojection_.farZ = 1200.0f;
	viewprojection_.Initialize();
}

void RailCamera::Update() {
	worldTransform_.rotation_ = Subtract(worldTransform_.rotation_, velocity_);
	

	viewprojection_.matView = Inverse(worldTransform_.matWorld_);

	worldTransform_.UpdateMatrix();
	
}

//WorldTransform RailCamera::GetWorldPosition() {
//	// ワールド座標を入れる変数
//	WorldTransform worldPos;
//	// ワールド行列の平行移動成分を取得(ワールド座標)
//	worldPos.translation_.x = worldTransform_.matWorld_.m[3][0];
//	worldPos.translation_.y = worldTransform_.matWorld_.m[3][1];
//	worldPos.translation_.z = worldTransform_.matWorld_.m[3][2];
//
//	return worldPos;
//}
//
//WorldTransform RailCamera::GetWorldRotation() {
//	// ワールド座標を入れる変数
//	WorldTransform worldRot;
//	// ワールド行列の回転成分を取得(ワールド座標)
//	worldRot.rotation_.x = worldTransform_.matWorld_.m[2][0];
//	worldRot.rotation_.y = worldTransform_.matWorld_.m[2][1];
//	worldRot.rotation_.z = worldTransform_.matWorld_.m[2][2];
//
//	return worldRot;
//}