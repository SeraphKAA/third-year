#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>

using namespace std;

const int PAGE_SIZE = 32;
const int PAGE_COUNT = 9;
const int EXTERNAL_STORAGE_SIZE = 8;
const int MEMORY_SIZE = 256;

struct value_in
{
    int first_id[PAGE_SIZE];
    int id[PAGE_SIZE];
    bool R;
    bool M;
    bool inMemory[PAGE_SIZE];
};

struct Page {
    value_in l;
    int data[PAGE_SIZE] { 0 };
};

struct Page_ {
    bool inMemory[PAGE_SIZE];
    int firsts_id[PAGE_SIZE];
    int data[PAGE_SIZE] { 0 };
};



Page Memory[PAGE_COUNT];
Page_ externalStorage[EXTERNAL_STORAGE_SIZE];


void initializePages() {
    for (int i = 0; i < PAGE_COUNT; ++i) {
        if (i == 0)
        {
            Memory[0].l.id[0] = 0;
            Memory[0].l.R = NULL;
            Memory[0].l.M = NULL;
            Memory[0].l.inMemory[0] = NULL;
            for (int j = 0; j < PAGE_SIZE; ++j)
                Memory[0].l.first_id[j] = j;
        }

        for (int j = 0; j < PAGE_SIZE; ++j)
        {
            //Memory[i].l.inMemory[j] = false;
            //Memory[i].l.M[j] = true;
            Memory[i].l.inMemory[j] = true;
            Memory[i].l.id[j] = j;
            Memory[i].l.M = false;
            Memory[i].l.R = false;
        }

    }
}


int* findPageToEvict(int *a) {
    for (int i = 1; i < PAGE_COUNT; ++i) {
        for (int j = 0; j < PAGE_SIZE; ++j)
        {
            // cout << "in find " << i << " " << j << " " << Memory[i].data[j] << " " << Memory[i].l.M[j] << endl;
            
            if (!Memory[i].l.M) {
                Memory[i].l.R = true;
                a[0] = i; a[1] = j;
                return a;
            }
        }
    }
    a[0] = -1;
    return a;
}

void Write(int index, int value)
{
    index--;
    if (index > 256 && index == 0)
    {
        cout << "Вы ввели недопустимый индекс" << endl;
        return;
    }
    int page_ind_1 = index / (PAGE_SIZE);
    page_ind_1++;
    int page_ind_2 = index % (PAGE_SIZE);

    Page& page = Memory[page_ind_1];
    page.l.first_id[page_ind_2] = index;
    cout << "Виртуальный номер: " << page.l.first_id[page_ind_2] << ", где разместилась: " << page_ind_2 << endl;
    Memory[page_ind_1].data[page_ind_2] = value;
    page.l.M = true;
    page.l.R = true;
    page.l.inMemory[page_ind_2] = false;
}




void Write_in_HDD(int index) 
{
    index--;
    if (index > 256 && index == 0)
    {
        cout << "Вы ввели недопустимый индекс" << endl;
        return;
    }
    int page_ind_1 = index / (PAGE_SIZE);
    page_ind_1++;
    int page_ind_2 = index % (PAGE_SIZE);

    Page& page = Memory[page_ind_1];


    if (page.l.first_id[page_ind_2] != 0)
    {
        for (int i = 0; i < EXTERNAL_STORAGE_SIZE; i++)
        {
            Page_& some_page = externalStorage[i];
            for (int j = 0; j < PAGE_SIZE; j++)
            {
                if (!some_page.inMemory[j])
                {
                    
                    some_page.inMemory[j] = true;
                    some_page.data[j] = page.data[page_ind_2];
                    some_page.firsts_id[j] = index + 1;
                    cout << "Номер виртуальной памяти: " << page.l.first_id[page_ind_2] << ", где разместилась: " << j << endl;
                    // cout << "что записываем: " << some_page.data[j] << ' ' << some_page.firsts_id[j] << endl;
                    return;
                }
            }
        }

    }
    else 
    {
        cout << "По данному адресу нет ничего\n";
        return;
    }
}

void Read(int index) 
{
    index--;
    if (index > 256 && index == 0)
    {
        cout << "Вы ввели недопустимый индекс" << endl;
        return;
    }
    int page_ind_1 = index / (PAGE_SIZE);
    page_ind_1++;
    int page_ind_2 = index % (PAGE_SIZE);

    cout << "Страница №" << page_ind_1 << ", ячейка №" << page_ind_2 << " (" << index << "): ";
    cout << "В оперативной памяти. " << "В ней находятся данные: " << Memory[page_ind_1].data[page_ind_2] << endl;
}

void Read_HDD(int index)
{
    for (int i = 0; i < PAGE_COUNT - 1; ++i) 
    {
        Page_& some_page = externalStorage[i];
        for (int j = 0; j < PAGE_SIZE; j++)
        {
            if (some_page.firsts_id[j] == index)
            {
                cout << "Страница №" << i << ", ячейка №" << j << " (" << index << "): ";
                cout << "Во внешнем носителе. " << "В ней находятся данные: " << externalStorage[i].data[j] << " " << externalStorage[i].firsts_id[j] << endl;

            }
        }
    }

}

void displayPageMappings() {
    cout << "Карта страниц:" << endl;
    int count = 1;
    for (int i = 1; i < PAGE_COUNT; ++i) {
        for (int j = 0; j < PAGE_SIZE; j++)
        {
            cout << "Страница №" << i << ", ячейка №" << j << " (" << count << "): "; count++;
            cout << "В оперативной памяти. " << "В ней находятся данные: " << Memory[i].data[j] << endl;
        }
    }
}

void displayPageMappings_exter() {
    cout << "Карта страниц:" << endl;
    int count = 1;
    for (int i = 0; i < PAGE_COUNT - 1; ++i) {
        for (int j = 0; j < PAGE_SIZE; j++)
        {
            cout << "Страница №" << i << ", ячейка №" << j << " (" << count << "): "; count++;
            cout << "Во внешнем носителе. В ней находятся данные: " << externalStorage[i].data[j] << " " << externalStorage[i].firsts_id[j] << endl;
        }
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    initializePages();
    Write(5, 3);
    Write(6, 2);
    Write(1, 33);
    Write(100, 33);

    Write_in_HDD(100);
    Write_in_HDD(5);

    Read(100);
    Read_HDD(100);
    //displayPageMappings();
    //displayPageMappings_exter();
    return 0;
}

//if (!page.l.inMemory[page_ind_2])
//{
//    cout << "InMemory (not false): " << page.l.inMemory[page_ind_2] << endl << endl;
//    int a[2]{ 0 };
//    findPageToEvict(a);
//    cout << a[0] << " " << a[1] << endl;
//    if (a[0] != -1)
//    {
//        Page& evictedPage = Memory[a[0]];
//        evictedPage.data[a[1]] = value;
//        cout << "Страница №" << index << " Занята. Вытесняется введеные данные на свободный блок ОЗУ" << "" << endl;
//        evictedPage.l.inMemory[a[1]] = true;
//        evictedPage.l.M[a[1]] = true;
//        evictedPage.l.R[a[1]] = true;
//    }
//    else
//    {
//        for (int i = 0; i < EXTERNAL_STORAGE_SIZE; i++)
//        {
//            Page_& some_page = externalStorage[i];
//            for (int j = 0; j < PAGE_SIZE; j++)
//            {
//                if (!some_page.inMemory[j])
//                {
//                    some_page.inMemory[j] = true;
//                    some_page.data[j] = value;
//                    return;
//                }
//            }
//        }
//    }
//    /*
//    externalStorage[evictedPage.l.id[page_ind_2]].l.inMemory[page_ind_2] = true;*/
//}
//else 
//{
//    cout << "InMemory (not true): " << page.l.inMemory[page_ind_2] << endl << endl;
//    Memory[page_ind_1].data[page_ind_2] = value;
//    page.l.M[page_ind_2] = true;
//    page.l.R[page_ind_2] = true;
//    page.l.inMemory[page_ind_2] = false;
//}



//Page& page = Memory[index];
//if (!page.inMemory && page.data == -1) {
//    int evictedPageIndex = findPageToEvict();
//    Page& evictedPage = Memory[evictedPageIndex];
//    cout << "Страница №" << index << " не находится в оперативной памяти. Вытесняется страница №" << evictedPageIndex << " на внешний носитель." << endl;
//    evictedPage.inMemory = false;
//    externalStorage[evictedPage.id].inMemory = true;
//}
//page.M = true;
//page.R = true;
//cout << "Запись данных в страницу №" << index << ": " << value << endl;
//page.data = value;

/*

struct Page {
    int id;
    bool inMemory;
    bool R;
    bool M;
    char data[PAGE_SIZE];
};

vector<Page> memory(PAGE_COUNT);
vector<Page> externalStorage(EXTERNAL_STORAGE_SIZE);

void initializePages() {
    for (int i = 0; i < PAGE_COUNT; ++i) {
        memory[i].id = i;
        memory[i].inMemory = true;
        memory[i].M = false;
        memory[i].R = false;

        //memory[i].id = i;
        //memory[i].inMemory = false;
        //memory[i].M = true;
        //memory[i].R = true;
        //memory[i].data[0] = 'r';
    }
    for (int i = 0; i < EXTERNAL_STORAGE_SIZE; ++i) {
        externalStorage[i].id = i;
        externalStorage[i].inMemory = false;
        externalStorage[i].M = false;
        memory[i].R = false;
    }
}

// Алгоритм NRU
int findPageToEvict() {
    for (int i = 0; i < PAGE_COUNT; ++i) {
        if (!memory[i].M) {
            memory[i].R = true;
            return i;
        }
    }
    for (int i = 0; i < PAGE_COUNT; ++i) {
        memory[i].M = false;
    }
    return 0;
}


bool isNumber(const string& str)
{
    for (char const& c : str) {
        if (isdigit(c) == 0) return false;
    }

    return true;
}

// чтение страницы
void readPage(int pageIndex) {
    if (pageIndex > 255) 
    {
        printf("Вы ввели несуществующую страницу\n");
        return;
    }
    Page& page = memory[pageIndex];
    if (!page.inMemory) {
        int evictedPageIndex = findPageToEvict();
        Page& evictedPage = memory[evictedPageIndex];
        cout << "Страница №" << pageIndex << " не находится в оперативной памяти. Вытесняется страница №" << evictedPageIndex << " на внешний носитель" << endl;
        evictedPage.inMemory = false;
        externalStorage[evictedPage.id].inMemory = true;
    }
    page.M = true;
    page.R = true;
    cout << "Чтение информации из страницы №" << pageIndex << ": " << page.data << endl;
}

// запись страницы
void writePage(int pageIndex, const char* data) {
    if (pageIndex > 255)
    {
        printf("Вы ввели несуществующую страницу\n");
        return;
    }

    if (strlen(data) > 32)
    {
        printf("Вы ввели больше данных, чем надо\nНадо до 32\n");
        return;
    }

    Page& page = memory[pageIndex];
    if (!page.inMemory) {
        int evictedPageIndex = findPageToEvict();
        Page& evictedPage = memory[evictedPageIndex];
        cout << "Страница №" << pageIndex << " не находится в оперативной памяти. Вытесняется страница №" << evictedPageIndex << " на внешний носитель." << endl;
        evictedPage.inMemory = false;
        externalStorage[evictedPage.id].inMemory = true;
    }
    page.M = true;
    page.R = true;
    cout << "Запись данных в страницу №" << pageIndex << ": " << data << endl;
    strncpy_s(page.data, data, PAGE_SIZE - 1); // Оставляем одно место для символа '\0'
    page.data[PAGE_SIZE - 1] = '\0';
}

// вывод всех страниц
void displayPageMappings() {
    cout << "Карта страниц:" << endl;
    for (int i = 0; i < PAGE_COUNT; ++i) {
        cout << "Страница №" << i << ": ";
        if (memory[i].inMemory) {
            cout << "В оперативной памяти. " << "В ней находятся данные: " << memory[i].data << endl;
        }
        else {
            cout << "Во внешнем носителе" << endl;
        }
    }
}
*/
/*
int main() {
    setlocale(LC_ALL, "Russian");
    
    setlocale(LC_ALL, "Russian");
    initializePages();

    while (true) {
        int choice;
        cout << "1. Чтение страницы\n2. Запись в страницу\n3. Карта страниц\n4. Выход" << endl;
        cin >> choice;

        if (choice == 1) {
            string pageIndex_str;
            int pageIndex;

            cout << "Напишите номер страницы которую нужно прочитать: ";
            cin >> pageIndex_str;

            if (isNumber(pageIndex_str))
            {
                pageIndex = stoi(pageIndex_str);
            }
            else
            {
                cout << "Введен некорректный тип данных" << endl;
                continue;
            }
            
            readPage(pageIndex);
        }
        else if (choice == 2) {
            char data[PAGE_SIZE];
            string pageIndex_str;
            int pageIndex;

            cout << "Напишите номер страницы в которую нужно записать данные: ";
            cin >> pageIndex_str;

            if (isNumber(pageIndex_str))
            {
                pageIndex = stoi(pageIndex_str);
            }
            else
            {
                cout << "Введен некорректный тип данных" << endl;
                continue;
            }

            cout << "Введите данные: ";

            cin.ignore();
            cin >> data;

            writePage(pageIndex, data);
        }
        else if (choice == 3) {
            displayPageMappings();
        }
        else if (choice == 4) {
            break;
        }
    }

    return 0;
    
}
*/