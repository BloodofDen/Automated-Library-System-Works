#include"Headers.h"

string Registration::zvezda(string text)
{
	do
	{
		char *pass = new char[16];
		pass[0] = '\0';
		char elem;
		size_t counter = 0;
		cout << "��� " << text << "������(�� 6 �� 16 ��������): ";
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
				cout << endl << "������� �������� ������, ���������� ���������!" << endl << endl;
				delete[] pass;
			}
			if (counter > 15)
			{
				cout << endl << "������� ������� ������, ���������� ���������!" << endl << endl;
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
	cout << "����� ��������(12 ����): +375 (";
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
		cout << "����� ������������������ ��� �������������, ��� ���������� ����� ��������� ����!" << endl
			 << "���������� ���������� �������: " << i << endl
			 << "������� ��������� ���� --> ";
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
		cerr << endl << "�� ������ ����!\n";
		_getch();
		}
	} while (i > 0);
	cout << endl << "������ ����!\n";
	_getch();
	Label::_tag();
	if (acc) cout << "����������� ��������������: " << endl;
	else		cout << "����������� ������������: " << endl;
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
		cerr << "���� �� ��� ������!" << endl;
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
			cerr << "������ ����� �� �����, ����������, ���������!" << endl;
			cout << "���������: ";
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
				cerr << "��� ������� ������������!\n��� ������� ���������� � ��������������!";
				_getch();
				exit(EXIT_SUCCESS);
			}
			cout << "���� �������� �������!";
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
		cout << "<0> - �����\n<1> - ����������� ������������\n<2> - ����������� ��������������\n--> ";
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
		if(acc) cout << "����������� ��������������: " << endl;
		else    cout << "����������� ������������: " << endl;
		cout << "��� �����: ";
		cin >> logpass;
		userlist = logpass;
		logpass = md5(logpass);
		if (is_similar = similarLogin(logpass, acc))
			cerr << endl << "����� ����� ��� ����������! ����������, ���������!" << endl;
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
		cerr << "���� �� ����� ���� ������!" << endl;
		_getch();
		exit(EXIT_FAILURE);
	}
	do
	{
		logpass = zvezda();
		cout << "��������� ������ ��� ���" << endl;
		string check = zvezda();
		if (check != logpass)
			cerr << "������ �� �������, ���������� ���������!\n" << endl;
		else break;
	} while (true);
	cout << endl << "��������� � ������(���� �� �������� ������, ��� ����������� ���������): ";
	char *prompt = new char[20];
	cin >> prompt;
	Label::_tag();
	if (acc) cout << "������������� ������� ���������������!";
	else     cout << "������������ ������� ���������������!";
	_getch();
	string number_of_library_card = new_card_number();
	string FIO = "", address = "", mobile = "";
	get_change_PersonalData(address, FIO, mobile, "������������ ����");
	file << md5(logpass) << endl
		 << static_cast<string>(prompt) << endl
		 << "0" << endl
		 << "������������ ����� � " << number_of_library_card << endl
		 << FIO << endl
		 << address << endl
		 << mobile;
	file.close();
	Label::_tag();
	cout << "������ ������ ������� ���������!" << endl;
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
			cout << "<0> - �����\n<1> - ����� ��� ������������\n<2> - ����� ��� �������������\n--> ";
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
	cout << "��� �����: ";
	cin >> login;
	login = md5(login);
	if (Access) file.open("Administrators\\" + login);
	else        file.open("Users\\" + login);
	if (!(file.is_open()))
	{
		Label::_tag();
		if(Access)	cerr << "������ �������������� �� ����������, �������� �����������!";
		else        cerr << "������ ������������ �� ����������, �������� �����������!";
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
			cout << "<0> - �����" << endl
				 << "<1> - ������ �����������" << endl
				 << "<2> - ����� � ������� ������" << endl
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
		cout << get_change << " ������ ������:" << endl
			<< "-------------------" << endl
			<< "���: ";
		cin >> name;
		cout << "�������: ";
		cin >> lastname;
		cout << "��������: ";
		cin >> patronymic;
		cout << "-------------------" << endl;
		cout << "�������� �����: ";
		cin >> street;
		cout << "����� ����: ";
		cin >> build;
		cout << "����� ��������(0 - ���� ������� ���): ";
		cin >> flat;
		if (flat[0] == '0') flat = "(������� ���)";
		cout << "-------------------" << endl;
		Registration::zvezda_number(mobile);
		Label::_tag(); 
		cout << endl << "��������� ����� �� ������(�������� ������ - \"-\", ����� ������� - \"����������\"): " << endl << endl
			<< lastname << ' ' << name << ' ' << patronymic << endl
			<< "��." << street << " �." << build << " ��." << flat << endl
			<< mobile;
	} while ('-' == _getch());
	FIO = lastname + " " + name + " " + patronymic;
	address = "��." + street + " �." + build + " ��." + flat;
}