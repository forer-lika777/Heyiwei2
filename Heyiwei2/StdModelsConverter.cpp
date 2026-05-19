#include "pch.h"
#include "StdModelsConverter.h"

std::vector<Heyiwei2::StdModels::Dorm> StdModelsConverter::ToStdDorms(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> winrtDorms)
{
	std::vector<Heyiwei2::StdModels::Dorm> stdDorms;
	for (auto const& winrtDormObject : winrtDorms) {
		auto const& winrtDorm = winrtDormObject.as<winrt::Heyiwei2::Models::Dorm>();
		auto const& winrtDormInfo = winrtDorm.Info();
		
		Heyiwei2::StdModels::Dorm stdDorm{};

		// convert dorm info
		auto& stdDormInfo = stdDorm.info;
		stdDormInfo.startYear = winrtDormInfo.StartDateYear();
		stdDormInfo.startMonth = winrtDormInfo.StartDateMonth();
		stdDormInfo.region = winrtDormInfo.Region();
		stdDormInfo.building = winrtDormInfo.BuildingNumber();
		stdDormInfo.floor = winrtDormInfo.Floor();
		stdDormInfo.room = winrtDormInfo.RoomNumber();

		// convert students
		auto& stdStudents = stdDorm.students;
		for (auto const& winrtStudentObject : winrtDorm.Students()) {
			auto winrtStudent = winrtStudentObject.as<winrt::Heyiwei2::Models::Student>();
			
			Heyiwei2::StdModels::Student stdStudent{};
			stdStudent.name = winrt::to_string(winrtStudent.Name());
			stdStudent.studentId = winrt::to_string(winrtStudent.StudentId());

			stdStudents.push_back(stdStudent);
		}

		//convert records
		auto& stdRecords = stdDorm.records;
		for (auto const& winrtRecordObject : winrtDorm.Records()) {
			auto winrtRecord = winrtRecordObject.as<winrt::Heyiwei2::Models::WaterRecord>();

			Heyiwei2::StdModels::WaterRecord stdRecord{};
			stdRecord.year = winrtRecord.Year();
			stdRecord.month = winrtRecord.Month();
			stdRecord.usage = winrtRecord.Usage();
			stdRecord.cost = winrtRecord.Cost();
			stdRecord.hasPaid = winrtRecord.HasPaid();

			stdRecords.push_back(stdRecord);
		}

        stdDorms.push_back(stdDorm);
	}

	return stdDorms;
}

winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> StdModelsConverter::ToWinrtDorms(std::vector<Heyiwei2::StdModels::Dorm> stdDorms)
{
    auto winrtDorms = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();

    for (auto const& stdDorm : stdDorms)
    {
        auto winrtDorm = winrt::make<winrt::Heyiwei2::Models::implementation::Dorm>();

        // convert dorm info
        auto winrtDormInfo = winrt::make<winrt::Heyiwei2::Models::implementation::DormInfo>();
        winrtDormInfo.StartDateYear(stdDorm.info.startYear);
        winrtDormInfo.StartDateMonth(stdDorm.info.startMonth);
        winrtDormInfo.Region(stdDorm.info.region);
        winrtDormInfo.BuildingNumber(stdDorm.info.building);
        winrtDormInfo.Floor(stdDorm.info.floor);
        winrtDormInfo.RoomNumber(stdDorm.info.room);

        winrtDorm.Info(winrtDormInfo);

        // convert students
        auto winrtStudents = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
        for (auto const& stdStudent : stdDorm.students)
        {
            auto winrtStudent = winrt::make<winrt::Heyiwei2::Models::implementation::Student>();
            winrtStudent.Name(winrt::to_hstring(stdStudent.name));
            winrtStudent.StudentId(winrt::to_hstring(stdStudent.studentId));

            winrtStudents.Append(winrtStudent);
        }
        winrtDorm.Students(winrtStudents);

        // convert records
        auto winrtRecords = winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>();
        for (auto const& stdRecord : stdDorm.records)
        {
            auto winrtRecord = winrt::make<winrt::Heyiwei2::Models::implementation::WaterRecord>();
            winrtRecord.Year(stdRecord.year);
            winrtRecord.Month(stdRecord.month);
            winrtRecord.Usage(stdRecord.usage);
            winrtRecord.Cost(stdRecord.cost);
            winrtRecord.HasPaid(stdRecord.hasPaid);

            winrtRecords.Append(winrtRecord);
        }
        winrtDorm.Records(winrtRecords);

        winrtDorms.Append(winrtDorm);
    }

    return winrtDorms;
}