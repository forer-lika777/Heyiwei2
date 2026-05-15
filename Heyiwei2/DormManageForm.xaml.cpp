#include "pch.h"
#include "DormManageForm.xaml.h"
#if __has_include("DormManageForm.g.cpp")
#include "DormManageForm.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    DormManageForm::DormManageForm() {

    }

    winrt::Heyiwei2::Models::Dorm DormManageForm::Dorm() {
        return dorm;
    }

    void DormManageForm::Dorm(winrt::Heyiwei2::Models::Dorm const& dorm) {
        this->dorm = dorm;
    }
}
