#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

#pragma comment(lib, "user32")
void addTime(string Id, int Case);

bool isYN(char YN){
    if(YN == 'Y' || YN == 'y'){
        return true;
    }
    else if(YN == 'N' || YN == 'n'){
        return false;
    }
    return false;
}

bool isNum(string id){
    for(int i = 0; i < 9; i++){
        if(!(id[i] >= '0' && id[i] <= '9')){
            return false;
        }
    }      
    return true;
}

bool vaildId(string Id){
    ifstream account;
    string filename;
    filename = ".\\list\\" + Id + ".dat";
    account.open(filename, ios::in);

    if(account.is_open()){
        cout << "학번 조회에 성공했습니다.\n";
        return true;
    }
    else{
        cout << "등록된 학번이 존재하지 않습니다.\n";
        return false;
    }
}

string checkId(){
    string Id;

    while(true){
        cout << "학번 9자리를 입력해주세요 : ";
        cin >> Id;

        if(isNum(Id)){
            return Id;
        }
        else{
            cout << "학번을 재입력해주세요\n";
            continue;
        }
    }
}

void uploadId(string Id, string Pw){
    fstream account;
    string filename;
    filename = ".\\list\\" + Id + ".dat";
    account.open(filename, ios::app);
    account << Pw << "\n\n";
    account.close();
    return;
}

void createAccount(string Id){
    cout << "등록할 학번 : " << Id << "\n";

    while(true){
        string Pw, RePw;
        cout << "비밀번호를 입력해주세요. : ";
        cin >> Pw;
        cout << "비밀번호를 한번 더 입력해주세요. : ";
        cin >> RePw;

        if(Pw == RePw){
            cout << "학번이 등록되었습니다.\n";
            uploadId(Id, Pw);
            addTime(Id, 1);
            system("cls");
            return;
        }
        else{
            cout << "비밀번호가 일치하지 않습니다.\n";
            system("pause");
            system("cls");
            continue;
        }
    }
}

void addTime(string Id, int Case){
    fstream account;
    string filename;
    filename = "log.dat";
    string nowTime;
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);

    struct tm {
        int tm_sec;
        int tm_min;
        int tm_hour;
        int tm_mday;
        int tm_mon;
        int tm_year;
    };

    nowTime = to_string(t->tm_year + 1900) + to_string(t->tm_mon + 1) + to_string(t->tm_mday) + to_string(t->tm_hour) + to_string(t->tm_min) + to_string(t->tm_sec);
    account.open(filename, ios::app);
    account << Id << " ";
    account << nowTime << " ";

    if(Case == 0){
        account << "loginId";
    }
    else if(Case == 1){
        account << "createId";
    }

    account << "\n";
    account.close();
}

int checkPw(string Id){
    fstream account;
    string filename;
    string Pw, Pw2;
    filename = ".\\list\\" + Id + ".dat";
    account.open(filename, ios::in);
    getline(account, Pw2);
    account.close();

    while(true){
        cout << "비밀번호를 입력해주세요. : ";
        cin >> Pw;

        if(Pw == Pw2){
            cout << "비밀번호가 일치합니다.\n";
            return 1;
        }
        else{
            cout << "비밀번호가 일치하지 않습니다.\n";
            return 0;
        }
    }
}

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);    
    #endif

    SetConsoleTitle("Title");
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    while(true){
        string Id;
        Id = checkId();

        if(vaildId(Id)){
            if(checkPw(Id)){
                addTime(Id, 0);
                system("PAUSE");        
                return 0;
            }
            else{
                system("pause");
                system("cls");
                continue;
            }
        }
        else{
            char YN;
            cout << "학번을 등록 또는 재입력해주세요.(Y == 학번 등록 / N == 학번 재입력)\n";
            cin >> YN;

            if(isYN(YN)){
                createAccount(Id);
                continue;
            }
            else{
                cout << "학번을 재입력합니다.\n";
                system("pause");
                system("cls");                
                continue;
            }
        }
    }
}