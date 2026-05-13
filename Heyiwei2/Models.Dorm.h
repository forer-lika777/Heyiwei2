#pragma once
#include "Models.Dorm.g.h"

namespace winrt::Heyiwei2::Models::implementation
{
    struct Dorm : DormT<Dorm>
    {
    public:
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
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> students{ winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>() };
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> records{ winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>() };
        int32_t startDateYear = 0;
        int32_t startDateMonth = 0;
        int32_t index = 0;
		winrt::Heyiwei2::Models::DormInfo info{ nullptr };
    };
}
