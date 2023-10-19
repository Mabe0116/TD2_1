#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"MyMath.h"
#include"ImGuiManager.h"
// GameSceneの前方宣言(苦肉の策)
class GameScene;



class Obstacles {
public:
	void Initialize(Model* model,float radian,const Vector3& position,Vector3& velocity);

	void Update();

	void Draw(ViewProjection& viewProojection);

	void SetCylinder(Cylinder* cylinder) { cylinder_ = cylinder; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	bool IsDead() const { return isDead_; }

	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	Vector3 GetWorldPosition();

	

	private:

		WorldTransform worldTransform_;

		Model* model_;
	    
		
		//どの角度に行くかのランダムな変数
		float radian_;

		//障害物の落下速度
		Vector3 velocity_;
		//条件式に入れる用のランダムな変数
		int32_t randX;
	    // どの位置に行く用の変数
		float position_;
		//スタート開始から何秒か待つ用の変数
	    int32_t timer_;
	    int32_t timerspeed_;
	    // デスフラグ
	    bool isDead_ = false;
};
