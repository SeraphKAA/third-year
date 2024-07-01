#include <conio.h>
#include "string.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define MEMORY_SIZE 294


typedef struct {
    int start_address;
    int size;
    int is_allocated;
} MemoryBlock;

int list_size = 21;
MemoryBlock memory[21];

void initialize_memory() {
    for (int i = 0; i < list_size; i++)
    {
        memory[i].start_address = 0;
        memory[i].size = 0;
        memory[i].is_allocated = 0;
    }
    memory[1].start_address = 160;
}

void Print() 
{
    for (int i = 0; i < list_size; i++)
    {
        printf("%d) %d %d %d\n", i, memory[i].start_address, memory[i].size, memory[i].is_allocated);
    }
}

void allocate_memory(int size) {
    int i;
    int cap = 0;
    for (int j = 0; j < list_size; j++) { cap += memory[j].size; /*printf("___%d___\n", memory[j].size);*/ }

    if (MEMORY_SIZE >= cap + size)
    {
        for (i = 0; i < list_size; i++) {
            if (!memory[i].is_allocated) {
                memory[i].is_allocated = 1;
                printf("Занятый адрес %d\n", memory[i + 1].start_address);

                memory[i + 2].start_address = memory[i + 1].start_address + size;
                memory[i + 1].size = size;
                if (memory[i + 2].start_address == 0 && memory[i + 2].size == 0)
                {
                    memory[i + 1].is_allocated = 0;
                }
                return;
            }
        }
        if (i == list_size) {
            printf("Переполнение памяти\n");
        }
    }
    else {
        printf("переполнение памятиии, %d %d\n", cap, size);
        return;
    }
}

void deallocate_memory(int address) {
    int i;
    for (i = 0; i < list_size; i++) {
        if (i == address) {
            memory[i].is_allocated = 0;
            printf("Освобождение %d блока памяти\n", address);
            break;  
        }
    }
    if (i == list_size) {
        printf("Неправильный адрес\n");
    }
}

void not_deallocate_memory(int address) {
    int i;
    for (i = 0; i < list_size; i++) {
        if (i == address) {
            memory[i].is_allocated = 1;
            break;
        }
    }
    if (i == list_size) {
        return;
    }
}


void print_memory_info() {
    int free_blocks = 0;
    int allocated_blocks = 0;
    int total_allocated_memory = 0;
    char abc[] = "abcdefghijklmnop";
    int count = 0;

    printf("\nБлок информации:\n");
    for (int i = 1; i < list_size; i++) {
        if (memory[i].is_allocated) {
            allocated_blocks++;
            total_allocated_memory += memory[i].size;
            printf("%d) Процесс: %c, Начальный адрес: %d, Размер: %d, Статус: Занят\n", i, abc[count], memory[i].start_address, memory[i].size);
            count++;
        }
        else if (!memory[i].is_allocated) {
            free_blocks++;
            printf("%d) Процесс: -, Начальный адрес: %d, Размер: %d, Статус: Свободен\n", i, memory[i].start_address, memory[i].size);
        }
        else { printf("else\n"); }
    }

    printf("\nКраткая сводка информации о памяти:\n");
    printf("Всего свободных блоков: %d\n", free_blocks);
    printf("Всего занятых блоков: %d\n", allocated_blocks);
    printf("Занятой памяти: %d байт\n", total_allocated_memory);
    printf("Свободной памяти: %d байт\n", MEMORY_SIZE - total_allocated_memory);
}

int main() {
    setlocale(LC_ALL, "Rus");
    initialize_memory();
    
    allocate_memory(24);
    allocate_memory(48);
    allocate_memory(16);
    allocate_memory(41);
    allocate_memory(20);
    allocate_memory(35);
    allocate_memory(27);
    allocate_memory(40);

    deallocate_memory(3);
    deallocate_memory(5);



    not_deallocate_memory(8);
    print_memory_info();

    return 0;
}