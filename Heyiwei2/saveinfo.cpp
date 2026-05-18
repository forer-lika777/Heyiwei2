#include "pch.h"
#include "saveinfo.h"
#include <fstream>
#include <filesystem>
#include <winrt/Windows.Storage.h>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

#include "Models.Result.h"
#include "Models.Dorm.h"
#include "Models.WaterRecord.h"
#include "Models.Student.h"

namespace fs = std::filesystem;

using namespace winrt;
using namespace Windows::Storage;

namespace cereal {
	// WaterRecord 序列化
	template<class Archive>
	void serialize(Archive& archive, WaterRecord& w) {
		archive(w.year, w.month, w.usage, w.cost, w.hasPaid);
	}

	// Student 序列化
	template<class Archive>
	void serialize(Archive& archive, Student& s) {
		std::string name, id;
		if (Archive::is_loading::value) {
			archive(name, id);
			s.name = winrt::to_hstring(name);
			s.studentId = winrt::to_hstring(id);
		} else {
			name = winrt::to_string(s.name);
			id = winrt::to_string(s.studentId);
			archive(name, id);
		}
	}

	// Region 枚举序列化（转成 int）
	template<class Archive>
	void serialize(Archive& archive, int32_t r) {
		int regionInt = static_cast<int>(r);
		archive(regionInt);
		if (Archive::is_loading::value) {
			r = static_cast<Models::Region>(regionInt);
		}
	}

	// DormInfo 序列化
	template<class Archive>
	void serialize(Archive& archive, DormInfo& info) {
		archive(info.region, info.buildingNumber, info.floor, info.roomNumber);
	}

	// Dorm 序列化
	template<class Archive>
	void serialize(Archive& archive, Dorm& dorm) {
		archive(dorm.students, dorm.records, dorm.startDateYear, dorm.startDateMonth, dorm.index, dorm.info);
	}
}

// 保存数据到本地文件夹
void SaveData(const winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& dorms, const std::string& filename) {

    auto localFolder = ApplicationData::Current().LocalFolder();
    auto path = localFolder.Path();
    fs::path filePath = fs::path(std::wstring(path.c_str())) / fs::path(filename);
    std::ofstream os(filePath);
    cereal::JSONOutputArchive archive(os);
    archive(dorms);
}

// 加载数据从本地文件夹
winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> LoadData(const std::string& filename) {
    std::vector<Dorm> dormsStd;
    auto localFolder = ApplicationData::Current().LocalFolder();
    auto path = localFolder.Path();
    fs::path filePath = fs::path(std::wstring(path.c_str())) / fs::path(filename);
    if (fs::exists(filePath)) {
        std::ifstream is(filePath);
        cereal::JSONInputArchive archive(is);
        archive(dormsStd);
    }
	auto dorms = winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>{ };
	for (const auto& dorm : dormsStd) {
		dorms.Append(dorm);
	}
    return dorms;
}