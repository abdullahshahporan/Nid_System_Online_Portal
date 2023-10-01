/*
Concepts here used are below:
1. Class
2.Object
3.Constructor (Default and Parameterized)
4. Inheritance (base class Informationsystem and derived class anotherclass)
5. Polymorphism
6. Operator overloading
7.Friend Function and class
8. Templates
9. STL
10. File Handling

                               Created By Abdullah Md. ShahPoran
                                       Roll:2107056
                                        Dept.: CSE
                                         Year:1st
                                         term: 2nd
=======================Title: "NID System Online Portal" ====================================
*/
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Information {                     //Class
public:
    char NID[15];
    char fName[30];
    char lName[30];
    char address[50];
    char phone_no[15];
    char email[50];
    char blood_group[5];

    Information() {} // Default constructor

    Information(const char* nid, const char* firstName, const char* lastName, const char* addr,
                const char* phone, const char* mail, const char* bloodGroup) {              //Parameterized Constructor
        strcpy_s(NID, nid);
        strcpy_s(fName, firstName);
        strcpy_s(lName, lastName);
        strcpy_s(address, addr);
        strcpy_s(phone_no, phone);
        strcpy_s(email, mail);
        strcpy_s(blood_group, bloodGroup);
    }

    friend ostream& operator<<(ostream& out, const Information& C);     //Operator Overloading
    friend istream& operator>>(istream& in, Information& C);
};

void gotoxy(int x, int y) {                      //used for proper spacing(cursor moving)
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

ostream& operator<<(ostream& out, const Information& C) {      //Operator Overloading
    gotoxy(37, 14);
    out << "NID: " << C.NID;
    gotoxy(37, 15);
    out << "Name: " << C.fName << " " << C.lName;
    gotoxy(37, 16);
    out << "Address: " << C.address;
    gotoxy(37, 17);
    out << "Phone Number: " << C.phone_no;
    gotoxy(37, 18);
    out << "Email: " << C.email;
    gotoxy(37, 19);
    out << "Blood Group: " << C.blood_group;
    return out;
}

istream& operator>>(istream& in, Information& C) {         //Operator overloading
    int print = 37;
    gotoxy(print, 12);
    cout << "NID: ";
    cin.ignore();
    in>>C.NID;
    gotoxy(print, 13);
    cout << "First Name: ";
    in>>C.fName;
    gotoxy(print, 14);
    cout << "Last Name: ";
    in>>C.lName;
    gotoxy(print, 15);
    cout << "Address: ";
    in>>C.address;
    gotoxy(print, 16);
    cout << "Phone Number: ";
    in>>C.phone_no;
    gotoxy(print, 17);
    cout << "E-mail: ";
    in>>C.email;
    gotoxy(print, 18);
    cout << "Blood Group: ";
    in>>C.blood_group;
    return in;
}

class InformationSystem {                    // Base Class
private:
    vector<Information> infoList;           //To store Info for individuals
    map<string, string> adminDatabase;      // Stores pairs of strings, which is used for log in
    map<string, string> userDatabase;
    Information C;

public:
    void virtual main_window() = 0;          //Virtual Function
    void virtual UserMainWindow() =0;        //Virtual Function
    virtual void regAndLogin()=0;            //Virtual Function
    void loginAsAdmin();
    void loginAsUser();
    void registerUser();
    void SetColor(int ForgC);
    void ClearConsoleToColors(int ForgC, int BackC);
    void SetColorAndBackground(int ForgC, int BackC);
    void gotoxy(int x, int y);
    void boxBorder();
    void window();
    void print_heading(const char title[]);
    void clearWindow();
    void add_info();
    void find_info();
    void display();
    void edit_info();
    void delete_info();
};
template <typename name, typename id>       //Template
class MyPair {
    name NAME;
    id PASS;
public:
    MyPair(){}
    MyPair(name _n, id _i) {
        NAME = _n;
        PASS = _i;
    }

    friend class InformationSystem;            //Friend class declaration
};
void InformationSystem::loginAsAdmin() {
    SetColor(10);
    gotoxy(25,7);
    cout << "Editor Login Page" << endl;
    gotoxy(15,8);
    cout << "This is the login page for the editor" << endl;
    gotoxy(15,9);
    cout << "This Page is password Protected" << endl;
    gotoxy(15,10);
    cout << "Enter Valid administrator Password to Enter" << endl;

    int count = 0;
    MyPair<string, string> pairarr;
    string inusername, pass;
    SetColor(17);
    gotoxy(20,15);
    cout << "USERNAME: ";
    cin >> pairarr.NAME;
    gotoxy(20,16);
    cout << "PASSWORD: ";
    cin >> pairarr.PASS;
    ifstream input("AdminsDataBase.txt");
    while(input >> inusername >> pass){
        if(inusername == pairarr.NAME && pass == pairarr.PASS){
            count = 1;
        }
    }
    input.close();
    if(count == 1){
        cout << "Hello " << pairarr.NAME << endl;
        cout << "Login Successful" << endl;
        system("cls");
        window();
        main_window();
    }
    else{
        system("cls");
        window();
        gotoxy(15,11);
        cout << "Login Failed" << endl;
        gotoxy(15,12);
        cout << "Please Try Again" << endl;
        loginAsAdmin();
    }
}

class anotherClass : public InformationSystem {          //Derived Class
public:
 void main_window () {         //function overrides
    SetColor(28);
    int choice;
    int x = 2;
    while(1){
        gotoxy(x,8);
        cout << "1. Add Information";
        gotoxy(x,10);
        cout << "2. Find Information";
        gotoxy(x,12);
        cout << "3. Display Information";
        gotoxy(x,14);
        cout << "4. Edit Information";
        gotoxy(x,16);
        cout << "5. Delete Information";
        gotoxy(x,18);
        cout << "6. Sign Out";
        gotoxy(x,20);
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                add_info();
                break;
            case 2:
                find_info();
                break;
            case 3:
                display();
                break;
            case 4:
                edit_info();
                break;
            case 5:
                delete_info();
                break;
            case 6:
                clearWindow();
                system("cls");
                window();
                regAndLogin();
                break;
            default:
                break;
        }
    }
}
void UserMainWindow() {          //function overrides
    SetColor(28);
    int choice;
    int x = 2;
    while(1){
        gotoxy(x,8);
        cout << "1. Add Information";
        gotoxy(x,10);
        cout << "2. Find Information";
        gotoxy(x,12);
        cout << "3. Display Information";
        gotoxy(x,14);
        cout << "4. Edit Information";
        gotoxy(x,18);
        cout << "5. Sign Out";
        gotoxy(x,20);
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                add_info();
                break;
            case 2:
                find_info();
                break;
            case 3:
                display();
                break;
            case 4:
                edit_info();
                break;
            case 5:
                clearWindow();
                system("cls");
                window();
                regAndLogin();
                break;
            default:
                break;
        }
    }
}
void regAndLogin() {          //function overrides
    int choice;
    SetColor(10);
    gotoxy(1, 7);
    cout << "________________________Main Menu______________________\n";
    gotoxy(1, 8);
    cout << "1. Login As Editor" << endl;
    gotoxy(1, 9);
    cout << "2. Login as Public User" << endl;
    gotoxy(1, 10);
    cout << "3. Register (Only for public User!)" << endl;
    gotoxy(1, 11);
    cout << "4. Exit" << endl;
    gotoxy(1, 13);
    SetColor(1024);

    cout<<"Rules And Regulations:"<<endl;
    cout<<"a.You have to set your NID as atleast 9 digit. Remember that the first number\n will be treated as city code.To find or display details you have to remove that number."<<endl;
    cout<<"b.Don't give wrong Information"<<endl;
    cout<<endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        window();
        loginAsAdmin();
        break;
    case 2:
        system("cls");
        window();
        loginAsUser();
        break;
    case 3:
        system("cls");
        window();
        registerUser();
        gotoxy(1, 12);
        cout << "Thank you for Registering" << endl;
        regAndLogin();
        break;
    case 4:
        cout << "Thank You" << endl;
        exit(0);
        break;
    default:
        cout << "Invalid Choice" << endl;
        system("cls");
        window();
        gotoxy(1, 12);
        regAndLogin();
    }

}
};

void InformationSystem::loginAsUser() {
    SetColor(10);
    gotoxy(25,7);
    cout << "Public User Login Page" << endl;
    gotoxy(15,8);
    cout << "This is the login page for Public User" << endl;
    gotoxy(15,9);
    cout << "This Page is Protected" << endl;
    gotoxy(15,10);
    cout << "Enter Password to Enter" << endl;

    int count = 0;
    string username, password, id, pass;
    SetColor(17);
    gotoxy(20,15);
    cout << "Your NAME: ";
    cin >> username;
    gotoxy(20,16);
    cout << "YOUR Password: ";
    cin >> password;
    ifstream input("UserDataBase.txt");
    while(input >> id >> pass){
        if(id == username && pass == password){
            count = 1;
        }
    }
    input.close();
    if(count == 1){
        cout << "Hello " << username << endl;
        cout << "Login Successful" << endl;
        system("cls");
        window();
        UserMainWindow();
    }
    else{
        system("cls");
        window();
        gotoxy(15,11);
        cout << "Login Failed" << endl;
        gotoxy(15,12);
        cout << "Please Try Again" << endl;
        loginAsUser();
    }
}

void InformationSystem::registerUser() {
    SetColor(10);
    gotoxy(25,7);
    cout << "Public User Registration Page" << endl;
    gotoxy(15,8);
    cout << "This is the Registration page for Public User" << endl;
    gotoxy(15,9);
    cout << "Enter name & Valid NID Serial No" << endl;

    int count = 0;
    string username, NID, id, pass;
    SetColor(17);
    gotoxy(20,15);
    cout << "Your NAME: ";
    cin >> username;
    gotoxy(20,16);
    cout << "YOUR PASSWORD: ";
    cin >> NID;
    ofstream reg("UserDataBase.txt", ios::app);
    reg << username << ' ' << NID << endl;
    reg.close();
    cout << "Registration Successful. Now add Your information" << endl;
    system("cls");
    window();
    regAndLogin();
}

void InformationSystem::add_info() {
    clearWindow();
    SetColor(10);
    print_heading(" -- Add Information -- ");
    int print = 37;
    char n_id[15];
    int isFound = 0;
    gotoxy(37, 10);
    cout << "Correct NID: ";
    fflush(stdin);
    cin.ignore();  // Use cin.ignore() instead of fflush(stdin) to clear the input buffer
    cin.getline(n_id, 15);

    // Check if the ID already exists
    for (const Information& info : infoList) {
        if (strcmp(n_id, info.NID) == 0) {
            isFound = 1;
            gotoxy(1, 22);
            cout << "Information already exists.";
            break;
        }
    }

    if (isFound == 0) {
        if (strlen(n_id) <= 8) {
            gotoxy(37, 12);
            cout << "ID must be greater than 8 characters";
        } else {
            // Populate the Information object
            C.NID[0] = '\0';  // Clear the existing content
            strcpy_s(C.NID, n_id);
            gotoxy(print, 12);
            cout << "First Name: ";
            cin.getline(C.fName, 30);
            gotoxy(print, 13);
            cout << "Last Name: ";
            cin.getline(C.lName, 30);
            gotoxy(print, 14);
            cout << "Address: ";
            cin.getline(C.address, 50);
            gotoxy(print, 15);
            cout << "Phone Number: ";
            cin.getline(C.phone_no, 15);
            gotoxy(print, 16);
            cout << "Email: ";
            cin.getline(C.email, 50);
            gotoxy(print, 17);
            cout << "Blood Group: ";
            cin.getline(C.blood_group, 5);

            // Append the new record to the vector and file
            infoList.push_back(C);
            ofstream outfile("publicInfo.txt", ios::app);
            outfile << "NID: " << C.NID << endl;
            outfile << "Name: " << C.fName << " " << C.lName << endl;
            outfile << "Contact No.: " << C.phone_no << endl;
            outfile << "E-mail: " << C.email << endl;
            outfile << "Blood Group: " << C.blood_group << endl;
            outfile << "Address: " << C.address << endl;
            outfile << endl;
            outfile.close();

            gotoxy(40, 24);
            cout << "Information is added successfully.";
        }
    }
    SetColor(28);
}
void InformationSystem::find_info() {
    clearWindow();
    SetColor(10);
    print_heading(" -- Find Information -- ");
    char n_id[15];
    int isFound = 0;
    gotoxy(37, 10);
    cout << "Enter NID: ";
    fflush(stdin);
    gets(n_id);
    ifstream data("publicInfo.txt");
    string line;
    bool found = false;

    while (getline(data, line)) {
        if (line.find("NID: " + string(n_id)) != string::npos) {
            found = true;
            gotoxy(37, 12);
            cout << "Information Found for NID: " << n_id << endl << endl;
            for (int i = 0; i < 6; i++) {
                getline(data, line);
                gotoxy(37, 14 + i);
                cout << line << endl;
            }
            break;
        }
    }

    if (!found) {
        gotoxy(37, 12);
        cout << "Sorry, We don't have any information for NID: " << n_id << endl;
    }
    SetColor(28);
    data.close();
    return;
}
void InformationSystem::display() {
    clearWindow();
    SetColor(10);
    print_heading(" -- Display Information -- ");
    char n_id[15];
    int isFound = 0;
    gotoxy(37, 10);
    cout << "Enter NID: ";
    fflush(stdin);
    gets(n_id);
    ifstream data("publicInfo.txt");
    string line;
    bool found = false;

    while (getline(data, line)) {
        if (line.find("NID: " + string(n_id)) != string::npos) {
            found = true;
            gotoxy(37, 12);
            cout << "Information Found for NID: " << n_id << endl << endl;
            for (int i = 0; i < 6; i++) {
                getline(data, line);
                gotoxy(37, 14 + i);
                cout << line << endl;
            }
            break;
        }
    }
    if (!found) {
        gotoxy(37, 12);
        cout << "Sorry, We don't have any information for NID: " << n_id << endl;
    }
    SetColor(28);
    data.close();
    return;
}
void InformationSystem::edit_info() {
    clearWindow();
    SetColor(10);
    print_heading(" -- Edit Information -- ");
    char n_id[15];
    int isFound = 0;
    gotoxy(37,10);
    cout << "Enter NID: ";
    fflush(stdin);
    gets(n_id);
    FILE *data;
    data = fopen("publicInfo.txt","r+");
    while(fread(&C, sizeof(C),1,data) == 1){
        if(strcmp(n_id, C.NID) == 0){
            fflush(stdin);
            cin >> C;
            fseek(data, -sizeof(C), SEEK_CUR);
            fwrite(&C,sizeof(C), 1, data);
            gotoxy(40,20);
            cout << "Information is updated successfully.";
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        gotoxy(37, 12);
        cout << "Sorry, We don't have any information about you.";
    }
    fclose(data);
    SetColor(28);
    return;
}
void InformationSystem::delete_info() {
    clearWindow();
    SetColor(10);
    print_heading(" -- Delete Information -- ");
    char n_id[15];
    gotoxy(37,10);
    cout << "Enter NID: ";
    fflush(stdin);
    gets(n_id);
    FILE *data, *backup;
    data = fopen("publicInfo.txt","r");
    backup = fopen("temp.txt", "w");
    while(fread(&C, sizeof(C),1,data) == 1){
        if(strcmp(n_id, C.NID) == 0){
            fwrite(&C,sizeof(C),1,backup);
        }
    }
    fclose(data);
    fclose(backup);
    rename("publicInfo.txt","backup.txt");
    remove("temp.txt");
    gotoxy(37,12);
    cout << "Information is deleted successfully.";
    SetColor(28);
    return;
}

void InformationSystem::SetColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        wColor = (csbi.wAttributes & 0xE0) + (ForgC & 0x0E);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void InformationSystem::ClearConsoleToColors(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0E) << 4) + (ForgC & 0x0E);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute(hStdOut, wColor);
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
        SetConsoleCursorPosition(hStdOut, coord);
    }
    return;
}

void InformationSystem::SetColorAndBackground(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0E);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);

}

COORD coord = {0,0};

void InformationSystem::gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void InformationSystem::window() {
    SetColor(12);
    gotoxy(10,1);
    cout << "\tBangladesh NID system online portal";
    SetColor(10);
    gotoxy(1,2);
    cout << "==========================================================================";
    SetColor(1024);
    gotoxy(1,3);
    cout << "\t\t  People's Republic Of Bangladesh"<<endl ;
    cout << "   This site is created and reserved by Bangladesh Election Commission";
    SetColor(17);
}

void InformationSystem::print_heading(const char title[]) {
    SetColor(10);
    SetColorAndBackground(31,3);
    gotoxy(45,8);
    cout << title;
    SetColorAndBackground(17,15);
}

void InformationSystem::clearWindow() {
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);
            cout << " ";
        }
    }
}

int main() {
    InformationSystem *system = new anotherClass();
    system->ClearConsoleToColors(0, 1023);
    system->window();       // Calls the overridden function in anotherClass
    system->regAndLogin();
    return 0;
}

