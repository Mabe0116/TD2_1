﻿#include "Player.h"
#include "MyMath.h"

#define LEG_ROTATE_MAX 30

Player::~Player() {
	delete body_;
	delete leg_;
	delete hand_;
}


void Player::Initialize() {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	body_ = Model::CreateFromOBJ("body");
	leg_ = Model::CreateFromOBJ("Leg");
	hand_ = Model::CreateFromOBJ("Hand");

	worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kBody)];
	worldTransforms_[static_cast<int>(Parts::kRootRightLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kBody)];

	worldTransforms_[static_cast<int>(Parts::kLeftLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)];
	worldTransforms_[static_cast<int>(Parts::kRightLeg)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kRootRightLeg)];

	// 手
	worldTransforms_[static_cast<int>(Parts::kRootLeftHand)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kBody)];
	worldTransforms_[static_cast<int>(Parts::kRootRightHand)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kBody)];
	worldTransforms_[static_cast<int>(Parts::kLeftHand)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kRootLeftHand)];
	worldTransforms_[static_cast<int>(Parts::kRightHand)].parent_ =
	    &worldTransforms_[static_cast<int>(Parts::kRootRightHand)];

	for (int i = 0; i < (int)Parts::kMaxParts; i++) {
		// 定数バッファ作成、これ呼ばないとTranferMatrixでエラーが起きる
		worldTransforms_[i].Initialize();
	}

	worldTransforms_[static_cast<int>(Parts::kBody)].rotation_ = {ToRadian(270), -ToRadian(0), ToRadian(180)};
	worldTransforms_[static_cast<int>(Parts::kBody)].translation_ = {0, 0.0f, -13};
	worldTransforms_[static_cast<int>(Parts::kLeftLeg)].translation_ = {0, -2.5f, 0};
	worldTransforms_[static_cast<int>(Parts::kRightLeg)].translation_ = {0, -2.5f, 0};
	worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)].translation_ = {-2, 0.0f, 0};
	worldTransforms_[static_cast<int>(Parts::kRootRightLeg)].translation_ = {2, 0.0f, 0};

	worldTransforms_[static_cast<int>(Parts::kLeftLeg)].translation_ = {0.0f, -3.0f, 0.0f};
	worldTransforms_[static_cast<int>(Parts::kRightLeg)].translation_ = {0.0f, -3.0f, 0.0f};
	worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)].translation_ = {-2.0f, -3.0f, 0.0f};
	worldTransforms_[static_cast<int>(Parts::kRootRightLeg)].translation_ = {2.0f, -3.0f, 0.0f};

	worldTransforms_[static_cast<int>(Parts::kLeftHand)].translation_ = {-1.0f, -0.5f, 0.0f};
	worldTransforms_[static_cast<int>(Parts::kRightHand)].translation_ = {1.0f, -0.5f, 0.0f};
	worldTransforms_[static_cast<int>(Parts::kRootLeftHand)].translation_ = {-2.0f, -0.5f, 0.0f};
	worldTransforms_[static_cast<int>(Parts::kRootRightHand)].translation_ = {2.0f, -0.5f, 0.0f};

	worldTransforms_[static_cast<int>(Parts::kRootRightHand)].rotation_ = {
	    0.0f, 0.0f, ToRadian(-20)};
	worldTransforms_[static_cast<int>(Parts::kRootLeftHand)].rotation_ = {0.0f, 0.0f, ToRadian(20)};

	//ライフ
	Life_ = 3;
}

void Player::Update() {

	worldTransforms_[static_cast<int>(Parts::kRootLeftLeg)].rotation_.x = ToRadian(leftLegRotate_);
	worldTransforms_[static_cast<int>(Parts::kRootRightLeg)].rotation_.x =
	    ToRadian(-leftLegRotate_);

	worldTransforms_[static_cast<int>(Parts::kRootLeftHand)].rotation_.x =
	    ToRadian(-leftHandRotate_);
	worldTransforms_[static_cast<int>(Parts::kRootRightHand)].rotation_.x =
	    ToRadian(leftHandRotate_);

	//worldTransforms_[static_cast<int>(Parts::kBody)].rotation_.y += 0.01f;

	// 足
	leftLegRotate_ += rotationSpeed_; // leftLegRotate_ = leftLegRotate_ + rotationSpeed_
	if (leftLegRotate_ >= LEG_ROTATE_MAX || leftLegRotate_ <= -LEG_ROTATE_MAX) {
		rotationSpeed_ = -rotationSpeed_;
		// rotationSpeed_ *= -1;
	}
	
	// 手
	leftHandRotate_ += rotationSpeed_; // leftHandRotate_ = leftHandRotate_ + rotationSpeed_
	
	for (int i = 0; i < (int)Parts::kMaxParts; i++) {
		// アフィン変換 -> 回転や拡大縮小、平行移動行うための行列
		// worldTransformのrotation,translation,scale
		// アフィン変換してワールド行列計算、ワールド行列を転送
		worldTransforms_[i].UpdateMatrix();
	}

	Vector3 offset = {0.0f, 2.0f, -10.0f};

	// カメラの角度から回転行列を計算する
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	//移動ベクトルをカメラの角度だけ回転する
	offset = TransformNormal(offset, worldTransform_.matWorld_);
}

void Player::Draw(const ViewProjection& viewProjection) {
	body_->Draw(worldTransforms_[static_cast<int>(Parts::kBody)], viewProjection);

	leg_->Draw(worldTransforms_[static_cast<int>(Parts::kRightLeg)], viewProjection);
	leg_->Draw(worldTransforms_[static_cast<int>(Parts::kLeftLeg)], viewProjection);

	hand_->Draw(worldTransforms_[static_cast<int>(Parts::kRightHand)], viewProjection);
	hand_->Draw(worldTransforms_[static_cast<int>(Parts::kLeftHand)], viewProjection);
}

void Player::OnCollision() {
	Life_--;
	if (Life_ <= 0) {
		isDead_ = true;
	}
}
