#pragma once

class Registration
{
public:

	/*Некоторые необходимые переменные*/

	//Индикатор доступа
	bool Access = false;

	//Ник в MD5
	string nickname_md5 = "";

private:
	
	//Метод специальной записи моб. тела.
	static void zvezda_number(string &mobile);

	//Метод создания индивидуального Номера Читательского Билета
	string new_card_number();

	//Проверка на то, знает ли Админ код или нет. Если нет - то он Пользователь
	void access(bool &acc);

	//Проверка на неповторение логинов
	bool similarLogin(string &logpass, bool &rights);

	//Проверка ввода пароля
	void checkPassword(fstream &file);

	//Регистрация
	void signUp();

	//Получение личных данных
	friend void get_change_PersonalData(string &address, string &FIO, string &mobile, string get_change);

public:

	/*Основной набор методов*/
	
	//Преобразование пароля в звёздочки
	string zvezda(string text = "");

	//Авторизация
	fstream logIn(bool &Access, bool change);

	//Вход в систему
	fstream signIn();
};