#pragma once
#include <iostream>

class AnimationInfo {
public:
	float motionDistanceX = 60.0f;
	float motionDistanceY = 0.0f;
	winrt::Windows::Foundation::TimeSpan duration = std::chrono::milliseconds(1200);
};
