#include "pch.h"
#include "Models.Dorm.h"
#include "Models.Dorm.g.cpp"
#include "Utils.h"

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
            propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Info"));
        }
        hstring id = Utils::generateDormId(info);
        if (dormId != id) {
            propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"DormId"));
            dormId = id;
        }
    }
    hstring Dorm::DormId()
    {
        return dormId;
    }
}
