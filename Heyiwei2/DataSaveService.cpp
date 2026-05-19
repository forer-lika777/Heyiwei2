#include "pch.h"
#include "DataSaveService.h"
#include "StdModelsConverter.h"
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

void DataSaveService::SaveToFile(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> dorms) {
    // 转换成 std::vector
    auto stdDorms = StdModelsConverter::ToStdDorms(dorms);

    // 序列化到 JSON 文件
    std::ofstream file("dorms_data.json");
    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("dorms", stdDorms));
}

winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> DataSaveService::LoadFromFile()
{
    std::vector<Heyiwei2::StdModels::Dorm> stdDorms;

    std::ifstream file("dorms_data.json");
    if (file.is_open())
    {
        try
        {
            cereal::JSONInputArchive archive(file);
            archive(cereal::make_nvp("dorms", stdDorms));
        }
        catch (...)
        {
            // 文件损坏或不存在，返回空列表
            stdDorms.clear();
        }
    }

    // 转换回 WinRT 类型
    return StdModelsConverter::ToWinrtDorms(stdDorms);
}
