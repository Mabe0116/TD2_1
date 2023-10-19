#include "Obstacles.h"
#include <cmath>

void Obstacles::Initialize(Model* model, float radian,const Vector3& position,Vector3& velocity) {
	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	radian_ = radian;

	velocity_ = velocity;
	randX=0;
	position_ = 6.0f;
	timer_ = 0;
	timerspeed_ = 1;
}

void Obstacles::Update() {
	
	timer_ += timerspeed_;
	worldTransform_.translation_.x = 0.0f + cosf(radian_) * position_;
	worldTransform_.translation_.z = 0.0f + sinf(radian_) * position_;
	if (timer_ >= 50)
	{
		worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);
		timerspeed_ = 0;
	}
	
	if (worldTransform_.translation_.y <= -50)
	{
		
		worldTransform_.translation_.y = 50;
		randX = rand() % 6+1;
		if (randX >= 1 && randX <= 3)
		{
			position_ = 7.0f;
		}
		else if (randX >= 4 && randX <= 6) {
			position_ = -7.0f;
		}
		

	
	}
	
		

	worldTransform_.UpdateMatrix();
}

void Obstacles::Draw(ViewProjection& viewProjection) {
	if (timer_ >= 20) {
		model_->Draw(worldTransform_, viewProjection);
	}
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