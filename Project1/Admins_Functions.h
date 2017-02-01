#pragma once

class AdminsPossibilities:protected UsersPossibilities
{
private:

	//�������� ����� ���������/���������� ������������
	void for_freeze_thawed(string str1, string str2, char ch);

	//������������� ����� ���������� ���������� ���� ����
	void refreshFile(fstream &file, string &path, size_t &linenumber);

	//�������� �� ������������ ����� ������ ����� �����
	bool publishingYear(string &year);

	//�������� ������������ �� ��������������
	void increacetoAdmin(fstream &file);

	//������� ��������������
	void changeAdmin(Registration *&enter, fstream &file);

	//������ ���� �������������
	void userlist();

	//���������
	void freeze() { for_freeze_thawed("����������", "������������", '1'); }

	//����������
	void thawed() { for_freeze_thawed("�������������", "�������������", '0'); }
	
	//�������� ������������� ������������
	void check_User();

	//���������� �����
	void addBook(fstream &file);

	//�������� �����
	void removeBook(fstream &file);

public:

	//������ ���������� ��������������
	void list(Registration *&enter, fstream &file);
};