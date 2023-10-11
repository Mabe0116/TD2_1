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
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	player_ = new Player();
	player_->Initialize();

	//leg1_ = Model::CreateFromOBJ("leg1",true);
	//leg2_ = Model::CreateFromOBJ("leg2",true);

	viewProjection_.Initialize();

	/*for (int i = 1; i < 5; i++) {
		worldTransforms_[i].parent_ = &worldTransforms_[i - 1];
	}
	for (int i = 0; i < 5; i++) {
		worldTransforms_[i].Initialize();
		worldTransforms_[i].translation_ = {0.0f,-1.5f,0.0f};
	}
	worldTransforms_[4].rotation_.x =ToRadian(90);
	worldTransforms_[1].rotation_.x = ToRadian(90);*/
}

void GameScene::Update() {
	viewProjection_.UpdateMatrix();
	player_->Update();

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

	player_->Draw(viewProjection_);


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
