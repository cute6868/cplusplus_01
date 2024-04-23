#include "workerManager.h"

using namespace std;


int main()
{
	// 实例化一个管理者对象
	WorkerManager wm;
	int choose = 0;

	while (true)
	{
		// 1. 展示菜单
		wm.Show_Menu();

		// 2. 获取用户选择的功能编号
		cout << "请输入您的选择：";
		cin >> choose;

		// 3. 执行具体功能
		switch (choose)
		{
		case 0:		// 退出系统
			wm.ExitSystem();
			break;
		case 1:		// 添加职工
			wm.Add_Emp();
			break;
		case 2:		// 显示职工
			wm.Show_Emp();
			break;
		case 3:		// 删除职工
			wm.Del_Emo();
			break;
		case 4:		// 修改职工
			wm.Mod_Emp();
			break;
		case 5:		// 查找职工
			wm.Find_Emp();
			break;
		case 6:		// 排序职工
			wm.Sort_Emp();
			break;
		case 7:		// 清空文件
			wm.Purge_File();
			break;
		default:
			break;
		}

		// 4. 暂停界面
		system("pause");

		// 5. 清空屏幕
		system("cls");
	}

	return 0;
}