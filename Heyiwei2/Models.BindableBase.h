#pragma once
#include "Models.BindableBase.g.h"
#include <winrt/Microsoft.UI.Xaml.Data.h>

namespace winrt::Heyiwei2::Models::implementation {
    struct BindableBase : BindableBaseT<BindableBase> {
    public:
        BindableBase() = default;

        winrt::event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler) {
            return propertyChanged.add(handler);
        }

        void PropertyChanged(winrt::event_token const& token) noexcept {
            propertyChanged.remove(token);
        }

    protected:
        template<class T>
        bool SetProperty(T& field, T const& value, winrt::hstring const& name) {
            if (field != value) {
                field = value;
                propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(name));
                return true;
            }
            return false;
        }

        void RaisePropertyChanged(winrt::hstring const& name) {
            propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(name));
        }

    private:
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged;
    };
}