#include "workerManager.h"

using namespace std;


int main()
{
	// ʵ����һ�������߶���
	WorkerManager wm;
	int choose = 0;

	while (true)
	{
		// 1. չʾ�˵�
		wm.Show_Menu();

		// 2. ��ȡ�û�ѡ��Ĺ��ܱ��
		cout << "����������ѡ��";
		cin >> choose;

		// 3. ִ�о��幦��
		switch (choose)
		{
		case 0:		// �˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1:		// ���ְ��
			wm.Add_Emp();
			break;
		case 2:		// ��ʾְ��
			wm.Show_Emp();
			break;
		case 3:		// ɾ��ְ��
			wm.Del_Emo();
			break;
		case 4:		// �޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:		// ����ְ��
			wm.Find_Emp();
			break;
		case 6:		// ����ְ��
			wm.Sort_Emp();
			break;
		case 7:		// ����ļ�
			wm.Purge_File();
			break;
		default:
			break;
		}

		// 4. ��ͣ����
		system("pause");

		// 5. �����Ļ
		system("cls");
	}

	return 0;
}