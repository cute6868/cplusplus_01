#include "workerManager.h"
using namespace std;
#include "boss.h"
#include "manager.h"
#include "employer.h"


// ���캯��-ʵ��
WorkerManager::WorkerManager()
{
	// -------------------- �����ļ����������� -------------------- 
	ifstream file;

	// -------------------- ���Դ��ļ� -------------------- 
	file.open(FILENAME, ios::in);

	// -------------------- �ļ������� -------------------- 
	// �ж��ļ��Ƿ���ı��򿪣����û�б��򿪣�˵���ļ������ڣ�
	if (!file.is_open())
	{
		/*
		cout << "�ļ�������" << endl;		// ����
		*/
		this->m_EmpNum = 0;			// ��ʼ������
		this->m_FileIsEmpty = true;	// ��ʼ���ļ�Ϊ�ձ�־
		this->m_EmpArray = NULL;	// ��ʼ������ָ��
		file.close();	// �ͷ�ϵͳ��Դ
		return;
	}

	// -------------------- �ļ����ڣ�����û�м�¼ -------------------- 
	char ch;
	file >> ch;			// �ȳ���ȥ��ȡ�ļ������һ���ַ�
	if (file.eof())		// ��ȡ��ɺ��ж��Ƿ���EOF (End Of File), ����ǣ�˵���ļ�Ϊ��
	{
		/*
		cout << "�ļ�Ϊ��" << endl;		// ����
		*/
		this->m_EmpNum = 0;			// ��ʼ������
		this->m_FileIsEmpty = true;	// ��ʼ���ļ�Ϊ�ձ�־
		this->m_EmpArray = NULL;	// ��ʼ������ָ��
		file.close();	// �ͷ�ϵͳ��Դ
		return;
	}

	// -------------------- �ļ����ڣ�������ְ������ -------------------- 
	// 1. ��ȡְ������
	int num = this->get_EmpNum();
	/*
	cout << "ְ���ĸ���Ϊ��" << num << endl;		// ����
	*/

	// 2. ��ʼ������
	this->m_EmpNum = num;

	// 3. ��ʼ���ļ�Ϊ�ձ�־
	this->m_FileIsEmpty = false;

	// 4. �����ڴ�ռ䣬׼��������󣨼�����ʼ������ָ�룩
	this->m_EmpArray = new Worker * [this->m_EmpNum];

	// 5. ���ļ����������ְ����Ϣ��ת��Ϊ���󣬲����뵽�ڴ�ռ��У�������ʼ��ְ����
	this->init_Emp();

	/*
	// ���Դ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
			<< " ������" << this->m_EmpArray[i]->m_Name
			<< " ���ű�ţ�" << this->m_EmpArray[i]->m_DeptId << endl;
	}
	*/
}


// ��������-ʵ��
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		// �ͷŶ��������һ����ְ������
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
		}

		// �ͷŶ��������������һ����ְ�����������
		delete[] this->m_EmpArray;

		// ���½�ָ��ָ��NULL
		this->m_EmpArray = NULL;
	}
}


// չʾ�˵�-ʵ�� {����}
void WorkerManager::Show_Menu()
{
	cout << "*****************************" << endl;
	cout << "**  ��ӭʹ��ְ������ϵͳ  **" << endl;
	cout << "*****  0.�˳��������	*****" << endl;
	cout << "*****  1.����ְ����Ϣ	*****" << endl;
	cout << "*****  2.��ʾְ����Ϣ	*****" << endl;
	cout << "*****  3.ɾ����ְְ��	*****" << endl;
	cout << "*****  4.�޸�ְ����Ϣ	*****" << endl;
	cout << "*****  5.����ְ����Ϣ	*****" << endl;
	cout << "*****  6.���ձ������	*****" << endl;
	cout << "*****  7.��������ĵ�	*****" << endl;
	cout << endl;
}


// �˳�����-ʵ�� {����}
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


// ���ְ��-ʵ�� {����}
void WorkerManager::Add_Emp()
{
	cout << "����������ְ��������";

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		// ����ռ��С
		int newSize = this->m_EmpNum + addNum;

		// �����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		// ��ԭ�ռ����ڴ��ŵ��¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < m_EmpNum; i++)
			{

				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// ��������µ�����
		for (int i = 0; i < addNum; i++)
		{
			int id;		// ְ�����
			string name;	// ְ������
			int dID;	// ���ű��

			// ��ȡ����
			cout << "�������" << i + 1 << "����ְ���ı�ţ�";
			cin >> id;
			cout << "�������" << i + 1 << "����ְ����������";
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cout << ">>> ";
			cin >> dID;

			// ���ݻ�ȡ�������ݴ�������
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

			// ������������ְ�������浽������
			newSpace[(this->m_EmpNum) + i] = worker;
		}

		// �ͷ�ԭ���Ŀռ�
		delete[] this->m_EmpArray;

		// ����ָ��ָ������ָ���¿ռ�
		this->m_EmpArray = newSpace;

		// ����ְ������
		this->m_EmpNum = newSize;

		// ���浽�ļ���
		this->save();

		// ��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
	}
	else
	{
		cout << "��������" << endl;
	}
}


// �����ļ�-ʵ��
void WorkerManager::save()
{
	// ����������
	ofstream file;

	// ���ļ�
	file.open(FILENAME, ios::out);

	// ���ļ�����д������
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		file << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	// �ر��ļ�
	file.close();
}


// ͳ������-ʵ��
int WorkerManager::get_EmpNum()
{
	// �����ļ�����������
	ifstream file;

	// ���Դ��ļ�
	file.open(FILENAME, ios::in);

	int id;
	string name;
	int dID;

	// ��¼����
	int num = 0;

	// ѭ���������
	while (file >> id && file >> name && file >> dID)
	{
		num++;		// ��¼����
	}

	// �ر��ļ�
	file.close();

	return num;
}


// ��ʼ��ְ��-ʵ��
void WorkerManager::init_Emp()
{
	// �����ļ�����������
	ifstream file;

	// ���Դ��ļ�
	file.open(FILENAME, ios::in);

	int id;
	string name;
	int dID;

	int index = 0;
	while (file >> id && file >> name && file >> dID)
	{
		// ����ְ��ָ��
		Worker* worker = NULL;

		// ���ݲ�ͬ�Ĳ���id������ͬ����
		if (dID == 1)	// ��ͨԱ��
		{
			worker = new Employee(id, name, dID);
		}
		else if (dID == 2)	// ����
		{
			worker = new Manager(id, name, dID);
		}
		else	// �ϰ�
		{
			worker = new Boss(id, name, dID);
		}

		// �����������
		this->m_EmpArray[index] = worker;
		index++;
	}

}


// ��ʾְ��-ʵ�� {����}
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		return;
	}

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		// ���ö�̬���ýӿ�
		this->m_EmpArray[i]->shoInfo();
	}
}


// ְ���������ж�-ʵ��
int WorkerManager::isExist(int id)
{
	/*
		param:id : ��ȡҪ�����жϵ�ְ�����
		param:return : -1 ���� �����е�λ��
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
		param:name : ��ȡҪ�����жϵ�ְ������
		param:return : -1 ���� �����е�λ��
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


// ɾ��ְ��-ʵ�� {����}
void WorkerManager::Del_Emo()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		return;
	}

	// ��ȡҪɾ����ְ���ı��
	int id;
	cout << "��������Ҫɾ��ְ���ı�ţ�";
	cin >> id;
	int index = this->isExist(id);

	// �ж��Ƿ���ڸ�ְ��
	if (index == -1)
	{
		cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
		return;
	}

	// ְ�����ڣ�����ɾ������������ǰ�ƣ�
	// 1. �ͷŸ�ָ��ָ��Ķ���
	delete this->m_EmpArray[index];

	// 2. ָ�����������ָ��������ǰ�ƶ�
	for (int i = index; i < this->m_EmpNum - 1; i++)
	{
		this->m_EmpArray[i] = this->m_EmpArray[i + 1];
	}

	// 3. ������Ա����
	this->m_EmpNum--;

	// ɾ�����������󣬽����µ�����ͬ�����ļ���
	this->save();

	// ��ʾ��Ϣ
	cout << "ɾ���ɹ�" << endl;
}


// �޸�ְ��-ʵ�� {����}
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		return;
	}

	int id;
	string name;
	int dID;

	// ��ȡҪ�޸ĵ�ְ���ı��
	cout << "��������Ҫ�޸�ְ���ı�ţ�";
	cin >> id;
	int index = this->isExist(id);

	// �ж��Ƿ���ڸ�ְ��
	if (index == -1)
	{
		cout << "�޸�ʧ�ܣ�δ�ҵ���ְ����" << endl;
		return;
	}

	// ְ�����ڣ������޸Ĳ���

	// 1. ��ȡ�޸�����
	cout << "�������µ�ְ����ţ�";
	cin >> id;
	cout << "�������µ�������";
	cin >> name;
	cout << "�������λ��" << endl;
	cout << "1. ��ְͨ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. �ϰ�" << endl;
	cout << ">>> ";
	cin >> dID;

	// 2. �����µ�ְ������ָ��
	Worker* worker = NULL;

	// 3. �����޸ĺ�Ľ����������Ӧ��ְ������
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

	// 4. �ͷ�ԭָ����ָ��Ķ���
	delete this->m_EmpArray[index];

	// 5. ������ָ�뵽ָ��������
	this->m_EmpArray[index] = worker;

	// �޸Ĳ��������󣬽����µ�����ͬ�����ļ���
	this->save();

	// ��ʾ��Ϣ
	cout << "�޸ĳɹ�" << endl;
}


// ����ְ��-ʵ�� {����}
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		return;
	}

	// ѡ����ҷ�ʽ
	int select;
	cout << "��������ҵķ�ʽ��" << endl;
	cout << "1. ��ְ����Ų���" << endl;
	cout << "2. ����������" << endl;
	cout << ">>> ";
	cin >> select;

	// ��ȡҪ���ҵ�ְ����Ż����������жϸ�ְ���Ƿ����
	int id;
	string name;
	int index;

	if (select == 1)
	{
		cout << "������Ҫ���ҵ�ְ����ţ�";
		cin >> id;
		index = isExist(id);
	}
	else if (select == 2)
	{
		cout << "������Ҫ���ҵ�ְ��������";
		cin >> name;
		index = isExist(name);
	}
	else
	{
		cout << "����ʧ�ܣ�����ѡ������" << endl;
		return;
	}

	if (index == -1)
	{
		cout << "���޴���" << endl;
		return;
	}

	// ְ�����ڣ������Ӧ��Ϣ
	this->m_EmpArray[index]->shoInfo();
}


// ����ְ��-ʵ�� {����}
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		return;
	}

	// ��ȡѡ��ʽ
	cout << "��ѡ������ʽ��" << endl;
	cout << "1. ��ְ���Ž�����������" << endl;
	cout << "2. ��ְ���Ž��н�������" << endl;
	cout << ">>> ";
	int select = 0;
	cin >> select;

	// ʹ�����ã������������
	Worker**& arr = this->m_EmpArray;
	int& num = this->m_EmpNum;

	// �������
	switch (select)
	{
	case 1:
		// ��������
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
		// ��������
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
		cout << "����ʧ�ܣ�ѡ��ʽ����" << endl;
		return;
	}

	// �޸Ĳ��������󣬽����µ�����ͬ�����ļ���
	this->save();

	// ��ʾ������
	this->Show_Emp();
}


// ����ļ�-ʵ�� {����}
void WorkerManager::Purge_File()
{
	int select;
	cout << "�˲��������档�Ƿ�ȷ����գ�" << endl;
	cout << "1. ȷ��" << endl;
	cout << "2. ����" << endl;
	cout << ">>> ";
	cin >> select;

	// �ٴ�ȷ�ϲ���
	if (select == 1)
	{
		string confirm;
		cout << "�����·����룺��պ��޷��ָ�����ȷ�����" << endl;
		cout << ">>> ";
		cin >> confirm;
		if (confirm != "��պ��޷��ָ�����ȷ�����")		return;
	}

	// ִ����ղ���
	if (select == 1)
	{
		// ---------------- ����ļ��е����� ----------------
		// ͨ��"��ģʽ"����ɾ��������ļ�������ɾ���ļ��������´�����ios::trunc
		ofstream file(FILENAME, ios::trunc);
		file.close();

		// ---------------- ����ڴ��е����� ----------------
		// 1. ָ��������û�����ݣ��ڴ���û�����ݣ�
		if (this->m_EmpArray == NULL)
		{
			cout << "����ɹ�" << endl;
			return;
		}

		// 2. ָ�������������ݣ��ڴ��������ݣ�
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];		// ָ�������е�ÿһ��ָ����ָ���ְ�������ͷ�
			}
			delete[] this->m_EmpArray;			// ָ�����鱻�ͷ�
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}

		// ��ʾ��Ϣ
		cout << "����ɹ�" << endl;
	}
}