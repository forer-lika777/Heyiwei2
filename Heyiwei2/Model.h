#include "pch.h"
#include <iostream>

namespace Model{
	struct Result {
		bool success;
		std::string message;
	};

	struct WaterRecord {
		int year;
		int month;
		double usage;
		double cost;
	};

	struct Student {
		std::string name;
		std::string studentId;
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
		std::string toString() {
			std::string regionStr = (region == Region::East) ? "东" : "西";
			return regionStr + "-" + std::to_string(buildingNumber) + "-" + std::to_string(floor) + "-" + std::to_string(roomNumber);
		}
	};

	struct Dorm {
		std::vector<Student> students;
		std::vector<WaterRecord> records;
		DormInfo info;
	};
}