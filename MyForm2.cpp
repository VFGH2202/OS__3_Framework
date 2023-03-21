#include "MyForm2.h"
#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <Psapi.h>
#include <memoryapi.h>
#include <sysinfoapi.h>


System::Void OS3Framework::MyForm2::SetTab2()
{
	DWORD cs = UINT32::Parse(selectedID);
	HANDLE op = OpenProcess(0x00000400, false, cs);
	UINT64 addr = 0;
	MEMORY_BASIC_INFORMATION* mbi = new MEMORY_BASIC_INFORMATION();
	SYSTEM_INFO s;
	GetSystemInfo(&s);
	addr = (UINT64)s.lpMinimumApplicationAddress;
	while (addr <= (UINT64)s.lpMaximumApplicationAddress) {
		VirtualQueryEx(op, (LPCVOID)addr, mbi, sizeof(MEMORY_BASIC_INFORMATION));
		String^ r1 = ((UINT64)mbi->BaseAddress).ToString();
		String^ r22 = (mbi->RegionSize/1024).ToString();
		String^ r2;
		switch (mbi->Type)
		{
		case MEM_PRIVATE:
			r2 = "Private";
			break;
		case MEM_MAPPED:
			r2 = "Mapped";
			break;
		case MEM_IMAGE:
			r2 = "Image";
			break;
		default:
			r2 = "Unknown";
			break;
		}
		String^ r3;
		switch (mbi->State)
		{
		case MEM_COMMIT:
			r3 = "Commit";
			break;
		case MEM_RESERVE:
			r3 = "Reserve";
			break;
		case MEM_FREE:
			r3 = "Free";
			break;
		default:
			r3 = "Unknown";
			break;
		}
		String^ r4;
		switch (mbi->Protect)
		{
		case PAGE_READWRITE:
			r4 = "ReadWrite";
			break;
		case PAGE_READONLY:
			r4 = "ReadOnly";
			break;
		case PAGE_WRITECOPY:
			r4 = "WriteCopy";
			break;
		case PAGE_EXECUTE:
			r4 = "Execute";
			break;
		case PAGE_EXECUTE_READ:
			r4 = "Execute_Read";
			break;
		case PAGE_EXECUTE_READWRITE:
			r4 = "Execute_ReadWrite";
			break;
		case PAGE_EXECUTE_WRITECOPY:
			r4 = "Execute_WriteCopy";
			break;
		case PAGE_GUARD:
			r4 = "Guard";
			break;
		case PAGE_NOACCESS:
			r4 = "NoAccess";
			break;
		case PAGE_NOCACHE:
			r4 = "NoCache";
			break;
		default:
			r4 = "Unknown";
			break;
		}
		dataGridView1->Rows->Add(r1, r2, r22, r3, r4);
		addr += (UINT64)mbi->RegionSize;
	}

	CloseHandle(op);
	return Void();
}


