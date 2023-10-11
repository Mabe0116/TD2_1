﻿#include "Player.h"
#include "MyMath.h"

#define LEG_ROTATE_MAX 30

void Player::Initialize() {
	body_ = Model::Create();
	leg_ = Model::CreateFromOBJ("Leg");

	worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kBody)];
	worldTransforms_[static_cast<int>(Parts::kRootRightLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kBody)];
	worldTransforms_[static_cast<int>(Parts::kLeftLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)];
	worldTransforms_[static_cast<int>(Parts::kRightLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kRootRightLeg)];

	for (int i = 0; i < kMaxParts; i++) {
		// 定数バッファ作成、これ呼ばないとTranferMatrixでエラーが起きる
		worldTransforms_[i].Initialize();
	}
	worldTransforms_[static_cast<int>(Parts::kBody)].rotation_.y = -ToRadian(60);
	worldTransforms_[static_cast<int>(Parts::kLeftLeg)].translation_ = {0, -2.5f, 0};
	worldTransforms_[static_cast<int>(Parts::kRightLeg)].translation_ = {0, -2.5f, 0};
	worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)].translation_ = {-2, 0.0f, 0};
	worldTransforms_[static_cast<int>(Parts::kRootRightLeg)].translation_ = {2, 0.0f, 0};
}

void Player::Update() {

	worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)].rotation_.x = ToRadian(leftLegRotate_);
	worldTransforms_[static_cast<int>(Parts::kRootRightLeg)].rotation_.x = ToRadian(-leftLegRotate_);

	leftLegRotate_ += rotationSpeed_; // leftLegRotate_ = leftLegRotate_ + rotationSpeed_ 
	if (leftLegRotate_ >= LEG_ROTATE_MAX || leftLegRotate_ <= -LEG_ROTATE_MAX)
	{
		rotationSpeed_ = -rotationSpeed_;
		// rotationSpeed_ *= -1;
	}
	for (int i = 0; i < kMaxParts; i++) {
		// アフィン変換 -> 回転や拡大縮小、平行移動行うための行列
		// worldTransformのrotation,translation,scale
		// アフィン変換してワールド行列計算、ワールド行列を転送
		worldTransforms_[i].UpdateMatrix();
	}
}

void Player::Draw(const ViewProjection& viewProjection) {
	body_->Draw(worldTransforms_[static_cast<int>(Parts::kBody)], viewProjection);
	leg_->Draw(worldTransforms_[static_cast<int>(Parts::kRightLeg)], viewProjection);
	leg_->Draw(worldTransforms_[static_cast<int>(Parts::kLeftLeg)], viewProjection);
}