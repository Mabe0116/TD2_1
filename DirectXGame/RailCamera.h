#pragma once
#include"WorldTransform.h"
#include <ViewProjection.h>
#include"MyMath.h"
/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(
	    const Vector3& velocity, const Vector3& position, const Vector3& rotation);
	/// <summary>
	/// 更新
	/// </summry>
	void Update();

	const ViewProjection& GetViewProjection() { return viewprojection_; }

	/*WorldTransform GetWorldPosition();
	WorldTransform GetWorldRotation();*/

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewprojection_;
	// 速度
	Vector3 velocity_;
};