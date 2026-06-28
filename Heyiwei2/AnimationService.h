#pragma once
#include "AnimationInfo.h"

class AnimationService {
public:
	static void GeneralAnimationControl(winrt::Microsoft::UI::Xaml::UIElement const& element, AnimationInfo const& animationInfo);
};
