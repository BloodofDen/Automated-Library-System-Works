#pragma once

class Registration
{
public:

	/*��������� ����������� ����������*/

	//��������� �������
	bool Access = false;

	//��� � MD5
	string nickname_md5 = "";

private:
	
	//����� ����������� ������ ���. ����.
	static void zvezda_number(string &mobile);

	//����� �������� ��������������� ������ ������������� ������
	string new_card_number();

	//�������� �� ��, ����� �� ����� ��� ��� ���. ���� ��� - �� �� ������������
	void access(bool &acc);

	//�������� �� ������������ �������
	bool similarLogin(string &logpass, bool &rights);

	//�������� ����� ������
	void checkPassword(fstream &file);

	//�����������
	void signUp();

	//��������� ������ ������
	friend void get_change_PersonalData(string &address, string &FIO, string &mobile, string get_change);

public:

	/*�������� ����� �������*/
	
	//�������������� ������ � ��������
	string zvezda(string text = "");

	//�����������
	fstream logIn(bool &Access, bool change);

	//���� � �������
	fstream signIn();
};