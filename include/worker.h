#pragma once
#include <string>		// ���� string ��
#include <iostream>		// ���������������ͷ�ļ�


// ְ��������
class Worker
{
public:
	// ��ʾ������Ϣ
	virtual void shoInfo() = 0;

	// ��ȡ��λ����
	virtual std::string getDeptName() = 0;
	
	int m_Id;	// ְ�����
	std::string m_Name;	// ְ������
	int m_DeptId;	// ְ�����ڲ������Ʊ��
};