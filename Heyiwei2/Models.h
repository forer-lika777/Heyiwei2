#pragma once
#include <vector>
#include <string>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

namespace Models {
	struct Result {
		bool success;
		winrt::hstring message;
	};

	struct WaterRecord {
		int year;
		int month;
		double usage;
		double cost;
		bool hasPaid;
	};

	struct Student {
		winrt::hstring name;
		winrt::hstring studentId;
	};

	enum Region {
		East,
		West,
	};

	struct DormInfo {
		Region region;
		int buildingNumber; // 楼号
		int floor; // 层数
		int roomNumber; // 门牌号
		winrt::hstring toString() {
			winrt::hstring regionStr = (region == Region::East) ? L"东" : L"西";
			return regionStr + L"区 " + winrt::to_hstring(buildingNumber) + L" 栋 " + winrt::to_hstring(floor) + L"-" + winrt::to_hstring(roomNumber);
		}
	};

	struct Dorm {
		std::vector<Student> students;
		std::vector<WaterRecord> records;
		DormInfo info;
	};

	struct DormPaneItem : winrt::implements<DormPaneItem, winrt::Windows::Foundation::IInspectable>
	{
		winrt::hstring DormInfo() const { return dormInfo; }
		void DormInfo(const winrt::hstring& value) { dormInfo = value; }

		int32_t Index() const { return index; }
		void Index(int32_t value) { index = value; }

	private:
		winrt::hstring dormInfo;
		int32_t index = 0;
	};
}

namespace cereal {
	// Result 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::Result& r) {
		archive(r.success, r.message);
	}

	// WaterRecord 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::WaterRecord& w) {
		archive(w.year, w.month, w.usage, w.cost);
	}

	// Student 序列化
	template<class Archive>
	void serialize(Archive& archive, Models::Student& s) {
		archive(s.name, s.studentId);
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
		archive(dorm.students, dorm.records, dorm.info);
	}
}