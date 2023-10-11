#pragma once
#include <Model.h>
#include <cassert>

class Tree {

	public:

		//デストラクタ
	    ~Tree();
	//初期化
	void Initialize(Model* model, const Vector3& position);
	//更新
	void Update();
	//描画
	void Draw(const WorldTransform& worldTransform_, const ViewProjection& viewProjection_);
	
//ワールド変換データ
	    WorldTransform worldTransform_;

	private:

		
	    //モデル
	    Model* model_ = nullptr;
		//テクスチャハンドル
	    uint32_t textureHandle_=0u;
};
