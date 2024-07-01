#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define PAGE_SIZE 32
#define MEMORY_SIZE 256

// ��������� ��� ������������� ��������
typedef struct {
    int data[PAGE_SIZE / sizeof(int)];
    bool in_memory; // ����, �����������, ��������� �� �������� � ����������� ������
    bool referenced; // ����, �����������, ��� �� ������ � ��������
} Page;

// ���������� ������� ��� ����������� ������ � �������� ��������
Page memory[MEMORY_SIZE];
Page external_storage[MEMORY_SIZE];

// ������� ��� ������ ������ ������
int read_memory(int virtual_address) {
    int page_index = virtual_address / PAGE_SIZE;
    if (page_index < 0 || page_index >= MEMORY_SIZE) {
        printf("������: ������������ ����������� �����.\n");
        return -1;
    }

    Page* page = &memory[page_index];
    page->referenced = true; // ��������� ���� ������� � ��������

    if (!page->in_memory) {
        // ���� �������� �� � ����������� ������, ��������� �� �� �������� ��������
        printf("������� �������� %d �� �������� �������� � ����������� ������.\n", page_index);
        page->in_memory = true;
        page->referenced = false; // ���������� ���� �������, ��� ��� �� ������ ��� ��������� ��������
    }

    return page->data[virtual_address % PAGE_SIZE];
}

void write_memory(int virtual_address, int value) {
    int page_index = virtual_address / PAGE_SIZE;
    if (page_index < 0 || page_index >= MEMORY_SIZE) {
        printf("������: ������������ ����������� �����.\n");
        return;
    }

    Page* page = &memory[page_index];
    page->referenced = true; // ��������� ���� ������� � ��������

    if (!page->in_memory) {
        // ���� �������� �� � ����������� ������, ��������� �� �� �������� ��������
        printf("������� �������� %d �� �������� �������� � ����������� ������.\n", page_index);
        page->in_memory = true;
        page->referenced = false; // ���������� ���� �������, ��� ��� �� ������ ��� ��������� ��������
    }

    int offset = virtual_address % PAGE_SIZE;
    if (offset < 0 || offset >= PAGE_SIZE) {
        printf("������: ������������ �������� ������ ��������.\n");
        return;
    }

    page->data[offset] = value;
}



// ������� ��� ����������� ����� ������������� �������
void display_page_map() {
    printf("����� ������������� �������:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].in_memory) {
            printf("�������� %d: � ����������� ������\n", i);
        }
        else {
            printf("�������� %d: �� ������� ��������\n", i);
        }
    }
    printf("\n"); // ��������� ������ ������ ��� ����������
}


int main() {
    setlocale(LC_ALL, "Russian");
    // ������������� ������� � ����������� ������ � ������� ��������
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].in_memory = false;
        memory[i].referenced = false;
        external_storage[i].in_memory = false;
        external_storage[i].referenced = false;
    }

    // ������ �������������
    int virtual_address = 64; // ������ ������������ ������ ��� ������ � ������
    int value_to_write = 42;

    int read_result = read_memory(virtual_address);
    printf("�������� ����������� ������ %d: %d\n", virtual_address, read_result);

    write_memory(virtual_address, value_to_write);
    printf("������ �������� %d � ����������� ������ %d\n", value_to_write, virtual_address);

    display_page_map(); // ���������� ����� ������������� �������

    return 0;
}
