#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
#include <cassert>
#include <string>
#include <iomanip>


constexpr uint32_t BLOCK_SIZE = 1024; // Размер блока в байтах (1 Кб)
const uint32_t MAX_BLOCKS = pow(2, 8) - 1; // Максимальное количество блоков

struct Block {
    std::vector<char> data; // Данные в блоке

    Block() : data(BLOCK_SIZE) {} // Инициализируем блоки данными размером BLOCK_SIZE
};

class BlockSpace {
private:
    std::vector<uint8_t> bitmap; // Битовая карта для отслеживания свободных/занятых блоков
    std::vector<Block> blocks; // Вектор блоков в блочном пространстве
    const std::string& F_name;
    std::vector<Block> originalBlocks;

public:
    BlockSpace(uint32_t block_size, const std::string& filename) : F_name(filename) {
        std::cout << "WORK IN PROGRESS" << std::endl;
        std::ofstream file(filename, std::ios::binary | std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Failed to create/open file: " << filename << std::endl;
            // Обработка ошибки...
            return;
        }

        // Вычисляем количество блоков
        uint32_t num_blocks = MAX_BLOCKS;
        while (block_size < BLOCK_SIZE && num_blocks > 0) {
            block_size *= 2;
            num_blocks /= 2;
        }
        blocks.resize(num_blocks);
        // Инициализация bitmap и запись в файл
        bitmap.resize((num_blocks + 7) / 8, 0); // Вычисляем размер битовой карты и инициализируем нулями
        std::cout << "Bitmap Contents:" << std::endl;
        for (const uint8_t& byte : bitmap) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
        // Запись битовой карты в файл
        file.write(reinterpret_cast<const char*>(bitmap.data()), bitmap.size());
        if (!file.good()) {
            std::cerr << "Error writing to file: " << filename << std::endl;
            // Обработка ошибки...
        }
        else {
            std::cout << "Bitmap data written to file successfully." << std::endl;
        }
        file.close();
        std::cout << "Block space created successfully in file: " << filename << std::endl;
        // Другие инициализации...
    }

    void beginTransaction() {
        // Кэширование текущего состояния блоков перед началом транзакции
        originalBlocks = blocks;
    }

    void commitTransaction() {
        // Запись изменений на физический носитель
        std::ofstream file(getFileName().c_str(), std::ios::out | std::ios::app | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << getFileName() << std::endl;
            return;
        }

        for (size_t i = 0; i < getTotalBlocks(); ++i) {
            file.seekp(i * getBlockSize());
            file.write(reinterpret_cast<const char*>(blocks[i].data.data()), getBlockSize());
        }

        if (!file.good()) {
            std::cerr << "Error writing changes to file." << std::endl;
            file.close();
            return;
        }

        file.close();
    }

    void rollbackTransaction() {
        // Откат изменений к сохраненному состоянию
        blocks = originalBlocks;
    }

    bool allocateBlock(uint32_t block_index) {
        beginTransaction();

        if (block_index >= blocks.size()) {
            std::cerr << "Block index out of range." << std::endl;
            rollbackTransaction();
            return false;
        }

        uint32_t byte_index = block_index / 8;
        uint8_t bit_mask = 1 << (block_index % 8);

        if (bitmap[byte_index] & bit_mask) {
            std::cerr << "Block " << block_index << " is already allocated." << std::endl;
            rollbackTransaction();
            return false;
        }

        bitmap[byte_index] |= bit_mask; // Устанавливаем бит в битовой карте
        commitTransaction();
        return true;
    }

    bool freeBlock(uint32_t block_index) {
        beginTransaction();

        if (block_index >= blocks.size()) {
            std::cerr << "Block index out of range." << std::endl;
            rollbackTransaction();
            return false;
        }

        uint32_t byte_index = block_index / 8;
        uint8_t bit_mask = 1 << (block_index % 8);

        if (!(bitmap[byte_index] & bit_mask)) {
            std::cerr << "Block " << block_index << " is already free." << std::endl;
            rollbackTransaction();
            return false;
        }

        // Обнуление данных внутри блока
        for (size_t i = 0; i < BLOCK_SIZE; ++i) {
            blocks[block_index].data[i] = 0;
        }

        bitmap[byte_index] &= ~bit_mask; // Сбрасываем бит в битовой карте

        // Удаление данных из файла
        std::fstream file(F_name, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << F_name << std::endl;
            rollbackTransaction();
            return false;
        }

        file.seekp(block_index * BLOCK_SIZE);
        for (size_t i = 0; i < BLOCK_SIZE; ++i) {
            file.put(0); // Записываем нули в блок
        }

        if (!file.good()) {
            std::cerr << "Error deleting data from block " << block_index << " in file." << std::endl;
            file.close();
            rollbackTransaction();
            return false;
        }

        file.close();
        commitTransaction();
        return true;
    }

    bool isBlockAllocated(uint32_t block_index) const {
        if (block_index >= blocks.size()) {
            std::cerr << "Block index out of range." << std::endl;
            return false;
        }

        uint32_t byte_index = block_index / 8;
        uint8_t bit_mask = 1 << (block_index % 8);

        return (bitmap[byte_index] & bit_mask);
    }

    bool writeDataToBlock(uint32_t block_index, const std::string& data, const std::string& filename) {
        beginTransaction();

        if (block_index >= blocks.size()) {
            std::cerr << "Block index out of range." << std::endl;
            rollbackTransaction();
            return false;
        }

        if (!isBlockAllocated(block_index)) {
            std::cerr << "Block " << block_index << " is not allocated. Cannot write data." << std::endl;
            rollbackTransaction();
            return false;
        }

        // Проверка на наличие данных в блоке
        for (size_t i = 0; i < BLOCK_SIZE; ++i) {
            if (blocks[block_index].data[i] != 0) {
                std::cerr << "Block " << block_index << " already contains data. Cannot write new data." << std::endl;
                rollbackTransaction();
                return false;
            }
        }

        // Пишем данные в блок
        for (size_t i = 0; i < data.size() && i < BLOCK_SIZE; ++i) {
            blocks[block_index].data[i] = data[i];
        }

        std::ofstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            rollbackTransaction();
            return false;
        }

        file.seekp(block_index * BLOCK_SIZE);
        file.write(data.c_str(), std::min(data.size(), static_cast<size_t>(BLOCK_SIZE)));

        if (!file.good()) {
            std::cerr << "Error writing data to block " << block_index << " in file." << std::endl;
            file.close();
            rollbackTransaction();
            return false;
        }

        file.close();
        commitTransaction();
        return true;
    }

    // ... остальной ваш код ...
    bool readDataFromBlock(uint32_t block_index, std::string& data) const {
        if (block_index >= blocks.size()) {
            std::cerr << "Block index out of range." << std::endl;
            return false;
        }

        if (!isBlockAllocated(block_index)) {
            std::cerr << "Block " << block_index << " is not allocated." << std::endl;
            return false;
        }

        // Читаем данные из блока
        data.clear();
        for (char c : blocks[block_index].data) {
            if (c != '\0') {
                data += c;
            }
            else {
                break;
            }
        }

        return true;
    };

    uint32_t getBlockSize() const {
        return BLOCK_SIZE;
    }

    uint32_t getTotalBlocks() const {
        return blocks.size();
    }

    std::vector<Block> getBlocks() {
        return blocks;
    }

    uint32_t getFreeBlocks() const {
        uint32_t count = 0;

        for (const uint8_t& byte : bitmap) {
            std::bitset<8> bits(byte);
            count += bits.count();
        }

        return count;
    }

    void printServiceInfo() const {
        uint64_t blockSize = BLOCK_SIZE;
        uint32_t totalBlocks = blocks.size();
        uint32_t freeBlocks = getFreeBlocks();
        uint64_t serviceInfoSize = sizeof(Block) * totalBlocks;

        std::cout << "Size of each block of data: " << blockSize << " bytes" << std::endl;
        std::cout << "Total number of blocks: " << totalBlocks << std::endl;
        std::cout << "Number of free blocks: " << freeBlocks << std::endl;
        std::cout << "Size of memory occupied by service information: " << serviceInfoSize << " bytes" << std::endl;

        // Вывод битовой карты
        std::cout << "Bitmap:" << std::endl;
        for (const auto& byte : bitmap) {
            std::bitset<8> bits(byte);
            std::cout << bits << " ";
        }
        std::cout << std::endl;
    }

    std::string getFileName() const {
        return F_name;
    }
};



void printMenu() {
    std::cout << "--------------------------" << std::endl;
    std::cout << "1. Выделение блока" << std::endl;
    std::cout << "2. Освобождение блока" << std::endl;
    std::cout << "3. Запись данных в блок" << std::endl;
    std::cout << "4. Чтение данных из блока" << std::endl;
    std::cout << "5. Получить служебную информацию" << std::endl;
    std::cout << "6. Выход" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string filename = "TEST_BLOCKSPACE.bin"; // Имя файла для блочного пространства
    uint32_t block_size = BLOCK_SIZE; // Размер блока (может быть изменен)
    BlockSpace blockSpace(256, filename);
    std::cout << "Блочное пространство успешно создано!" << std::endl;
    int choice = 0;
    while (choice != 6) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            uint32_t block_index;
            std::cout << "Введите индекс блока для выделения: ";
            std::cin >> block_index;
            if (blockSpace.allocateBlock(block_index)) {
                std::cout << "Блок " << block_index << " успешно выделен." << std::endl;
            }
            else {
                std::cout << "Ошибка выделения блока " << block_index << "." << std::endl;
            }
            break;
        }
        case 2: {
            uint32_t block_index;
            std::cout << "Введите индекс блока для освобождения: ";
            std::cin >> block_index;
            if (blockSpace.freeBlock(block_index)) {
                std::cout << "Блок " << block_index << " Успешно освобожден." << std::endl;
            }
            else {
                std::cout << "Ошибка освобождения блока " << block_index << "." << std::endl;
            }
            break;
        }
        case 3: {
            uint32_t block_index;
            std::string data_to_write;

            std::cout << "Введите индекс блока для записи данных: ";
            std::cin >> block_index;

            std::cin.ignore(); // Очистка буфера ввода

            std::cout << "Введите данные для записи: ";
            getline(std::cin, data_to_write);

            if (blockSpace.writeDataToBlock(block_index, data_to_write, filename)) {
                std::cout << "Запись данных в блок " << block_index << " завершена успешно." << std::endl;
            }
            else {
                std::cout << "Ошибка записи данных в блок " << block_index << "." << std::endl;
            }
            break;
        }
        case 4: {
            uint32_t block_index;
            std::string read_data;

            std::cout << "Введите индекс блока для чтения данных из него: ";
            std::cin >> block_index;

            if (blockSpace.readDataFromBlock(block_index, read_data)) {
                std::cout << "Данные из блока " << block_index << ": " << read_data << std::endl;
            }
            else {
                std::cout << "Ошибка чтения данных из блока " << block_index << "." << std::endl;
            }
            break;
        }
        case 5: {
            blockSpace.printServiceInfo();
            break;
        }
        case 6:
            std::cout << "Выходим..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова!" << std::endl;
            break;
        }
    }
    return 0;
}
