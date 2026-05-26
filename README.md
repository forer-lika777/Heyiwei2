Heyiwei2
===

什么是Heyiwei2？
---

Heyiwei2是一个使用winui c++的学生水费管理系统，是Heyiwei的超级重构升级版。

为什么要开发Heyiwei2？
---

我们用炫酷的winui界面替代了那古老的黑色命令行窗口，旨在对标第一次答辩第一个上台的组那糟糕的UI设计。

我们写出来的将会是广工史无前例最牛逼的项目~~，将会怼的唐平哑口无言（不是）~~。

我们的项目百分百传统艺能（纯手敲），不照搬外部代码，旨在对标第一次答辩第一个上台的组那仅有不到30％代码是自己敲的窘况。

广东工业大学

课程设计报告

---

课程名称：C语言课程设计

设计题目：学生宿舍水费管理系统

学生姓名：[你的名字]

学　　号：[你的学号]

班　　级：[你的班级]

指导教师：[老师姓名]

完成日期：2026年6月

---

目录

1. 项目概述

2. 需求分析

3. 系统设计

4. 详细实现

5. 关键技术难点

6. 测试与运行

7. 总结与展望

---

一、项目概述

1.1 项目背景

学生宿舍水费管理是高校后勤工作的重要组成部分。传统的人工抄表、纸质记录方式效率低下，易出错，不便于数据统计与分析。本项目旨在开发一套现代化的学生宿舍水费管理系统，实现宿舍信息管理、学生入住管理、用水记录登记与费用计算等核心功能。

1.2 项目目标

* 提供直观的图形化界面，降低操作门槛

* 实现宿舍、学生、用水记录的增删改查

* 自动计算阶梯水费

* 支持数据持久化存储

* 提供流畅的用户体验

1.3 技术选型

技术 说明

编程语言 C++17

UI 框架 WinUI 3

语言投影 C++/WinRT

数据序列化 cereal (JSON)

开发环境 Visual Studio 2026

运行平台 Windows 10/11

选型理由：WinUI 3 是微软最新的原生 UI 框架，搭配 C++/WinRT 可获得极致性能与原生 Windows 11 视觉风格。与传统的 Qt、MFC 等方案相比，WinUI 3 提供现代化的 Fluent Design 界面，用户体验更佳。

---

二、需求分析

2.1 功能需求

2.1.1 宿舍管理

· 添加宿舍（选择区域、楼栋、楼层、房间号）

· 编辑宿舍基本信息

· 删除宿舍

· 查看宿舍列表

2.1.2 学生管理

· 添加学生（姓名、学号）到指定宿舍

· 编辑学生信息

· 删除学生

2.1.3 用水记录管理

· 添加用水记录（年月、用量）

· 编辑用水记录

· 删除用水记录

· 自动计算水费（阶梯水价）

2.1.4 数据持久化

· 程序启动时自动加载数据

· 数据变更时自动保存

· 支持 JSON 格式存储，便于调试

2.2 非功能需求

· 界面响应流畅，操作延迟 < 100ms

· 数据自动保存，避免数据丢失

· 界面布局自适应窗口大小

· 错误提示友好，避免程序崩溃

---

三、系统设计

3.1 系统架构

```
┌─────────────────────────────────────┐
│              UI 层 (Pages)           │
│  DormListPage  DormManageForm       │
│  EditDormForm   EditStudentForm     │
│  EditRecordForm                     │
└──────────────┬──────────────────────┘
               │ 数据绑定
┌──────────────▼──────────────────────┐
│          业务逻辑层 (Manager)         │
│  MainManager                        │
│  - 数据 CRUD 操作                    │
│  - 水费计算                          │
│  - 数据验证                          │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│           数据层 (Models)            │
│  Dorm, Student, WaterRecord         │
│  DormInfo                           │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│         持久化层 (Service)           │
│  DataSaveService                    │
│  StdModelsConverter                 │
│  (cereal JSON 序列化)               │
└─────────────────────────────────────┘
```

3.2 核心数据结构

3.2.1 DormInfo（宿舍基本信息）

属性 类型 说明

Region int32_t 区域编号

BuildingNumber int32_t 楼栋号

Floor int32_t 楼层

RoomNumber int32_t 房间号

StartDateYear int32_t 入住起始年份

StartDateMonth int32_t 入住起始月份

3.2.2 Dorm（宿舍）

属性 类型 说明
DormId hstring 唯一标识（由区域+楼栋+楼层+房间号生成）

Info DormInfo 基本信息

Students IObservableVector\<Student\> 入住学生列表

Records IObservableVector\<WaterRecord\> 用水记录列表

3.2.3 WaterRecord（用水记录）

属性 类型 说明

Year int32_t 年份

Month int32_t 月份

Usage double 用水量（吨）

Cost double 水费（元）

HasPaid bool 是否已缴费

3.2.4 Student（学生）

属性 类型 说明
Name hstring 姓名
StudentId hstring 学号

3.3 UI 数据绑定机制

本项目采用 INotifyPropertyChanged 绑定方案。

```
MainManager 持有 IObservableVector<Dorm>
        ↓
ListView 绑定到该集合
        ↓
数据修改 → MainManager.xxxMethod()
        ↓
修改集合中的对象 → SetAt(index, modifiedObject)
        ↓
触发 VectorChanged 事件
        ↓
ListView 自动刷新 UI
```

---

四、详细实现

4.1 主界面（MainPage）

主界面采用 NavigationView 布局，包含：

· 导航菜单（宿舍列表、学生管理等）

· 内容区域（Frame 控件实现页面导航）

4.2 宿舍列表页（DormListPage）

功能：

· 显示所有宿舍信息

· 提供添加、编辑、删除操作入口

· 点击宿舍查看详细信息

数据绑定：

```cpp
// 构造函数中
dormItems = mainManager->getDormItems();
// dormItems 直接绑定到 ListView 的 ItemsSource
```

4.3 宿舍管理表单（DormManageForm）

功能：

· 显示宿舍详细信息

· 管理学生列表

· 管理用水记录

· 通过 ContentDialog 弹出编辑窗口

关键实现：

```cpp
winrt::IAsyncAction DormManageForm::openEditDormDialogAsync()
{
    auto form = winrt::make_self<EditDormForm>();
    // 初始化表单数据
    // 设置对话框
    // 等待用户确认
    co_await dialog.ShowAsync();
}
```

4.4 水费计算（Utils::calculateTotalWaterFee）

采用广州市居民阶梯水价标准：

阶梯 用水量 单价

第一阶梯 ≤26吨/月 2.93元/吨

第二阶梯 27-34吨/月 4.40元/吨

第三阶梯 34吨/月 7.87元/吨

```cpp
double Utils::calculateTotalWaterFee(double const& usage)
{
    constexpr double tier1Price = 2.93;
    constexpr double tier2Price = 4.40;
    constexpr double tier3Price = 7.87;
    constexpr double tier1Limit = 26.0;
    constexpr double tier2Limit = 34.0;

    if (usage <= tier1Limit)
        return usage * tier1Price;
    else if (usage <= tier2Limit)
        return tier1Limit * tier1Price + (usage - tier1Limit) * tier2Price;
    else
        return tier1Limit * tier1Price 
             + (tier2Limit - tier1Limit) * tier2Price 
             + (usage - tier2Limit) * tier3Price;
}
```

4.5 数据持久化

序列化流程：

```
WinRT Models → StdModelsConverter → StdModels (普通C++结构体)
        ↓
    cereal::JSONOutputArchive
        ↓
    dorms_data.json
```

反序列化流程：

```
dorms_data.json
        ↓
    cereal::JSONInputArchive
        ↓
StdModels → StdModelsConverter → WinRT Models
```

---

五、关键技术难点

5.1 UI 数据绑定方案选择

问题：C++/WinRT 中没有 C# 那样的 [ObservableProperty] 自动通知机制。

尝试：最初尝试在 Model 类上实现 INotifyPropertyChanged，遇到线程调度问题——属性变更事件必须在 UI 线程触发，而在后台线程修改数据时无法正确调度。

5.2 多页面数据同步

问题：DormListPage 和 DormManageForm 同时引用 Dorm 对象，一处修改需要多处更新。

5.2 多页面数据同步

问题：DormListPage 和 DormManageForm 同时引用 Dorm 对象，一处修改需要多处更新。

方案：所有数据由 MainManager 统一管理，各页面通过 IObservableVector 绑定同一份数据。修改后通过 SetAt 触发通知，所有绑定自动刷新。

5.3 编译内存不足

问题：项目包含大量 WinRT 头文件，预编译头体积庞大，编译器虚拟内存不足导致编译失败。

解决：

· 增大 Windows 虚拟内存（页面文件）
· 关闭不必要的后台程序
· 确保使用 x64 编译配置

5.4 日期补全逻辑

问题：修改宿舍入住起始日期时，需要自动补全或删除对应月份的用水记录。

方案：编写 completeMonths 方法，根据新旧日期比较，自动计算需要补全的月份范围并生成对应记录。

---

六、测试与运行

6.1 测试环境

· 操作系统：Windows 11
· 编译环境：Visual Studio 2022
· 运行时：WinUI 3 + C++/WinRT

6.2 功能测试

测试项 预期结果 实际结果

添加宿舍 宿舍列表中显示新宿舍 ✓ 通过

编辑宿舍信息 信息更新且列表刷新 ✓ 通过

删除宿舍 列表中移除该宿舍 ✓ 通过

添加学生 学生列表更新 ✓ 通过

添加用水记录 记录显示且水费自动计算 ✓ 通过

数据保存 关闭程序后重新打开数据仍在 ✓ 通过

6.3 运行截图

（此处插入程序运行截图）

---

七、总结与展望

7.1 项目总结

本项目基于 WinUI 3 + C++/WinRT 技术栈，成功实现了一套功能完整的学生宿舍水费管理系统。系统具备宿舍管理、学生管理、用水记录管理、阶梯水费自动计算、数据持久化等核心功能。

在开发过程中，深入研究了 C++/WinRT 的数据绑定机制，探索了多种 UI 刷新方案，最终确定了 IObservableVector + SetAt 的实用主义方案。解决了多线程 UI 更新、跨页面数据同步、编译优化等实际问题。

7.2 收获与体会

通过本次课程设计，深入理解了：

· C++/WinRT 的运行时特性与线程模型

· WinUI 3 的数据绑定机制

· 现代 C++ 的协程、智能指针等特性

· 软件架构分层设计的重要性

· 问题排查与调试技巧

7.3 未来改进

· 引入 MVVM 框架进一步解耦 UI 与业务逻辑

· 增加数据统计图表功能

· 支持数据导出为 Excel

· 部署到局域网服务器，支持多用户访问

---

参考文献

[1] Microsoft. WinUI 3 Documentation. https://learn.microsoft.com/en-us/windows/apps/winui/

[2] Microsoft. C++/WinRT Documentation. https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/

[3] cereal. A C++11 library for serialization. https://github.com/USCiLab/cereal

---


---

广东工业大学

课程设计报告

课程名称：C 语言课程设计

设计题目：学生宿舍水费管理系统

学生姓名：[你的名字]

学　　号：[你的学号]

班　　级：[你的班级]

指导教师：[唐平]

完成日期：2026 年 5 月

---

一、项目概述

1.1 项目背景

学生宿舍水费管理是高校后勤工作的重要组成部分。传统人工抄表、纸质记录方式效率低、易出错、不便于统计。本系统旨在提供一套现代化的宿舍水费管理方案，实现宿舍信息、学生入住、用水记录的信息化管理。

1.2 项目目标

· 提供直观的图形化界面
· 实现宿舍、学生、用水记录的增删改查
· 自动计算阶梯水费
· 支持数据持久化存储

1.3 技术选型

技术 说明
编程语言 C++17
UI 框架 WinUI 3
语言投影 C++/WinRT
数据序列化 cereal (JSON)
开发环境 Visual Studio 2026

选型理由：WinUI 3 是微软最新的原生 UI 框架，提供 Fluent Design 现代界面风格。C++/WinRT 编译为原生代码，性能高、启动快，适合桌面应用开发。

---

二、需求分析

2.1 功能需求

宿舍管理：添加、编辑、删除宿舍，查看宿舍列表

学生管理：添加、编辑、删除学生，学生关联到宿舍

用水记录管理：添加、编辑、删除用水记录，自动计算阶梯水费

数据持久化：启动时自动加载，修改后自动保存，JSON 格式存储

2.2 非功能需求

· 界面响应流畅
· 数据自动保存
· 错误提示友好

---

三、系统设计

3.1 系统架构

系统采用三层架构设计：

· UI 层：XAML 页面，负责界面展示与用户交互
· 业务逻辑层：MainManager，负责数据操作、水费计算、数据验证
· 数据层：Dorm、Student、WaterRecord 等模型，以及 DataSaveService 序列化模块

3.2 UI 数据绑定机制

采用 IObservableVector + SetAt 方案：MainManager 持有 IObservableVector 集合，各页面通过数据绑定连接。数据修改后通过 SetAt 触发 VectorChanged 事件，UI 自动刷新。相比 INotifyPropertyChanged，该方案在 C++/WinRT 中更简洁稳定。

3.3 水费计算

采用广州市居民阶梯水价标准：第一阶梯 ≤26 吨，2.93 元/吨；第二阶梯 27-34 吨，4.40 元/吨；第三阶梯 >34 吨，7.87 元/吨。

---

四、详细实现

4.1 主界面

采用 NavigationView 布局，左侧导航菜单，右侧 Frame 控件实现页面切换。

4.2 宿舍管理

DormListPage 展示宿舍列表，DormManageForm 展示宿舍详情及学生、用水记录管理。编辑操作通过 ContentDialog 弹窗完成。

4.3 数据持久化

使用 cereal 库实现 JSON 序列化。程序启动时从 dorms_data.json 加载数据，数据变更时自动保存。

---

五、关键技术难点

5.1 数据绑定方案选择

C++/WinRT 中实现 INotifyPropertyChanged 需手动处理线程调度。最终采用 IObservableVector::SetAt 替换整个对象触发集合级通知，简洁可靠。

5.2 多页面数据同步

所有数据由 MainManager 统一管理，各页面通过 IObservableVector 绑定同一数据源。修改后通过 SetAt 触发通知，所有绑定处自动刷新。

5.3 编译优化

项目包含大量 WinRT 头文件，预编译头体积大，需增大虚拟内存并确保使用 x64 配置编译。

---

六、测试与运行

6.1 测试环境

· 操作系统：Windows 11
· 编译环境：Visual Studio 2026
· 运行时：WinUI 3 + C++/WinRT

6.2 功能测试

测试项 预期结果 实际结果
添加宿舍 列表中显示新宿舍 通过
编辑宿舍信息 信息更新且列表刷新 通过
删除宿舍 列表中移除 通过
添加学生 学生列表更新 通过
添加用水记录 记录显示且水费自动计算 通过
数据持久化 重启后数据仍在 通过

6.3 运行截图

（此处插入软件运行截图）

---

七、总结与展望

7.1 项目总结

本项目基于 WinUI 3 + C++/WinRT 技术栈，实现了一套功能完整的学生宿舍水费管理系统。在开发过程中深入研究了 WinRT 的数据绑定机制，解决了多线程 UI 更新、跨页面数据同步、编译优化等实际问题。

7.2 收获与体会

通过本次课程设计，深入理解了 C++/WinRT 运行时特性、WinUI 3 数据绑定机制、现代 C++ 协程与智能指针、软件分层架构设计的重要性。

7.3 未来改进

· 增加数据统计图表
· 支持数据导出为 Excel
· 添加登录与权限管理
· 部署到局域网支持多用户访问

---

参考文献

[1] Microsoft. WinUI 3 Documentation.
[2] Microsoft. C++/WinRT Documentation.
[3] cereal. A C++11 library for serialization.

---




1. DormManager编写

DormManager包含以下功能：
包含一个学生对象列表；vector<Student> students;

包含一个水费记录对象列表；vector<WaterRecord> waterRecords;

添加学生；addStudent(Student student)

删除学生；removeStudent(string id)

修改学生姓名；updateStudentName(string id, string name)

查询学生；queryStudent(string id)

查询宿舍水费记录；queryWaterRecords(string id)（返回一整个水费记录列表）

查询宿舍特定水费记录；querySpecificWaterRecord(string id, int year, int month)（返回一个水费记录对象）

添加宿舍水费记录；addWaterRecord(WaterRecord record)（要返回一个Result对象。新建一个Result对象，修改他的属性success和info，然后返回）

删除宿舍水费记录；removeWaterRecord(int year, int month)

修改宿舍水费记录；updateWaterRecord(int year, int month, double usage)


2. RecordManager编写

RecordManager包含以下功能：

包含一个水费记录对象列表引用；vector<WaterRecord>& waterRecords;

添加水费记录；addWaterRecord(WaterRecord record);（要返回一个Result对象。新建一个Result对象，修改属性success和info）

删除水费记录；removeWaterRecord(int year, int month);

修改水费记录；updateWaterRecord(int year, int month, double usage);

查询水费记录；queryWaterRecord(int year, int month);（返回水费记录列表吧？）

查询特定水费记录：querySpecificWaterRecord(string id, int year, int month);（返回一个水费记录对象）


RecordManager如何获取宿舍对象？

每次要执行与学生相关的水费记录操作时，

RecordManager需要通过DormManager来获取对应的学生对象。（注意是引用或者引用，否则只会传递副本）

可以在RecordManager中添加一个成员变量来引用DormManager，并在构造函数中进行初始化。


3. Utils编写

Utils工具类包含以下功能：（Utils类是静态类static，不会实例化）

提供一些常用的工具函数，例如：

计算水费总额；calculateTotalWaterFee(const &vector<WaterRecord> records); （为什么使用引用？为了不创建副本；为什么加const？为了保证函数不修改传入的向量） 

格式化输出水费记录；formatWaterRecord(const WaterRecord& record); 

验证输入的学生ID是否合法；validateStudentId(const string& id);

验证输入的水费记录是否合法；validateWaterRecord(const WaterRecord& record);

排序水费记录；sortWaterRecords(vector<WaterRecord>& records); （为什么使用引用？为了直接修改传入的向量）

其他可能的工具函数，例如日期验证、字符串处理等。

这个工具包在整个系统中都可以使用，提供了方便的函数来处理常见的操作，减少代码重复，提高代码的可维护性和可读性。


：

4. UI界面



必读事项
---

不要点击上面的绿色运行按钮，而是使用单元测试。

使用单元测试来测试StudentManager和RecordManager的功能，确保它们的正确性和稳定性。

测试项目在解决发难资源管理器的UnitTests项目中，

test_studentmanager.cpp包含了一个示例测试。 

模仿示例编写自己的测试测试自己函数功能是否正常。

上方菜单栏选择“测试”-->“测试资源管理器”测试自己写的单元测试。



以下是一个简单的实现示例：
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class WaterRecord {
public:
    int year;
    int month;
    double usage;
    WaterRecord(int y, int m, double u) : year(y), month(m), usage(u) {}
};
class Student {
public:
    string id;
    string name;
    Student(string i, string n) : id(i), name(n) {}
};
class StudentManager {
private:
    vector<Student> students;
public:
    void addStudent(Student student) {
        students.push_back(student);
    }
    void removeStudent(string id) {
        students.erase(remove_if(students.begin(), students.end(),
            [&id](Student& s) { return s.id == id; }), students.end());
    }
    void updateStudentName(string id, string name) {
        for (auto& student : students) {
            if (student.id == id) {
                student.name = name;
                break;
            }
        }
    }
    Student* queryStudent(string id) {
        for (auto& student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }
};
class RecordManager {
private:
    vector<WaterRecord> waterRecords;
    StudentManager& studentManager; // 引用StudentManager
public:
    RecordManager(StudentManager& sm) : studentManager(sm) {}

```

这代码自动补全太神人了，别写了

只是一些吐槽
---

如果你喜欢经受折磨，那就快来写winui c++吧！

喜欢我c++编译器的超级报错吗？😍😍😍

喜欢我visual studio自动创建命令把函数放命名空间外面吗？😍😍

我最初的架构设计可以说是专门针对数据绑定做的。MainManager、StudentManager、RecordManager，一层层修改接受到的引用，直接操作源对象，然后反映到UI层...想象很美好，现实很骨感。什么叫只有IOvservableVector有自动数据绑定的能力？什么叫我还要在Model层面手动实现INotifyPropertyChanged？彳亍，那我去实现吧，我去修改数据结构了...什么叫UI线程冲突？我那线程不就是在UI上的吗？这集神了，我又得把INotifyPripertyChanged删了。还是得回退到最基本的操作——直接后台代码操控UI文本。

你不是都没有用ViewModel吗？你都用数据绑定了，不用viewmodel？意义为何？我也不知道。可能因为我讨厌ViewModel，但不讨厌数据绑定。

omg我终于搞好那个煞笔INotifyPropertyChanged了，还是看csdn博客看到的。果然靠ai不如靠自己，我是正版gemini的受害者！现在那些架构设计就不是白做的了。

当你整段复制代码给ai，让他给你修复代码，然后再复制到代码编辑器里面运行调试，循环往复了好几次，你就应该知道，这条路走不通了，他给的信息没任何帮助。我简直是正版gemini的受害者！谁让我选了winui c++呢？自己选的苦自己吃好吧！~_~（但是做出来的界面真的好看啊！）

当我第一次听说winrt的东西全都是引用传递的时候，我人都傻了。引用传递是何意味？意为你压根不需要给类型加&，就能直接像引用变量一样使用。变量传递时，只会拷贝数据源的地址，动传过来的winrt对象时，虽然没加&，依然在修改源数据。好家伙，净学c#那一套是吧？不愧是你，巨硬！

---

我不明白，为什么你们写C++的写私有成员老喜欢在前面加个m_？就是你们这群臭写c++的搞得我老是要改你们给的m_。我靠，你们是m吧，所以喜欢加个m_？公有成员开头大写会死是吧？真不明白你们为什么老是喜欢加个_，你他妈，_在键盘上面，还要按shift切换，我操你妈，每次打这个符号还要一只手按那个shift键另一只手伸上去按那个傻逼_键。他妈的，为什么不管c++还是C#老有这种傻逼写法？c++就是m_bitchPropertyName，c#就是_bitchPropertyName？你妈的下次再给我写这样的字段名我他妈一脚踹你脸上！

