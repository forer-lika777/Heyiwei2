#pragma once
#include "Converters.HasPaidToStringConverter.g.h"

namespace winrt::Heyiwei2::Converters::implementation
{
    struct HasPaidToStringConverter : HasPaidToStringConverterT<HasPaidToStringConverter>
    {
        HasPaidToStringConverter() = default;

        winrt::Windows::Foundation::IInspectable Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
        winrt::Windows::Foundation::IInspectable ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
    };
}
namespace winrt::Heyiwei2::Converters::factory_implementation
{
    struct HasPaidToStringConverter : HasPaidToStringConverterT<HasPaidToStringConverter, implementation::HasPaidToStringConverter>
    {
    };
}
