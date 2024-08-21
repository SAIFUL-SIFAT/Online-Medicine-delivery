#include "online_medicine_delivery.h"

Information info;
fstream file;

void slipPrint(int voucher, char location, int item[][2], int selection, const char* emailAddress) {
    file.open("Information.txt", ios::in);

    system("clear");

    cout << "\n\n                                    Payment Slip Print\n";
    cout << "-----------------------------------------------------------------------------------------------\n\n";
    
    while (file.read(reinterpret_cast<char*>(&info), sizeof(info))) {
        if (strcmp(info.email, emailAddress) == 0) {
            cout << "Name: " << info.name << "\nAddress: " << info.address << "\nNumber: " << info.number << "\n\n";
        }
    }
    
    cout << "       Medicine Name                   Quantity                  Price\n";
    cout << "---------------------------------------------------------------------------\n";
    int i = 0, total = 0;
    while (i < selection) {
        switch (item[i][0]) {
            case 1:
                cout << "Paracetamol                              " << item[i][1] << "                      " << item[i][1] * 10 << "\n";
                total += item[i][1] * 10;
                break;
            case 2:
                cout << "Ibuprofen                                " << item[i][1] << "                      " << item[i][1] * 12 << "\n";
                total += item[i][1] * 12;
                break;
            case 3:
                cout << "Amoxicillin                              " << item[i][1] << "                      " << item[i][1] * 15 << "\n";
                total += item[i][1] * 15;
                break;
            case 4:
                cout << "Cough Syrup                              " << item[i][1] << "                      " << item[i][1] * 20 << "\n";
                total += item[i][1] * 20;
                break;
            case 5:
                cout << "Vitamin C                                " << item[i][1] << "                      " << item[i][1] * 25 << "\n";
                total += item[i][1] * 25;
                break;
            case 6:
                cout << "Allergy Tablets                          " << item[i][1] << "                      " << item[i][1] * 18 << "\n";
                total += item[i][1] * 18;
                break;
            case 7:
                cout << "Pain Relief Cream                        " << item[i][1] << "                      " << item[i][1] * 22 << "\n";
                total += item[i][1] * 22;
                break;
            case 8:
                cout << "Antiseptic Lotion                        " << item[i][1] << "                      " << item[i][1] * 14 << "\n";
                total += item[i][1] * 14;
                break;
            case 9:
                cout << "Antacid                                  " << item[i][1] << "                      " << item[i][1] * 8 << "\n";
                total += item[i][1] * 8;
                break;
            case 10:
                cout << "Cold Medicine                            " << item[i][1] << "                      " << item[i][1] * 30 << "\n";
                total += item[i][1] * 30;
                break;
            default:
                cout << "Unknown Medicine                         " << item[i][1] << "                      " << item[i][1] * 0 << "\n";
                break;
        }
        i++;
    }
    
    cout << "---------------------------------------------------------------------------\n";
    cout << "                                                              = " << total << "\n";
    cout << "Adding " << voucher << "% off\n";
    int delivery = (location == 'y' || location == 'Y') ? 50 : 100;
    cout << "Delivery Charge +" << delivery << "TK\n";
    cout << "---------------------------------------------------------------------------\n";
    float result = total - (total * (static_cast<float>(voucher) / 100)) + delivery;
    cout << "Total Bill with delivery charge                               = " << result << "\n";
    
    file.close();
    cout << "\nThanks for ordering :) \n";
    exit(0);
}

void mainPage(const char* emailAddress, const char* pass) {
    file.open("Information.txt", ios::in);

    system("clear");

    int selection;
    cout << "\n                                 Online Medicine Delivery Service\n";
    cout << "-----------------------------------------------------------------------------------------------\n\n";
    cout << "    Available Item Code           Medicine Name                Quantity             Price            \n";
    cout << "-----------------------------------------------------------------------------------------------\n";
    cout << "              1                 Paracetamol                     1                  10 TK\n";
    // Add other medicines similarly
    cout << "-----------------------------------------------------------------------------------------------\n\n";

    while (file.read(reinterpret_cast<char*>(&info), sizeof(info))) {
        if (strcmp(info.email, emailAddress) == 0 && strcmp(info.password, pass) == 0) {
            cout << "Name: " << info.name << "\nAddress: " << info.address << "\nEmail: " << info.email << "\n\n";
        }
    }

    cout << "How many items do you want to buy: ";
    cin >> selection;

    int item[selection][2];
    int i = 0;
    while (i < selection) {
        cout << i + 1 << ". Input item code: ";
        cin >> item[i][0];
        cout << i + 1 << ". Input item quantity: ";
        cin >> item[i][1];
        i++;
    }
    
    char location;
    cin.ignore();
    cout << "Are you inside Dhaka(y/n): ";
    cin >> location;

    char coupon[50];
    const char c1[] = "medic15", c2[] = "medic10", c3[] = "medic5";
    cin.ignore();
    cout << "Do you have any coupon (if yes then input the code or else input n/N): ";
    cin.getline(coupon, 50);

    int voucher = 0;
    if (strcmp(c1, coupon) == 0) voucher = 15;
    else if (strcmp(c2, coupon) == 0) voucher = 10;
    else if (strcmp(c3, coupon) == 0) voucher = 5;

    slipPrint(voucher, location, item, selection, emailAddress);
    file.close();
}

void logIn() {
    file.open("Information.txt", ios::in);

    system("clear");
    char emailAddress[50], pass[50];
    int count = 0;

    cin.ignore();
    cout << ">> Input Email: ";
    cin.getline(emailAddress, sizeof(emailAddress));

    cout << ">> Input Password: ";
    cin.getline(pass, sizeof(pass));

    while (file.read(reinterpret_cast<char*>(&info), sizeof(info))) {
        if (strcmp(info.email, emailAddress) == 0 && strcmp(info.password, pass) == 0) {
            count = 1;
        }
    }

    if (count == 0) {
        cout << "Invalid Email or Password";
        return;
    } else {
        mainPage(emailAddress, pass);
    }

    file.close();
}

void create() {
    file.open("Information.txt", ios::app);

    system("clear");
    cout << ">>Please input the information required for sign up<<\n\n";

    cin.ignore();
    cout << ">> Name: ";
    cin.getline(info.name, sizeof(info.name));

    cout << ">> Address: ";
    cin.getline(info.address, sizeof(info.address));

    cout << ">> Number: ";
    cin.getline(info.number, sizeof(info.number));

    cout << ">> Email: ";
    cin.getline(info.email, sizeof(info.email));

    cout << ">> Password: ";
    cin.getline(info.password, sizeof(info.password));

    file.write(reinterpret_cast<char*>(&info), sizeof(info));
    file.close();
}

void signUp() {
    system("clear");

    int selection;
    cout << "1. Create an account\n";
    cout << "2. Already have an account\n";
    cout << "Input 1 or 2: ";
    cin >> selection;

    switch (selection) {
    case 1:
        create();
        break;
    case 2:
        logIn();
        break;
    default:
        cout << "Please input the correct digit.\n";
    }
}

int main() {
    system("clear");

    int selection = -1;
    cout << "\n                            Welcome To Online Medicine Delivery Service\n";
    cout << "----------------------------------------------------------------------------------------------\n";

    while (selection != 0) {
        cout << "\n                                         0. Exit\n";
        cout << "                                         1. Sign Up\n";
        cout << "                                         2. Log In\n\n\n";
        cout << "Input 0 or 1 or 2: ";
        cin >> selection;

        switch (selection) {
        case 0:
            break;
        case 1:
            signUp();
            break;
        case 2:
            logIn();
            break;
        default:
            cout << "Please input the correct digit.\n";
        }
    }
    return 0;
}
