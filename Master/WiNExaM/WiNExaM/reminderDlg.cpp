#pragma once
#include "reminderDlg.h"

reminderDlg* reminderDlg::ptr;

struct prompt
{
	int Day = 0;
	int Hour = 0;
	int Month = 0;
	int Min = 0;
	wstring Name;
	wstring Description;
};
vector<prompt> baseReminder;
prompt tempStruct;
HANDLE hFile;
DWORD dwByte;
TCHAR buff[50];
void SaveFile()
{
	

	bool test = false;
	
	
	

	hFile = CreateFile(TEXT("BaseReminder.txt"), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	for (size_t i = 0; i < baseReminder.size(); i++)
	{
		WriteFile(hFile, &baseReminder[i], sizeof(prompt), &dwByte, NULL);
		
	}
	CloseHandle(hFile);

}
reminderDlg :: reminderDlg()
{
	ptr = this;
}

void reminderDlg::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}
BOOL reminderDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{
	// получим дескрипторы элементов управления
	hButton1 = GetDlgItem(hWnd, IDC_BUTTON1);
	hButton2 = GetDlgItem(hWnd, IDC_BUTTON2);
	hButton3 = GetDlgItem(hWnd, IDC_BUTTON3);
	hButton4 = GetDlgItem(hWnd, IDC_BUTTON4);
	hButton5 = GetDlgItem(hWnd, IDC_BUTTON5);

	hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
	hEdit3 = GetDlgItem(hWnd, IDC_EDIT3);
	hEdit4 = GetDlgItem(hWnd, IDC_EDIT4);
	hEdit5 = GetDlgItem(hWnd, IDC_EDIT5);
	hEdit6 = GetDlgItem(hWnd, IDC_EDIT6);

	hSpin1 = GetDlgItem(hWnd, IDC_SPIN1);
	hSpin2 = GetDlgItem(hWnd, IDC_SPIN2);
	hSpin3 = GetDlgItem(hWnd, IDC_SPIN3);
	hSpin4 = GetDlgItem(hWnd, IDC_SPIN4);

	hList1 = GetDlgItem(hWnd, IDC_LIST1);

	SendMessage(hSpin1, UDM_SETBUDDY, (WPARAM)hEdit3, 0);
	SendMessage(hSpin1, UDM_SETRANGE32, 0, 30);
	SetWindowText(hEdit3, TEXT("0"));
	SendMessage(hSpin2, UDM_SETBUDDY, (WPARAM)hEdit4, 0);
	SendMessage(hSpin2, UDM_SETRANGE32, 0, 24);
	SetWindowText(hEdit4, TEXT("0"));
	SendMessage(hSpin3, UDM_SETBUDDY, (WPARAM)hEdit5, 0);
	SendMessage(hSpin3, UDM_SETRANGE32, 0, 12);
	SetWindowText(hEdit5, TEXT("0"));
	SendMessage(hSpin4, UDM_SETBUDDY, (WPARAM)hEdit6, 0);
	SendMessage(hSpin4, UDM_SETRANGE32, 0, 59);
	SetWindowText(hEdit6, TEXT("0"));

	hFile = CreateFile(TEXT("BaseReminder.txt"), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	for (size_t i = 0; i < 5; i++)
	{
		ReadFile(hFile, &tempStruct, sizeof(prompt), &dwByte, NULL);
		if (dwByte == 0) break;
		baseReminder.push_back(tempStruct);

		_stprintf_s(buff, _T("%d,%d %d:%d %s"), baseReminder[i].Day, baseReminder[i].Month, baseReminder[i].Hour, baseReminder[i].Min, baseReminder[i].Name);
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(buff));
	}
	CloseHandle(hFile);
	return TRUE;
}

void reminderDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
#pragma region BUTTON1
		case IDC_BUTTON1:
		{
						
			EnableWindow(hButton4, TRUE);
			EnableWindow(hButton5, TRUE);
			EnableWindow(hEdit1, TRUE);
			EnableWindow(hEdit2, TRUE);
			EnableWindow(hEdit3, TRUE);
			EnableWindow(hEdit4, TRUE);
			EnableWindow(hEdit5, TRUE);
			EnableWindow(hEdit6, TRUE);

			EnableWindow(hSpin1, TRUE);
			EnableWindow(hSpin2, TRUE);
			EnableWindow(hSpin3, TRUE);
			EnableWindow(hSpin4, TRUE);
			
		}
		break;
#pragma endregion  
#pragma region BUTTON4
		case IDC_BUTTON4:
		{
							
							tempStruct.Day = SendMessage(hSpin1, UDM_GETPOS32, 0, 0);
							tempStruct.Hour = SendMessage(hSpin2, UDM_GETPOS32, 0, 0);
							tempStruct.Month = SendMessage(hSpin3, UDM_GETPOS32, 0, 0);
							tempStruct.Min = SendMessage(hSpin4, UDM_GETPOS32, 0, 0);

			int length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
			TCHAR *tmp = new TCHAR[length + 1];
			GetWindowText(hEdit1, tmp, length + 1);
			tempStruct.Name = tmp;
			delete []tmp;
				
			
			

			length = SendMessage(hEdit2, WM_GETTEXTLENGTH, 0, 0);

			TCHAR *temp = new TCHAR[length + 1];

			GetWindowText(hEdit2, temp, length + 1);
			tempStruct.Description = temp;
			baseReminder.push_back(tempStruct);
			SaveFile();
				
			
			
			
			_stprintf_s(buff, _T("%d,%d %d:%d %s"), tempStruct.Day, tempStruct.Month, tempStruct.Hour, tempStruct.Min, temp);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(buff));

			
			EnableWindow(hButton4, FALSE);
			EnableWindow(hButton5, FALSE);
			EnableWindow(hEdit1, FALSE);
			EnableWindow(hEdit2, FALSE);
			EnableWindow(hEdit3, FALSE);
			EnableWindow(hEdit4, FALSE);
			EnableWindow(hEdit5, FALSE);
			EnableWindow(hEdit6, FALSE);

			EnableWindow(hSpin1, FALSE);
			EnableWindow(hSpin2, FALSE);
			EnableWindow(hSpin3, FALSE);
			EnableWindow(hSpin4, FALSE);
			SetWindowText(hEdit1, TEXT(""));
			SetWindowText(hEdit2, TEXT(""));
			SetWindowText(hEdit3, TEXT("0"));
			SetWindowText(hEdit4, TEXT("0"));
			SetWindowText(hEdit5, TEXT("0"));
			SetWindowText(hEdit6, TEXT("0"));

		

			
							
							
		}
		break;
#pragma endregion 
#pragma region BUTTON5
		case IDC_BUTTON5:
		{
			EnableWindow(hButton4, FALSE);
			EnableWindow(hButton5, FALSE);
			EnableWindow(hEdit1, FALSE);
			EnableWindow(hEdit2, FALSE);
			EnableWindow(hEdit3, FALSE);
			EnableWindow(hEdit4, FALSE);
			EnableWindow(hEdit5, FALSE);
			EnableWindow(hEdit6, FALSE);

			EnableWindow(hSpin1, FALSE);
			EnableWindow(hSpin2, FALSE);
			EnableWindow(hSpin3, FALSE);
			EnableWindow(hSpin4, FALSE);
			SetWindowText(hEdit1, TEXT(""));
			SetWindowText(hEdit2, TEXT(""));
			SetWindowText(hEdit3, TEXT("0"));
			SetWindowText(hEdit4, TEXT("0"));
			SetWindowText(hEdit5, TEXT("0"));
			SetWindowText(hEdit6, TEXT("0"));
		}
			break;

		case IDC_LIST1:
		{
		     EnableWindow(hButton3, TRUE);
		}
			break;
#pragma endregion 
#pragma region BUTTON2
		case IDC_BUTTON2:
		{
							EnableWindow(hButton4, FALSE);
							EnableWindow(hButton5, FALSE);
							EnableWindow(hEdit1, FALSE);
							EnableWindow(hEdit2, FALSE);
							EnableWindow(hEdit3, FALSE);
							EnableWindow(hEdit4, FALSE);
							EnableWindow(hEdit5, FALSE);
							EnableWindow(hEdit6, FALSE);

							EnableWindow(hSpin1, FALSE);
							EnableWindow(hSpin2, FALSE);
							EnableWindow(hSpin3, FALSE);
							EnableWindow(hSpin4, FALSE);
							SetWindowText(hEdit1, TEXT(""));
							SetWindowText(hEdit2, TEXT(""));
							SetWindowText(hEdit3, TEXT("0"));
							SetWindowText(hEdit4, TEXT("0"));
							SetWindowText(hEdit5, TEXT("0"));
							SetWindowText(hEdit6, TEXT("0"));
		}
			break;
#pragma endregion 
#pragma region BUTTON3
		case IDC_BUTTON3:
		{
			int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
		if (index != LB_ERR) // выбран ли элемент списка?
		{
			// определим длину названия выбранного клуба
			int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
			// выделим память необходимого размера
			TCHAR *pBuffer = new TCHAR[length + 1];
			// скопируем название клуба в выделенную память
			SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
			MessageBox(hWnd, pBuffer, TEXT("Удаление напоминания"), MB_OK | MB_ICONINFORMATION);
			SendMessage(hList1, LB_DELETESTRING, index, 0);
			delete[] pBuffer;
		}
		else
			MessageBox(hWnd, TEXT("Напоминание не выбрано"), TEXT("Удаление напоминания"), MB_OK | MB_ICONSTOP);

		}
			break;
#pragma endregion 
	}
}


BOOL CALLBACK reminderDlg ::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_OnCommand);
		
	}
	return FALSE;
}