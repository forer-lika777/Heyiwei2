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
    winrt::Heyiwei2::Models::DormInfo Dorm::Info()
    {
        return info;
    }
    void Dorm::Info(winrt::Heyiwei2::Models::DormInfo const& value)
    {
        if (info != value) {
            info = value;
            RaisePropertyChanged(L"Info");
        }
		hstring id = L"Dorm-" + winrt::to_hstring(value.Region()) + 
            L"-" + winrt::to_hstring(value.BuildingNumber()) + 
            L"-" + winrt::to_hstring(value.Floor()) + 
            L"-" + winrt::to_hstring(value.RoomNumber());
        if (dormId != id) {
            dormId = id;
            RaisePropertyChanged(L"DormId");
        }
    }
    hstring Dorm::DormId()
    {
        return dormId;
    }
}
