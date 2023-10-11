#include "Obstacles.h"
#include<cmath>

void Obstacles::Initialize(Model* model)
{ model_ = model;

worldTransform_.Initialize();
	
	worldTransform_.translation_ = {0.0f,-5.0f,0.0f};
worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

}

void Obstacles::Update() { 
	worldTransform_.UpdateMatrix();
	




	worldTransform_.translation_.x = 0.0f + cosf(0.0f) * 0.8f;
	worldTransform_.translation_.z = 0.0f + sinf(-0.5f) * 9.0f;
	


	


}

void Obstacles::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}