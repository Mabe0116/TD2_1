#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_.x = 60;
	worldTransform_.scale_.y = 60;
	worldTransform_.scale_.z = 60;
	worldTransform_.UpdateMatrix();
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
