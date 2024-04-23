#pragma once
#include "worker.h"


// 员工类
class Employee :public Worker
{
public:
	// 构造函数-声明
	Employee(int id, std::string name, int dID);

	// 显示个人信息-声明
	void shoInfo();

	// 获取岗位名称-声明
	std::string getDeptName();
};


// 构造函数-实现
Employee::Employee(int id, std::string name, int dID)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dID;
}


// 显示个人信息-实现
void Employee::shoInfo()
{
	std::cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务" << std::endl;
}


// 获取岗位名称-实现
std::string Employee::getDeptName()
{
	return std::string("员工");
}