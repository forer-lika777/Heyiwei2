#include "pch.h"
#include "Converters.StatusToStringConverter.h"
#include "Converters.StatusToStringConverter.g.cpp"

namespace winrt::Heyiwei2::Converters::implementation {
	winrt::Windows::Foundation::IInspectable StatusToStringConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language) {
		auto status = winrt::unbox_value<bool>(value);
		return winrt::box_value(status ? L"正常" : L"欠费");
	}
	winrt::Windows::Foundation::IInspectable StatusToStringConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language) {
		throw hresult_not_implemented(); 
	}
}
