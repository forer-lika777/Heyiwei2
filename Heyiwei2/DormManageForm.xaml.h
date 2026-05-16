#pragma once

#include "DormManageForm.g.h"
#include "Models.Dorm.h"
#include "DormListPage.xaml.h"
#include "IMainManager.h"
#include <functional>

namespace winrt::Heyiwei2::implementation
{
    struct DormManageForm : DormManageFormT<DormManageForm>
    {
    private:
        winrt::Heyiwei2::Models::Dorm dorm{ nullptr };
        std::function<void()> onCloseCallback;
        Interfaces::IMainManager* mainManager = nullptr;
        winrt::Windows::Foundation::IAsyncAction openEditDormDialogAsync();

        //void RaisePropertyChanged(winrt::hstring const& propertyName)
        //{
        //    propertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        //}

        //winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged;

    public:
        DormManageForm();
        winrt::Heyiwei2::Models::Dorm Dorm();
        void Dorm(winrt::Heyiwei2::Models::Dorm const& dorm);
        void CloseButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SetOnCloseCallback(std::function<void()> callback);
        void EditDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        //// INotifyPropertyChanged 实现
        //winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        //{
        //    return propertyChanged.add(handler);
        //}

        //void PropertyChanged(winrt::event_token const& token) noexcept
        //{
        //    propertyChanged.remove(token);
        //}
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct DormManageForm : DormManageFormT<DormManageForm, implementation::DormManageForm>
    {
    };
}
