#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include <Tree.h>

class Player {
public: // メンバ関数
	~Player();
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	 void SetParent(const WorldTransform* parent) { 
		 worldTransforms_[(int)Parts::kBody].parent_ = parent;
	 }

	 void SetViewProjection(const ViewProjection* viewProjection) {
		 viewProjection_ = viewProjection;
	 }

	
	const WorldTransform& GetWorldTransform() { return worldTransforms_[(int)Parts::kBody]; }
	
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition(){// ワールド座標を入れる変数
		Vector3 worldPos;
		// ワールド行列の平行移動成分を取得(ワールド座標)
		worldPos.x = worldTransforms_[(int)Parts::kBody].matWorld_.m[3][0];
		worldPos.y = worldTransforms_[(int)Parts::kBody].matWorld_.m[3][1];
		worldPos.z = worldTransforms_[(int)Parts::kBody].matWorld_.m[3][2];
		return worldPos;
	};

private:	// メンバ変数
  // キーボード入力
	Input* input_ = nullptr;
	enum class Parts{
		kBody,

		kRootLeftLeg,
		kRootRightLeg,
		kLeftLeg,
		kRightLeg,

		kRootLeftHand,
		kRootRightHand,
		kLeftHand,
		kRightHand,
		

		kMaxParts,
	};

	// ワールド変換データ
	WorldTransform worldTransform_;
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	Model* leg_ = nullptr;
	Model* body_ = nullptr;
	Model* hand_ = nullptr;
	//static const int kMaxParts = 5;
	WorldTransform worldTransforms_[(int)Parts::kMaxParts];
	int32_t leftLegRotate_ = 0u;  
	int32_t rightLegRotate_ = 0u;
	int32_t leftHandRotate_ = 0u;
	int32_t rightHandRotate_ = 0u;
	int32_t rotationSpeed_ = 1;
};
