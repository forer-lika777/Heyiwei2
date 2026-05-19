#pragma once
#include <string>
#include <vector>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace Heyiwei2::StdModels {
    struct WaterRecord {
        int32_t year = 0;
        int32_t month = 0;
        double usage = 0.0;
        double cost = 0.0;
        bool hasPaid = false;

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(
                CEREAL_NVP(year),
                CEREAL_NVP(month),
                CEREAL_NVP(usage),
                CEREAL_NVP(cost),
                CEREAL_NVP(hasPaid)
            );
        }
    };

    struct Student {
        std::string name;
        std::string studentId;

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(
                CEREAL_NVP(name),
                CEREAL_NVP(studentId)
            );
        }
    };

    struct DormInfo {
        int32_t startYear = 0;
        int32_t startMonth = 0;
        int32_t region = 0;
        int32_t building = 0;
        int32_t floor = 0;
        int32_t room = 0;

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(
                CEREAL_NVP(startYear),
                CEREAL_NVP(startMonth),
                CEREAL_NVP(region),
                CEREAL_NVP(building),
                CEREAL_NVP(floor),
                CEREAL_NVP(room)
            );
        }
    };

    struct Dorm {
        DormInfo info;
        std::vector<Student> students;
        std::vector<WaterRecord> records;

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(
                CEREAL_NVP(info),
                CEREAL_NVP(students),
                CEREAL_NVP(records)
            );
        }
    };


}