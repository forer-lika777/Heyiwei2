#include "pch.h"
#include "Converters.HasPaidToStringConverter.h"
#include "Converters.HasPaidToStringConverter.g.cpp"

namespace winrt::Heyiwei2::Converters::implementation {
	winrt::Windows::Foundation::IInspectable HasPaidToStringConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language) {
		auto hasPaid = winrt::unbox_value<bool>(value);
		return winrt::box_value(hasPaid ? L"已缴费" : L"未缴费");
	}

	winrt::Windows::Foundation::IInspectable HasPaidToStringConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language) {
		throw hresult_not_implemented();
	}
}
