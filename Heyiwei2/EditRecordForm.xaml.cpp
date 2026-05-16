#include "pch.h"
#include "EditRecordForm.xaml.h"
#if __has_include("EditRecordForm.g.cpp")
#include "EditRecordForm.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    winrt::Windows::Foundation::Collections::IObservableVector<int32_t> EditRecordForm::Years()
    {
        return years;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<int32_t> EditRecordForm::Months()
    {
        return months;
    }
}
