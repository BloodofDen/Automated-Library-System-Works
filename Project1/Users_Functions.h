#pragma once

class UsersPossibilities
{
private:

	/*��� ��������� ������-���������/������-����� �������� �������*/

	//����� ���������� ���������� � �����
	fstream refreshFile(Registration *&enter, fstream &file, string changes, size_t linenumber);

	//����� ����� �����
	friend string chooseGenre(fstream &book, string &genre);

	//�������, ��������������� ��������� �� ���������� � ������ n-��� ������
	template<class Type> friend void numberofstring(Type &file, size_t n);

	//�������� ����� - �����/������� �����
	size_t friend checkInput(size_t &quantityofdebt);

	//����� ���������� ����� �� ������
	void borrow(fstream &file, fstream &book, size_t &count);

	//������� ���������� ����� �� ������
	void give_back(Registration *&enter, fstream &file, size_t &booknumber);

protected:

	/*�������� ����� ����������� �������*/

	//�������� ������
	void changePassword(Registration *&enter, fstream &file);
	
	//������� ��������
	void historyofOperations(fstream &file);

	//��������� ������ ������
	void change_Personal_Data(Registration *&enter, fstream &file);

	//���� �����
	void get_book(fstream &file);

	//������� �����
	void put_book(Registration *&enter, fstream &file);

public:

	//���������������� ����������
	void list(Registration *&enter, fstream &file);
};