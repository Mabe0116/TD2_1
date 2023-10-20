#include "Tree.h"


Tree::~Tree() {
	
}

void Tree::Initialize(Model* model, const Vector3& position) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

}

void Tree::Update() { 	

	//回転速度
	const float RotateSpeed = 0.1f;

	if (input_->PushKey(DIK_SPACE)) {
		worldTransform_.rotation_.y += RotateSpeed;
		Timer++;
	}

	if (Timer > 60) {
		Meter++;
		Timer = 0;
	}

	worldTransform_.UpdateMatrix();

}

void Tree::Draw(const ViewProjection& viewProjection_) {
	//3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection_);
}

