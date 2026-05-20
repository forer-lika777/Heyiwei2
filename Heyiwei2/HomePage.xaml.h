#pragma once

#include "HomePage.g.h"

namespace winrt::Heyiwei2::implementation {
	struct HomePage : HomePageT<HomePage> {
		HomePage() {}
	};
}

namespace winrt::Heyiwei2::factory_implementation {
	struct HomePage : HomePageT<HomePage, implementation::HomePage> {};
}
