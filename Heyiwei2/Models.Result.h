#pragma once
#include "Models.Result.g.h"

namespace winrt::Heyiwei2::Models::implementation
{
    struct Result : ResultT<Result>
    {
        Result() = default;
        Result(bool success, winrt::hstring const& message)
            : success(success), message(message) {}

        bool Success();
        void Success(bool value);
        hstring Message();
        void Message(hstring const& value);
    private:
        bool success;
		hstring message;
    };
}

namespace winrt::Heyiwei2::Models::factory_implementation
{
    struct Result : ResultT<Result, implementation::Result>
    {};
}
