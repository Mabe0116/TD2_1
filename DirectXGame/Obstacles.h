#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"MyMath.h"
#include"ImGuiManager.h"
// GameSceneの前方宣言(苦肉の策)
class GameScene;

class Cylinder;

class Obstacles {
public:
	void Initialize(Model* model,float radian,const Vector3& position,Vector3& velocity);

	void Update();

	void Draw(ViewProjection& viewProojection);

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void SetCylinder(Cylinder* cylinder) { cylinder_ = cylinder; }

	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	private:

		WorldTransform worldTransform_;

		Model* model_;
	    
		Cylinder* cylinder_ = nullptr;

		float radian_;

		GameScene* gameScene_ = nullptr;

		Vector3 velocity_;

		int32_t randX;

};
