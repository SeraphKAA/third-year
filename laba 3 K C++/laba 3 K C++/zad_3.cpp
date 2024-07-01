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
//    // Открытие файла input.txt в режиме чтения и установка его как стандартного ввода
//    HANDLE hInputFile = CreateFile("input.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    if (hInputFile == INVALID_HANDLE_VALUE) {
//        std::cout << "Failed to open input file." << std::endl;
//        return 1;
//    }
//    startupInfo.hStdInput = hInputFile;
//
//    // Открытие файла output.txt в режиме записи и установка его как стандартного вывода
//    HANDLE hOutputFile = CreateFile("output.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    if (hOutputFile == INVALID_HANDLE_VALUE) {
//        std::cout << "Failed to open output file." << std::endl;
//        CloseHandle(hInputFile);
//        return 1;
//    }
//    startupInfo.hStdOutput = hOutputFile;
//    startupInfo.hStdError = hOutputFile;
//
//    // Создание процесса с подмененными стандартными потоками
//    if (!CreateProcess(NULL, "your_application.exe", NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInfo)) {
//        std::cout << "Failed to create process." << std::endl;
//        CloseHandle(hInputFile);
//        CloseHandle(hOutputFile);
//        return 1;
//    }
//
//    // Ожидание завершения процесса
//    WaitForSingleObject(processInfo.hProcess, INFINITE);
//
//    // Закрытие дескрипторов файлов
//    CloseHandle(hInputFile);
//    CloseHandle(hOutputFile);
//
//    return 0;
//}




//int main() {
//    // Создание процесса
//    STARTUPINFOW si = {};
//    si.cb = sizeof(STARTUPINFO);
//    PROCESS_INFORMATION pi = {};
//
//    // Преобразование строк из const char * в LPCWSTR
//    WCHAR inputFileName[] = L"input.txt";
//    WCHAR outputFileName[] = L"output.txt";
//
//    // Создание файлов с использованием параметров типа LPCWSTR
//    si.hStdInput = CreateFile(inputFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.hStdOutput = CreateFile(outputFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.dwFlags |= STARTF_USESTDHANDLES;
//    ZeroMemory(&pi, sizeof(pi));
//
//    if (CreateProcess(NULL, (LPWSTR)L"notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
//        // Ожидание завершения процесса
//        WaitForSingleObject(pi.hProcess, INFINITE);
//
//        // Закрытие дескрипторов файлов
//        CloseHandle(pi.hProcess);
//        CloseHandle(pi.hThread);
//        CloseHandle(si.hStdInput);
//        CloseHandle(si.hStdOutput);
//    }
//    else {
//        std::cout << "Не удалось запустить процесс" << std::endl;
//    }
//
//    return 0;
//}


//int main() {
//    // Создание процесса
//    STARTUPINFOA si = {};
//    si.cb = sizeof(STARTUPINFO);
//    PROCESS_INFORMATION pi = {};
//
//    // Преобразование строк из const char * в LPCWSTR
//    WCHAR inputFileName[] = L"input.txt";
//    WCHAR outputFileName[] = L"output.txt";
//
//    // Создание файлов с использованием параметров типа LPCWSTR
//    si.hStdInput = CreateFile(inputFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.hStdOutput = CreateFile(outputFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    si.dwFlags |= STARTF_USESTDHANDLES;
//    ZeroMemory(&pi, sizeof(pi));
//
//    if (CreateProcess(NULL, (LPWSTR)L"notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
//        // Ожидание завершения процесса
//        WaitForSingleObject(pi.hProcess, INFINITE);
//
//        // Закрытие дескрипторов файлов
//        CloseHandle(pi.hProcess);
//        CloseHandle(pi.hThread);
//        CloseHandle(si.hStdInput);
//        CloseHandle(si.hStdOutput);
//    }
//    else {
//        std::cout << "Не удалось запустить процесс" << std::endl;
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
//	HANDLE out = CreateFile(L"output.txt",//дескриптор вывода
//		FILE_APPEND_DATA,
//		FILE_SHARE_WRITE | FILE_SHARE_READ,
//		&sa,
//		OPEN_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//	HANDLE in = CreateFile(L"input.txt",//дескриптор ввода
//		FILE_APPEND_DATA,
//		FILE_SHARE_WRITE | FILE_SHARE_READ,
//		&sa,
//		OPEN_ALWAYS,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//	PROCESS_INFORMATION pi;
//	STARTUPINFO si;
//	BOOL ret = FALSE;//хз чё эт
//
//	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));//Функция ZeroMemory предназначена для обнуления памяти
//	ZeroMemory(&si, sizeof(STARTUPINFO));
//	si.cb = sizeof(STARTUPINFO);
//	si.dwFlags |= STARTF_USESTDHANDLES;
//	si.hStdInput = in;//переопределённый поток ввода
//	//si.hStdError = out;//переопределённый поток ошибки
//	si.hStdOutput = out;//переопределённый поток вывода
//
//	TCHAR process[] = TEXT("C:\\Users\\79045\\Desktop\\бессонные ночи\\сделанное дз\\3 курс 5 сем\\kudya\\for_3_ex\\x64\\Debug\\for_3_ex.exe");
//	if (CreateProcess(NULL, process, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))//запуск экзешника
//	{
//		CloseHandle(pi.hProcess);//закрыли дескриптор процесса
//		CloseHandle(pi.hThread);//закрыли дескриптор потока
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
	//TCHAR process[] = TEXT("C:\\Users\\79045\\Desktop\\бессонные ночи\\сделанное дз\\3 курс 5 сем\\kudya\\test\\x64\\Debug\\test.exe");
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