#include "pch.h"
#include "Converters.StatusToColorConverter.h"
#include "Converters.StatusToColorConverter.g.cpp"
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Windows.UI.h>

namespace winrt::Heyiwei2::Converters::implementation {
	winrt::Windows::Foundation::IInspectable StatusToColorConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language) {
		auto status = winrt::unbox_value<bool>(value);
		if (status) {
			auto brush = winrt::Microsoft::UI::Xaml::Media::SolidColorBrush();
			brush.Color(winrt::Windows::UI::Colors::Green());
			return winrt::box_value(brush);
		}
		else {
			auto brush = winrt::Microsoft::UI::Xaml::Media::SolidColorBrush();
			brush.Color(winrt::Windows::UI::Colors::Red());
			return winrt::box_value(brush);
		}
	}
	winrt::Windows::Foundation::IInspectable StatusToColorConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language) {
		throw hresult_not_implemented();
	}
}
