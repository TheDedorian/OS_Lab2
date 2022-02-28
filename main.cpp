#include <iostream>
#include <Windows.h>

using namespace std;

void Menu()
{
    cout << "1 - Information Systems" << endl;
    cout << "2 - Information Memory" << endl;
    cout << "3 - Information Memory at a certain address" << endl;
    cout << "4 - Reservation Memory" << endl;
    cout << "5 - Reservation Memory 2" << endl;
    cout << "6 - Input Data Memory" << endl;
    cout << "7 - Protect Memory" << endl;
    cout << "0 - Exit Program" << endl;
}

void SystemInfo() //GetSystemInfo
{
    SYSTEM_INFO SysInfo; //SY structure
    GetSystemInfo(&SysInfo);
    cout <<"Processor type: "<< SysInfo.wProcessorArchitecture << endl;
    cout <<"Type guide: 9 = x64 (AMD or Intel), 6 = Intel Itanium Family, 0 = x86." << endl;
    cout <<"OEM ID: " << SysInfo.dwOemId << endl; 
    cout <<"Number of processors: " << SysInfo.dwNumberOfProcessors << endl;
    cout <<"Page size: " << SysInfo.dwPageSize << endl;
    cout <<"Processor type:" <<  SysInfo.dwProcessorType << endl;
    cout <<"Minimum application address: " << SysInfo.lpMinimumApplicationAddress << endl;
    cout <<"Maximum application address: " << SysInfo.lpMaximumApplicationAddress << endl;
    cout <<"Active processor mask: " << SysInfo.dwActiveProcessorMask << endl;
    cout <<"Granularity for the starting address where virtual memory can be allocated: " << SysInfo.dwAllocationGranularity << endl;
    cout <<"Architecture dependent processor level: " << SysInfo.wProcessorLevel << endl;
    cout <<"Architecture dependent processor revision: " << SysInfo.wProcessorRevision << endl;
}

void VirtualMemory()
{
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
	cout <<"RAM: "<< ms.dwTotalPhys << endl;
	cout <<"Procent RAM used now: "<< ms.dwMemoryLoad << endl;
	cout <<"Free RAM space: "<< ms.dwAvailPhys << endl;
	cout << "Sizeof  bytes: " << ms.dwLength << endl;
    cout << "Physical memory plus the size of the page file: " << ms.dwTotalPageFile << endl;
    cout << "Free bytes of page file: " << ms.dwAvailPageFile << endl;
    cout << "The size of the user-mode portion of the virtual address space: " << ms.dwTotalVirtual << endl;
    cout << "The amount of unreserved and uncommitted memory currently in the user-mode portion of the virtual address space: " << ms.dwAvailVirtual;
}

void AddressStatus()
{
	LPVOID lpAddress;
    MEMORY_BASIC_INFORMATION lpBuffer;
	SIZE_T s;
    s = sizeof(lpBuffer);
    
    cout << "Input adress memory: " << endl;
    cin >> lpAddress;
    
    s = VirtualQuery(lpAddress, &lpBuffer, s);
    if (s != 0){
        cout << "Base Adress: " << lpBuffer.BaseAddress << endl; // Сообщает то же значение, что и параметр lpAddress, но округленное до ближайшего меньшего адреса, кратного размеру страницы
        cout << "AllocationBase: " << lpBuffer.AllocationBase << endl; // Идентифицирует базовый адрес региона, включающего в себя адрес, указанный в параметре lpAddress
        cout << "AllocationProtect: " << lpBuffer.AllocationProtect << endl; // Идентифицирует атрибут защиты, присвоенный региону при его резервировании
        cout << "RegionSize: " << lpBuffer.RegionSize << endl; // Сообщает суммарный размер (в байтах) группы страниц, которые начинаются с базового адреса BaseAddress и имеют те же атрибуты защиты, состояние и тип, что и страница, расположенная по адресу, указанному в параметре lpAddress
        cout << "Protect: " << lpBuffer.Protect << endl; //Идентифицирует атрибут защиты (PAGE_*) всех смежных страниц, которые имеют те же атрибуты защиты, состояние и тип, что и страница, располо-женная по адресу, указанному в параметре lpAddress
        
        if( lpBuffer.State == MEM_COMMIT){
            cout << "Ficksation Page " << endl;
        }
        else if( lpBuffer.State == MEM_FREE ){
            cout << "Free Page .... " << endl;
        }
        else if( lpBuffer.State == MEM_RESERVE ){
            cout << "Rezerv Page" << endl;
        }
        
        cout << "Memory type: ";
        
        switch(lpBuffer.Type) {
            case MEM_PRIVATE:
                cout << "MEM_PRIVATE" << endl; 
                break;
            case MEM_IMAGE:
                cout << "MEM_IMAGE" << endl;
                break;
            case MEM_MAPPED:
                cout << "MEM_MAPPED" << endl;
                break;
            default:
                cout << "NO TYPE" << endl;
                break;
        }
    }
    else{
        cout << "Error!" << endl;
    }
}

void FirstAlloc()
{
	BOOL free;
    cout << "Auto reserving mode." << endl;
    SIZE_T dwSize = 10;
    LPVOID lpAddress1 = NULL, lpAddress2 = NULL;
    lpAddress1 = VirtualAlloc(NULL, dwSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (lpAddress1 != NULL)
	{
			cout << "Reserved! Basic region address 0х"<< lpAddress1 << endl;
			cout << "Reserving with input mode." << endl;
			cout << "Input address: 0x";
			cin >> lpAddress2;
			lpAddress1 = VirtualAlloc(lpAddress2, dwSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (lpAddress1!=NULL) cout << "Reserved! Basic region address 0х"<< lpAddress1 << endl;
			else cout << "Error" << endl;
	}
	else cout << "Error" << endl;

	free = VirtualFree(lpAddress1, 0, MEM_RELEASE);
    if (free != 0 ){
        cout << "Memory Cleaned!" << endl;
    }
    else{
        cout << "No Cleaned Memory!" << endl;
    }
}

void SecondAlloc()
{
	BOOL free;
    cout << "Auto reserving and highlighting mode." << endl;
    SIZE_T dwSize = 10;
    LPVOID lpAddress1 = NULL, lpAddress2 = NULL;
    lpAddress1 = VirtualAlloc(NULL, dwSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (lpAddress1 != NULL)
	{
			cout << "Reserved and highlighted! Basic region address 0х"<< lpAddress1 << endl;
			cout << "Reserving and highlighting with input mode." << endl;
			cout << "Input address: 0x";
			cin >> lpAddress2;
			lpAddress1 = VirtualAlloc(lpAddress2, dwSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (lpAddress1!=NULL) cout << "Reserved and highlighted! Basic region address 0х"<< lpAddress1 << endl;
			else cout << "Error" << endl;
	}
	else cout << "Error" << endl;

	free = VirtualFree(lpAddress1, 0, MEM_RELEASE);
    if (free != 0 ){
        cout << "Memory Cleaned!" << endl;
    }
    else{
        cout << "No Cleaned Memory!" << endl;
    }
}

void Input()
{
    /*LPVOID adr=NULL;
	CHAR* c_tmp = NULL;
	string tmp="";
	cout << "Input data" << endl;
	cin >> tmp;
	cout << "Input address" << endl;
	cin >> adr;
	SIZE_T len = tmp.length() * sizeof(CHAR);
	if (adr != NULL)
	{
		c_tmp = (CHAR*)adr;
		CopyMemory(c_tmp, tmp.c_str(), len);
		cout << "Ok" << endl;
	}
	else cout << "ADR=NULL" << endl;*/
	LPVOID address;
    SIZE_T dwSize=10;
    PVOID p;
	BOOL free;
    
    cout << "Input address (0 - Auto):"<< endl;
    cin >> address;
    p = VirtualAlloc(address, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if(p == 0) {
        cout << "Memory no highlighted" << endl;
	
    } else cout <<"Ok! Address 0х" << p << endl;

	free = VirtualFree(p, 0, MEM_RELEASE);
    if (free != 0 ){
        cout << "Memory Cleaned!" << endl;
    }
    else{
        cout << "No Cleaned Memory!" << endl;
    }
}

void ProtectionMenu(DWORD Pm) //Pro
{
	switch (Pm)
	{
	case 0:
		cout << "Access error" << endl;
		break;
	case PAGE_EXECUTE:
		cout << "Enables execute access to the committed region of pages. (PAGE_EXECUTE)" << endl;
		break;
	case PAGE_EXECUTE_READ:
		cout << "Enables execute or read-only access to the committed region of pages. (PAGE_EXECUTE_READ)" << endl;
		break;
	case PAGE_EXECUTE_READWRITE:
		cout << "Enables execute, read-only, or read/write access to the committed region of pages. (PAGE_EXECUTE_READWRITE)" << endl;
		break;
	case PAGE_EXECUTE_WRITECOPY:
		cout << "Enables execute, read-only, or copy-on-write access to a mapped view of a file mapping object. (PAGE_EXECUTE_WRITECOPY)" << endl;
		break;
	case PAGE_NOACCESS:
		cout << "Disables all access to the committed region of pages. (PAGE_NOACCESS)" << endl;
		break;
	case PAGE_READONLY:
		cout << "Enables read-only access to the committed region of pages. (PAGE_READONLY)" << endl;
		break;
	case PAGE_READWRITE:
		cout << "Enables read-only or read/write access to the committed region of pages.  (PAGE_READWRITE)" << endl;
		break;
	case PAGE_WRITECOPY:
		cout << "Enables read-only or copy-on-write access to a mapped view of a file mapping object. (PAGE_WRITECOPY)" << endl;
		break;
	}
	if ((Pm & PAGE_GUARD) != 0)
	{
		cout << "Pages in the region become guard pages (PAGE_GUARD)" << endl;
	}
	if ((Pm & PAGE_NOCACHE) != 0)
	{
		cout << "Sets all pages to be non-cachable (PAGE_NOCACHE)" << endl;
	}
	if ((Pm & PAGE_WRITECOMBINE) != 0)
	{
		cout << "Sets all pages to be write-combined. (PAGE_WRITECOMBINE)" << endl;
	}
}

void Protection()
{
	BOOL B=FALSE;
	LPVOID adr = NULL;
	DWORD NPro=0;
	DWORD OPro=0;
	cout << "Input address: 0x";
	cin >> adr;
	if (adr != NULL) {
		cout << "Input new protection level:" << endl;
		cin >> NPro;
		cout << "New protection level: ";
		ProtectionMenu(NPro);
		cout << "===========================================" << endl << endl;
		B = VirtualProtect(adr, sizeof(DWORD), NPro, &OPro);
		if (B != 0)
		{
			cout << "Old protect level"<<endl;
			ProtectionMenu(OPro);
		}
		else cout << "Error.";

	}
	else cout << "Address empty" << endl;
}

int main()
{
    Menu();
	int c;
	do {
		cin >> c;
		switch (c)
		{
		case 1:
			SystemInfo();
			break;
		case 2:
			VirtualMemory();
			break;
		case 3:
			AddressStatus();
			break;
		case 4:
			FirstAlloc();
			break;
		case 5:
			SecondAlloc();
			break;
		case 6:
			Input();
			break;
		case 7:
			Protection();
			break;
		case 0:
			system("cls");
			break;
		default:
			system("cls");
			cout << "Wrong!" << endl;
			break;

		}
	} 
	while (c);
	
	return 0;
}