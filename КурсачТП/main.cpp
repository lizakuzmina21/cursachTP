#include <iostream>
#include <fstream>
#include "windows.h"
#include <exception>
#include <algorithm>
#include <list>
#include <string>
#include "Park_Car.h"
#include "Car.h"
#include "Valid.h"
using namespace std;

Park_Car read_from_file(int);//������ �� �����
void write_to_file(Park_Car);//�������� � ����
int main_menu();

bool str_cmp(Data d1, Data d2)
{
	return d1.typeCar > d2.typeCar;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	int menu = 1; 
	int ship_type;
	int num;
	string tmp;
	Park_Car h;
	int n = 0;
	while (menu)
	{
		system("cls");
		menu = main_menu();

		switch (menu)
		{
		case 1:
			system("cls");
			cout << "������� ����� �� ������ ��������?\n";

			while (true) // ��������� ������������ �����
			{
				cout << "> ";
				getline(cin, tmp);
				num = atoi(tmp.c_str());
				if (num_valid(tmp)) // ���� �������� ������ ������ ��������
					if (num > 0) // ���� ������ �������
						break;
			}

			for (int i = 0; i < num; i++)
			{
				system("cls");
				cout << "1. �������� ������" << endl;
				cout << "2. �������� ������" << endl;
				cout << "3.�������" << endl;

				while (true)
				{
					cout << "> ";
					getline(cin, tmp);
					ship_type = atoi(tmp.c_str());
					if (num_valid(tmp))
						if (ship_type == 1 || ship_type == 2 || ship_type == 3)
							break;
				}

				if (ship_type == 1)
					h.create_passenger();
				else if (ship_type == 2)
					h.create_truck();
				else
					h.create_tram();
			}
			break;

		case 2:
			h.show();
			getchar();
			break;

		case 3:
			system("cls");
			cout << "������� ����� �� ������ �������� �� ����� ?\n";

			while (true)
			{
				cout << "> ";
				getline(cin, tmp);
				num = atoi(tmp.c_str());
				if (num_valid(tmp))
					if (num > 0)
						break;
			}

			h = read_from_file(num);
			break;

		case 4:
			cout << "�������� �����\n";
			write_to_file(h);
			getchar();
			break;

		case 5:
			cout << "����� ������ �� ������ ��������" << endl;
			h.show();

		/*	cin >> n;*/
			while (true)
			{
				cout << "> ";
				getline(cin, tmp);
				num = atoi(tmp.c_str());
				if (num_valid(tmp))
					if (num > 0)
						break;
			}
			h.change(num - 1);

		}
	}
	
	return 0;
}

int main_menu()
{
	int menu;
	string tmp;

	cout << "1. �������� ������ � ����" << endl;
	cout << "2. �������� ����" << endl;
	cout << "3. ��������� ������ �� �����" << endl;
	cout << "4. ��������� ���� � ����" << endl;
	cout << "5. �������� ������ � �����" << endl;
	cout << "0. Exit" << endl;

	while (true) // ��������� ������������ �����
	{
		cout << "> ";
		getline(cin, tmp);
		menu = atoi(tmp.c_str());
		if (num_valid(tmp)) // ���� �������� ������ ������ ��������
			if (menu >= 0 && menu <= 5) // ���� ������ �������
				break;
	}

	return menu;
}

Park_Car read_from_file(int num)
{
	ifstream in;
	Park_Car h;
	Data data;
	string tmp;
	int flag = 1;
	int pos;

	try
	{
		in.open("C:\\Users\\������\\source\\repos\\Project9\\Project9\\Debug\\parck.txt", ios::in);
		if (!in.is_open())
			throw exception("���� �� �����������!\n");

		if (in.peek() == EOF)
			throw exception("���� ����!\n");

		while (in.peek() != EOF && num != 0) // Read data from file
		{
			getline(in, tmp);
			if (tmp.empty())
				continue;

			cout << tmp << endl;

			switch (flag)
			{
			case 1:
				if (pos = tmp.find("��� ������: ") != 0)
					throw exception("������ � �����\n");

				data.typeCar = tmp.substr(12);
			if (data.typeCar != "��������" && data.typeCar != "��������" && data.typeCar != "�������")
					throw exception("� ����� ���� ������ ���� ������");
				break;

			case 2:
				if (pos = tmp.find("���� ������: ") != 0)
					throw exception("������ � �����\n");

				data.color = tmp.substr(13);
				break;

			case 3:
				if (pos = tmp.find("����: ") != 0)
					throw exception("������ � �����\n");

				tmp = tmp.substr(6);
				if (!num_valid(tmp))
					throw exception("������ � �����\n");

				data.price = atoi(tmp.c_str()); // Convert string to integer
				if (data.price < 0)
					throw exception("������ ���� � �����\n");
				break;

			case 4:
				if (pos = tmp.find("����� ���������: ") != 0)
					throw exception("������ � �����\n");

				tmp = tmp.substr(17);
				if (!num_valid(tmp))
					throw exception("������ � �����\n");

				data.volumeD = atoi(tmp.c_str()); // Convert string to integer
				if (data.volumeD < 0)
					throw exception("������ ������ ��������� � �����\n");
				break;

			case 5:
				if (pos = tmp.find("����� ��������: ") != 0)
					throw exception("������ � �����\n");

				tmp = tmp.substr(16);
				if (!num_valid(tmp))
					throw exception("������ � �����\n");

				data.number = atoi(tmp.c_str()); // Convert string to integer
				if (data.number < 0)
					throw exception("������ ������ �������� � �����\n");
				break;
			case 6:
				if (pos = tmp.find("��� ������������: ") != 0)
					throw exception("������ � �����\n");

				tmp = tmp.substr(18);
				if (!num_valid(tmp))
					throw exception("������ � �����\n");

				data.yearP = atoi(tmp.c_str()); // Convert string to integer
				if (data.yearP < 0)
					throw exception("������ ��� ������������ � �����\n");
				break;

			case 7:
				if (pos = tmp.find("��� ������� � ������������: ") != 0)
					throw exception("������ � �����\n");

				tmp = tmp.substr(28);
				if (!num_valid(tmp))
					throw exception("������ � �����\n");

				data.yearZ = atoi(tmp.c_str()); // Convert string to integer
				if (data.yearZ < 0)
					throw exception("������ ��� ������� � ������������ � �����\n");
				break;

			case 8:
				if (pos = tmp.find("��� �������: ") != 0)
					throw exception("������ � �����\n");

				data.type = tmp.substr(13);
				break;

			case 9:
				if (pos = tmp.find("����� ����������: ") != 0)
					throw exception("������ � �����\n");

				tmp = tmp.substr(18);
				if (!num_valid(tmp))
					throw exception("������ � �����\n");

				data.passengers = atoi(tmp.c_str());
				if (data.passengers < 0)
					throw exception("������ ����� ���������� � �����\n");
				break;

			case 10:
				if (pos = tmp.find("����� �����: ") != 0)
					throw exception("������ � �����\n");

				tmp = tmp.substr(13);
				if (!num_valid(tmp))
					throw exception("������ � �����\n");

				data.volumeG = atoi(tmp.c_str());
				if (data.volumeG < 0)
					throw exception("������ � ������ ����� � �����\n");
				break;
			}
			//cout << "�����";
			//system("pause");
			if (flag == 10)
			{
				cout << endl;
				flag = 0; // Zero because of increment below
				h.setData(data);
				num--;
			}

			flag++;
		}
	}

	catch (exception& ex)
	{
		cout << ex.what() << endl;
		getchar();
	}

	in.close();

	return h;
}

void write_to_file(Park_Car h)
{
	ofstream out;
	Data d;
	list<Car*> l = h.get_Car();

	l.sort([](const Car* s1, const Car* s2)
		{
			return s1->get_data().typeCar < s2->get_data().typeCar;
		});

	try
	{
		out.open("C:\\Users\\������\\source\\repos\\Project9\\Project9\\Debug\\parck.txt", ios_base::app);
		if (!out.is_open())
			throw exception("File can not be opened!");

		for (auto el : l)
		{
			d = el->get_data();
			out << "��� ������: " << d.typeCar << endl;
			out << "���� ������: " << d.color << endl;
			out << "����: " << d.price << endl;
			out << "����� ���������: " << d.volumeD << endl;
			out << "����� ��������: " << d.number << endl;
			out << "��� ������������: " << d.yearP << endl;
			out << "��� ������� � ������������: " << d.yearZ << endl;
			out << "��� �������: " << d.type << endl;
			out << "����� ����������: " << d.passengers << endl;
			out << "����� �����: " << d.volumeG << endl;
		}
		out.close();
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
}


