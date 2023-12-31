#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene(){ delete sprite_; };

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//画像
	textureHandle_=TextureManager::Load("mrtn.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	//音
	soundDataHandle_ = audio_->LoadWave("BGM/BGM.wav");
	audio_->PlayWave(soundDataHandle_, true);
}
	
	

void TitleScene::Update() {
	
	isSceneEnd_ = false;

	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}

}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	//画像
	sprite_->Draw();
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
