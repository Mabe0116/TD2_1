#include "Result.h"
#include "Tree.h"

Result::Result() {}

Result::~Result(){

};

void Result::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// スコア
	TextureHandle_[0] = TextureManager::Load("UI/Resultscore/0'.png");
	TextureHandle_[1] = TextureManager::Load("UI/Resultscore/1'.png");
	TextureHandle_[2] = TextureManager::Load("UI/Resultscore/2'.png");
	TextureHandle_[3] = TextureManager::Load("UI/Resultscore/3'.png");
	TextureHandle_[4] = TextureManager::Load("UI/Resultscore/4'.png");
	TextureHandle_[5] = TextureManager::Load("UI/Resultscore/5'.png");
	TextureHandle_[6] = TextureManager::Load("UI/Resultscore/6'.png");
	TextureHandle_[7] = TextureManager::Load("UI/Resultscore/7'.png");
	TextureHandle_[8] = TextureManager::Load("UI/Resultscore/8'.png");
	TextureHandle_[9] = TextureManager::Load("UI/Resultscore/9'.png");
	// メートル
	TextureHandle_[10] = TextureManager::Load("UI/Resultscore/meter'.png");

	// スコアの配置
	sprite0 = Sprite::Create(TextureHandle_[0], {265.0f, 290.0f});
	sprite1 = Sprite::Create(TextureHandle_[0], {415.0f, 290.0f});
	sprite2 = Sprite::Create(TextureHandle_[0], {565.0f, 290.0f});
	sprite3 = Sprite::Create(TextureHandle_[0], {715.0f, 290.0f});
	sprite4 = Sprite::Create(TextureHandle_[10], {865.0f, 290.0f});
}

void Result::Update() {}

void Result::Draw() {
	int32_t Meter = Tree::GetMeter();

	// 1000の位
	eachNumber[0] = Meter / 1000;
	Meter = Meter % 1000;

	// 100の位
	eachNumber[1] = Meter / 100;
	Meter = Meter % 100;

	// 10の位
	eachNumber[2] = Meter / 10;
	Meter = Meter % 10;

	// 1の位
	eachNumber[3] = Meter;

	// 1000の位
	sprite0->SetTextureHandle(TextureHandle_[eachNumber[0]]);
	// 100の位
	sprite1->SetTextureHandle(TextureHandle_[eachNumber[1]]);
	// 10の位
	sprite2->SetTextureHandle(TextureHandle_[eachNumber[2]]);
	// 1の位
	sprite3->SetTextureHandle(TextureHandle_[eachNumber[3]]);

	sprite0->Draw();
	sprite1->Draw();
	sprite2->Draw();
	sprite3->Draw();
	sprite4->Draw();
}