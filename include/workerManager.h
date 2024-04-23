#pragma once			// ��ֹͷ�ļ��ظ�����
#include "worker.h"
#include <fstream>
#define FILENAME "empFile.txt"


class WorkerManager
{
public:
	// ���캯��-����
	WorkerManager();

	// ��������-����
	~WorkerManager();

	// չʾ�˵�-���� {����}
	void Show_Menu();

	// �˳�����-���� {����}
	void ExitSystem();

	// ���ְ��-���� {����}
	void Add_Emp();

	// �����ļ�-����
	void save();

	// ͳ������-����
	int get_EmpNum();

	// ��ʼ��ְ��-����
	void init_Emp();

	// ��ʾְ��-���� {����}
	void Show_Emp();

	// ְ���������ж�
	int isExist(int);
	int isExist(std::string);

	// ɾ��ְ��-���� {����}
	void Del_Emo();

	// �޸�ְ��-���� {����}
	void Mod_Emp();

	// ����ְ��-���� {����}
	void Find_Emp();

	// ����ְ��-���� {����}
	void Sort_Emp();

	// ����ļ�-���� {����}
	void Purge_File();


private:
	// ��¼ְ������
	int m_EmpNum;

	// ְ������ָ��
	Worker** m_EmpArray;

	// ��׼�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
};