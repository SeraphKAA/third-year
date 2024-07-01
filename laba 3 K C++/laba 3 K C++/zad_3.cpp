//#include <iostream>
//#include <windows.h>
//#include <string>

//int main() {
//    STARTUPINFO startupInfo;
//    PROCESS_INFORMATION processInfo;
//
//    ZeroMemory(&startupInfo, sizeof(startupInfo));
//    startupInfo.cb = sizeof(startupInfo);
//    startupInfo.dwFlags = STARTF_USESTDHANDLES;
//
//    // �������� ����� input.txt � ������ ������ � ��������� ��� ��� ������������ �����
//    HANDLE hInputFile = CreateFile("input.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    if (hInputFile == INVALID_HANDLE_VALUE) {
//        std::cout << "Failed to open input file." << std::endl;
//        return 1;
//    }
//    startupInfo.hStdInput = hInputFile;
//
//    // �������� ����� output.txt � ������ ������ � ��������� ��� ��� ������������ ������
//    HANDLE hOutputFile = CreateFile("output.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    if (hOutputFile == INVALID_HANDLE_VALUE) {
//        std::cout << "Failed to open output file." << std::endl;
//        CloseHandle(hInputFile);
//        return 1;
//    }
//    startupInfo.hStdOutput = hOutputFile;
//    startupInfo.hStdError = hOutputFile;
//
//    // �������� �������� � ������������ ������������ ��������
//    if (!CreateProcess(NULL, "your_application.exe", NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInfo)) {
//        std::cout << "Failed to create process." << std::endl;
//        CloseHandle(hInputFile);
//        CloseHandle(hOutputFile);
//        return 1;
//    }
//
//    // �������� ���������� ��������
//    WaitForSingleObject(processInfo.hProcess, INFINITE);
//
//    // �������� ������������ ������
//    CloseHandle(hInputFile);
//    CloseHandle(hOutputFile);
//
//    return 0;
//}




//int main() {
//    // �������� ��������
//    STARTUPINFOW si = {};
//    si.cb = sizeof(STARTUPINFO);
//    PROCESS_INFORMATION pi = {};
//
//    // �������������� ����� �� const char * � LPCWSTR
//    WCHAR inputFileName[] = L"input.txt";
//    WCHAR outputFileName[] = L"output.txt";
//
//    // �������� ������ � �������������� ���������� ���� LPCWSTR
//    si.hStdInput = CreateFile(inputFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.hStdOutput = CreateFile(outputFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.dwFlags |= STARTF_USESTDHANDLES;
//    ZeroMemory(&pi, sizeof(pi));
//
//    if (CreateProcess(NULL, (LPWSTR)L"notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
//        // �������� ���������� ��������
//        WaitForSingleObject(pi.hProcess, INFINITE);
//
//        // �������� ������������ ������
//        CloseHandle(pi.hProcess);
//        CloseHandle(pi.hThread);
//        CloseHandle(si.hStdInput);
//        CloseHandle(si.hStdOutput);
//    }
//    else {
//        std::cout << "�� ������� ��������� �������" << std::endl;
//    }
//
//    return 0;
//}


//int main() {
//    // �������� ��������
//    STARTUPINFOA si = {};
//    si.cb = sizeof(STARTUPINFO);
//    PROCESS_INFORMATION pi = {};
//
//    // �������������� ����� �� const char * � LPCWSTR
//    WCHAR inputFileName[] = L"input.txt";
//    WCHAR outputFileName[] = L"output.txt";
//
//    // �������� ������ � �������������� ���������� ���� LPCWSTR
//    si.hStdInput = CreateFile(inputFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.hStdOutput = CreateFile(outputFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.dwFlags |= STARTF_USESTDHANDLES;
//    ZeroMemory(&pi, sizeof(pi));
//
//    if (CreateProcess(NULL, (LPWSTR)L"notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
//        // �������� ���������� ��������
//        WaitForSingleObject(pi.hProcess, INFINITE);
//
//        // �������� ������������ ������
//        CloseHandle(pi.hProcess);
//        CloseHandle(pi.hThread);
//        CloseHandle(si.hStdInput);
//        CloseHandle(si.hStdOutput);
//    }
//    else {
//        std::cout << "�� ������� ��������� �������" << std::endl;
//    }
//
//    return 0;
//}


//#include <iostream>
//#include <Windows.h>
//void ex3() {
//	SECURITY_ATTRIBUTES sa;
//	sa.nLength = sizeof(sa);
//	sa.lpSecurityDescriptor = NULL;
//	sa.bInheritHandle = TRUE;
//
//	HANDLE out = CreateFile(L"output.txt",//���������� ������
//		FILE_APPEND_DATA,
//		FILE_SHARE_WRITE | FILE_SHARE_READ,
//		&sa,
//		OPEN_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//	HANDLE in = CreateFile(L"input.txt",//���������� �����
//		FILE_APPEND_DATA,
//		FILE_SHARE_WRITE | FILE_SHARE_READ,
//		&sa,
//		OPEN_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//	PROCESS_INFORMATION pi;
//	STARTUPINFO si;
//	BOOL ret = FALSE;//�� �� ��
//
//	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));//������� ZeroMemory ������������� ��� ��������� ������
//	ZeroMemory(&si, sizeof(STARTUPINFO));
//	si.cb = sizeof(STARTUPINFO);
//	si.dwFlags |= STARTF_USESTDHANDLES;
//	si.hStdInput = in;//��������������� ����� �����
//	//si.hStdError = out;//��������������� ����� ������
//	si.hStdOutput = out;//��������������� ����� ������
//
//	TCHAR process[] = TEXT("C:\\Users\\79045\\Desktop\\��������� ����\\��������� ��\\3 ���� 5 ���\\kudya\\for_3_ex\\x64\\Debug\\for_3_ex.exe");
//	if (CreateProcess(NULL, process, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))//������ ���������
//	{
//		CloseHandle(pi.hProcess);//������� ���������� ��������
//		CloseHandle(pi.hThread);//������� ���������� ������
//	}
//}
//int main() {
//	setlocale(LC_ALL, "RUS");
//	ex3();
//}

#include <iostream>
#include <Windows.h>

void ex3() {
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	HANDLE out = CreateFile(L"output.txt",
		FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		&sa,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	HANDLE in = CreateFile(L"input.txt",
		FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		&sa,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	BOOL ret = FALSE;

	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags |= STARTF_USESTDHANDLES;
	si.hStdInput = in;
	si.hStdError = out;
	si.hStdOutput = out;

	TCHAR process[] = TEXT("test.exe");
	//TCHAR process[] = TEXT("C:\\Users\\79045\\Desktop\\��������� ����\\��������� ��\\3 ���� 5 ���\\kudya\\test\\x64\\Debug\\test.exe");
	if (CreateProcess(NULL, process, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}


int main() {
	setlocale(LC_ALL, "RUS");
	ex3();
}