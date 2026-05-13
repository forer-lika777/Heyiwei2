#include "pch.h"
#include "Models.DormInfo.h"
#include "Models.DormInfo.g.cpp"

namespace winrt::Heyiwei2::Models::implementation
{
    int32_t DormInfo::Region() const
    {
		return region;
    }
    void DormInfo::Region(int32_t value)
    {
        region = value;
    }
    int32_t DormInfo::BuildingNumber() const
    {
		return buildingNumber;
    }
    void DormInfo::BuildingNumber(int32_t value)
    {
		buildingNumber = value;
    }
    int32_t DormInfo::Floor() const
    {
		return floor;
    }
    void DormInfo::Floor(int32_t value)
    {
		floor = value;
    }
    int32_t DormInfo::RoomNumber() const
    {
		return roomNumber;
    }
    void DormInfo::RoomNumber(int32_t value)
    {
		roomNumber = value;
    }
    hstring DormInfo::ToString()
    {
        winrt::hstring regionStr = (region == 0) ? L"东" : L"西";
        return regionStr + L"区 " + winrt::to_hstring(buildingNumber) + L" 栋 " + winrt::to_hstring(floor) + L"-" + winrt::to_hstring(roomNumber);
    }
}
