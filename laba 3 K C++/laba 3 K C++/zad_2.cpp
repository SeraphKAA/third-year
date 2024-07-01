#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <windows.h>



//using namespace std;
//namespace fs = std::experimental::filesystem;
//string DIRECTORY_PATH = "C:\\Users\\79045\\Desktop\\бессонные ночи\\сделанное дз\\3 курс 5 сем\\kudya\\for_2_ex";//ПУТЬ ДО ДИРЕКТОРИИ
//vector<string> getExecutableFiles(const string& directory) {//функция для получения исполняемых файлов(пути к нему)
//    vector<string> executableFiles;
//    for (const auto& entry : fs::directory_iterator(directory)) { // entry является классом, представляющим запись каталога и хранит path в качестве члена
//        //directory_iterator является итератором записей каталога directory_entry
//        if (fs::is_regular_file(entry)) {
//            string extension = entry.path().extension().string();
//            if (extension == ".exe" || extension == ".bat" || extension == ".cmd") {
//                executableFiles.push_back(entry.path().string());
//            }
//        }
//    }
//    return executableFiles;
//}
//LPWSTR StringToLPWSTR(const string& str) {//такая же хуйня как и в прошлом задании, только теперь указатель неконстантный
//    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
//    LPWSTR buffer = new WCHAR[size];
//    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
//    return buffer;
//}
//
//void runExecutableFiles(const vector<string>& files) {//запуск файлов
//    for (const auto& file : files) {
//        STARTUPINFO si = { sizeof(si) };//стандартные дескрипторы с++
//        PROCESS_INFORMATION pi;//дескриптор о процессе и его потоке(поток это код типа, из процесс состоит из одного или более потоков) NERD
//        string command = file;
//        if (file.find(".bat") != string::npos || file.find(".cmd") != string::npos) {
//            command = "cmd.exe /C " + file;
//        }
//        LPWSTR lpwstr_command = StringToLPWSTR(command);
//        if (CreateProcess(NULL, lpwstr_command, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
//            //мы открыли процесс через командную строку, т.к. второй параметр это Command Line
//            WaitForSingleObject(pi.hProcess, INFINITE);//ждём завершения процесса(Он спросит можно ли в Винде удалить файл во время его работы
//            //Нельзя, выдаст ошибку
//            CloseHandle(pi.hProcess);//закрыли дескриптор процесса и его потока
//            CloseHandle(pi.hThread);
//            fs::remove(file);//удалили из директории
//            cout << "Executed and removed: " << file << endl;
//        }
//    }
//}

//int main() {
//    setlocale(LC_ALL, "RUS");
//    while (true) {//запустили бесконечный цикл для постоянной работы программы, чтобы можно было во время работы накидывать файлов в папку
//        vector<string> executableFiles = getExecutableFiles(DIRECTORY_PATH);
//        if (executableFiles.empty()) {//если файлов не осталось в директории
//            cout << "No executable files found. Waiting..." << endl;
//            Sleep(1000);//хоньк шимими на секунду
//        }
//        else {
//            runExecutableFiles(executableFiles);//запуск файла и удаление
//        }
//    }
//
//    return 0;
//}

namespace fs = std::experimental::filesystem;

std::vector<std::wstring> getFilesInDir(const char* dirPath) {
	std::vector<std::wstring> files;
	for (const auto& entry : fs::directory_iterator(dirPath)) {
		std::cout << entry << '\n';
		if (fs::is_regular_file(entry)) {
			std::wstring extension = entry.path().extension().wstring();
			if (extension == L".exe" || extension == L".bat" || extension == L".cmd")
				files.push_back(entry.path().wstring());
		}
	}

	return files;
}

void runExecutableFiles(const std::vector<std::wstring>& files) {
	for (const auto& file : files) {
		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;
		std::wstring wFile = file;
		if (wFile.find(L".bat") != std::wstring::npos || wFile.find(L".cmd") != std::wstring::npos) {
			wFile = L"cmd.exe /C " + wFile;
		}
		if (CreateProcess(NULL, (LPWSTR)wFile.c_str(), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			fs::remove(file);
		}
	}
}


//int main() {
//	setlocale(LC_ALL, "RUS");
//	
//	while (true) {
//		auto files = getFilesInDir("C:\\Users\\79045\\Desktop\\бессонные ночи\\сделанное дз\\3 курс 5 сем\\kudya\\for_2_ex");
//		if (files.size() == 0) {
//			std::wcout << L"В папке нет исполняемых файлов! В ожидании.\n";
//			Sleep(8000);
//		}
//		else {
//			runExecutableFiles(files);
//		}
//	}
//
//    return 0;
//}