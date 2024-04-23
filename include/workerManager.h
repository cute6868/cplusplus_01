#pragma once			// 防止头文件重复包含
#include "worker.h"
#include <fstream>
#define FILENAME "empFile.txt"


class WorkerManager
{
public:
	// 构造函数-声明
	WorkerManager();

	// 析构函数-声明
	~WorkerManager();

	// 展示菜单-声明 {功能}
	void Show_Menu();

	// 退出功能-声明 {功能}
	void ExitSystem();

	// 添加职工-声明 {功能}
	void Add_Emp();

	// 保存文件-声明
	void save();

	// 统计人数-声明
	int get_EmpNum();

	// 初始化职工-声明
	void init_Emp();

	// 显示职工-声明 {功能}
	void Show_Emp();

	// 职工存在性判断
	int isExist(int);
	int isExist(std::string);

	// 删除职工-声明 {功能}
	void Del_Emo();

	// 修改职工-声明 {功能}
	void Mod_Emp();

	// 查找职工-声明 {功能}
	void Find_Emp();

	// 排序职工-声明 {功能}
	void Sort_Emp();

	// 清除文件-声明 {功能}
	void Purge_File();


private:
	// 记录职工人数
	int m_EmpNum;

	// 职工数组指针
	Worker** m_EmpArray;

	// 标准文件是否为空
	bool m_FileIsEmpty;
};