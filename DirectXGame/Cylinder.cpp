#include "Cylinder.h"
#include <cassert>
void Cylinder::Initialize(Model* model,Vector3& velocity,Vector3& position) { 
	assert(model);

	model_ = model;
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {1.0f, 5.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.Initialize();

	velocity_ = velocity;

}

void Cylinder::Update() { worldTransform_.UpdateMatrix();

worldTransform_.rotation_ = Subtract(worldTransform_.rotation_, velocity_);


}

void Cylinder::Draw(ViewProjection& viewProjection)
{ model_->Draw(worldTransform_, viewProjection); }

Vector3 Cylinder::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Cylinder::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}