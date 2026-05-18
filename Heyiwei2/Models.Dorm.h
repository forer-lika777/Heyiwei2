#pragma once
#include "Models.Dorm.g.h"
#include <winrt/Windows.UI.Xaml.Data.h>

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Heyiwei2::Models;

namespace winrt::Heyiwei2::Models::implementation
{
    struct Dorm : DormT<Dorm, winrt::Windows::UI::Xaml::Data::INotifyPropertyChanged>
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

        winrt::event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged;
        winrt::event_token PropertyChanged(
            winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return propertyChanged.add(handler);
        }
        void PropertyChanged(winrt::event_token const& token)
        {
            propertyChanged.remove(token);
        }

        // 辅助方法：触发属性变更
        void RaisePropertyChanged(hstring const& propertyName)
        {
            propertyChanged(*this,
                winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }

    private:
        IObservableVector<IInspectable> students{ winrt::single_threaded_observable_vector<IInspectable>() };
        IObservableVector<IInspectable> records{ winrt::single_threaded_observable_vector<IInspectable>() };
		hstring dormId;
        int32_t index = 0;
        winrt::Heyiwei2::Models::DormInfo info{ nullptr };
    };
}
