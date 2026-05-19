#pragma once
#include "StdModels.h"
#include "Models.Dorm.h"
#include "Models.DormInfo.h"
#include "Models.Student.h"
#include "Models.WaterRecord.h"

class StdModelsConverter {
public:
	static std::vector<Heyiwei2::StdModels::Dorm> ToStdDorms(
		winrt::Windows::Foundation::Collections::IObservableVector<
		winrt::Windows::Foundation::IInspectable> winrtDorms);

	static winrt::Windows::Foundation::Collections::IObservableVector<
		winrt::Windows::Foundation::IInspectable> ToWinrtDorms(
			std::vector<Heyiwei2::StdModels::Dorm> stdDorms);
private:

};

