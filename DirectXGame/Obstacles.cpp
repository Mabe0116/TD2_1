#include "Obstacles.h"
#include "Cylinder.h"
#include <cmath>

void Obstacles::Initialize(Model* model, float radian,const Vector3& position,Vector3& velocity) {
	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	radian_ = radian;

	velocity_ = velocity;
	randX=0;
}

void Obstacles::Update() {
	

	worldTransform_.translation_.x = 0.0f + cosf(radian_) * randX;
	worldTransform_.translation_.z = 0.0f + sinf(radian_) * randX;

	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);
	if (worldTransform_.translation_.y <= -50)
	{
		
		worldTransform_.translation_.y = 50;
		randX = rand() % 6-5;
		
	
	}
	
		

	worldTransform_.UpdateMatrix();
}

void Obstacles::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

void Obstacles::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

Vector3 Obstacles::GetWorldPosition()
{ 
	Vector3 worldPos;

    worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
    worldPos.z = worldTransform_.matWorld_.m[3][2];

    return worldPos;
}