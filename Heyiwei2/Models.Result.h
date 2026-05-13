#pragma once
#include "Models.Result.g.h"

namespace winrt::Heyiwei2::Models::implementation
{
    struct Result : ResultT<Result>
    {
        Result() = default;

        bool Success();
        void Success(bool value);
        hstring Message();
        void Message(hstring const& value);
    private:
        bool success;
		hstring message;
    };
}
