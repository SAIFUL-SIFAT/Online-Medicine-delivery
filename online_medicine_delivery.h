#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Information {
    char name[50];
    char address[50];
    char number[15];
    char email[50];
    char password[50];
};

void slipPrint(int voucher, char location, int item[][2], int selection, const char* emailAddress);
void mainPage(const char* emailAddress, const char* pass);
void logIn();
void create();
void signUp();
