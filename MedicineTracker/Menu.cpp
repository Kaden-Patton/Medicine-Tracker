#include "Menu.h"


bool Menu::isRunning = true;
std::vector<std::string> Menu::options{ "View", "Create", "Delete", "Exit" };

void Menu::Display() {
	std::cout << "Medicine tracker\n" << "\nOptions:\n";

	RenderOptions();


	std::cout << "Enter your choice: ";
	int choice = atoi(GetInput().c_str());

	if (choice >= 1 && choice <= options.size()) {
		if (choice == 1) {
			ClearScreen();
			ViewRecords();
		}
		else if (choice == 2) {
			ClearScreen();
			InsertRecord();

		}
		else if (choice == 3) {
			ClearScreen();
			DeleteRecord();
		}
		else if (choice == 4) {
			isRunning = false;
			return;
		}
	}
	else {
		std::cout << "Invalid choice!";
	}

	Sleep(500);
	ClearScreen();

}

void Menu::RenderOptions() {
	for (int i = 0; i < options.size(); ++i) {
		std::cout << (i + 1) << ". " << options[i] << "\n";
	}
}

std::string Menu::GetInput() {
	std::string temp;
	std::getline(std::cin, temp);
	return temp;
}

void Menu::ClearScreen() {
	system("cls");
}

void Menu::ViewRecords() {
	std::vector<Record> records{};
	if (!Database::GetRecords(records)) {
		std::cout << "Failed to retrieve records.\n";
		return;
	}

	if (records.empty()) {
		std::cout << "No records found in database.\n";
	}
	else {
		std::cout << "Records:\n";
		for (const auto& record : records) {
			std::cout << "ID: " << record.id << ", Name: " << record.name << ", Dosage: " << record.dosage << ", Date taken: " << record.dateTaken << ", Time taken: " << record.timeTaken << ", Notes: " << record.notes << "\n";
		}
	}

	std::cout << "\n\nPress <Enter> to exit.";
	std::string temp;
	std::getline(std::cin, temp);
}

void Menu::InsertRecord() {
	std::string name{};
	std::string dosage{};
	std::string timeTaken{};
	std::string dateTaken{};
	std::string notes{};

	std::cout << "Enter name of medicine: ";
	std::getline(std::cin, name);

	std::cout << "Enter dosage of the medicine: ";
	std::getline(std::cin, dosage);

	std::cout << "Enter time taken: ";
	std::getline(std::cin, timeTaken);

	std::cout << "Enter date taken: ";
	std::getline(std::cin, dateTaken);

	std::cout << "Enter any additional notes: ";
	std::getline(std::cin, notes);

	if (Database::Insert(name, dosage, timeTaken, dateTaken, notes)) {
		std::cout << "Record inserted succesfully.\n";
	}
	else {
		std::cout << "Failed to insert record.\n";
	}

	Sleep(1500);
}

void Menu::DeleteRecord() {
	std::string id{};
	std::cout << "Enter ID of record to delete: ";
	std::getline(std::cin, id);

	if (Database::Delete(atoi(id.c_str()))) {
		std::cout << "Record deleted.\n";
	}
	else {
		std::cout << "Failed to delete record.\n";
	}
}
