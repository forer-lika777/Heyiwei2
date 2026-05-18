#pragma once
#include "Models.Student.g.h"

namespace winrt::Heyiwei2::Models::implementation
{
    struct Student : StudentT<Student>
    {
    public:
        Student() = default;

        hstring Name();
        void Name(hstring const& value);
        hstring StudentId();
        void StudentId(hstring const& value);

    private:
         hstring name;
		 hstring studentId;
    };
}

namespace winrt::Heyiwei2::Models::factory_implementation
{
    struct Student : StudentT<Student, implementation::Student>
    {};
}