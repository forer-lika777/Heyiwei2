#include "saveinfo.h"
#include <fstream>
#include <filesystem>
#include <winrt/Windows.Storage.h>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

namespace fs = std::filesystem;

using namespace winrt;
using namespace Windows::Storage;

namespace cereal {
	// Result 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::Result& r) {
		std::string msg;
		if (Archive::is_loading::value) {
			archive(r.success, msg);
			r.message = winrt::to_hstring(msg);
		} else {
			msg = winrt::to_string(r.message);
			archive(r.success, msg);
		}
	}

	// WaterRecord 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::WaterRecord& w) {
		archive(w.year, w.month, w.usage, w.cost, w.hasPaid);
	}

	// Student 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::Student& s) {
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
	void serialize(Archive& archive, Models::Region& r) {
		int regionInt = static_cast<int>(r);
		archive(regionInt);
		if (Archive::is_loading::value) {
			r = static_cast<Models::Region>(regionInt);
		}
	}

	// DormInfo 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::DormInfo& info) {
		archive(info.region, info.buildingNumber, info.floor, info.roomNumber);
	}

	// Dorm 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::Dorm& dorm) {
		archive(dorm.students, dorm.records, dorm.startDateYear, dorm.startDateMonth, dorm.index, dorm.info);
	}
}

// 保存数据到本地文件夹
void SaveData(const std::vector<Models::Dorm>& dorms, const std::string& filename) {
    auto localFolder = ApplicationData::Current().LocalFolder();
    auto path = localFolder.Path();
    fs::path filePath = fs::path(std::wstring(path.c_str())) / fs::path(filename);
    std::ofstream os(filePath);
    cereal::JSONOutputArchive archive(os);
    archive(dorms);
}

// 加载数据从本地文件夹
std::vector<Models::Dorm> LoadData(const std::string& filename) {
    std::vector<Models::Dorm> dorms;
    auto localFolder = ApplicationData::Current().LocalFolder();
    auto path = localFolder.Path();
    fs::path filePath = fs::path(std::wstring(path.c_str())) / fs::path(filename);
    if (fs::exists(filePath)) {
        std::ifstream is(filePath);
        cereal::JSONInputArchive archive(is);
        archive(dorms);
    }
    return dorms;
}