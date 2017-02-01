#include"Headers.h"

string Registration::zvezda(string text)
{
	do
	{
		char *pass = new char[16];
		pass[0] = '\0';
		char elem;
		size_t counter = 0;
		cout << "Ваш " << text << "пароль(от 6 до 16 символов): ";
		do
		{
			elem = _getch();
			switch (elem)
			{
			case 8:
			{
				if (counter)
				{
					swap(pass[counter], pass[counter - 1]);
					counter--;
					cout << "\b \b";
				}
			}break;
			case 13:break;
			default:
			{
				if (counter < 15)
				{
					swap(pass[counter], pass[counter + 1]);
					pass[counter] = elem;
					cout << '*';
				}
				if (counter == 15)
				{
					pass[counter] = elem;
					cout << '*';
				}
				counter++;
			}
			}
			if (elem == 13) break;
			if (counter > 15) break;
		} while (true);
		if (counter < 6 || counter > 15)
		{
			if (counter < 6)
			{
				cout << endl << "Слишком короткий пароль, пожалуйста повторите!" << endl << endl;
				delete[] pass;
			}
			if (counter > 15)
			{
				cout << endl << "Слишком длинный пароль, пожалуйста повторите!" << endl << endl;
				delete[] pass;
			}
		}
		else
		{
			cout << endl;
			return (static_cast<string>(pass));
		}
	} while (true);
}

void Registration::zvezda_number(string &mobile)
{
	char number;
	int counter = 3;
	char *pass = new char[13];
	pass[0] = '3'; pass[1] = '7'; pass[2] = '5';
	pass[3] = '\0';
	cout << "Номер телефона(12 цифр): +375 (";
	do
	{
		number = _getch();
		switch (number)
		{
		case 8:
		{
			if (counter)
			{
				swap(pass[counter], pass[counter - 1]);
				counter--;
				cout << "\b \b";
			}
		}break;
		default:
		{
			swap(pass[counter], pass[counter + 1]);
			pass[counter] = number;
			counter++;
			cout << number;
			if (counter == 12)
			{
				cout << endl;
				mobile = "+" + static_cast<string>(pass);
				delete[] pass;
				return;
			}
			if (counter == 5)
				cout << ") ";
			if (counter == 8)
				cout << '-';
			if (counter == 10)
				cout << '-';
		}
		}
	} while (true);
}

string Registration::new_card_number()
{
	string temp = "";
	fstream quantity("quantity", ios_base::in);
	quantity.seekg(0, ios::beg);
	getline(quantity, temp); 
	quantity.close();
	quantity.open("quantity", ios_base::out | ios_base::trunc);
	quantity.seekp(0, ios::beg);
	size_t number = stoi(temp) + 1;
	quantity << number;
	quantity.close();
	return ("4507829" + to_string(number));
}

void Registration::access(bool &acc)
{
	int i = 3;
	do
	{
		Label::_tag();
		string code = "";
		cout << "Чтобы зарегистрироваться как Администратор, вам необходимо знать секретный ключ!" << endl
			 << "Оставшееся количество попыток: " << i << endl
			 << "Введите секретный ключ --> ";
		try
		{
			cin >> code;
			if (code.size() == 3 && code[0] == '6' && code[1] == '6'  && code[2] == '6') throw true;
			else																		 throw false;
		}
		catch (bool a) 
		{ 
			if (a) { acc = true; break; }
		i--;
		cerr << endl << "НЕ верный ключ!\n";
		_getch();
		}
	} while (i > 0);
	cout << endl << "Верный ключ!\n";
	_getch();
	Label::_tag();
	if (acc) cout << "Регистрация Администратора: " << endl;
	else		cout << "Регистрация Пользователя: " << endl;
}

bool Registration::similarLogin(string &logpass, bool &rights)
{
	ifstream file;
	if (rights) file.open("Administrators\\" + logpass);
	else        file.open("Users\\" + logpass);
	bool exist = file.is_open();
	file.close();
	return (exist);
}

void Registration::checkPassword(fstream &file)
{
	if (!file.is_open())
	{
		Label::_tag();
		cerr << "Файл не был открыт!" << endl;
		_getch();
		exit(EXIT_FAILURE);
	}
	string str = "";
	file.seekg(0, ios_base::beg);
	getline(file, str);
	string prompt = "";
	bool prompt_bool = true;
	do
	{
		string password = zvezda();
		password = md5(password);
		if (str != password)
		{
			cerr << "Пароль введён не верно, пожалуйста, повторите!" << endl;
			cout << "Подсказка: ";
			if (prompt_bool)
			{
				getline(file, prompt);
				prompt_bool = false;
			}
			cout << prompt << endl << endl;
		}
		else
		{
			Label::_tag();
			file.seekg(0, ios::beg);
			string freeze = "";
			for (int i(0); i < 5; i++)
				getline(file, freeze);
			if (freeze[0] == '1')
			{
				cerr << "Ваш аккаунт Заблокирован!\nВам следует обратиться к Администратору!";
				_getch();
				exit(EXIT_SUCCESS);
			}
			cout << "Вход выполнен успешно!";
			break;
		}
	} while (true);
	_getch();
}

void Registration::signUp()
{
	string input = "";
	bool acc;
	do
	{
		Label::_tag();
		cout << "<0> - Назад\n<1> - Регистрация Пользователя\n<2> - Регистрация Администратора\n--> ";
		try
		{
			cin >> input;
			if (input.size() > 1 || '0' > input[0] || input[0] > '2') throw 0;
			else                                                      throw 1;
		}
		catch (int i) { if (i) break; }
	} while (true);
	switch (input[0])
	{
	case '0': return;
	case '1': acc = false; break;
	case '2': access(acc); break;
	}
	string logpass = "";
	string userlist = "";
	bool is_similar;
	do
	{
		Label::_tag();
		if(acc) cout << "Регистрация Администратора: " << endl;
		else    cout << "Регистрация Пользователя: " << endl;
		cout << "Ваш логин: ";
		cin >> logpass;
		userlist = logpass;
		logpass = md5(logpass);
		if (is_similar = similarLogin(logpass, acc))
			cerr << endl << "Такой логин уже существует! Пожалуйста, повторите!" << endl;
	} while (is_similar);
	fstream file;
	if (acc)
		file.open("Administrators\\" + logpass, ios_base::out);
	else 
	{
		file.open("userlist", ios_base::out | ios_base::app);
		file << userlist << endl;
		file.close();
		file.open("Users\\" + logpass, ios_base::out);
	}
	if (!file.is_open())
	{
		Label::_tag();
		cerr << "Файл не может быть создан!" << endl;
		_getch();
		exit(EXIT_FAILURE);
	}
	do
	{
		logpass = zvezda();
		cout << "Повторите пароль еще раз" << endl;
		string check = zvezda();
		if (check != logpass)
			cerr << "Пароли не совпали, пожалуйста повторите!\n" << endl;
		else break;
	} while (true);
	cout << endl << "Подсказка к паролю(если вы забудите пароль, вам высветиться подсказка): ";
	char *prompt = new char[20];
	cin >> prompt;
	Label::_tag();
	if (acc) cout << "Администратор успешно зарегистрирован!";
	else     cout << "Пользователь успешно зарегистрирован!";
	_getch();
	string number_of_library_card = new_card_number();
	string FIO = "", address = "", mobile = "";
	get_change_PersonalData(address, FIO, mobile, "Обязательный ввод");
	file << md5(logpass) << endl
		 << static_cast<string>(prompt) << endl
		 << "0" << endl
		 << "Читательский билет № " << number_of_library_card << endl
		 << FIO << endl
		 << address << endl
		 << mobile;
	file.close();
	Label::_tag();
	cout << "Личные данные успешно заполнены!" << endl;
	_getch();
}


fstream Registration::logIn(bool &Access, bool change)
{
	fstream file;
	if (change)
	{
		string input = "";
		do
		{
			Label::_tag();
			cout << "<0> - Назад\n<1> - Войти как Пользователь\n<2> - Войти как Администратор\n--> ";
			try
			{
				cin >> input;
				if (input.size() > 1 || '0' > input[0] || input[0] > '2') throw 0;
				else                                                      throw 1;
			}
			catch (int i) { if (i) break; }
		} while (true);
		switch (input[0])
		{
		case '0': return file;
		case '1': break;
		case '2': Access = true; break;
		} 
		Label::_tag();
	}
	string login;
	cout << "Ваш логин: ";
	cin >> login;
	login = md5(login);
	if (Access) file.open("Administrators\\" + login);
	else        file.open("Users\\" + login);
	if (!(file.is_open()))
	{
		Label::_tag();
		if(Access)	cerr << "Такого Администратора не существует, пройдите регистрацию!";
		else        cerr << "Такого Пользователя не существует, пройдите регистрацию!";
		Access = false;
		file.close();
		_getch();
		return file;
	}
	else
	{
		file.close();
		if (Access) file.open("Administrators\\" + login, ios_base::in | ios_base::out);
		else        file.open("Users\\" + login, ios_base::in | ios_base::out);
	}
	Registration::checkPassword(file);
	nickname_md5 = login;
	return file;
	_getch();
}

fstream Registration::signIn()
{
	_mkdir("Users");
	_mkdir("Administrators");
	fstream file("quantity", ios_base::in);
	if (!file.is_open())
	{
		file.close();
		file.open("quantity", ios_base::out);
		file.put('0');
		file.close();
	}
	else file.close();
	while (true)
	{
		string input = "";
		do
		{
			Label::_tag();
			cout << "<0> - Выход" << endl
				 << "<1> - Пройти регистрацию" << endl
				 << "<2> - Войти в учётную запись" << endl
				 << "--> ";
			try
			{
				cin >> input;
				if (input.size() > 1 || '0' > input[0] || input[0] > '2') throw 0;
				else                                                      throw 1;
			}
			catch (int i) { if (i) break; }
		} while (true);
		switch (input[0])
		{
		case '0': return file;
		case '1': Registration::signUp(); break;
		case '2': file = Registration::logIn(Access, true); break;
		}      
		Label::_tag();
		if (file.is_open()) break;
	}
	return file;
}

void get_change_PersonalData(string & address, string & FIO, string & mobile, string get_change)
{
	string street = "", flat = "", build = "";
	string name = "", lastname = "", patronymic = "";
	do
	{
		Label::_tag();
		cout << get_change << " личных данных:" << endl
			<< "-------------------" << endl
			<< "Имя: ";
		cin >> name;
		cout << "Фамилия: ";
		cin >> lastname;
		cout << "Отчество: ";
		cin >> patronymic;
		cout << "-------------------" << endl;
		cout << "Название Улицы: ";
		cin >> street;
		cout << "Номер Дома: ";
		cin >> build;
		cout << "Номер Квартиры(0 - если частный дом): ";
		cin >> flat;
		if (flat[0] == '0') flat = "(частный дом)";
		cout << "-------------------" << endl;
		Registration::zvezda_number(mobile);
		Label::_tag(); 
		cout << endl << "Проверьте верны ли данные(Изменить данные - \"-\", любая клавиша - \"продолжить\"): " << endl << endl
			<< lastname << ' ' << name << ' ' << patronymic << endl
			<< "ул." << street << " д." << build << " кв." << flat << endl
			<< mobile;
	} while ('-' == _getch());
	FIO = lastname + " " + name + " " + patronymic;
	address = "ул." + street + " д." + build + " кв." + flat;
}