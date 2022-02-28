#include <iostream>
#include <windows.h>

using namespace std;

HANDLE CF()
{
    LPCWSTR  name;
    string select_file;
    cout << "Select a file path:" << endl;
    cin >> select_file;
    name =  (LPCWSTR) (select_file.c_str());
    HANDLE hfile = CreateFile((LPCSTR) name,  GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hfile != INVALID_HANDLE_VALUE){
        cout << "File created" << endl;
        return CreateFileMapping(hfile, NULL, PAGE_READWRITE, 0, 128, TEXT("Local\\MyFileMappingObject"));
    }
    else{
        cout << "Error" << endl;
        return NULL;
    }
}

int main()
{
    HANDLE Map;
    LPVOID Map_1;
    Map = CF();
    if( Map != NULL){
        cout << "File Maping Access!" << endl;
        Map_1 = MapViewOfFile(Map, FILE_MAP_WRITE, 0, 0, 0);
        if(Map_1 == 0 ) cout << "File not projected!" << endl;
        else{
            cout << "The file is projected!" << endl;
            CopyMemory(Map_1, TEXT("TEXT"), 5);
            system("pause");
            UnmapViewOfFile(Map_1);
            cout << "Data recorded!" << endl;
        }
    }
    else
    {
        cout << "File Maping Error!" << endl;    
    }
    return 0;
}