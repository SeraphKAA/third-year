#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define PAGE_SIZE 32
#define MEMORY_SIZE 256

// Структура для представления страницы
typedef struct {
    int data[PAGE_SIZE / sizeof(int)];
    bool in_memory; // Флаг, указывающий, находится ли страница в оперативной памяти
    bool referenced; // Флаг, указывающий, был ли доступ к странице
} Page;

// Глобальные массивы для оперативной памяти и внешнего носителя
Page memory[MEMORY_SIZE];
Page external_storage[MEMORY_SIZE];

// Функция для чтения ячейки памяти
int read_memory(int virtual_address) {
    int page_index = virtual_address / PAGE_SIZE;
    if (page_index < 0 || page_index >= MEMORY_SIZE) {
        printf("Ошибка: недопустимый виртуальный адрес.\n");
        return -1;
    }

    Page* page = &memory[page_index];
    page->referenced = true; // Обновляем флаг доступа к странице

    if (!page->in_memory) {
        // Если страница не в оперативной памяти, переносим ее из внешнего носителя
        printf("Перенос страницы %d из внешнего носителя в оперативную память.\n", page_index);
        page->in_memory = true;
        page->referenced = false; // Сбрасываем флаг доступа, так как мы только что загрузили страницу
    }

    return page->data[virtual_address % PAGE_SIZE];
}

void write_memory(int virtual_address, int value) {
    int page_index = virtual_address / PAGE_SIZE;
    if (page_index < 0 || page_index >= MEMORY_SIZE) {
        printf("Ошибка: недопустимый виртуальный адрес.\n");
        return;
    }

    Page* page = &memory[page_index];
    page->referenced = true; // Обновляем флаг доступа к странице

    if (!page->in_memory) {
        // Если страница не в оперативной памяти, переносим ее из внешнего носителя
        printf("Перенос страницы %d из внешнего носителя в оперативную память.\n", page_index);
        page->in_memory = true;
        page->referenced = false; // Сбрасываем флаг доступа, так как мы только что загрузили страницу
    }

    int offset = virtual_address % PAGE_SIZE;
    if (offset < 0 || offset >= PAGE_SIZE) {
        printf("Ошибка: недопустимое смещение внутри страницы.\n");
        return;
    }

    page->data[offset] = value;
}



// Функция для отображения карты распределения страниц
void display_page_map() {
    printf("Карта распределения страниц:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].in_memory) {
            printf("Страница %d: в оперативной памяти\n", i);
        }
        else {
            printf("Страница %d: на внешнем носителе\n", i);
        }
    }
    printf("\n"); // Добавляем пустую строку для читаемости
}


int main() {
    setlocale(LC_ALL, "Russian");
    // Инициализация страниц в оперативной памяти и внешнем носителе
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].in_memory = false;
        memory[i].referenced = false;
        external_storage[i].in_memory = false;
        external_storage[i].referenced = false;
    }

    // Пример использования
    int virtual_address = 64; // Пример виртуального адреса для чтения и записи
    int value_to_write = 42;

    int read_result = read_memory(virtual_address);
    printf("Значение виртуальной ячейки %d: %d\n", virtual_address, read_result);

    write_memory(virtual_address, value_to_write);
    printf("Запись значения %d в виртуальную ячейку %d\n", value_to_write, virtual_address);

    display_page_map(); // Отображаем карту распределения страниц

    return 0;
}
