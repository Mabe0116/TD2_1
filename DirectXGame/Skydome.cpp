#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_.x = 30;
	worldTransform_.scale_.y = 30;
	worldTransform_.scale_.z = 30;
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
