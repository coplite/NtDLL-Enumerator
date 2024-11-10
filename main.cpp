#include <Windows.h>
#include <stdio.h>

int main()
{
	HMODULE ntdll = LoadLibraryA("ntdll.dll");
	IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)ntdll;
	IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((BYTE*)ntdll + dosHeader->e_lfanew);
	IMAGE_EXPORT_DIRECTORY* exportDir = (IMAGE_EXPORT_DIRECTORY*)((BYTE*)ntdll + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	int counter = 0;
	DWORD* AddressOfNamesTable = (DWORD*)((BYTE*)ntdll + exportDir->AddressOfNames);
	WORD* AddressOfOrdinalsTable = (WORD*)((BYTE*)ntdll + exportDir->AddressOfNameOrdinals);
	DWORD* AddressOfFuncs = (DWORD*)((BYTE*)ntdll + exportDir->AddressOfFunctions);
	
	for(int i = 0; i < exportDir->NumberOfNames; ++i)
	{
		char* name = (char*)((BYTE*)ntdll + AddressOfNamesTable[i]);
		DWORD* address = (DWORD*)((BYTE*)ntdll + AddressOfFuncs[(WORD)AddressOfOrdinalsTable[i]]);
		printf("Function: [%s]\n", name);
		printf("\\___[Address: 0x%p]\n", address);
	}
}
