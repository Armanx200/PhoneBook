#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function prototypes
void addNumber();
void expropriateNumber();
void deleteNumber(string phoneNumber);

int main() {
    int choice;

    do {
        cout << "1. Add Number\n";
        cout << "2. Expropriate Number\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNumber();
                break;
            case 2:
                expropriateNumber();
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void addNumber() {
    ofstream outFile("phonebook.txt", ios::app);

    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    string phoneNumber, nationalCode;
    int status = 1; // Automatically set status to 1

    cout << "Enter phone number: ";
    cin >> phoneNumber;

    // Check if the phone number already exists
    ifstream inFile("phonebook.txt");
    string line;
    while (getline(inFile, line)) {
        string storedPhoneNumber = line.substr(0, line.find(' '));
        int storedStatus = stoi(line.substr(line.find(' ') + 1));

        if (storedPhoneNumber == phoneNumber && storedStatus == 1) {
            cout << "Error: Phone number already exists with status 1.\n";
            inFile.close();
            outFile.close();
            return;
        }
        else if (storedPhoneNumber == phoneNumber && storedStatus == 0){
            inFile.close();
            outFile.close();
            deleteNumber(phoneNumber);
            ofstream outFile("phonebook.txt", ios::app);
            ifstream inFile("phonebook.txt");
        }
    }

    cout << "Enter national code: ";
    cin >> nationalCode;

    inFile.close();

    // Status is automatically set to 1
    outFile << phoneNumber << " " << status << " ";



    outFile << nationalCode << endl;
    cout << "Number added successfully.\n";

    outFile.close();
}

void expropriateNumber() {
    ifstream inFile("phonebook.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening file for reading or writing.\n";
        return;
    }

    string phoneNumber, status, nationalCode;
    bool found = false;

    cout << "Enter phone number to expropriate: ";
    cin >> phoneNumber;

    while (inFile >> phoneNumber >> status >> nationalCode) {
        if (phoneNumber == phoneNumber) {
            found = true;
            // Set status to 0 and nullify national code
            tempFile << phoneNumber << " 0 null\n";
            cout << "Number expropriated successfully.\n";
            break;  // exit the loop after processing the input number
        } else {
            tempFile << phoneNumber << " " << status << " " << nationalCode << endl;
        }
    }

    if (!found) {
        cout << "Error: Phone number not found.\n";
    }

    // Copy the rest of the file to the temp file
    while (inFile >> phoneNumber >> status >> nationalCode) {
        tempFile << phoneNumber << " " << status << " " << nationalCode << endl;
    }

    inFile.close();
    tempFile.close();

    // Remove the original file and rename the temp file
    remove("phonebook.txt");
    rename("temp.txt", "phonebook.txt");
}

void deleteNumber(string phoneNumber) {
    ifstream inFile("phonebook.txt");
    ofstream tempFile("tempp.txt");

    if (!inFile || !tempFile) {
        cerr << "Error opening file for reading or writing.\n";
        return;
    }

    string currentPhoneNumber, status, nationalCode;
    bool found = false;

    while (inFile >> currentPhoneNumber >> status >> nationalCode) {
        if (phoneNumber == currentPhoneNumber) {
            found = true;
            cout << "Number deleted successfully.\n";
            continue; // Skip writing the deleted number to tempFile
        } else {
            tempFile << currentPhoneNumber << " " << status << " " << nationalCode << endl;
        }
    }

    if (!found) {
        cout << "Error: Phone number not found.\n";
    }

    inFile.close();
    tempFile.close();

    // Remove the original file and rename the temp file
    remove("phonebook.txt");
    rename("tempp.txt", "phonebook.txt");
}
