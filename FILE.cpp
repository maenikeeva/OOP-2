#include "FILE.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Book::Book(const string& file) : filename(file) {
    LoadFile();
}

bool Book::Add(const Contact& contact) {
    if (!contact.getCheck()) {
        cout << "ÄÀÍÍÛÅ ÍÅÊÎÐÐÅÊÒÍÛ!" << endl;
        return false;
    }
    contacts.push_back(contact);
    SaveFIle();
    cout << "ÊÎÍÒÀÊÒ ÄÎÁÀÂËÅÍ" << endl;
    return true;
}

bool Book::Remove(const string& name, const string& surname) {
    auto it = remove_if(contacts.begin(), contacts.end(),
        [&](const Contact& c) {
            return c.getName() == name && c.getSurname() == surname;
        });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        SaveFIle();
        cout << "ÊÎÍÒÀÊÒ ÓÄÀË¨Í!" << endl;
        return true;
    }
    cout << "ÒÀÊÎÃÎ ÊÎÍÒÀÊÒÀ ÍÅÒ!" << endl;
    return false;
}

void Book::Sort() {
    // Ïîêà îñòàâèì ïóñòûì èëè ðåàëèçóåì ñîðòèðîâêó
}

bool Book::SaveFIle() const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "ÎØÈÁÊÀ ÎÒÊÐÛÒÈß ÔÀÉËÀ!" << endl;
        return false;
    }
    for (const auto& contact : contacts) {
        file << ContactToString(contact) << "\n";
    }
    file.close();
    return true;
}

bool Book::LoadFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ÔÀÉË ÍÅ ÍÀÉÄÅÍ, ÑÎÇÄÀÍÈÅ ÍÎÂÎÃÎ!" << endl;
        return false;
    }
    contacts.clear();
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            Contact contact = ContactFromString(line);
            if (contact.getCheck()) {
                contacts.push_back(contact);
            }
        }
    }
    file.close();
    cout << "ÊÎÍÒÀÊÒÛ ÇÀÃÐÓÆÅÍÛ!" << endl;
    return true;
}

vector<Contact> Book::Search(const string& n) const {
    vector<Contact> result;
    for (const auto& contact : contacts) {
        if (contact.getName().find(n) != string::npos ||
            contact.getSurname().find(n) != string::npos ||
            contact.getEmail().find(n) != string::npos) {
            result.push_back(contact);
        }
    }
    return result;
}

vector<Contact> Book::ALLContacts() const {
    return contacts;
}

void Book::ShowALL() const {
    if (contacts.empty()) {
        cout << "ÊÎÍÒÀÊÒÎÂ ÍÅÒ" << endl;
        return;
    }
    cout << "ÂÑÅ ÊÎÍÒÀÊÒÛ:" << endl;
    for (size_t i = 0; i < contacts.size(); ++i) {
        const auto& contact = contacts[i];
        cout << i + 1 << ") " << contact.getSurname() << " "
            << contact.getName() << " " << contact.getMiddleName()
            << " - " << contact.getEmail() << endl;

        auto phones = contact.getAllPhones();
        for (const auto& phone : phones) {
            cout << "   " << phone.second << ": " << phone.first << endl;
        }
        cout << "   Àäðåñ: " << contact.getAdress() << endl;
        cout << "   Äàòà ðîæäåíèÿ: " << contact.getDateOfBirth() << endl;
        cout << "---" << endl;
    }
}

string Book::ContactToString(const Contact& contact) const {
    stringstream ss;
    ss << contact.getName() << "|" << contact.getSurname() << "|"
        << contact.getMiddleName() << "|" << contact.getEmail() << "|"
        << contact.getAdress() << "|" << contact.getDateOfBirth();

    auto phones = contact.getAllPhones();
    ss << "|";
    for (size_t i = 0; i < phones.size(); i++) {
        if (i > 0) ss << ";";
        ss << phones[i].first << ":" << phones[i].second;
    }
    return ss.str();
}

Contact Book::ContactFromString(const string& line) const {
    stringstream ss(line);
    string name, surname, middlename, email, address, date, phonesStr;

    getline(ss, name, '|');
    getline(ss, surname, '|');
    getline(ss, middlename, '|');
    getline(ss, email, '|');
    getline(ss, address, '|');
    getline(ss, date, '|');
    getline(ss, phonesStr);

    string firstPhone = "";
    PhoneType firstType = PhoneType::work;

    if (!phonesStr.empty()) {
        stringstream phonesStream(phonesStr);
        string phoneEntry;
        if (getline(phonesStream, phoneEntry, ';')) {
            size_t colonPos = phoneEntry.find(':');
            if (colonPos != string::npos) {
                firstPhone = phoneEntry.substr(0, colonPos);
                string typeStr = phoneEntry.substr(colonPos + 1);
                if (typeStr == "äîìàøíèé") firstType = PhoneType::home;
                else if (typeStr == "ñëóæåáíûé") firstType = PhoneType::official;
                else firstType = PhoneType::work;
            }
        }
    }

    Contact contact(name, surname, email, firstPhone, firstType);
    contact.setMiddleName(middlename);
    contact.setAdress(address);
    contact.setDateOfBirth(date);

    // Äîáàâëÿåì îñòàëüíûå òåëåôîíû
    if (!phonesStr.empty()) {
        stringstream phonesStream(phonesStr);
        string phoneEntry;
        bool first = true;
        while (getline(phonesStream, phoneEntry, ';')) {
            if (first) {
                first = false;
                continue;
            }

            size_t colonPos = phoneEntry.find(':');
            if (colonPos != string::npos) {
                string phone = phoneEntry.substr(0, colonPos);
                string typeStr = phoneEntry.substr(colonPos + 1);

                PhoneType type = PhoneType::work;
                if (typeStr == "äîìàøíèé") type = PhoneType::home;
                else if (typeStr == "ñëóæåáíûé") type = PhoneType::official;

                contact.addNumber(phone, type);
            }
        }
    }

    return contact;
}