#include"Headers.h"

void AdminsPossibilities::increacetoAdmin(fstream &file)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "Ошибка!Файл не был открыт!";
		_getch();
		exit(EXIT_FAILURE);
	}
	cout << "Введите имя Пользователя: ";
	string username = "";
	cin >> username;
	string spforAnsw = username;
	username = md5(username);
	ifstream oldUser("Users\\" + username);
	if (!(oldUser.is_open()))
	{
		Label::_tag();
		cerr << "Пользователь с таким именем не найден!" << endl;
		_getch();
		return;
	}
	else
	{
		fstream newAdmin("Administrators\\" + username);
		if (newAdmin.is_open())
		{
			Label::_tag();
			cerr << "Администратор с таким именем уже существует!" << endl;
			_getch();
			return;
		}
		else
		{
			newAdmin.close();
			newAdmin.open("Administrators\\" + username, ios_base::out);
			oldUser.seekg(0, ios::beg);
			string copy = "";
			while (!oldUser.eof())
			{
				getline(oldUser, copy);
				newAdmin << copy << endl;
			}
			oldUser.close();
			newAdmin << endl << "Был повышен до Администратора!";
			newAdmin.close();
			Label::_tag();
			string path = "Users\\" + username;
			if (remove(path.c_str())) cerr << "Внимание! Файл \"старого\" Пользователя не был удалён!" << endl;
			else                      cout << endl << "Пользователь " << spforAnsw << " теперь Администратор!";
		}
	}
	_getch();
}

void AdminsPossibilities::changeAdmin(Registration *&enter, fstream &file)
{
	file.close();
	file = enter->logIn(enter->Access = true, false);
}

void AdminsPossibilities::for_freeze_thawed(string str1, string str2, char ch)
{
	string login = "";
	cout << "Логин для " << str1 << ": ";
	cin >> login;
	fstream file("Users\\" + md5(login));
	Label::_tag();
	if (!(file.is_open()))
		cerr << "Такого Пользователя не существует!";
	else
	{
		numberofstring(file, 3);
		file.seekp(file.tellg(), ios::beg);
		file << ch;
		cout << "Пользователь " << str2 << '!';
		file.seekp(0, ios::end);
		file << endl << "Был " << str2 << " Администратором!";
		file.close();
	}
	_getch();
}

void AdminsPossibilities::userlist()
{
	ifstream file("userlist");
	if (!file.is_open())
	{
		Label::_tag();
		cerr << "На данный момент ни один пользователь не зарегистрирован!" << endl;
		_getch();
		return;
	}
	size_t userNumber = 0;
	string user = "";
	cout << "Зарегестрированные пользователи: " << endl << "--------------------------------------------------------" << endl;
	file.seekg(0, ios::beg);
	while (!file.eof())
	{
		getline(file, user);
		cout << user << endl;
		userNumber++;
	}
	cout << "--------------------------------------------------------" << endl
		<< "Количество Пользователей: " << userNumber << endl;
	file.close();
	_getch();
}

void AdminsPossibilities::check_User()
{
	string name = "";
	cout << "Введите имя пользователя: ";
	cin >> name;
	name = md5(name);
	ifstream file("Users\\" + name);
	bool exist = file.is_open();
	file.close();
	if (exist) cout << "\nПользователь Существует!";
	else cout << "\nПользователь НЕ Существует!";
	_getch();
}

void AdminsPossibilities::addBook(fstream &file)
{
	fstream book;
	string genre = "";
	chooseGenre(book, genre);
	if (!book.is_open())
		return;
	char *author = NULL, *bookname = NULL;
	string year = "";
	while (true)
	{
		Label::_tag();
		author = new char[30];
		bookname = new char[50];
		cout << "Добавление книги в жанр " << genre << ':' << endl
			<< "---------------------------------------" << endl
			<< "Введите данные об Авторе: ";
		fflush(stdin);
		rewind(stdin);
		gets_s(author, 30);
		cout << "Введите название произведения: ";
		fflush(stdin);
		rewind(stdin);
		gets_s(bookname, 50);
		bool flag = publishingYear(year);
		if (!flag)
			delete author, bookname, year;
		else
		{
			cout << "---------------------------------------" << endl << endl
				<< "Проверьте верны ли данные(Изменить данные - \"-\", любая клавиша - \"продолжить\"):\n--> " << author << " - \"" << bookname << "\" " << year << endl;
			char ch = _getch();
			if (ch != '-')
				break;
			delete author, bookname;
		}
	}
	book.seekp(0, ios::end);
	book << endl << author << " - \"" << bookname << "\" " << year;
	delete author, bookname;
	book.close();
	file.seekp(0, ios::end);
	file << endl << "Новая книга была добавлена в базу!";
	Label::_tag();
	cout << "Новая книга жанра " << genre << " успешно добавлена в базу!" << endl;
	_getch();
}

bool AdminsPossibilities::publishingYear(string &year)
{
	bool flag;
	do
	{
		flag = false;
		try
		{
			cout << "Введите год написания произведения: ";
			cin >> year;
			size_t size = year.size();
			if (size < 3 || size > 4) throw false;
			if (size == 3)
			{
				if ('1' > year[0] || year[0] > '9' || '0' > year[1] || year[1] > '9' || '0' > year[2] || year[2] > '9')
					throw false;
				else  throw true;
			}
			else if (size == 4)
			{
				if ('1' > year[0] || year[0] > '2' || '0' > year[1] || year[1] > '9' || '0' > year[2] || year[2] > '9' || '0' > year[3] || year[3] > '9')
					throw false;
				else
				{
					if (stoi(year) > 2016)
						throw false;
					else
						throw true;
				}
			}
		}
		catch (bool a)
		{
			if (a)
				flag = true;
			else
			{
				cout << endl << "Неверный ввод!" << endl;
				_getch();
			}
			break;
		}
	} while (true);
	return flag;
}

void AdminsPossibilities::removeBook(fstream &file)
{
	fstream book;
	string genre = "";
	string path = chooseGenre(book, genre);
	if (!book.is_open())
		return;
	size_t booknumber;
	do
	{
		Label::_tag();
		cout << "Список книг жанра " << genre << ':' << endl
			<< "-------------------------------------------" << endl;
		size_t count = 0;
		string book_name = "";
		book.seekg(0, ios::beg);
		while (!book.eof())
		{
			getline(book, book_name);
			cout << '<' << ++count << "> " << book_name << endl;
		}
		if (!count)
		{
			cout << "(пусто)" << endl
				<< "-------------------------------------------" << endl;
			_getch();
			return;
		}
		cout << "-------------------------------------------" << endl
			 << endl << "Удалить книгу №:";
		booknumber = checkInput(count);
	} while (!booknumber);
	refreshFile(book, path, booknumber);
	file.seekp(0, ios::end);
	file << endl << "Книга была удалена из базы!";
	Label::_tag();
	cout << "Книга жанра " << genre << " успешно удалена из базы!" << endl;
	_getch();
}

void AdminsPossibilities::sort()
{

}

void AdminsPossibilities::refreshFile(fstream &book, string &path, size_t &linenumber)
{
	if (!(book.is_open()))
	{
		book.close();
		Label::_tag();
		cerr << "Ошибка!Файл не был открыт!";
		_getch();
		exit(EXIT_FAILURE);
	}
	fstream refreshfile(path + ".temp", ios_base::out);
	book.seekg(0, ios::beg);
	refreshfile.seekp(0, ios::beg);
	string old_path = path;
	string new_path = path + ".temp";

	char copy_char;
	for (size_t i(0); i < linenumber - 1; i++)
	{
		do
		{
			book.get(copy_char);
			refreshfile.put(copy_char);
		} while (copy_char != '\n');
	}
	

	do//Пропуск строки
	{
		if (book.eof())
			break;
		book.get(copy_char);
	} while (copy_char != '\n');


	if (!book.eof())
	{
		book.get(copy_char);
		while (!book.eof())
		{
			refreshfile.put(copy_char);
			book.get(copy_char);
		}
	}
	book.close();
	refreshfile.close();
	remove(old_path.c_str());
	rename(new_path.c_str(), old_path.c_str());
}

void AdminsPossibilities::list(Registration *&enter, fstream &file)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "Ошибка!Файл не был открыт!";
		_getch();
		exit(EXIT_FAILURE);
	}
	do
	{
		string input = "";
		do
		{
			Label::_tag();
			cout << "Возможности Администратора: "                    << endl
				 << "<0>  -  Выход"                                   << endl
				 << "<1>  -  Взять книгу"                             << endl
				 << "<2>  -  Сдать книгу"                             << endl
				 << "<3>  -  Добавить книгу в базу"				      << endl
				 << "<4>  -  Удалить книгу из базы"					  << endl
				 << "<5>  -  История операций"                        << endl
			     << "<6>  -  Личные данные"							  << endl
				 << "<7>  -  Сменить пароль"                          << endl
				 << "<8>  -  Повысить до Администратора"              << endl
				 << "<9>  -  Заморозить доступ Пользователю"          << endl
				 << "<10> -  Разморозить доступ Пользователю"         << endl
				 << "<11> -  Сменить Администратора"                  << endl
				 << "<12> -  Список всех Пользователей"               << endl
				 << "<13> -  Проверить Пользователя на существование" << endl
				 << "--> ";
			try
			{
				cin >> input;
				if (input.size() > 2) throw 0;
				if (input.size() == 1)
				{
					if ('0' > input[0] || input[0] > '9')
						throw 0;
					else  throw 1;
				}
				else if (input.size() == 2)
				{
					if ('1' > input[0] || input[0] > '1' || '0' > input[1] || input[1] > '3')
						throw 0;
					else  throw 1;
				}
			}
			catch (int i) { if (i) break; }
		} while (true);
		Label::_tag();
		switch (stoi(input))
		{
		case 0:
		cout << "Хорошего дня!";
		_getch();
		file.close();
		return;
		case 1:  UsersPossibilities::get_book(file);				    break;
		case 2:  UsersPossibilities::put_book(enter, file);			    break;
		case 3:  AdminsPossibilities::addBook(file);					break;
		case 4:  AdminsPossibilities::removeBook(file);					break;
		case 5:  UsersPossibilities::historyofOperations(file);		    break;
		case 6:  UsersPossibilities::change_Personal_Data(enter, file); break;
		case 7:  UsersPossibilities::changePassword(enter, file);	    break;
		case 8:  AdminsPossibilities::increacetoAdmin(file);		    break;
		case 9:  AdminsPossibilities::freeze();						    break;
		case 10: AdminsPossibilities::thawed();						    break;
		case 11: AdminsPossibilities::changeAdmin(enter, file);		    break;
		case 12: AdminsPossibilities::userlist();					    break;
		case 13: AdminsPossibilities::check_User();					    break;
		}
	} while (true);
}