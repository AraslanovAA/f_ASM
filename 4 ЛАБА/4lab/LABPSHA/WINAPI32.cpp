#include <windows.h>
#include <stdlib.h>
#include <objidl.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <TCHAR.H>
#include <wchar.h>
#include <cstring>
#include <windowsx.h>
#include <windows.h>


using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define LABEL_TEXT 20
#define MAX_MATRIX_SIZE 15


// Объявляем прототип CALLBACK функции
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcc(HWND hWndinp, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcg(HWND hWndinp, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern "C" int my_assembler(int n);


HINSTANCE hInst;

HWND textbox, textbox1, text_out_nums, hWndinp, hWndres, rbutton,textbox8,textbox7, textbox9,textout10,textout11;
HWND  button1, button2, button3, edit, edit1, edit2, edit3, textbox6, Edit5, button10, edit11, editout1, editout2;
HWND *labels1 = new HWND[MAX_MATRIX_SIZE];
HWND arrayEdits1[15];
HWND arrayEdits2[15];
HWND arrayEdits3[15];
HWND hWindow;
HWND button4, button5, button6;
bool prov = false;
int flag = 0;
int flagop = 1;
int m1;
int siddle1;
bool siddle = false;
int n1;
int mas1[15];
double *a;
int resmas[15];
string tmpstr = "";
string str;
string str1;
wchar_t *err = NULL;
int num;
const int n = 10, m = 10;

template<typename T>
T StringToNumber(const std::string& numberAsString)
{
	T valor;

	std::stringstream stream(numberAsString);
	stream >> valor;
	if (stream.fail()) {
		std::runtime_error e(numberAsString);
		throw e;
	}
	return valor;
}

void copy()
{
	for (int i = 0; i < m1; i++)
	{
			resmas[i] = 0;
			resmas[i] = mas1[i];
	}
}



// Функция WinAPI для точки входа в программу
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Регистрация класса окна
	// Объявляем переменную типа WNDCLASSEX

	WNDCLASSEX wClass, wNewClass, elseClass;
	ZeroMemory(&wClass, sizeof(wClass)); // Обнуляем память
	ZeroMemory(&wNewClass, sizeof(wNewClass));
	ZeroMemory(&elseClass, sizeof(wNewClass));
	// Заполняем структуру WNDCLASSEX
	wClass.cbSize = sizeof(wClass); // Размер равен размеру структуры
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW; // Определяем фон окна
	wClass.hInstance = hInstance; // hInstance window
	wClass.lpfnWndProc = (WNDPROC)WndProc; // Процедура обработки окна
	wClass.lpszClassName = L"Class1"; // Имя класса

	wNewClass.cbSize = sizeof(wNewClass); // Размер равен размеру структуры
	wNewClass.hbrBackground = (HBRUSH)COLOR_WINDOW; // Определяем фон окна
	wNewClass.hInstance = hInstance; // hInstance window
	wNewClass.lpfnWndProc = (WNDPROC)WndProcc; // Процедура обработки окна
	wNewClass.lpszClassName = L"Class2"; // Имя класса

	elseClass.cbSize = sizeof(elseClass); // Размер равен размеру структуры
	elseClass.hbrBackground = (HBRUSH)COLOR_WINDOW; // Определяем фон окна
	elseClass.hInstance = hInstance; // hInstance window
	elseClass.lpfnWndProc = (WNDPROC)WndProcg; // Процедура обработки окна
	elseClass.lpszClassName = L"Class3"; // Имя класса

	// Если произошла ошибка, то выводим сообщение
	if (!RegisterClassEx(&wClass))
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Класс окна не был создан!", L"Ошибка", MB_ICONERROR);
	}

	if (!RegisterClassEx(&wNewClass))
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Класс окна не был создан!", L"Ошибка", MB_ICONERROR);
	}

	if (!RegisterClassEx(&elseClass))
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Класс окна не был создан!", L"Ошибка", MB_ICONERROR);
	}

	// Создаем окно при помощи функции WinApi CreateWindowEx
	hWindow = CreateWindowEx(NULL,
		L"Class1", // Имя класса, который мы определили ранее
		L"Лабораторная №4", // Заголовок окна
		WS_TILED,
		300, // x координата по горизонтали
		300, // y координата по вертикали
		500, // ширина создаваемого окна
		200, // высота создаваемого окна
		NULL,
		NULL,
		hInstance, // переменная экземпляра приложения
		NULL);



	// Если окно не было создано, то выдаем сообщение
	if (!hWindow)
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Окно не было создано!", L"Ошибка", MB_ICONERROR);
	}

	hWndinp = CreateWindowEx(NULL,
		L"Class2", // Имя класса, который мы определили ранее
		L"Ввод числа", // Заголовок окна
		WS_TILED,
		100, // x координата по горизонтали
		20, // y координата по вертикали
		620, // ширина создаваемого окна
		330, // высота создаваемого окна
		hWindow,
		NULL,
		hInstance, // переменная экземпляра приложения
		NULL);

	if (!hWndinp)
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Окно не было создано!", L"Ошибка", MB_ICONERROR);
	}

	hWndres = CreateWindowEx(NULL,
		L"Class3", // Имя класса, который мы определили ранее
		L"ASSEMBLER", // Заголовок окна
		WS_TILED,
		100, // x координата по горизонтали
		20, // y координата по вертикали
		400, // ширина создаваемого окна
		400, // высота создаваемого окна
		hWindow,
		NULL,
		hInstance, // переменная экземпляра приложения
		NULL);

	if (!hWndres)
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Окно не было создано!", L"Ошибка", MB_ICONERROR);
	}

	// Показываем окно
	ShowWindow(hWindow, SW_SHOW);
	UpdateWindow(hWindow);

	// Объявляем переменную для сообщений типа MSG
	MSG msg;
	// Обнуляем память по размеру структуры MSG
	ZeroMemory(&msg, sizeof(MSG));

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// определяем процедуру обратного вызова (WinApi)

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
					  textbox = CreateWindow(L"STATIC", L"Лабораторная работа №4", WS_VISIBLE | WS_CHILD | WS_BORDER,
						  10, 30, 200, 20, hwnd, NULL, NULL, NULL);
					  textbox8 = CreateWindow(L"STATIC", L"Определение простоты числа", WS_VISIBLE | WS_CHILD | WS_BORDER,
						  10, 70, 460, 20, hwnd, NULL, NULL, NULL);
					  

					  // Здесь будем создавать элементы управления окна
					  HWND buttonpitch = CreateWindow(L"BUTTON", L"Ввести число", WS_VISIBLE | WS_CHILD
						  | WS_BORDER, 30, 110, 120, 30, hwnd, (HMENU)1, NULL, NULL);

					  HWND button0 = CreateWindow(L"BUTTON", L"Закрыть", WS_VISIBLE | WS_CHILD
						  | WS_BORDER, 350,110, 70, 30, hwnd, (HMENU)3, NULL, NULL);
					  SendMessage(button1, EM_SETLIMITTEXT, 8, 0);
					  break;
	}

	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
						   // Обработка команд (нажатие кнопок, мыши, полей ввода и т.д.)
					   case 1:
					   {
								 ShowWindow(hWndinp, SW_SHOW);
								 EnableWindow(hWindow, FALSE);
								 break;
					   }
					 
					   case 3:
					   {
								 PostQuitMessage(0);
								 return 0;
								 break;
					   }


					   }

					   break;
	}

	case WM_DESTROY: 
	{
					
						 PostQuitMessage(0);
						 return 0;
						 break;
	}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcc(HWND hWndinp, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int tmpnum = 0;
	LPWSTR tmp = L"0";
	char *err = NULL;
	unsigned int TextLength;
	char *Text = NULL;
	switch (uMsg)
	{
	case WM_CREATE:
	{
				  HWND button0 = CreateWindow(L"BUTTON", L"Закрыть", WS_VISIBLE | WS_CHILD
						  | WS_BORDER,530,250, 70, 30, hWndinp, (HMENU)1, NULL, NULL);
					  SendMessage(button1, EM_SETLIMITTEXT, 8, 0);
					  {
						
							  textbox1 = CreateWindow(L"STATIC", L"                       Число:", WS_VISIBLE | WS_CHILD,
								  20, 50, 200, 20, hWndinp, NULL, NULL, NULL);
							  edit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
								  180, 50, 30, 20, hWndinp, NULL, NULL, NULL);
							  Edit_LimitText(edit, 3);
							  button2 = CreateWindow(L"BUTTON", L"ОК", WS_VISIBLE | WS_CHILD
								  | WS_BORDER, 220, 50, 80, 25, hWndinp, (HMENU)5, NULL, NULL);
							  flag = 0;
							  text_out_nums = CreateWindow(L"STATIC", L"Введите число", WS_VISIBLE | WS_CHILD | WS_BORDER,
								  10, 120, 420, 20, hWndinp, NULL, NULL, NULL);
							  break;
						  }
					  
					  break;


	}

	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
				
					   case 1:
					   {
								 SetForegroundWindow(hWindow);
								 ShowWindow(hWndinp, SW_HIDE);
								 EnableWindow(hWindow, TRUE);
								 SetFocus(hWindow);
								 break;
					   }
					  
					   case 5:
					   {
								
								 //Считать число
								 TextLength = GetWindowTextLength(edit) + 1;
								 Text = new char[TextLength];
								 GetWindowTextA(edit, Text, TextLength + 1);
								 m1 = atoi(Text);
								 delete(Text);		

								 if (m1 < 2)
								 {
									 MessageBox(hWndinp, L"Введите число >=2", L"Ошибка", MB_OK);
								 }
								 else{
									 num = my_assembler(m1);
									 if (num == 2) {
										 SetWindowText(text_out_nums, L"Число является простым");
									 }
									 else {
										 SetWindowText(text_out_nums, L"Число не является простым");
									 }
								 }

								
					
								 break;
					   }								
					   
					   case 8:
					   {

								 break;
					   }
					   }

					   break;
	}

	case WM_DESTROY: 
	{
						 PostQuitMessage(0);
						 return 0;
						 break;
	}
	}

	return DefWindowProc(hWndinp, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcg(HWND hWndres, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (uMsg)
	{
	case WM_CREATE:
	{

					  HWND button6 = CreateWindow(L"BUTTON", L"Закрыть", WS_VISIBLE | WS_CHILD
						  | WS_BORDER, 660, 310, 90, 30, hWndres, (HMENU)1, NULL, NULL);
					  wchar_t str[65];
					  string buf;
					  if (flagop == 1)
					  {
							  copy();
						  for (int i = 0; i < m1; i++)
						  {

								  DestroyWindow(arrayEdits3[i]);
								  buf = to_string(resmas[i]);
								  arrayEdits3[i] = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
									  i * 40 + 10, 40 + i * 25 + 25, 40, 25, hWndres, NULL, NULL, NULL);
								 
							  
						  }
					  }
					  if ((flagop != 2) && (flagop != 1))
					  {
						  MessageBox(hWndres, L"Матрица не была введена!", L"Ошибка", MB_OK);
					  }
					  break;
	}
	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {
						   // Обработка команд (нажатие кнопок, мыши, полей ввода и т.д.)
					   case 1:
					   {
								 SetForegroundWindow(hWindow);
								 ShowWindow(hWndres, SW_HIDE);
								 EnableWindow(hWindow, TRUE);
								 SetFocus(hWindow);
								 break;
					   }
				
						   break;
					   }
					   break;
	case WM_DESTROY:
	{
					   PostQuitMessage(0);
					   return 0;
	}
	default:
		return DefWindowProc(hWndres, uMsg, wParam, lParam);
	}
	}
}