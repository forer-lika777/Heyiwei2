#pragma once
#include "Models.Dorm.g.h"
#include <winrt/Windows.UI.Xaml.Data.h>

using namespace winrt::Windows::Foundation::Collections;
//using namespace winrt::Heyiwei2::Models;

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
        DormInfo Info();
        void Info(DormInfo const& value);
        hstring DormId();

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler) {
            return propertyChanged.add(handler);
        }

        void PropertyChanged(winrt::event_token const& token) noexcept {
            propertyChanged.remove(token);
        }

    private:
        IObservableVector<IInspectable> students{ winrt::single_threaded_observable_vector<IInspectable>() };
        IObservableVector<IInspectable> records{ winrt::single_threaded_observable_vector<IInspectable>() };
		hstring dormId;
        int32_t index = 0;
        winrt::Heyiwei2::Models::DormInfo info{ nullptr };

        event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged{};
    };
}

namespace winrt::Heyiwei2::Models::factory_implementation
{
    struct Dorm : DormT<Dorm, implementation::Dorm>
    {};
}