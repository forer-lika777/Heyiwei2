#pragma once
#include <windows.h>
#include <unknwn.h>
#include <restrictederrorinfo.h>
#include <hstring.h>

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#undef GetCurrentTime

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
//#include <winrt/Microsoft.UI.Xaml.Markup.h>
//#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
//#include <winrt/Microsoft.UI.Xaml.Shapes.h>
//#include <winrt/Microsoft.UI.Dispatching.h>
#include <wil/cppwinrt_helpers.h>

#include "Models.Dorm.h"
#include "Models.DormInfo.h"
#include "Models.Student.h"
#include "Models.WaterRecord.h"

// 使用 Converter 时编译经常出现下列类似错误：
// “winrt::Heyiwei2::implementation::TypeInfos”: 必须初始化 const 对象
// “StatusToStringConverter”: 未声明的标识符
// "StatusToStringConverter": 不是 "winrt::Heyiwei2::Converters::implementation" 的成员
// 这是 Visual Studio 中 winui c++ 的预编译问题。
// 在 pch.h 头文件添加这些 Converter 的引用可避免此错误。
#include "Converters.HasPaidToStringConverter.h"
#include "Converters.StatusToStringConverter.h"
#include "Converters.StatusToColorConverter.h"