#pragma once

class UsersPossibilities
{
private:

	/*Тут находятся методы-помошники/методы-части основных методов*/

	//Метод обновления информации в файле
	fstream refreshFile(Registration *&enter, fstream &file, string changes, size_t linenumber);

	//Выбор жанра книги
	friend string chooseGenre(fstream &book, string &genre);

	//Функция, устанавливающий указатель на считывание в начале n-ной строки
	template<class Type> friend void numberofstring(Type &file, size_t n);

	//Проверка ввода - взять/вернуть книгу
	size_t friend checkInput(size_t &quantityofdebt);

	//Взять конкретную книгу из списка
	void borrow(fstream &file, fstream &book, size_t &count);

	//Вернуть конкретную книгу из списка
	void give_back(Registration *&enter, fstream &file, size_t &booknumber);

protected:

	/*Основной набор наследуемых методов*/

	//Изменить пароль
	void changePassword(Registration *&enter, fstream &file);
	
	//История операций
	void historyofOperations(fstream &file);

	//Изменение личных данных
	void change_Personal_Data(Registration *&enter, fstream &file);

	//Вять книгу
	void get_book(fstream &file);

	//Вернуть книгу
	void put_book(Registration *&enter, fstream &file);

public:

	//Пользовательский функционал
	void list(Registration *&enter, fstream &file);
};