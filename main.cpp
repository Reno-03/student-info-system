#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using std::string;
using std::vector;

void updateUI();
void organizeUI();
void userInterface();

int cmdMain{};
string stop{};

struct studentRec {
	int ID{ 0 };
	string lastName{ "" };
	string firstName{ "" };
	int age{ 0 };
	string gender{ "" };
	string contactNo{ "" };
};

// global vector so it will be easier
vector<studentRec> dataset; 

class Operations {

	// Merging Process are private since it
	// is used within the class only
private:
	void mergeInt(std::vector<studentRec>& arr, int low, int mid, int high) {
		int leftSize = mid - low + 1;
		int rightSize = high - mid;

		// Create temporary left and right subvectors
		std::vector<studentRec> left(leftSize);
		std::vector<studentRec> right(rightSize);

		// Copy data to the left and right subvectors
		for (int i = 0; i < leftSize; i++) {
			left[i] = arr[low + i];
		}
		for (int j = 0; j < rightSize; j++) {
			right[j] = arr[mid + 1 + j];
		}

		// mergeInt the left and right subvectors back into the original vector
		int i = 0;  // Index for left subvector
		int j = 0;  // Index for right subvector
		int k = low;  // Index for merged vector

		while (i < leftSize && j < rightSize) {
			if (left[i].ID <= right[j].ID) {
				arr[k] = left[i];
				i++;
			}
			else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		// Copy the remaining elements of the left subvector
		while (i < leftSize) {
			arr[k] = left[i];
			i++;
			k++;
		}

		// Copy the remaining elements of the right subvector
		while (j < rightSize) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}

	void mergeString(std::vector<studentRec>& arr, int low, int mid, int high) {
		int leftSize = mid - low + 1;
		int rightSize = high - mid;

		// Create temporary left and right subvectors
		std::vector<studentRec> left(leftSize);
		std::vector<studentRec> right(rightSize);

		// Copy data to the left and right subvectors
		for (int i = 0; i < leftSize; i++) {
			left[i] = arr[low + i];
		}
		for (int j = 0; j < rightSize; j++) {
			right[j] = arr[mid + 1 + j];
		}

		// mergeString the left and right subvectors back into the original vector
		int i = 0;  // Index for left subvector
		int j = 0;  // Index for right subvector
		int k = low;  // Index for merged vector

		while (i < leftSize && j < rightSize) {
			if (left[i].lastName <= right[j].lastName) {
				arr[k] = left[i];
				i++;
			}
			else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		// Copy the remaining elements of the left subvector
		while (i < leftSize) {
			arr[k] = left[i];
			i++;
			k++;
		}

		// Copy the remaining elements of the right subvector
		while (j < rightSize) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}

public:
	// Recursive function to perform merge sort based on ID
	void mergeSortInt(std::vector<studentRec>& arr, int low, int high) {
		if (low < high) {
			int mid = low + (high - low) / 2;

			mergeSortInt(arr, low, mid);
			mergeSortInt(arr, mid + 1, high);

			mergeInt(arr, low, mid, high);
		}
	}

	// Recursive function to perform merge sort based on last name
	void mergeSortString(std::vector<studentRec>& arr, int low, int high) {
		if (low < high) {
			int mid = low + (high - low) / 2;

			mergeSortString(arr, low, mid);
			mergeSortString(arr, mid + 1, high);

			mergeString(arr, low, mid, high);
		}
	}
};

class Manipulations {
	// these linear search are private
	// since there's another function that controls
	// these algorithms

private:
	// linear search by ID
	// when found, return the index
	// otherwise, return -1
	int SearchID(const vector<studentRec>& record, int search) {
		for (int i = 0; i < record.size(); i++) {
			if (record[i].ID == search) {
				return i;
			}
		}
		return -1;
	}

	// linear search by last name
	// when found, return the index
	// otherwise, return -1
	int SearchLastName(const vector<studentRec>& record, string search) {
		for (int i = 0; i < record.size(); i++) {
			if (record[i].lastName == search) {
				return i;
			}
		}
		return -1;
	}

public:
	// after input each field, it is added to the dataset
	// cons - the first name should only be one name
	void addData() {
		int ID;
		string lastName;
		string firstName;
		int age;
		string gender;
		string contactNo;

		system("cls");

		std::cout << "Enter ID Number: ";
		std::cin >> ID;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining characters on the line, including the newline character
		
		std::cout << "Enter LastName: ";
		getline(std::cin, lastName);

		std::cout << "Enter First Name (one name only): ";
		getline(std::cin, firstName);

		std::cout << "Enter age: ";
		std::cin >> age;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character

		std::cout << "Enter gender: ";
		std::cin >> gender;

		std::cout << "Enter contact Number: ";
		std::cin >> contactNo;

		dataset.push_back({ ID, lastName, firstName, age, gender, contactNo });

		std::cout << "\nStudent added successfully to the dataset. \n";
		std::cout << "\nPress any character and <enter> to exit. ";
		std::cin >> stop;
	}

	// search controller function
	// search by ID or last name
	void searchData() {
		int cmdSearch{};
		string searchString{};
		int searchID{};
		int result{};
		string stop{};

		do {
			system("cls");
			std::cout
				<< "\n\t+------------------------+\n"
				<< "\t|      search data       |\n"
				<< "\t+------------------------+\n\n";

			std::cout
				<< "\t[1] search by ID. \n"
				<< "\t[2] search by Last Name. \n"
				<< "\t[0] Exit. \n\n";

			std::cout << "INPUT: ";
			std::cin >> cmdSearch;

			switch (cmdSearch) {

			case 1:
				std::cout << "What ID you want to search? ";
				std::cin >> searchID;

				result = SearchID(dataset, searchID);
				system("cls");
				if (result != -1) {
					std::cout << "Student " << searchID << " information: ";
					std::cout
						<< "\nName: " << dataset[result].firstName << " " << dataset[result].lastName
						<< "\nAge: " << dataset[result].age
						<< "\nGender: " << dataset[result].gender
						<< "\nContact No. : " << dataset[result].contactNo;
				}
				else {
					std::cout << "\n ID number " << searchID << " was not found. \n";
				}

				break;
			case 2:
				std::cout << "What Last Name you want to search? ";
				std::cin >> searchString;

				result = SearchLastName(dataset, searchString);

				if (result != -1) {
					system("cls");
					std::cout << dataset[result].lastName << " information: ";
					std::cout
						<< "\nID: " << dataset[result].ID
						<< "\nName: " << dataset[result].firstName << " " << dataset[result].lastName
						<< "\nAge: " << dataset[result].age
						<< "\nGender: " << dataset[result].gender
						<< "\nContact No. : " << dataset[result].contactNo;
				}
				else {
					std::cout << "\n" << searchString << " is not found. \n";
				}

				break;
			}

			std::cout << "\n\nPress any character and <enter> to exit. ";
			std::cin >> stop;

		} while (cmdSearch != 0);
	}

	// update any field by searching an ID number
	void updateData() {
		int IDupdate{};
		int cmdUpdateData{};
		int index{};
		string updateReplace{};
		int numReplace{};
		Manipulations oper6;
		system("cls");

		std::cout << "Enter ID number you want to update: ";
		std::cin >> IDupdate;

		index = oper6.SearchID(dataset, IDupdate);

		if (index != -1) {
			std::cout << "\nID " << IDupdate << " is found.";
			std::cout
				<< "\nWhat field you want to update? \n\n"
				<< "[1] ID. \n"
				<< "[2] Last Name. \n"
				<< "[3] First Name. \n"
				<< "[4] Age. \n"
				<< "[5] Gender. \n"
				<< "[6] Contact Number. \n";

			std::cout << "\nINPUT: ";
			std::cin >> cmdUpdateData;

			std::cout << "Enter the data to replace: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters including newline
			std::getline(std::cin, updateReplace);

			switch (cmdUpdateData) {
			case 1:
				numReplace = std::stoi(updateReplace);
				dataset[index].ID = numReplace;
				break;
			case 2:
				dataset[index].lastName = updateReplace;
				break;
			case 3:
				dataset[index].firstName = updateReplace;
				break;
			case 4:
				numReplace = std::stoi(updateReplace);
				dataset[index].age = numReplace;
				break;
			case 5:
				dataset[index].gender = updateReplace;
				break;
			case 6:
				dataset[index].contactNo = updateReplace;
				break;
			}
		}
		else {
			std::cout << IDupdate << " was not found. \n";
			std::cout << "\nPress any character and <enter> to exit. ";
			std::cin >> stop;
		}
	}

	// delete an entry by the ID number
	void deleteData() {
		int IDdel;
		Manipulations oper5;
		int result;
		system("cls");

		std::cout << "What student you want to remove? <enter ID>:  ";
		std::cin >> IDdel;

		result = oper5.SearchID(dataset, IDdel);
		if (result != -1) {
			dataset.erase(dataset.begin() + result);
			std::cout << "Deleted successfully\n";
		}
		else {
			std::cout << "\n" << IDdel << " was not found. \n";
		}

		std::cout << "\nPress any character and <enter> to exit. ";
		std::cin >> stop;
	}

	// save the dataset as a text file, may overwrite
	// the old saved file
	void saveFile(const string& filename) {
		system("cls");
		std::ofstream outputFile(filename);

		if (outputFile.is_open()) {
			for (const auto& student : dataset) {
				outputFile
					<< student.ID << " "
					<< student.lastName << " "
					<< student.firstName << " "
					<< student.age << " "
					<< student.gender << " "
					<< student.contactNo << " "
					<< "\n";
			}
			outputFile.close();
			std::cout << "Data saved to " << filename << "\n";
		}
		else {
			std::cout << "Unable to open file." << "\n";
		}

		std::cout << "\nPress any character and <enter> to exit. ";
		std::cin >> stop;
	}

	// load data from the saved text file
	// the current dataset will be overwritten
	void readFile(const string& filename) {
		system("cls");
		dataset.clear();
		std::ifstream inputFile(filename);

		if (inputFile.is_open()) {
			studentRec student;
			while (inputFile 
				>> student.ID 
				>> student.lastName
				>> student.firstName
				>> student.age
				>> student.gender
				>> student.contactNo) {

				dataset.push_back(student);
			}

			inputFile.close();
			std::cout << "Data read from " << filename << "\n";
		}
		else {
			std::cout << "Unable to open file." << "\n";
		}

		std::cout << "\nPress any character and <enter> to exit. ";
		std::cin >> stop;
	}

	// display in a tabulated form
	void displayDataset() {
		system("cls");

		int NoOfMales = 0;
		int NoOfFemales = 0;
		int sumAge = 0;

		// Display Header
		std::cout << std::left 
			<< std::setw(5) << "ID"
			<< std::setw(15) << "Last Name"
			<< std::setw(15) << "First Name"
			<< std::setw(5) << "Age"
			<< std::setw(10) << "Gender"
			<< std::setw(15) << "Contact No." << "\n";

		// Display entries
		for (const auto& student : dataset) {
			std::cout << std::left 
				<< std::setw(5) << student.ID
				<< std::setw(15) << student.lastName
				<< std::setw(15) << student.firstName
				<< std::setw(5) << student.age
				<< std::setw(10) << student.gender
				<< std::setw(15) << student.contactNo << "\n";

			if (student.gender == "Male") {
				NoOfMales++;
			}
			else if (student.gender == "Female") {
				NoOfFemales++;
			}
			sumAge += student.age;
		}

		std::cout << "\nNo. of students: " << dataset.size() << "\n";
		std::cout << "No. of Male students: " << NoOfMales << "\n";
		std::cout << "No. of Female students: " << NoOfFemales << "\n";
		if (dataset.size() != 0) {
			std::cout << "Mean Age: " << sumAge / dataset.size() << "\n";
		}

		std::cout << "\nPress any character and <enter> to exit. ";
		std::cin >> stop;
	}
};

// UI MODULE
void userInterface() {
	do {
		system("cls");
		std::cout
			<< "\n\t+---------------------------+\n"
			<< "\t|    INFORMATION SYSTEM     |\n"
			<< "\t|     by: Loreen Yboa       |\n"
			<< "\t+---------------------------+\n\n";

		std::cout
			<< "\t[1] UPDATE dataset. \n"
			<< "\t[2] ORGANIZE dataset. \n"
			<< "\t[0] Exit. \n\n";

		std::cout << "INPUT: ";
		std::cin >> cmdMain;

		switch (cmdMain) {

		case 1:
			updateUI();
			break;
		case 2:
			organizeUI();
			break;
		}
	} while (cmdMain != 0);
}

void updateUI() {
	int cmdUpdateUI{};
	Manipulations oper1;

	do {
		system("cls");
		std::cout
			<< "\n\t+---------------------------+\n"
			<< "\t| update dataset operations |\n"
			<< "\t+---------------------------+\n\n";

		std::cout
			<< "\t[1] add entry. \n"
			<< "\t[2] search entry. \n"
			<< "\t[3] update entry. \n"
			<< "\t[4] delete entry. \n"
			<< "\t[5] display dataset. \n"
			<< "\t[6] save dataset as txt file. \n"
			<< "\t[7] load dataset from file. \n"
			<< "\t[0] Exit. \n\n";

		std::cout << "INPUT: ";
		std::cin >> cmdUpdateUI;

		switch (cmdUpdateUI) {

		case 1:
			oper1.addData();
			break;
		case 2:
			oper1.searchData();
			break;
		case 3:
			oper1.updateData();
			break;
		case 4:
			oper1.deleteData();
			break;
		case 5:
			oper1.displayDataset();
			break;
		case 6:
			oper1.saveFile("studentData.txt");
			break;
		case 7:
			oper1.readFile("studentData.txt");
			break;
		}
	} while (cmdUpdateUI != 0);
}

void organizeUI() {
	int cmdorganizeUI{};
	Operations oper2;
	Manipulations oper1;
	int n = dataset.size();

	do {
		system("cls");
		std::cout
			<< "\n\t+-----------------------------+\n"
			<< "\t| organize dataset operations |\n"
			<< "\t+-----------------------------+\n\n";

		std::cout
			<< "\t[1] sort by ID. \n"
			<< "\t[2] sort by Last Name. \n"
			<< "\t[3] display dataset. \n"
			<< "\t[0] Exit. \n\n";

		std::cout << "INPUT: ";
		std::cin >> cmdorganizeUI;

		switch (cmdorganizeUI) {

		case 1:
			oper2.mergeSortInt(dataset, 0, n - 1);
			break;
		case 2:
			oper2.mergeSortString(dataset, 0, n - 1);
			break;
		case 3:
			oper1.displayDataset();
			break;
		default:
			continue;
		}

	} while (cmdorganizeUI != 0);
}

int main() {

	userInterface();

	return 0;
}