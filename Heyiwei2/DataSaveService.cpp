#include "pch.h"
#include "DataSaveService.h"
#include "StdModelsConverter.h"
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include <shlobj.h>       // 包含此头文件，用于 SHGetKnownFolderPath 
#include <filesystem>
#pragma comment(lib, "shell32.lib")

// 辅助函数：安全地获取非打包应用的本地数据存储绝对路径
// 返回类似于：C:\Users\用户名\AppData\Local\Heyiwei2\dorms_data.json
static std::filesystem::path GetUnpackagedDataPath() {
    wchar_t* localAppDataFolder = nullptr;
    std::filesystem::path fullPath;

    // 获取当前用户的 AppData\Local 路径
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppDataFolder))) {
        fullPath = localAppDataFolder;
        CoTaskMemFree(localAppDataFolder); // 必须手动释放系统分配的内存

        // 为你的应用创建一个独立的子文件夹（避免直接污染 Local 根目录）
        fullPath /= L"Heyiwei2";

        // 非打包应用不会自动创建文件夹，所以写入前需要手动确保文件夹存在
        std::filesystem::create_directories(fullPath);

        // 拼接文件名
        fullPath /= L"dorms_data.json";
    }
    return fullPath;
}

// ==================== 1. 保存数据 ====================
void DataSaveService::SaveToFile(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> dorms) {
    auto stdDorms = StdModelsConverter::ToStdDorms(dorms);

    // 获取非打包应用的绝对路径
    std::filesystem::path fullPath = GetUnpackagedDataPath();
    if (fullPath.empty()) {
        return; // 获取路径失败（极少发生）
    }

    // 使用绝对路径进行标准流操作 (std::ofstream 完美支持 std::filesystem::path)
    std::ofstream file(fullPath);
    if (file.is_open()) {
        cereal::JSONOutputArchive archive(file);
        archive(cereal::make_nvp("dorms", stdDorms));
    }
}

// ==================== 2. 读取数据 ====================
winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> DataSaveService::LoadFromFile() {
    std::vector<Heyiwei2::StdModels::Dorm> stdDorms;

    // 读取时也使用相同的非打包路径
    std::filesystem::path fullPath = GetUnpackagedDataPath();

    if (!fullPath.empty() && std::filesystem::exists(fullPath)) // 确保路径有效且文件存在
    {
        std::ifstream file(fullPath);
        if (file.is_open()) {
            try {
                cereal::JSONInputArchive archive(file);
                archive(cereal::make_nvp("dorms", stdDorms));
            }
            catch (...) {
                stdDorms.clear();
            }
        }
    }

    return StdModelsConverter::ToWinrtDorms(stdDorms);
}