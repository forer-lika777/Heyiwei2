#include "pch.h"
#include "DataSaveService.h"
#include "StdModelsConverter.h"
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <winrt/Windows.Storage.h> // 确保引入了该头文件
#include <filesystem>              // 用于方便地拼接路径

void DataSaveService::SaveToFile(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> dorms) {
    auto stdDorms = StdModelsConverter::ToStdDorms(dorms);

    // 【核心修复】：获取 WinUI 3 应用法定的本地存储绝对路径
    auto localFolderPath = winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path();
    std::filesystem::path fullPath(localFolderPath.c_str());
    fullPath /= "dorms_data.json"; // 拼接成绝对路径

    // 使用绝对路径进行标准流操作 (注意 Windows 下路径转换成 wstring 或 string)
    std::ofstream file(fullPath.wstring());
    if (file.is_open()) {
        cereal::JSONOutputArchive archive(file);
        archive(cereal::make_nvp("dorms", stdDorms));
    }
}

winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> DataSaveService::LoadFromFile()
{
    std::vector<Heyiwei2::StdModels::Dorm> stdDorms;

    // 【核心修复】：读取时也必须从同一个绝对路径读取
    auto localFolderPath = winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path();
    std::filesystem::path fullPath(localFolderPath.c_str());
    fullPath /= "dorms_data.json";

    std::ifstream file(fullPath.wstring());
    if (file.is_open())
    {
        try
        {
            cereal::JSONInputArchive archive(file);
            archive(cereal::make_nvp("dorms", stdDorms));
        }
        catch (...)
        {
            stdDorms.clear();
        }
    }

    return StdModelsConverter::ToWinrtDorms(stdDorms);
}
