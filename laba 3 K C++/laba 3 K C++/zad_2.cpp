#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <windows.h>



//using namespace std;
//namespace fs = std::experimental::filesystem;
//string DIRECTORY_PATH = "C:\\Users\\79045\\Desktop\\��������� ����\\��������� ��\\3 ���� 5 ���\\kudya\\for_2_ex";//���� �� ����������
//vector<string> getExecutableFiles(const string& directory) {//������� ��� ��������� ����������� ������(���� � ����)
//    vector<string> executableFiles;
//    for (const auto& entry : fs::directory_iterator(directory)) { // entry �������� �������, �������������� ������ �������� � ������ path � �������� �����
//        //directory_iterator �������� ���������� ������� �������� directory_entry
//        if (fs::is_regular_file(entry)) {
//            string extension = entry.path().extension().string();
//            if (extension == ".exe" || extension == ".bat" || extension == ".cmd") {
//                executableFiles.push_back(entry.path().string());
//            }
//        }
//    }
//    return executableFiles;
//}
//LPWSTR StringToLPWSTR(const string& str) {//����� �� ����� ��� � � ������� �������, ������ ������ ��������� �������������
//    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
//    LPWSTR buffer = new WCHAR[size];
//    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
//    return buffer;
//}
//
//void runExecutableFiles(const vector<string>& files) {//������ ������
//    for (const auto& file : files) {
//        STARTUPINFO si = { sizeof(si) };//����������� ����������� �++
//        PROCESS_INFORMATION pi;//���������� � �������� � ��� ������(����� ��� ��� ����, �� ������� ������� �� ������ ��� ����� �������) NERD
//        string command = file;
//        if (file.find(".bat") != string::npos || file.find(".cmd") != string::npos) {
//            command = "cmd.exe /C " + file;
//        }
//        LPWSTR lpwstr_command = StringToLPWSTR(command);
//        if (CreateProcess(NULL, lpwstr_command, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
//            //�� ������� ������� ����� ��������� ������, �.�. ������ �������� ��� Command Line
//            WaitForSingleObject(pi.hProcess, INFINITE);//��� ���������� ��������(�� ������� ����� �� � ����� ������� ���� �� ����� ��� ������
//            //������, ������ ������
//            CloseHandle(pi.hProcess);//������� ���������� �������� � ��� ������
//            CloseHandle(pi.hThread);
//            fs::remove(file);//������� �� ����������
//            cout << "Executed and removed: " << file << endl;
//        }
//    }
//}

//int main() {
//    setlocale(LC_ALL, "RUS");
//    while (true) {//��������� ����������� ���� ��� ���������� ������ ���������, ����� ����� ���� �� ����� ������ ���������� ������ � �����
//        vector<string> executableFiles = getExecutableFiles(DIRECTORY_PATH);
//        if (executableFiles.empty()) {//���� ������ �� �������� � ����������
//            cout << "No executable files found. Waiting..." << endl;
//            Sleep(1000);//����� ������ �� �������
//        }
//        else {
//            runExecutableFiles(executableFiles);//������ ����� � ��������
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
//		auto files = getFilesInDir("C:\\Users\\79045\\Desktop\\��������� ����\\��������� ��\\3 ���� 5 ���\\kudya\\for_2_ex");
//		if (files.size() == 0) {
//			std::wcout << L"� ����� ��� ����������� ������! � ��������.\n";
//			Sleep(8000);
//		}
//		else {
//			runExecutableFiles(files);
//		}
//	}
//
//    return 0;
//}