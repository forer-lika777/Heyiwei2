#pragma once
#include "Models.Dorm.g.h"

namespace winrt::Heyiwei2::Models::implementation
{
    struct Dorm : DormT<Dorm>
    {
        Dorm() = default;

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Students();
        void Students(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> const& value);
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Records();
        void Records(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> const& value);
        int32_t StartDateYear();
        void StartDateYear(int32_t value);
        int32_t StartDateMonth();
        void StartDateMonth(int32_t value);
        int32_t Index();
        void Index(int32_t value);
        winrt::Heyiwei2::Models::DormInfo Info();
        void Info(winrt::Heyiwei2::Models::DormInfo const& value);
    };
}
