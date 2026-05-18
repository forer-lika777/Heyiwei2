#pragma once
#include <winrt/base.h>
#include <cereal/cereal.hpp>
#include <string>

namespace cereal {
    // 支持 winrt::hstring 的序列化
    template <class Archive>
    void save(Archive& ar, const winrt::hstring& str) {
        ar(winrt::to_string(str));
    }

    template <class Archive>
    void load(Archive& ar, winrt::hstring& str) {
        std::string s;
        ar(s);
        str = winrt::to_hstring(s);
    }
}