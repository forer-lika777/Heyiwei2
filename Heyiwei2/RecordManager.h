#pragma once

class RecordManager
{
private:
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> waterRecords;
public:
    RecordManager() = default;

    Result addWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record);
    Result removeWaterRecord(int year, int month);
    Result updateWaterRecord(int year, int month, double usage);

    int32_t querySpecificWaterRecord(int year, int month);

    void setRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> records);
};