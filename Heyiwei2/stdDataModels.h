#pragma once
#include <string>
#include <vector>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace Heyiwei2::Data {
    struct WaterRecordData {
        int32_t year;
        int32_t month;
        double usage;
        double cost;
        bool hasPaid;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(year, month, usage, cost, hasPaid);
        }
    };

    struct StudentData {
        std::string name;
        std::string studentId;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(name, studentId);
        }
    };

    struct DormInfoData {
        int32_t region, building, floor, room;
        int32_t startYear, startMonth;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(region, building, floor, room, startYear, startMonth);
        }
    };

    struct DormData {
        DormInfoData info;
        std::vector<StudentData> students;
        std::vector<WaterRecordData> records;

        template<class Archive>
        void serialize(Archive& ar) {
            ar(info, students, records);
        }
    };
}