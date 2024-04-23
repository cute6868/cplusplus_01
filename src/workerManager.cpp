#include "workerManager.h"
using namespace std;
#include "boss.h"
#include "manager.h"
#include "employer.h"


// 构造函数-实现
WorkerManager::WorkerManager()
{
	// -------------------- 创建文件输入流对象 -------------------- 
	ifstream file;

	// -------------------- 尝试打开文件 -------------------- 
	file.open(FILENAME, ios::in);

	// -------------------- 文件不存在 -------------------- 
	// 判断文件是否真的被打开（如果没有被打开，说明文件不存在）
	if (!file.is_open())
	{
		/*
		cout << "文件不存在" << endl;		// 测试
		*/
		this->m_EmpNum = 0;			// 初始化人数
		this->m_FileIsEmpty = true;	// 初始化文件为空标志
		this->m_EmpArray = NULL;	// 初始化数组指针
		file.close();	// 释放系统资源
		return;
	}

	// -------------------- 文件存在，并且没有记录 -------------------- 
	char ch;
	file >> ch;			// 先尝试去读取文件里面的一个字符
	if (file.eof())		// 读取完成后，判断是否是EOF (End Of File), 如果是，说明文件为空
	{
		/*
		cout << "文件为空" << endl;		// 测试
		*/
		this->m_EmpNum = 0;			// 初始化人数
		this->m_FileIsEmpty = true;	// 初始化文件为空标志
		this->m_EmpArray = NULL;	// 初始化数组指针
		file.close();	// 释放系统资源
		return;
	}

	// -------------------- 文件存在，并且有职工数据 -------------------- 
	// 1. 获取职工人数
	int num = this->get_EmpNum();
	/*
	cout << "职工的个数为：" << num << endl;		// 测试
	*/

	// 2. 初始化人数
	this->m_EmpNum = num;

	// 3. 初始化文件为空标志
	this->m_FileIsEmpty = false;

	// 4. 开辟内存空间，准备存入对象（即：初始化数组指针）
	this->m_EmpArray = new Worker * [this->m_EmpNum];

	// 5. 将文件数据里面的职工信息，转化为对象，并读入到内存空间中（即：初始化职工）
	this->init_Emp();

	/*
	// 测试代码
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmpArray[i]->m_Id
			<< " 姓名：" << this->m_EmpArray[i]->m_Name
			<< " 部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
	}
	*/
}


// 析构函数-实现
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		// 释放堆区里面的一个个职工对象
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
		}

		// 释放堆区里面用来存放一个个职工对象的数组
		delete[] this->m_EmpArray;

		// 重新将指针指向NULL
		this->m_EmpArray = NULL;
	}
}


// 展示菜单-实现 {功能}
void WorkerManager::Show_Menu()
{
	cout << "*****************************" << endl;
	cout << "**  欢迎使用职工管理系统  **" << endl;
	cout << "*****  0.退出管理程序	*****" << endl;
	cout << "*****  1.增加职工信息	*****" << endl;
	cout << "*****  2.显示职工信息	*****" << endl;
	cout << "*****  3.删除离职职工	*****" << endl;
	cout << "*****  4.修改职工信息	*****" << endl;
	cout << "*****  5.查找职工信息	*****" << endl;
	cout << "*****  6.按照编号排序	*****" << endl;
	cout << "*****  7.清空所有文档	*****" << endl;
	cout << endl;
}


// 退出功能-实现 {功能}
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


// 添加职工-实现 {功能}
void WorkerManager::Add_Emp()
{
	cout << "请输入增加职工数量：";

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		// 计算空间大小
		int newSize = this->m_EmpNum + addNum;

		// 开辟新空间
		Worker** newSpace = new Worker * [newSize];

		// 将原空间下内存存放到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < m_EmpNum; i++)
			{

				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// 批量添加新的数据
		for (int i = 0; i < addNum; i++)
		{
			int id;		// 职工编号
			string name;	// 职工姓名
			int dID;	// 部门编号

			// 获取数据
			cout << "请输入第" << i + 1 << "个新职工的编号：";
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的姓名：";
			cin >> name;
			cout << "请选择该职工的岗位" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cout << ">>> ";
			cin >> dID;

			// 根据获取到的数据创建对象
			Worker* worker = NULL;
			switch (dID)
			{
			case 1:
				worker = new Employee(id, name, dID);
				break;
			case 2:
				worker = new Manager(id, name, dID);
				break;
			case 3:
				worker = new Boss(id, name, dID);
				break;
			default:
				break;
			}

			// 将创建出来的职工，保存到数组中
			newSpace[(this->m_EmpNum) + i] = worker;
		}

		// 释放原来的空间
		delete[] this->m_EmpArray;

		// 更新指针指向，让它指向新空间
		this->m_EmpArray = newSpace;

		// 更新职工人数
		this->m_EmpNum = newSize;

		// 保存到文件中
		this->save();

		// 提示信息
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else
	{
		cout << "输入有误" << endl;
	}
}


// 保存文件-实现
void WorkerManager::save()
{
	// 创建流对象
	ofstream file;

	// 打开文件
	file.open(FILENAME, ios::out);

	// 向文件里面写入数据
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		file << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	// 关闭文件
	file.close();
}


// 统计人数-实现
int WorkerManager::get_EmpNum()
{
	// 创建文件输入流对象
	ifstream file;

	// 尝试打开文件
	file.open(FILENAME, ios::in);

	int id;
	string name;
	int dID;

	// 记录人数
	int num = 0;

	// 循环输出数据
	while (file >> id && file >> name && file >> dID)
	{
		num++;		// 记录人数
	}

	// 关闭文件
	file.close();

	return num;
}


// 初始化职工-实现
void WorkerManager::init_Emp()
{
	// 创建文件输入流对象
	ifstream file;

	// 尝试打开文件
	file.open(FILENAME, ios::in);

	int id;
	string name;
	int dID;

	int index = 0;
	while (file >> id && file >> name && file >> dID)
	{
		// 创建职工指针
		Worker* worker = NULL;

		// 根据不同的部门id创建不同对象
		if (dID == 1)	// 普通员工
		{
			worker = new Employee(id, name, dID);
		}
		else if (dID == 2)	// 经理
		{
			worker = new Manager(id, name, dID);
		}
		else	// 老板
		{
			worker = new Boss(id, name, dID);
		}

		// 存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}

}


// 显示职工-实现 {功能}
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		// 利用多态调用接口
		this->m_EmpArray[i]->shoInfo();
	}
}


// 职工存在性判断-实现
int WorkerManager::isExist(int id)
{
	/*
		param:id : 获取要进行判断的职工编号
		param:return : -1 或者 数组中的位置
	*/
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
int WorkerManager::isExist(string name)
{
	/*
		param:name : 获取要进行判断的职工姓名
		param:return : -1 或者 数组中的位置
	*/
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Name == name)
		{
			index = i;
			break;
		}
	}
	return index;
}


// 删除职工-实现 {功能}
void WorkerManager::Del_Emo()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		return;
	}

	// 获取要删除的职工的编号
	int id;
	cout << "请输入想要删除职工的编号：";
	cin >> id;
	int index = this->isExist(id);

	// 判断是否存在该职工
	if (index == -1)
	{
		cout << "删除失败，未找到该职工！" << endl;
		return;
	}

	// 职工存在，进行删除操作（数据前移）
	// 1. 释放该指针指向的对象
	delete this->m_EmpArray[index];

	// 2. 指针数组里面的指针数据往前移动
	for (int i = index; i < this->m_EmpNum - 1; i++)
	{
		this->m_EmpArray[i] = this->m_EmpArray[i + 1];
	}

	// 3. 更新人员个数
	this->m_EmpNum--;

	// 删除操作结束后，将最新的数据同步到文件中
	this->save();

	// 提示信息
	cout << "删除成功" << endl;
}


// 修改职工-实现 {功能}
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		return;
	}

	int id;
	string name;
	int dID;

	// 获取要修改的职工的编号
	cout << "请输入想要修改职工的编号：";
	cin >> id;
	int index = this->isExist(id);

	// 判断是否存在该职工
	if (index == -1)
	{
		cout << "修改失败，未找到该职工！" << endl;
		return;
	}

	// 职工存在，进行修改操作

	// 1. 获取修改数据
	cout << "请输入新的职工编号：";
	cin >> id;
	cout << "请输入新的姓名：";
	cin >> name;
	cout << "请输入岗位：" << endl;
	cout << "1. 普通职工" << endl;
	cout << "2. 经理" << endl;
	cout << "3. 老板" << endl;
	cout << ">>> ";
	cin >> dID;

	// 2. 创建新的职工对象指针
	Worker* worker = NULL;

	// 3. 根据修改后的结果，创建对应的职工对象
	switch (dID)
	{
	case 1:
		worker = new Employee(id, name, dID);
		break;
	case 2:
		worker = new Manager(id, name, dID);
		break;
	case 3:
		worker = new Boss(id, name, dID);
		break;
	default:
		break;
	}

	// 4. 释放原指针所指向的对象
	delete this->m_EmpArray[index];

	// 5. 更新新指针到指针数组中
	this->m_EmpArray[index] = worker;

	// 修改操作结束后，将最新的数据同步到文件中
	this->save();

	// 提示信息
	cout << "修改成功" << endl;
}


// 查找职工-实现 {功能}
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		return;
	}

	// 选择查找方式
	int select;
	cout << "请输入查找的方式：" << endl;
	cout << "1. 按职工编号查找" << endl;
	cout << "2. 按姓名查找" << endl;
	cout << ">>> ";
	cin >> select;

	// 获取要查找的职工编号或姓名，并判断该职工是否存在
	int id;
	string name;
	int index;

	if (select == 1)
	{
		cout << "请输入要查找的职工编号：";
		cin >> id;
		index = isExist(id);
	}
	else if (select == 2)
	{
		cout << "请输入要查找的职工姓名：";
		cin >> name;
		index = isExist(name);
	}
	else
	{
		cout << "查找失败，输入选项有误" << endl;
		return;
	}

	if (index == -1)
	{
		cout << "查无此人" << endl;
		return;
	}

	// 职工存在，输出对应信息
	this->m_EmpArray[index]->shoInfo();
}


// 排序职工-实现 {功能}
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		return;
	}

	// 获取选择方式
	cout << "请选择排序方式：" << endl;
	cout << "1. 按职工号进行升序排序" << endl;
	cout << "2. 按职工号进行降序排序" << endl;
	cout << ">>> ";
	int select = 0;
	cin >> select;

	// 使用引用，精简排序过程
	Worker**& arr = this->m_EmpArray;
	int& num = this->m_EmpNum;

	// 排序过程
	switch (select)
	{
	case 1:
		// 升序排序
		for (int i = 0; i < num; i++)
		{
			for (int j = i + 1; j < num; j++)
			{
				if (arr[i]->m_Id > arr[j]->m_Id)
				{
					Worker* temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
		break;

	case 2:
		// 降序排序
		for (int i = 0; i < num; i++)
		{
			for (int j = i + 1; j < num; j++)
			{
				if (arr[i]->m_Id < arr[j]->m_Id)
				{
					Worker* temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
		break;

	default:
		cout << "排序失败，选择方式有误" << endl;
		return;
	}

	// 修改操作结束后，将最新的数据同步到文件中
	this->save();

	// 显示排序结果
	this->Show_Emp();
}


// 清除文件-实现 {功能}
void WorkerManager::Purge_File()
{
	int select;
	cout << "此操作不可逆。是否确认清空？" << endl;
	cout << "1. 确认" << endl;
	cout << "2. 返回" << endl;
	cout << ">>> ";
	cin >> select;

	// 再次确认操作
	if (select == 1)
	{
		string confirm;
		cout << "请在下方输入：清空后无法恢复，我确认清空" << endl;
		cout << ">>> ";
		cin >> confirm;
		if (confirm != "清空后无法恢复，我确认清空")		return;
	}

	// 执行清空操作
	if (select == 1)
	{
		// ---------------- 清除文件中的数据 ----------------
		// 通过"打开模式"进行删除（如果文件存在则删除文件，并重新创建）ios::trunc
		ofstream file(FILENAME, ios::trunc);
		file.close();

		// ---------------- 清除内存中的数据 ----------------
		// 1. 指针数组中没有数据（内存中没有数据）
		if (this->m_EmpArray == NULL)
		{
			cout << "清除成功" << endl;
			return;
		}

		// 2. 指针数组中有数据（内存中有数据）
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];		// 指针数组中的每一个指针所指向的职工对象被释放
			}
			delete[] this->m_EmpArray;			// 指针数组被释放
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}

		// 提示信息
		cout << "清除成功" << endl;
	}
}