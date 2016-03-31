#pragma once
#include "header.h"

class reminderDlg
{
public:
	reminderDlg(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp); // dlgproc
	static reminderDlg* ptr; // для созранения this
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam); // initdlg
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify); // command
	void Cls_OnClose(HWND hwnd); //close

	HWND hDialog, hButton1, hButton2, hButton3, hButton4, hButton5, hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6, hList1,
		hSpin1, hSpin2, hSpin3, hSpin4;
};