#include "MyForm.h"
#include "MyForm1.h"
#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	OS3Framework::MyForm form;
	Application::Run(% form);

	return 0;
}

Void OS3Framework::MyForm::Charts()
{
	int DIV = 1024;
	int WIDTH = 7;
	char divisor = 'K';

	MEMORYSTATUS stat;

	GlobalMemoryStatus(&stat);

	label1->Text = "Load";
	label2->Text = "Total";
	label3->Text = "Free";

	label4->Text = stat.dwMemoryLoad.ToString() + "%";
	label5->Text = (stat.dwTotalPhys / DIV / 1024).ToString();
	label6->Text = (stat.dwAvailPhys / DIV / 1024).ToString();

	chart1->Series[0]->Points->Clear();
	chart1->Series[0]->Points->AddXY("Used", stat.dwTotalPhys / DIV);
	chart1->Series[0]->Points->AddXY("Free", stat.dwAvailPhys / DIV);
	//-----
	label7->Text = "Load";
	label8->Text = "Total";
	label9->Text = "Free";
	float xv = stat.dwTotalVirtual / DIV;
	float yv = stat.dwAvailVirtual / DIV;
	label10->Text = floor( (xv/(xv+yv)) * 100 ).ToString() + "%";
	label11->Text = (stat.dwTotalVirtual / DIV / 1024).ToString();
	label12->Text = (stat.dwAvailVirtual / DIV / 1024).ToString();
	//-----
	chart2->Series[0]->Points->Clear();
	chart2->Series[0]->Points->AddXY("Used", stat.dwTotalVirtual / DIV);
	chart2->Series[0]->Points->AddXY("Free", stat.dwAvailVirtual / DIV);

	label13->Text = "Load";
	label14->Text = "Total";
	label15->Text = "Free";
	float x = stat.dwTotalPageFile / DIV;
	float y = stat.dwAvailPageFile / DIV;
	label16->Text = floor( (x/(x+y)) * 100 ).ToString() + "%";
	label17->Text = (stat.dwTotalPageFile / DIV / 1024).ToString();
	label18->Text = (stat.dwAvailPageFile / DIV / 1024).ToString();

	chart3->Series[0]->Points->Clear();
	chart3->Series[0]->Points->AddXY("Used", stat.dwTotalPageFile / DIV);
	chart3->Series[0]->Points->AddXY("Free", stat.dwAvailPageFile / DIV);
	return Void();
}
System::Void OS3Framework::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyForm1^ secDl = gcnew MyForm1;
	secDl->Show();
	return System::Void();
}
//Alt+Enter создать определение