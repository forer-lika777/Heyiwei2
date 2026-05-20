#include "pch.h"
#include "Models.Result.h"
#include "Models.Result.g.cpp"

namespace winrt::Heyiwei2::Models::implementation {
	bool Result::Success() const {
		return success;
	}

	void Result::Success(bool value) {
		success = value;
	}

	hstring Result::Message() {
		return message;
	}

	void Result::Message(hstring const& value) {
		message = value;
	}
}
