#pragma once
#include "worker.h"


// �ϰ���
class Boss :public Worker
{
public:
	// ���캯��-����
	Boss(int id, std::string, int dID);
	
	// ��ʾ������Ϣ-����
	void shoInfo();

	// ��ȡ��λ����-����
	std::string getDeptName();
};


// ���캯��-ʵ��
Boss::Boss(int id, std::string name, int dID)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dID;
}


// ��ʾ������Ϣ-ʵ��
void Boss::shoInfo()
{
	std::cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ�𣺰��չ�˾�����������" << std::endl;
}


// ��ȡ��λ����-ʵ��
std::string Boss::getDeptName()
{
	return std::string("�ϰ�");
}