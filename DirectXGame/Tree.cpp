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

}

void Tree::Update() { 
}

void Tree::Draw(const WorldTransform &worldTransfom_,const ViewProjection& viewProjection_) {
	//3Dモデルの描画
	model_->Draw(worldTransfom_, viewProjection_);
}

