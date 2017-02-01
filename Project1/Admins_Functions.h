#pragma once

class AdminsPossibilities:protected UsersPossibilities
{
private:

	//Основной метод заморозки/разиорозки Пользователя
	void for_freeze_thawed(string str1, string str2, char ch);

	//Перегруженный метод обновления информации базы книг
	void refreshFile(fstream &file, string &path, size_t &linenumber);

	//Проверка на правильность ввода данных новой книги
	bool publishingYear(string &year);

	//Повысить Пользователя до Администратора
	void increacetoAdmin(fstream &file);

	//Сменить Администратора
	void changeAdmin(Registration *&enter, fstream &file);

	//Список всех пользователей
	void userlist();

	//Заморозка
	void freeze() { for_freeze_thawed("блокировки", "заблокирован", '1'); }

	//Разморозка
	void thawed() { for_freeze_thawed("разблокировки", "разблокирован", '0'); }
	
	//Проверка существования пользователя
	void check_User();

	//Добавление книги
	void addBook(fstream &file);

	//Удаление книги
	void removeBook(fstream &file);

public:

	//Полный функционал Администратора
	void list(Registration *&enter, fstream &file);
};