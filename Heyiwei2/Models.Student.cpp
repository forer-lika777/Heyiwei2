#include "pch.h"
#include "Models.Student.h"
#include "Models.Student.g.cpp"

namespace winrt::Heyiwei2::Models::implementation
{
    hstring Student::Name()
    {
        return name;
    }
    void Student::Name(hstring const& value)
    {
		name = value;
    }
    hstring Student::StudentId()
    {
        return studentId;
    }
    void Student::StudentId(hstring const& value)
    {
		studentId = value;
    }
}
