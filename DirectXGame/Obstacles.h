#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"MyMath.h"
#include"ImGuiManager.h"

class Obstacles {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProojection);

	

	private:

		WorldTransform worldTransform_;

		Model* model_;
	    
		

		

		

};
