#include "Headers.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Registration *enter = new Registration();
	fstream file = enter->signIn();
	if (file.is_open())
	{
		if (enter->Access)
		{
			AdminsPossibilities *admin = new AdminsPossibilities();
			admin->list(enter, file);
			delete admin;
		}
		else
		{
			UsersPossibilities *user = new UsersPossibilities();
			user->list(enter, file);
			delete user;
		}

	}
	delete enter;
	return 0;
}