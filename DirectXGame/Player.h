#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include <Tree.h>

class Player {
public: // メンバ関数
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

	const WorldTransform& GetWorldTransform() { return worldTransforms_[(int)Parts::kBody]; }
	
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
		kRightLeg
		
	};

	//// ワールド変換データ
	//WorldTransform worldTransform_;

	Model* leg_ = nullptr;
	Model* body_ = nullptr;
	static const int kMaxParts = 5;
	WorldTransform worldTransforms_[kMaxParts];
	int32_t leftLegRotate_ = 0u;  
	int32_t rightLegRotate_ = 0u;
	int32_t rotationSpeed_ = 1;
};
