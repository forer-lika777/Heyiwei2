#pragma once

class DataSaveService {
public:
	static void SaveToFile(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> dorms);
	static winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> LoadFromFile();
};