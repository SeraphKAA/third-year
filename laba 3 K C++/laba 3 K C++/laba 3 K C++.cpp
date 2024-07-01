//#include <iostream>
//#include <fstream>
//#include <string>
//#include <chrono>
//#include <thread>
//
//using namespace std;
//
//// Функция для запуска процесса
//void runProcess(const string& processName, int maxTime) {
//    cout << "Запуск процесса: " << processName << endl;
//    time_t t = time(NULL);
//
//    cout << "Процесс " << processName;
//
//    //this_thread::sleep_for(chrono::seconds(maxTime));
//    getchar();
//    time_t end_timer = time(NULL) - t;
//    
//    if (end_timer <= maxTime)
//    {
//        cout << " успешно завершен в течение " << maxTime << " секунд, закрыт процесс за " << end_timer << " секунд";
//    }
//    else
//    {
//        cout << " не уложился в допустимое время " << maxTime << " секунд, закрыт процесс за " << end_timer << " секунд";
//    }
//    cout << endl;
//}
//
//void runProcess_1(const string& processName, int maxTime) {
//    cout << "Запуск процесса: " << processName << endl;
//    time_t t = time(NULL);
//    cout << "Процесс " << processName;
//
//    //this_thread::sleep_for(chrono::seconds(maxTime));
//    getchar();
//
//    time_t end_timer = time(NULL) - t;
//
//    
//    if (end_timer <= maxTime)
//    {
//        cout << " успешно завершен в течение " << maxTime << " секунд, закрыт процесс за " << end_timer << "секунд";
//    }
//    else
//    {
//        cout << " не уложился в допустимое время " << maxTime << " секунд, закрыт процесс за " << end_timer << "секунд";
//    }
//    cout << endl;
//}
//
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//    ifstream configFile("config.txt");
//
//    if (!configFile) {
//        cerr << "Ошибка при открытии файла" << endl;
//        return 1;
//    }
//
//    string processName;
//    int maxTime;
//
//    while (configFile >> processName >> maxTime) {
//        runProcess(processName, maxTime);
//        system("pause");
//    }
//
//    configFile.close();
//
//    return 0;
//}











//#include <iostream>
//#include <fstream>
//#include <string>
//#include <chrono>
//#include <thread>
//#include <ctime>
//#include <windows.h>
//
//// Функция для запуска процесса
//void runProcess(const std::string& processName, int maxTime) {
//    std::cout << "Запуск процесса: " << processName << std::endl;
//
//    // Стартовое время выполнения процесса
//    std::clock_t start = std::clock();
//
//    // Имитация работы процесса
//    std::this_thread::sleep_for(std::chrono::seconds(maxTime));
//
//    // Определение времени завершения процесса
//    std::clock_t end = std::clock();
//
//    // Вычисление затраченного времени в секундах
//    double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
//
//    std::cout << "Процесс " << processName;
//
//    if (elapsedTime <= maxTime) {
//        std::cout << " успешно завершен в течение " << elapsedTime << " секунд" << std::endl;
//    }
//    else {
//        std::cout << " не уложился в допустимое время" << std::endl;
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//    std::ifstream configFile("config.txt");
//
//    if (!configFile) {
//        std::cerr << "Ошибка при открытии файла" << std::endl;
//        return 1;
//    }
//
//    std::string processName;
//    int maxTime;
//
//    while (configFile >> processName >> maxTime) {
//        runProcess(processName, maxTime);
//
//        // Запрос пользователя на закрытие процесса
//        char input;
//        std::cout << "Для закрытия процесса " << processName << " нажмите Y или y: ";
//        std::cin >> input;
//
//        if (input == 'Y' || input == 'y') {
//            std::string command = "taskkill /F /IM " + processName + ".exe";
//
//            // Выполнение команды для завершения процесса
//            system(command.c_str());
//        }
//    }
//
//    configFile.close();
//
//    return 0;
//}














//#include <stdio.h>
//#include <iostream>
//#include <vector>
//#include <windows.h>
//#include <thread>
//#include <chrono>
//
//#define MAX_INPUT_EVENTS 100
//
//int main()
//{
//    //Handle to console input buffer
//    HANDLE g_console_handle;
//    //Return dword
//    DWORD ret, ret_aux;
//    //Input event structure
//    INPUT_RECORD input_event[MAX_INPUT_EVENTS];
//    //return flag
//    bool f_ret;
//
//
//    std::cout << "press some keys while the process waits 3 seconds...\n";
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//
//    //get handle to console
//    g_console_handle = GetStdHandle(STD_INPUT_HANDLE);
//
//    //Get number of pending input events
//    f_ret = GetNumberOfConsoleInputEvents(g_console_handle, &ret);
//    //if: fail
//    if (f_ret == false)
//    {
//        std::cerr << "ERR: could not get number of pending input events\n";
//        return true; //Fail
//    }
//    //if: at least one event has been detected
//    if (ret > 0)
//    {
//        //if: above processing limits
//        if (ret >= MAX_INPUT_EVENTS)
//        {
//            std::cerr << "ERR: too many input events\n";
//            return true; //Fail
//        }
//        //Get all the input event
//        f_ret = ReadConsoleInput
//        (
//            g_console_handle,
//            input_event,
//            ret,
//            &ret_aux
//        );
//        //for: every input event
//        for (DWORD t = 0; t < ret_aux; t++)
//        {
//            //switch: Decode event type
//            switch (input_event[t].EventType)
//            {
//                //case: keyboard
//            case KEY_EVENT:
//            {
//                //Structure holding key event
//                KEY_EVENT_RECORD& event = input_event[t].Event.KeyEvent;
//                //List of virtual keys
//                //https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes
//                //true=down, pressed
//                if (event.bKeyDown == true)
//                {
//                    std::cout << "Virtual key: " << event.wVirtualKeyCode << " is down\n";
//                }
//                //false = up, released
//                else
//                {
//                    std::cout << "Virtual key: " << event.wVirtualKeyCode << " is up\n";
//                }
//
//                break;
//            }
//            //unhandled input event
//            default:
//            {
//                //do nothing
//            }
//            }   //end switch: Decode event type
//        }   //end for: every input event
//    }   //end if: at least one event has been detected
//    //if: no event detected
//    else
//    {
//
//    }
//}






//#include <iostream>
//#include <string>
//#include <fstream>
//#include <Windows.h>
//#include <vector>
//#include <windows.h>
//
//using namespace std;
//
//
//void callProcesses(vector<string>& vec_paths, vector<double>& vec_times) {
//    STARTUPINFO si = { sizeof(si) };
//    PROCESS_INFORMATION pi;
//    LPCSTR temp_path = NULL;
//    double temp_time = 0.0;
//
//
//    for (int i = 0; i < vec_paths.size(); i++) {
//        //преобразовать строку в строку в стиле c
//        temp_path = vec_paths.at(i).c_str();
//        temp_time = vec_times.at(i);
//
//        if (CreateProcess(temp_path, NULL, NULL, NULL,
//            FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
//            CloseHandle(pi.hThread);
//            if (WaitForSingleObject(pi.hProcess, temp_time * 1000) >= WAIT_TIMEOUT) {
//                cout << "Процесс был завершен позже" << endl;
//            }
//            else { cout << "Процесс был завершен ранее" << endl; }
//            TerminateProcess(pi.hProcess, 0);
//            CloseHandle(pi.hProcess);
//        }
//    }
//
//}
//
//
//void readFile(string file_name) {
//    vector<string> arr_paths;
//    vector<double> arr_times;
//    string temp = "";
//    double temp_time = 0.0;
//
//
//    //создание потока файлов
//    fstream fin(file_name);
//    if (!fin.is_open()) { cerr << "Файл не может быть открыт" << endl; }
//    else {
//        //прочитать файл построчно
//        while (getline(fin, temp)) {
//            arr_paths.push_back(temp);
//
//
//            //прочитать и преобразовать строку в двойное число
//            getline(fin, temp);
//            temp_time = stod(temp);
//
//            arr_times.push_back(temp_time);
//        }
//
//        fin.close();
//    }
//
//    // запуск процессов вызова функций
//    callProcesses(arr_paths, arr_times);
//}
//
//int main() {
//    SetConsoleOutputCP(CP_UTF8);
//    readFile("config.txt");
//
//    return 0;
//}



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

string F_NAME = "config.txt";

vector<string> split(const string str, char separator) {//Функция для получения структуры с путями к исполняемому файлу(процессу)
    vector<string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

LPCWSTR StringToLPCWSTR(const string& str) {//Функция для перевода string в указатель на длинную константную широкую строку(пиздец да)
    //указатель на константную UNICODE строку
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    wchar_t* buffer = new wchar_t[size];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, size);
    return buffer;
}

//int main() {
//    setlocale(LC_ALL, "Russian");
//    string line;
//    ifstream FILE(F_NAME);
//    STARTUPINFO si = { sizeof(si) };//стандартные дескрипторы с++
//    PROCESS_INFORMATION pi;//дескриптор процесса и его потока и прочая хуйня
//
//    if (FILE.is_open()) {
//        while (getline(FILE, line)) {
//            vector<string> process_names = split(line, ',');
//            for (int i = 0; i < process_names.size(); i++) {
//                cout << process_names[i] << endl;
//                LPCWSTR wname = StringToLPCWSTR(process_names[i]);//путь исполняемого файла
//                cout << wname << endl;
//                if (CreateProcess(wname, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
//                    //открытие процесса(первый параметр это путь к файлу)
//                    cout << true << endl;
//                    cout << "Process " << process_names[i] << " started" << endl;
//                    CloseHandle(pi.hThread);//закрытие дескриптора потока данного процесса
//                    DWORD result = WaitForSingleObject(pi.hProcess, 10000);//ожидание завершения процесса
//                    if (result == WAIT_TIMEOUT) {//WAIT_TIMEOUT это значит, что превышено время ожидания
//                        cout << "Process " << process_names[i] << " did not finish within the time limit" << endl;
//                        TerminateProcess(pi.hProcess, 0);//закрыли принудительно процесс
//                    }
//                    else if (result == WAIT_OBJECT_0) {//WAIT_OBJECT_0 это изменение состояния процесса(завершился он в общем)
//                        cout << "Process " << process_names[i] << " finished within the time limit" << endl;
//                    }
//                    CloseHandle(pi.hProcess);//закрыли дескриптор
//                }
//                else { cout << false << endl; }
//                delete[] wname;
//            }
//        }
//    }
//    else
//    {
//        cout << "File did not opened" << endl;
//    }
//
//    return 0;
//}
//:3