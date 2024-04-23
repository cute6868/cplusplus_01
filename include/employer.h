#pragma once
#include "worker.h"


// Ա����
class Employee :public Worker
{
public:
	// ���캯��-����
	Employee(int id, std::string name, int dID);

	// ��ʾ������Ϣ-����
	void shoInfo();

	// ��ȡ��λ����-����
	std::string getDeptName();
};


// ���캯��-ʵ��
Employee::Employee(int id, std::string name, int dID)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dID;
}


// ��ʾ������Ϣ-ʵ��
void Employee::shoInfo()
{
	std::cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << std::endl;
}


// ��ȡ��λ����-ʵ��
std::string Employee::getDeptName()
{
	return std::string("Ա��");
}