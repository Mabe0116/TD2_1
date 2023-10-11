#include "Cylinder.h"
#include <cassert>
void Cylinder::Initialize(Model* model) { 
	assert(model);

	model_ = model;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 5.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.Initialize();

}

void Cylinder::Update() { worldTransform_.UpdateMatrix(); }

void Cylinder::Draw(ViewProjection& viewProjection)
{ model_->Draw(worldTransform_, viewProjection); }