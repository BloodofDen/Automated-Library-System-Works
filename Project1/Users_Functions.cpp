#include"Headers.h"
fstream UsersPossibilities::refreshFile(Registration *&enter, fstream &file, string changes, size_t linenumber)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "������!���� �� ��� ������!";
		_getch();
		exit(EXIT_FAILURE);
	}
	fstream refreshfile;
	string old_path = "";
	string new_path = "";
	char copy_char;
	if (enter->Access)
	{
		refreshfile.open("Administrators\\" + enter->nickname_md5 + ".temp", ios_base::out);
		old_path = "Administrators\\" + enter->nickname_md5;
		new_path = "Administrators\\" + enter->nickname_md5 + ".temp";
	}
	else
	{
		refreshfile.open("Users\\" + enter->nickname_md5 + ".temp", ios_base::out);
		old_path = "Users\\" + enter->nickname_md5;
		new_path = "Users\\" + enter->nickname_md5 + ".temp";
	}
 	file.seekg(0, ios::beg);
	refreshfile.seekp(0, ios::beg);
	for (size_t i(0); i < linenumber - 1; i++)
	{
		do
		{
			file.get(copy_char);
			refreshfile.put(copy_char);
		} while (copy_char != '\n');
	}
	refreshfile << changes;
	
	do//������� ������
	{
		if (file.eof())
			break;
		file.get(copy_char);
	} while (copy_char != '\n');
	
	bool flag = true;
	if (!file.eof())
	{
		if (flag)
		{
			if (changes != "")
			{
				refreshfile.put('\n');
				flag = false;
			}
		}
		file.get(copy_char);
		while (!file.eof())
		{
			refreshfile.put(copy_char);
			file.get(copy_char);
		}
	}
	file.close();
	refreshfile.close();
	remove(old_path.c_str());
	rename(new_path.c_str(), old_path.c_str());
	if (enter->Access)	refreshfile.open("Administrators\\" + enter->nickname_md5, ios_base::in | ios_base::out);
	else                refreshfile.open("Users\\" + enter->nickname_md5, ios_base::in | ios_base::out);
	return refreshfile;
}

template<class Type> void numberofstring(Type &file, size_t n)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "������!���� �� ��� ������!";
		_getch();
		exit(EXIT_FAILURE);
	}
	char p;
	size_t i = 0;
	file.seekg(0, ios::beg);
	while (i < n - 1) 
	{
		do { 
			p = file.get(); 
		} while (p != '\n');
		i++;
	}
}

void UsersPossibilities::changePassword(Registration *&enter, fstream &file)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "������!���� �� ��� ������!";
		_getch();
		exit(EXIT_FAILURE);
	}
	string newpassword = enter->zvezda("����� ");
	file = refreshFile(enter, file, md5(newpassword), 1);
	string prompt = "";
	cout << "������� ����� ��������� � ������: ";
	cin >> prompt;
	file = refreshFile(enter, file, prompt, 2);
	Label::_tag();
	cout << "������ ������� ������!";
	file.seekp(0, ios::end);
	file << endl << "������ ��� ������� ������!";
	_getch();
}

void UsersPossibilities::historyofOperations(fstream &file)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "������!���� �� ��� ������!";
		_getch();
		exit(EXIT_FAILURE);
	}
	string hisory = "";
	bool empty = true;
	cout << "������� ��������: " << endl << "-------------------------------------------" << endl;
	numberofstring(file, 7);
	getline(file, hisory);
	while (!file.eof())
	{
		empty = false;
		getline(file, hisory);
		if (hisory == "0")
		{
			cout << "������: �����" << endl;
			if (file.eof())
				break;
			continue;
		}
		if (hisory == "1")
		{
			cout << "������: ����" << endl;
			if (file.eof())
				break;
			continue;
		}
		cout << hisory << endl;
	}
	file.seekg(0, ios::beg);
	if (empty)
		cout << "(�����)" << endl;
	cout << "-------------------------------------------" << endl;
	_getch();
}

void UsersPossibilities::change_Personal_Data(Registration *&enter, fstream &file)
{
	do
	{
		string input = "";
		do
		{
			Label::_tag();
			cout << "<0>  - �����" << endl
				<< "<1>  - �������� ������ ������" << endl
				<< "<2>  - �������� ������ ������" << endl
				<< "--> ";
			try
			{
				cin >> input;
				if (input.size() > 1 || '0' > input[0] || input[0] > '2')
					throw 0;
				else
					throw 1;
			}
			catch (int i) { if (i) break; }
		} while (true);
		switch (input[0])
		{
		case '0': return;
		case '1':
		{
			Label::_tag();
			string personalData = "";
			cout << "������� ������������ ������: " << endl
				<< "-----------------------------" << endl;
			numberofstring(file, 4);
			getline(file, personalData);
			for (size_t i(0); i < 3; i++)
			{
				cout << personalData << endl;
				getline(file, personalData);
			}
			cout << "-----------------------------" << endl;
		}break;
		case '2':
		{
			string FIO = "", address = "", mobile = "";
			get_change_PersonalData(address, FIO, mobile, "���������");
			file = refreshFile(enter, file, FIO, 5);
			file = refreshFile(enter, file, address, 6);
			file = refreshFile(enter, file, mobile, 7);
			file.seekp(0, ios::end);
			file << endl << "������ ������ ���� ��������!";
			Label::_tag();
			cout << "������ ������ ������� ��������!" << endl;
		}break;
		}
		_getch();
	} while (true);
}

string chooseGenre(fstream &book, string &genre)
{
	string input = "";
	string path = "";
	do
	{
		Label::_tag();
		cout << "�������� ����:"                << endl
			 << "-------------------------" << endl
			 << "<0>  - �����"              << endl
			 << "<1>  - �����������"        << endl
			 << "<2>  - �������"            << endl
			 << "<3>  - ��������"           << endl
			 << "<4>  - ���������"          << endl
			 << "<5>  - ����������"         << endl
			 << "<6>  - �������"            << endl
			 << "<7>  - �������"            << endl
			 << "<8>  - �����������"        << endl
			 << "<9>  - �������"            << endl
			 << "<10> - ����-�����������"   << endl
			 << "<11> - ����������� �����"  << endl
			 << "<12> - ������� ����������" << endl
			 << "<13> - �������/����"       << endl
			 << "<14> - ��������/�������"   << endl
			 << "-------------------------" << endl
			 << "--> ";
		try
		{
			cin >> input;
			switch (input.size())
			{
			case 1:
			{
				if ('0' > input[0] || input[0] > '9')
					throw 0;
				else  throw 1;
			}break;
			case 2:
			{
				if ('1' > input[0] || input[0] > '1' || '0' > input[1] || input[1] > '4')
					throw 0;
				else  throw 1;
			}break;
			default: throw 0; break;
			}
		}
		catch (int i) { if (i) break; }
	} while (true);
	switch (stoi(input))
	{
	case 0:  book.close(); return path;
	case 1:  path = "Books//adventure.txt";		   book.open(path, ios_base::in | ios_base::out);  genre = "�����������";        break;
	case 2:  path = "Books//children.txt";		   book.open(path, ios_base::in | ios_base::out);  genre = "�������";            break;
	case 3:  path = "Books//classic.txt";		   book.open(path, ios_base::in | ios_base::out);  genre = "��������";           break;
	case 4:  path = "Books//detective.txt";		   book.open(path, ios_base::in | ios_base::out);  genre = "���������";          break;
	case 5:  path = "Books//fantastic.txt";		   book.open(path, ios_base::in | ios_base::out);  genre = "����������";         break;
	case 6:  path = "Books//fantasy.txt";          book.open(path, ios_base::in | ios_base::out);  genre = "�������";            break;
	case 7:  path = "Books//horrors.txt";          book.open(path, ios_base::in | ios_base::out);  genre = "�������";            break;
	case 8:  path = "Books//modern.txt";	       book.open(path, ios_base::in | ios_base::out);  genre = "�����������";        break;
	case 9:  path = "Books//novel.txt";		       book.open(path, ios_base::in | ios_base::out);  genre = "�������";            break;
	case 10: path = "Books//post-apocalyptic.txt"; book.open(path, ios_base::in | ios_base::out);  genre = "����-�����������";	 break;
	case 11: path = "Books//prose.txt";            book.open(path, ios_base::in | ios_base::out);  genre = "����������� �����";  break;
	case 12: path = "Books//scientific.txt";       book.open(path, ios_base::in | ios_base::out);  genre = "������� ����������"; break;
	case 13: path = "Books//sex.txt";              book.open(path, ios_base::in | ios_base::out);  genre = "�������/����";       break;
	case 14: path = "Books//thriller.txt";         book.open(path, ios_base::in | ios_base::out);  genre = "��������/�������";   break;
	}
	return path;
}

size_t checkInput(size_t &quantity)
{
	string numberofbook = "";
	cin >> numberofbook;
	bool flag = true;
	for (size_t i(0); i < numberofbook.size(); i++)
	{
		if (numberofbook[i] < '0' || numberofbook[i] > '9')
		{
			flag = false;
			cout << "�������� ����!" << endl;
			_getch();
			break;
		}
	}
	if (flag)
	{
		if (stoi(numberofbook) < 1 || stoi(numberofbook) > quantity)
		{
			flag = false;
			cout << "�������� ����!" << endl;
			_getch();
		}
		else
			return stoi(numberofbook);
	}
	return 0;
}

void UsersPossibilities::borrow(fstream &file, fstream &book, size_t &count)
{
	string bookname = "";
	numberofstring(book, count);
	getline(book, bookname);
	file.seekp(0, ios::end);
	file << endl << bookname;
	file << endl << "1";
	Label::_tag();
	cout << "�������� ���� ����� --> " << bookname << endl;
	_getch();
}

void UsersPossibilities::get_book(fstream &file)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "������!���� �� ��� ������!";
		_getch();
		exit(EXIT_FAILURE);
	}
	do
	{
		fstream book;
		string genre = "";
		chooseGenre(book, genre);
		if (!book.is_open()) 
			return;
		size_t booknumber;
		do
		{
			Label::_tag();
			cout << "������ ���� ����� " << genre << ':' << endl
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
				cout << "(�����)" << endl
					<< "-------------------------------------------" << endl;
				_getch();
				return;
			}
			cout << "-------------------------------------------" << endl
				 << endl << "����� ����� �:";
			booknumber = checkInput(count);
		} while (!booknumber); 
		borrow(file, book, booknumber);
		book.close();
		cout << "����� ��� ���� �����? \"Any button\" - ��, \"N\" - ���";
		char check = _getch();
		if (check == 'n' || check == '�') 
			break;
	} while (true);
}

void UsersPossibilities::give_back(Registration *&enter, fstream &file, size_t &booknumber)
{
	string book = "";
	string status = "";
	size_t number = 0;
	size_t linenumber = 7;
	bool eof = false;
	numberofstring(file, 7);
	getline(file, book);
	while (!file.eof())
	{
		getline(file, book);
		while (true)
		{
			linenumber++;
			if (file.eof())
			{
				eof = true;
				break;
			}
			if (book != "����� ����� ���� ��������� � ����!" && book != "����� ���� ������� �� ����!" && book != "������ ������ ���� ��������!" && book != "������ ��� ������� ������!" && book != "��� ������� �� ��������������!" && book != "��� ������������ ���������������!" && book != "��� ������������� ���������������!")
				break;
			getline(file, book);
		}
		if (!eof)
		{
			getline(file, status);
			linenumber++;
			if (status == "1")
			{
				if (++number == booknumber)
				{
					file = refreshFile(enter, file, "0", linenumber);
					Label::_tag();
					cout << "�� ������� ����� ����� --> " << book << endl;
					_getch();
					break;
				}
			}
		}
		else break;
	}
	file.seekg(0, ios::beg);
}

void UsersPossibilities::put_book(Registration *&enter, fstream &file)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "������!���� �� ��� ������!";
		_getch();
		exit(EXIT_FAILURE);
	}
	do
	{
		size_t booknumber;
		do
		{
			Label::_tag();
			bool eof = false;
			string booklist = "";
			string status = "";
			size_t quantityofdebt = 0;
			cout << "������ ������:" << endl
			     << "-------------------------------------------" << endl;
			numberofstring(file, 7);
			getline(file, booklist);
			while (!file.eof())
			{
				getline(file, booklist);
				while (true)
				{
					if (file.eof())
					{
						eof = true;
						break;
					}
					if (booklist != "����� ����� ���� ��������� � ����!" && booklist != "����� ���� ������� �� ����!" && booklist != "������ ������ ���� ��������!" && booklist != "������ ��� ������� ������!" && booklist != "��� ������� �� ��������������!" && booklist != "��� ������������ ���������������!" && booklist != "��� ������������� ���������������!")
						break;
					getline(file, booklist);
				}
				if (!eof)
				{
					getline(file, status);
					if (status == "1")
						cout << '<' << ++quantityofdebt << "> " << booklist << endl;
				}
				else break;
			}
			file.seekg(0, ios::beg);
			if (!quantityofdebt)
			{
				cout << "� ��� ��� ������!" << endl
				     << "-------------------------------------------" << endl;
				_getch();
				return;
			}
			cout << "-------------------------------------------" << endl;
			cout << endl << "����� ����� �:";
			booknumber = checkInput(quantityofdebt);
		} while (!booknumber);
		give_back(enter, file, booknumber);
		cout << "����� ��� ���� �����? \"Any button\" - ��, \"N\" - ���";
		char check = _getch();
		if (check == 'n' || check == '�')
			break;
	} while (true);
}

void UsersPossibilities::list(Registration *&enter, fstream &file)
{
	if (!(file.is_open()))
	{
		file.close();
		Label::_tag();
		cerr << "������!���� �� ��� ������!";
		_getch();
		exit(EXIT_FAILURE);
	}
	do
	{
		string input = "";
		do
		{
			Label::_tag();
			cout << "����������� ������������: "   << endl
				 << "<0> - �����"                  << endl
				 << "<1> - ����� �����"            << endl
				 << "<2> - ����� �����"            << endl
				 << "<3> - ������� ��������"       << endl
				 << "<4> - ������ ������"		   << endl
				 << "<5> - ������� ������"         << endl
				 << "--> ";
			try
			{
				cin >> input;
				if (input.size() > 1 || '0' > input[0] || input[0] > '5') throw 0;
				else                                                      throw 1;
			}
			catch (int i) { if (i) break; }
		} while (true);
		Label::_tag();
		switch (input[0])
		{
		case '0':
		cout << "�������� ���!";
		_getch();
		file.close();
		return; 
		case '1': get_book(file);                    break;
		case '2': put_book(enter, file);             break;
		case '3': historyofOperations(file);         break;
		case '4': change_Personal_Data(enter, file); break;
		case '5': changePassword(enter, file);       break;
		}
	} while (true);
}