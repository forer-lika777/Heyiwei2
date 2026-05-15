#include "pch.h"
#include "Models.Dorm.h"
#include "Models.Dorm.g.cpp"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Foundation;

namespace winrt::Heyiwei2::Models::implementation
{
    IObservableVector<IInspectable> Dorm::Students()
    {
		return students;
    }
    void Dorm::Students(IObservableVector<IInspectable> const& value)
    {
        students = value;
    }
    IObservableVector<IInspectable> Dorm::Records()
    {
        return records;
    }
    void Dorm::Records(IObservableVector<IInspectable> const& value)
    {
		records = value;
    }
    int32_t Dorm::StartDateYear()
    {
		return startDateYear;
    }
    void Dorm::StartDateYear(int32_t value)
    {
		startDateYear = value;
    }
    int32_t Dorm::StartDateMonth()
    {
		return startDateMonth;
    }
    void Dorm::StartDateMonth(int32_t value)
    {
		startDateMonth = value;
    }
    int32_t Dorm::Index()
    {
        return index;
    }
    void Dorm::Index(int32_t value)
    {
        index = value;
    }
    winrt::Heyiwei2::Models::DormInfo Dorm::Info()
    {
        return info;
    }
    void Dorm::Info(winrt::Heyiwei2::Models::DormInfo const& value)
    {
		dormId = L"Dorm-" + winrt::to_hstring(value.Region()) + 
            L"-" + winrt::to_hstring(value.BuildingNumber()) + 
            L"-" + winrt::to_hstring(value.Floor()) + 
            L"-" + winrt::to_hstring(value.RoomNumber());
		info = value;
    }
    hstring Dorm::DormId()
    {
        return dormId;
    }
}
