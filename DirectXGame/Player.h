#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"

class Player {
public:		// メンバ関数
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
	void Draw(const ViewProjection &viewProjection);



private:	// メンバ変数
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
