#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
vector<string> split(const string& s, char delimiter){
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;

    LinkedList() {
        this->head = nullptr;
    }

    void append(int new_data) {
        Node* new_node = new Node(new_data);
        if (this->head == nullptr) {
            this->head = new_node;
            return;
        }
        Node* last = this->head;
        while (last->next) {
            last = last->next;
        }
        last->next = new_node;
    }

    void printList() {
        Node* temp = this->head;
        while (temp) {
            cout << "\n\t" << temp->data;
            temp = temp->next;
        }
    }
};

vector<string> stack;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int>& arr) {
    for (int step = 1; step < arr.size(); ++step) {
        int key = arr[step];
        int j = step - 1;
        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int binarySearch(const vector<int>& arr, int low, int high, int x) {
    if (high >= low) {
        int mid = (high + low) / 2;
        if (arr[mid] == x) {
            return mid;
        }
        else if (arr[mid] > x) {
            return binarySearch(arr, low, mid - 1, x);
        }
        else {
            return binarySearch(arr, mid + 1, high, x);
        }
    }
    return -1;
}

int linearSearch(const vector<int>& arr, int x) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

class Contacts {
public:
    vector<int> contacts;
    string emailAccount;
    string name;
    string phoneNumber;
    string email;
    string address;


   Contacts() {
        // Initialize the member variables
        emailAccount = "";
        name = "";
        phoneNumber = "";
        email = "";
        address = "";
    }
    Contacts(const string& emailAccount, const string& name, const string& phoneNumber, const string& email, const string& address) {
        this->emailAccount = emailAccount;
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->email = email;
        this->address = address;
    }

    void getAllContactNumbers() {
        string file = this->emailAccount + "_contacts.txt";
        ifstream inputFile(file);
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                vector<string> data = split(line, ',');
                if (data.size() >= 2) {
                    // Check if the phone number is a valid integer before converting
                    if (all_of(data[1].begin(), data[1].end(), ::isdigit)) {
                        try {
                            int phoneNumber = stoi(data[1]);
                            this->contacts.push_back(phoneNumber);
                        } catch (const invalid_argument& e) {
                            cout << "Error converting phone number to integer: " << e.what() << endl;
                            cout << "Invalid phone number: " << data[1] << endl;
                            // Handle the error accordingly, such as skipping the invalid entry or exiting the loop.
                        }
                    } else {
                        cout << "Invalid phone number format: " << data[1] << endl;
                        // Handle the error accordingly, such as skipping the invalid entry or exiting the loop.
                    }
                }
            }
            inputFile.close();
        }
    }

    bool isContactAlreadyTaken() {
        this->contacts.clear();
        this->getAllContactNumbers();
        return (linearSearch(this->contacts, stoi(this->phoneNumber)) != -1);
    }

    void addContact() {
        string file = this->emailAccount + "_contacts.txt";
        ofstream outputFile(file, ios::app);
        if (outputFile.is_open()) {
            if (!this->isContactAlreadyTaken()) {
                outputFile << this->name << "," << this->phoneNumber << "," << this->email << "," << this->address << "," << "\n";
            }
            else {
                cout << "\tContact Number Already In List\n";
            }
            outputFile.close();
        }
    }

    void displayContacts() {
        this->contacts.clear();
        this->getAllContactNumbers();
        int ascdes;
        cout << "\t1. Ascending Order\n\t2. Descending Order\n\t3. Back\n";
        cin >> ascdes;
        if (ascdes == 1) {
            stack.push_back("displayContacts");
            bubbleSort(this->contacts);
            string file = this->emailAccount + "_contacts.txt";
            ifstream inputFile(file);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    vector<string> data = split(line, ',');
                    for (int i = 0; i < this->contacts.size(); ++i) {
                        if (this->contacts[i] == stoi(data[1])) {
                            cout << "\n\tContact\n";
                            cout << "\tName: " << data[0] << "\n";
                            cout << "\tPhone: " << data[1] << "\n";
                            cout << "\tEmail: " << data[2] << "\n";
                            cout << "\tAddress: " << data[3] << "\n";
                        }
                    }
                }
                inputFile.close();
            }
            else {
                cout << "\tNo Contacts in Your Account\n";
            }
        }
        else if (ascdes == 2) {
            stack.push_back("displayContacts");
            insertionSort(this->contacts);
            string file = this->emailAccount + "_contacts.txt";
            ifstream inputFile(file);
            if (inputFile.is_open()) {
                            string line;
            while (getline(inputFile, line)) {
                vector<string> data = split(line, ',');
                for (int i = 0; i < this->contacts.size(); ++i) {
                    if (this->contacts[i] == stoi(data[1])) {
                        cout << "\n\tContact\n";
                        cout << "\tName: " << data[0] << "\n";
                        cout << "\tPhone: " << data[1] << "\n";
                        cout << "\tEmail: " << data[2] << "\n";
                        cout << "\tAddress: " << data[3] << "\n";
                    }
                }
            }
            inputFile.close();
        }
        else {
            cout << "\tNo Contacts in Your Account\n";
        }
    }
    else if (ascdes == 3) {
        stack.pop_back();
    }

    cout << "\tPress Any Key To Go Back To The Main Menu\n\n";
    stack.pop_back();
}

void deleteContacts() {
    this->contacts.clear();
    this->getAllContactNumbers();
    string file = this->emailAccount + "_contacts.txt";
    string file2 = this->emailAccount + "_tempcontacts.txt";
    ifstream f(file);
    ofstream f2(file2);
    if (f.is_open() && f2.is_open()) {
        string line;
        while (getline(f, line)) {
            vector<string> data = split(line, ',');
            if (this->phoneNumber != data[1]) {
                f2 << data[0] << "," << data[1] << "," << data[2] << "," << data[3] << ",\n";
            }
        }
        f.close();
        f2.close();
        cout << "\n\tSuccessfully Deleted\n\tPress Any Key To Go Back To The Main Menu\n\n";
        moveData(file2, file);
        stack.pop_back();
    }
}

void deleteAllContacts() {
    string confirmation;
    cout << "Are You Sure You Want To Delete All Contacts Y/N: ";
    cin >> confirmation;
    string file = this->emailAccount + "_contacts.txt";
    if (ifstream(file) && confirmation == "Y") {
        remove(file.c_str());
        cout << "\n\tSuccessfully Deleted All Contacts\n\tPress Any Key To Go Back To The Main Menu\n\n";
        stack.pop_back();
    }
}

void editContacts() {
    string file = this->emailAccount + "_contacts.txt";
    string file2 = this->emailAccount + "_tempcontacts.txt";
    ifstream x(file);
    ofstream x2(file2);
    if (x.is_open() && x2.is_open()) {
        string line;
        while (getline(x, line)) {
            vector<string> data = split(line, ',');
            if (this->phoneNumber == data[1]) {
                cout << "\tEnter New Name: ";
                cin.ignore();
                getline(cin, this->name);
                cout << "\tEnter New Phone Number: ";
                getline(cin, this->phoneNumber);
                cout << "\tEnter New Email: ";
                getline(cin, this->email);
                cout << "\tEnter Your New Address: ";
                getline(cin, this->address);
                x2 << this->name << "," << this->phoneNumber << "," << this->email << "," << this->address << ",\n";
            }
            else {
                x2 << data[0] << "," << data[1] << "," << data[2] << "," << data[3] << ",\n";
            }
        }
        x.close();
        x2.close();
        cout << "\n\tSuccessfully Edited\n\tPress Any Key To Go Back To The Main Menu\n\n";
        moveData(file2, file);
        stack.pop_back();
    }
}

void searchContacts() {
    this->contacts.clear();
    this->getAllContactNumbers();
    bool var = false;
    string file = this->emailAccount + "_contacts.txt";
    ifstream inputFile(file);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            vector<string> data = split(line, ',');
            int index = binarySearch(this->contacts, 0, this->contacts.size() - 1, stoi(this->phoneNumber));
            if (index == stoi(data[1])) {
                cout << "\tName: " << data[0] << "\n";
                cout << "\tPhone: " << data[1] << "\n";
                cout << "\tEmail: " << data[2] << "\n";
                cout << "\tAddress: " << data[3] << "\n";
                var = true;
            }
        }
        inputFile.close();
    }
    if (!var) {
        cout << "\tNo Contact Found\n";
    }
    stack.pop_back();
}

void moveData(const string& file, const string& file2) {
    ifstream f(file);
    ofstream f1(file2, ios::app);
    if (f.is_open() && f1.is_open()) {
        f1 << f.rdbuf();
        f.close();
        f1.close();
    }
    remove(file.c_str());
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
};
class User {
public:
    string emailAccount;
    string password;

    User(const string& emailAccount, const string& password) {
        this->emailAccount = emailAccount;
        this->password = password;
    }

    void signUp() {
        ofstream outputFile("users.txt", ios::app);
        if (outputFile.is_open()) {
            outputFile << this->emailAccount << "," << this->password << "\n";
            string file = this->emailAccount + "_contacts.txt";
            ofstream outputFile2(file);
            if (outputFile2.is_open()) {
                cout << "\tSign Up Successful\n";
            }
            else {
                cout << "\tError Creating Contact File\n";
            }
            outputFile2.close();
        }
        else {
            cout << "\tError Signing Up\n";
        }
        outputFile.close();
    }

    bool isAccountExist() {
        string email;
        string password;
        ifstream inputFile("users.txt");
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                vector<string> data = split(line, ',');
                if (data.size() >= 2) {
                    email = data[0];
                    password = data[1];
                    if (email == this->emailAccount && password == this->password) {
                        return true;
                    }
                }
            }
            inputFile.close();
        }
        return false;
    }

    void logIn() {
        if (this->isAccountExist()) {
            cout << "\tLog In Successful\n";
            this->mainMenu();
        }
        else {
            cout << "\tInvalid Email or Password\n";
        }
    }

    void mainMenu() {
        int choice;
        while (true) {
            cout << "\n\tMain Menu\n";
            cout << "\t1. Add Contact\n";
            cout << "\t2. Display Contacts\n";
            cout << "\t3. Delete Contact\n";
            cout << "\t4. Delete All Contacts\n";
            cout << "\t5. Edit Contact\n";
            cout << "\t6. Search Contact\n";
            cout << "\t7. Log Out\n";
            cout << "\tEnter Your Choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    this->addContact();
                    break;
                case 2:
                    this->displayContacts();
                    break;
                case 3:
                    this->deleteContacts();
                    break;
                case 4:
                    this->deleteAllContacts();
                    break;
                case 5:
                    this->editContacts();
                    break;
                case 6:
                    this->searchContacts();
                    break;
                case 7:
                    cout << "\tLogging Out\n";
                    return;
                default:
                    cout << "\tInvalid Choice\n";
                    break;
            }
        }
    }

private:
    Contacts contacts;

    void addContact() {
        string name, phoneNumber, email, address;
        cout << "\tEnter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "\tEnter Phone Number: ";
        getline(cin, phoneNumber);
        cout << "\tEnter Email: ";
        getline(cin, email);
        cout << "\tEnter Address: ";
        getline(cin, address);

        this->contacts = Contacts(this->emailAccount, name, phoneNumber, email, address);
        this->contacts.addContact();
    }

    void displayContacts() {
        this->contacts = Contacts(this->emailAccount, "", "", "", "");
        this->contacts.displayContacts();
    }

    void deleteContacts() {
        string phoneNumber;
        cout << "\tEnter Phone Number to Delete: ";
        cin >> phoneNumber;

        this->contacts = Contacts(this->emailAccount, "", phoneNumber, "", "");
        this->contacts.deleteContacts();
    }

    void deleteAllContacts() {
        this->contacts = Contacts(this->emailAccount, "", "", "", "");
        this->contacts.deleteAllContacts();
    }

    void editContacts() {
        string phoneNumber;
        cout << "\tEnter Phone Number to Edit: ";
        cin >> phoneNumber;

        this->contacts = Contacts(this->emailAccount, "", phoneNumber, "", "");
        this->contacts.editContacts();
    }

    void searchContacts() {
        string phoneNumber;
        cout << "\tEnter Phone Number to Search: ";
        cin >> phoneNumber;

        this->contacts = Contacts(this->emailAccount, "", phoneNumber, "", "");
        this->contacts.searchContacts();
    }
};

int main() {
    int choice;
    while (true) {
        cout << "\n\tWelcome to the Contact Management System\n";
        cout << "\t1. Sign Up\n";
        cout << "\t2. Log In\n";
        cout << "\t3. Exit\n";
        cout << "\tEnter Your Choice: ";
        cin >> choice;

        string email, password;
        User user("", "");

        switch (choice) {
            case 1:
                cout << "\tEnter Email: ";
                cin >> email;
                cout << "\tEnter Password: ";
                cin >> password;
                user = User(email, password);
                user.signUp();
                break;
            case 2:
                cout << "\tEnter Email: ";
                cin >> email;
                cout << "\tEnter Password: ";
                cin >> password;
                user = User(email, password);
                user.logIn();
                break;
            case 3:
                cout << "\tExiting the Contact Management System\n";
                return 0;
            default:
                cout << "\tInvalid Choice\n";
                break;
        }
    }
}

