#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HANDLE Map;
    LPVOID Map_1;
    Map =  OpenFileMapping(FILE_MAP_READ, false, TEXT("Local\\MyFileMappingObject"));
    if( Map != NULL){
        cout << "File Maping Access!" << endl;
        Map_1 = MapViewOfFile(Map, FILE_MAP_READ, 0, 0, 0);
        if(Map_1 == 0 ) cout << "File not projected!" << endl;
        else{
            cout << "The file is projected!" << endl;
            cout << (char*)(Map_1) << endl;
            UnmapViewOfFile(Map_1);
        }
    }
    else{
        cout << "File Maping Error!" << endl;
        cout << GetLastError() << endl;
        return 0;
    }
    
    return 0;
}