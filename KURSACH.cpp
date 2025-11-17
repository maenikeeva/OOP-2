// KURSACH.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "CONTACT.h"
#include "FILE.h"
#include <iostream>
#include <limits>
using namespace std;

void MENU() {
	cout << "МЕНЮ:" << endl << "1) Новый контакт" << endl << "2) Поиск контакта" << endl << "3) Удаление контакта" <<
		endl << "4) Все контакты" << endl  << "5) Сохранить в файл" << endl
		<< "6) Выгрузить из файла" << endl << "7) Выход" << endl;
}

void AddM(Book& book) {
	string name;
	string middlename;
	string surname;
	string email;
	string address;
	string date;
	string phone;
	int choice;

	cout << "Введите данные контакта:" << endl;
	cout << "Имя:  ";
	getline(cin, name);
	cout << "Отчество:  ";
	getline(cin, middlename);
	cout << "Фамилия:  ";
	getline(cin, surname);
	cout << "Почта:  ";
	getline(cin, email);
	cout << "Адрес:  ";
	getline(cin, address);
	cout << "Дата рождения:  ";
	getline(cin, date);
	cout << "Телефон:  ";
	getline(cin, phone);
	cout << "Тип телефона (1 - рабочий, 2 - домашний, 3 - служебный):  ";
	cin >> choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	PhoneType type = PhoneType::work;
	if (choice == 2) {
		type = PhoneType::home;
	}
	else if (choice == 3) {
		type = PhoneType::official;
	}
	Contact contact(name, surname, email, phone, type);
	contact.setMiddleName(middlename);
	contact.setAdress(address);
	contact.setDateOfBirth(date);
	book.Add(contact);
}

void SearchM(Book& book){
	string surname;
	vector<Contact> result;
	cout << "Введите фамилию: " << endl;
	getline(cin, surname);
	result = book.Search(surname);
	if (result.empty()) {
		cout << "Контакты не найдены" << endl;
	}
	else {
		for (const auto& contact : result) {
			cout << contact.getName() << " " << contact.getSurname() << " " << contact.getEmail() << endl;
		}
	}
}

void DeleteM(Book& book) {
	string name;
	string surname;
	cout << "Введите данные контакта, который вы хотите удалить:" << endl;
	cout << "Имя: " << endl;
	getline(cin, name);
	cout << "Фамилия: " << endl;
	getline(cin, surname);
	book.Delete(name, surname);
}




int main() {
	Book book("my_phonebook.txt");
	int choice;
	do {
		MENU();
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (choice) {
		case 1:
			AddM(book);
			break;
		case 2:
			SearchM(book);
			break;
		case 3:
			DeleteM(book);
			break;
		case 4:
			book.ShowALL();
			break;
		case 5:
			if (book.SaveFIle()) {
				cout << "Данные сохранены." << endl;
				break;
		case 6:
			if (book.LoadFile()) {
				cout << "Данные загружены." << endl;
				break;
			}
		case 7:
			break;
			}
		default:
			cout << "Введите число от 1 до 7" << endl;
		}
	} while (choice != 0);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
