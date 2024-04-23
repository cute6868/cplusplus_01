#pragma once
#include "worker.h"


// 老板类
class Boss :public Worker
{
public:
	// 构造函数-声明
	Boss(int id, std::string, int dID);
	
	// 显示个人信息-声明
	void shoInfo();

	// 获取岗位名称-声明
	std::string getDeptName();
};


// 构造函数-实现
Boss::Boss(int id, std::string name, int dID)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dID;
}


// 显示个人信息-实现
void Boss::shoInfo()
{
	std::cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：把握公司整体运行情况" << std::endl;
}


// 获取岗位名称-实现
std::string Boss::getDeptName()
{
	return std::string("老板");
}