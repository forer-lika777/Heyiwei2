Heyiwei2
===

汪泽群 竹永琪 吴溢轩选择1、2、3写：

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


我和陈东扬：

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

如果你喜欢经受折磨，那就快来写winui c++吧！

喜欢我c++编译器的超级报错吗？😍😍😍

我最初的架构设计可以说是专门针对数据绑定做的。MainManager、StudentManager、RecordManager，一层层修改接受到的引用，直接操作源对象，然后反映到UI层...想象很美好，现实很骨感。什么叫只有IOvservableVector有自动数据绑定的能力？什么叫我还要在Model层面手动实现INotifyPropertyChanged？彳亍，那我去实现吧，我去修改数据结构了...什么叫UI线程冲突？我那线程不就是在UI上的吗？这集神了，我又得把INotifyPripertyChanged删了。还是得回退到最基本的操作——直接后台代码操控UI文本。

