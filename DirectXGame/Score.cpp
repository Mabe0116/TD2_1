#include "Score.h"

void Score::Initialize()
{ timer_=Timer; }

void Score::Update()
{ timer_--;

if (timer_ <= 0)
{
	score_++;
	timer_ = Timer;
}



//ImGui::Begin("Timer");
//ImGui::DragInt("timer", &timer_, 0.01f);
//ImGui::DragInt("m", &score_, 0.01f);
//ImGui::End();

}
