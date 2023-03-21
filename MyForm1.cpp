#include "MyForm1.h"
#include "MyForm2.h"
#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <Psapi.h>

System::Void OS3Framework::MyForm1::SetTable()
{
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) return Void();

	PROCESSENTRY32 procEntr;
	procEntr.dwSize = sizeof(PROCESSENTRY32);
	int count = 1;
	Process32First(snap, &procEntr);
	do {
		String^ r1 = count.ToString();
		String^ r2 = gcnew String(procEntr.szExeFile);
		String^ r3 = procEntr.th32ProcessID.ToString();
		String^ r4 = procEntr.cntThreads.ToString();
		HANDLE op = OpenProcess(PROCESS_QUERY_INFORMATION, false, procEntr.th32ProcessID);
		String^ r5 = "";
		if (op != NULL) {
			int cb = sizeof(PROCESS_MEMORY_COUNTERS);
			PROCESS_MEMORY_COUNTERS pmc;
			if (GetProcessMemoryInfo(op, &pmc, cb)) {
				r5 = (pmc.WorkingSetSize / 1024).ToString() + " Kb";
			}
			else r5 = "Unknown";
		}
		else r5 = "Unknown";
		CloseHandle(op);
		dataGridView1->Rows->Add(r1, r2, r3, r4, r5);
		count++;
	} while (Process32Next(snap, &procEntr));

	CloseHandle(snap);
	return Void();
}

System::Void OS3Framework::MyForm1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox1->Text == "") return System::Void();
	String^ dat = textBox1->Text;
	MyForm2^ secDl2 = gcnew MyForm2(dat);
	secDl2->Show();
	return System::Void();
}

System::Void OS3Framework::MyForm1::dataGridView1_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	
	textBox1->Text = dataGridView1->Rows[e->RowIndex]->Cells["Column3"]->Value->ToString();
	return System::Void();
}
