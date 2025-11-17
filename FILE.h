#pragma once
#include "CONTACT.h"

class Book {
private:
	vector<Contact> contacts;
	string filename;
public:
	Book(const string& file = "book.txt");
	bool Add(const Contact& contact);
	bool Delete(const string& name, const string& surname);
	void Sort();
	bool SaveFIle() const;
	bool LoadFile();
	vector<Contact> Search(const string& name);
	vector<Contact> ALLContacts() const;
	void ShowALL() const;
private:
	Contact ContactFromString(const string& line) const;
	string ContactToString(const Contact& contact) const;
};