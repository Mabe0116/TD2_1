#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
class TitleScene {

	public:
	TitleScene();
	    /// <summary>
	    /// デストラクタ
	    /// </summary>
	    ~TitleScene();

	    /// <summary>
	    /// 初期化
	    /// </summary>
	    void Initialize();

	    /// <summary>
	    /// 毎フレーム処理
	    /// </summary>
	    void Update();

	    ///< summary>
	    /// 描画
	    /// </summary>
	    void Draw();

	    

	   

	private: // メンバ変数
	    DirectXCommon* dxCommon_ = nullptr;
	    Input* input_ = nullptr;
	    Audio* audio_ = nullptr;
	  

	   

};
