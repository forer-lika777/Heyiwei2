#pragma once

#include "DormManageForm.g.h"
#include "Models.Dorm.h"

namespace winrt::Heyiwei2::implementation
{
    struct DormManageForm : DormManageFormT<DormManageForm>
    {
    public:
        DormManageForm();
        winrt::Heyiwei2::Models::Dorm Dorm();
        void Dorm(winrt::Heyiwei2::Models::Dorm const& dorm);
    private:
        winrt::Heyiwei2::Models::Dorm dorm{ nullptr };
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct DormManageForm : DormManageFormT<DormManageForm, implementation::DormManageForm>
    {
    };
}
