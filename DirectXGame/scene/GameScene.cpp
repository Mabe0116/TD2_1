#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "MyMath.h"
#include "ImGuiManager.h"
#include "Player.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	/*delete leg1_;
	delete leg2_;*/
	delete player_;
	delete modelTree_;
	delete tree_;
	delete debugCamera_;
	delete followCamera_;
}

void GameScene::Initialize() {

	//デバッグカメラの生成
	debugCamera_=new DebugCamera(1280,720);
	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	player_ = new Player();
	player_->Initialize();


	// 柱の初期化
	modelTree_ = Model::CreateFromOBJ("tree", true);
	Vector3 position_(0, 0, 0);
	tree_ = new Tree();
	tree_->Initialize(modelTree_,position_);
	player_->SetParent(&tree_->GetWorldTransform());

	viewProjection_.Initialize();
	worldTransform_.Initialize();


	// 追従カメラの生成
	followCamera_ = new FollowCamera;
	// 追従カメラの初期化
	followCamera_->Initialize();
	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
}

void GameScene::Update() {
	//viewProjection_.UpdateMatrix();
	
	// デバッグカメラの更新
	//debugCamera_->Update();
	

	//追従カメラの更新
	followCamera_->Update();
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.matView= followCamera_->GetViewProjection().matView;


	
	player_->Update();
	tree_->Update();

	

	//leg1_->Update(viewProjection_);
	/*worldTransforms_[0].rotation_.y += 0.01f;*/

	/*if (input_->TriggerKey(DIK_UP)) {
		count++;
	}
	if (input_->TriggerKey(DIK_DOWN)) {
		count--;
	}

	if (input_->PushKey(DIK_Q)) {
		worldTransforms_[count].rotation_.x +=0.01f;
	}
	if (input_->PushKey(DIK_E)) {
		worldTransforms_[count].rotation_.x += 0.01f;
	}*/

	/*for (int i = 0; i < 5; i++) {
		worldTransforms_[i].UpdateMatrix();
	}*/

	ImGui::Begin("count");

	ImGui::End();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	/*tree_->Draw(viewProjection_);

	player_->Draw(viewProjection_);*/

	tree_->Draw( debugCamera_->GetViewProjection());
	player_->Draw(debugCamera_->GetViewProjection());

	/*leg1_->Draw(worldTransforms_[0],viewProjection_ );
	leg2_->Draw(worldTransforms_[1],viewProjection_ );
	leg1_->Draw(worldTransforms_[2],viewProjection_ );
	leg2_->Draw(worldTransforms_[3],viewProjection_ );
	leg1_->Draw(worldTransforms_[4], viewProjection_);*/



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
