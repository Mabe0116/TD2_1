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

	Vector3 GetWorldPosition();

	private:

		WorldTransform worldTransform_;

		Model* model_;
	    
		Cylinder* cylinder_ = nullptr;
		//どの角度に行くかのランダムな変数
		float radian_;

		GameScene* gameScene_ = nullptr;
		//障害物の落下速度
		Vector3 velocity_;
		//どの位置に行くかのランダムな変数
		int32_t randX;

};
