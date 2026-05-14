#pragma once
#include "Models.Dorm.g.h"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Heyiwei2::Models;

namespace winrt::Heyiwei2::Models::implementation
{
    struct Dorm : DormT<Dorm>
    {
    public:
        Dorm() = default;

        IObservableVector<IInspectable> Students();
        void Students(IObservableVector<IInspectable> const& value);
        IObservableVector<IInspectable> Records();
        void Records(IObservableVector<IInspectable> const& value);
        int32_t StartDateYear();
        void StartDateYear(int32_t value);
        int32_t StartDateMonth();
        void StartDateMonth(int32_t value);
        int32_t Index();
        void Index(int32_t value);
        DormInfo Info();
        void Info(DormInfo const& value);
        hstring DormID();
    private:
        IObservableVector<IInspectable> students{ winrt::single_threaded_observable_vector<IInspectable>() };
        IObservableVector<IInspectable> records{ winrt::single_threaded_observable_vector<IInspectable>() };
		hstring dormId;
        int32_t startDateYear = 0;
        int32_t startDateMonth = 0;
        int32_t index = 0;
        winrt::Heyiwei2::Models::DormInfo info{ nullptr };
    };
}
