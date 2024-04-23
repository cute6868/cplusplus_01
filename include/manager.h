#pragma once
#include "worker.h"


// ������
class Manager :public Worker
{
public:
	// ���캯��-����
	Manager(int id, std::string name, int dID);

	// ��ʾ������Ϣ-����
	void shoInfo();

	// ��ȡ��λ����-����
	std::string getDeptName();
};


// ���캯��-ʵ��
Manager::Manager(int id, std::string name, int dID)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dID;
}


// ��ʾ������Ϣ-����
void Manager::shoInfo()
{
	std::cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ������ϰ彻��������" << std::endl;
}


// ��ȡ��λ����-����
std::string Manager::getDeptName()
{
	return std::string("����");
}