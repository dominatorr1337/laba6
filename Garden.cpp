#include "Garden.h"

Plant::Plant() : id(0), name(""), type(""), growth_time_months(0), next(nullptr) {}

Plant::Plant(int id, const std::string& name, const std::string& type, int growth_time)
    : id(id), name(name), type(type), growth_time_months(growth_time), next(nullptr) {}

Plant::~Plant() {}

Plant::Plant(const Plant& other)
    : id(other.id), name(other.name), type(other.type), 
      growth_time_months(other.growth_time_months), next(nullptr) {}

Plant& Plant::operator=(const Plant& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        type = other.type;
        growth_time_months = other.growth_time_months;
        next = nullptr;
    }
    return *this;
}

int Plant::getId() const {
    return id;
}

std::string Plant::getName() const {
    return name;
}

std::string Plant::getType() const {
    return type;
}

int Plant::getGrowthTime() const {
    return growth_time_months;
}

void Plant::setName(const std::string& new_name) {
    name = new_name;
}

void Plant::setType(const std::string& new_type) {
    type = new_type;
}

void Plant::setGrowthTime(int new_time) {
    growth_time_months = new_time;
}

Plant* Plant::getNext() const {
    return next;
}

void Plant::setNext(Plant* next) {
    this->next = next;
}

void Plant::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Название: " << name << std::endl;
    std::cout << "Вид: " << type << std::endl;
    std::cout << "Время роста: " << growth_time_months << " месяцев" << std::endl;
}

std::string Plant::toString() const {
    return std::to_string(id) + "|" + name + "|" + type + "|" + std::to_string(growth_time_months);
}

Plant Plant::fromString(const std::string& line) {
    size_t pos1 = line.find('|');
    size_t pos2 = line.find('|', pos1 + 1);
    size_t pos3 = line.find('|', pos2 + 1);
    
    if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) {
        int id = std::stoi(line.substr(0, pos1));
        std::string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string type = line.substr(pos2 + 1, pos3 - pos2 - 1);
        int growth_time = std::stoi(line.substr(pos3 + 1));
        return Plant(id, name, type, growth_time);
    }
    
    return Plant();
}

GardenDB::GardenDB() : head(nullptr), tail(nullptr), count(0), next_id(1), filename("garden_db.txt") {}

GardenDB::GardenDB(const std::string& filename) 
    : head(nullptr), tail(nullptr), count(0), next_id(1), filename(filename) {}

GardenDB::~GardenDB() {
    clear();
}

void GardenDB::clear() {
    Plant* current = head;
    while (current != nullptr) {
        Plant* next = current->getNext();
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
    next_id = 1;
}

Plant* GardenDB::findPlantById(int id) {
    Plant* current = head;
    while (current != nullptr && current->getId() != id) {
        current = current->getNext();
    }
    return current;
}

const Plant* GardenDB::findPlantById(int id) const {
    Plant* current = head;
    while (current != nullptr && current->getId() != id) {
        current = current->getNext();
    }
    return current;
}

void GardenDB::addPlant() {
    std::string name, type;
    int growth_time;
    
    std::cout << "Введите название растения: ";
    std::getline(std::cin, name);
    
    std::cout << "Введите вид растения (дерево, кустарник, цветок и т.д.): ";
    std::getline(std::cin, type);
    
    std::cout << "Введите время роста в месяцах: ";
    std::cin >> growth_time;
    clearInputBuffer();
    
    Plant* new_plant = new Plant(next_id++, name, type, growth_time);
    
    if (head == nullptr) {
        head = new_plant;
        tail = new_plant;
    } else {
        tail->setNext(new_plant);
        tail = new_plant;
    }
    
    count++;
    std::cout << "Растение успешно добавлено! ID: " << new_plant->getId() << std::endl;
}

bool GardenDB::deletePlant(int id) {
    if (head == nullptr) {
        std::cout << "База данных пуста!" << std::endl;
        return false;
    }
    
    Plant* current = head;
    Plant* prev = nullptr;
    
    while (current != nullptr && current->getId() != id) {
        prev = current;
        current = current->getNext();
    }
    
    if (current == nullptr) {
        std::cout << "Растение с ID " << id << " не найдено!" << std::endl;
        return false;
    }
    
    if (prev == nullptr) {
        head = current->getNext();
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        prev->setNext(current->getNext());
        if (current == tail) {
            tail = prev;
        }
    }
    
    delete current;
    count--;
    std::cout << "Растение с ID " << id << " успешно удалено!" << std::endl;
    return true;
}

bool GardenDB::editPlant(int id) {
    Plant* plant = findPlantById(id);
    
    if (plant == nullptr) {
        std::cout << "Растение с ID " << id << " не найдено!" << std::endl;
        return false;
    }
    
    std::cout << "Редактирование растения (ID: " << id << "):" << std::endl;
    std::cout << "Текущее название: " << plant->getName() << std::endl;
    std::cout << "Введите новое название (или нажмите Enter для пропуска): ";
    
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) {
        plant->setName(input);
    }
    
    std::cout << "Текущий вид: " << plant->getType() << std::endl;
    std::cout << "Введите новый вид (или нажмите Enter для пропуска): ";
    
    std::getline(std::cin, input);
    if (!input.empty()) {
        plant->setType(input);
    }
    
    std::cout << "Текущее время роста: " << plant->getGrowthTime() << " месяцев" << std::endl;
    std::cout << "Введите новое время роста (или -1 для пропуска): ";
    
    int new_time;
    if (std::cin >> new_time && new_time >= 0) {
        plant->setGrowthTime(new_time);
    }
    clearInputBuffer();
    
    std::cout << "Растение успешно обновлено!" << std::endl;
    return true;
}

void GardenDB::displayAllPlants() const {
    if (head == nullptr) {
        std::cout << "База данных пуста!" << std::endl;
        return;
    }
    
    std::cout << "\n=========================================" << std::endl;
    std::cout << "          БАЗА ДАННЫХ РАСТЕНИЙ" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "ID  | Название               | Вид              | Время роста" << std::endl;
    std::cout << "----|------------------------|------------------|------------" << std::endl;
    
    Plant* current = head;
    while (current != nullptr) {
        printf("%-3d | %-22s | %-16s | %d месяцев\n",
               current->getId(),
               current->getName().c_str(),
               current->getType().c_str(),
               current->getGrowthTime());
        current = current->getNext();
    }
    
    std::cout << "=========================================" << std::endl;
    std::cout << "Всего растений: " << count << std::endl;
}

const Plant& GardenDB::findPlantByName(const std::string& name) const {
    static Plant empty_plant;
    
    Plant* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            return *current;
        }
        current = current->getNext();
    }
    
    return empty_plant;
}

const Plant& GardenDB::findPlantByType(const std::string& type) const {
    static Plant empty_plant;
    
    Plant* current = head;
    while (current != nullptr) {
        if (current->getType() == type) {
            return *current;
        }
        current = current->getNext();
    }
    
    return empty_plant;
}

bool GardenDB::saveToFile() const {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла '" << filename << "' для записи!" << std::endl;
        return false;
    }
    
    file << next_id << std::endl;
    
    Plant* current = head;
    while (current != nullptr) {
        file << current->toString() << std::endl;
        current = current->getNext();
    }
    
    file.close();
    std::cout << "Данные успешно сохранены в файл '" << filename << "'!" << std::endl;
    return true;
}

bool GardenDB::loadFromFile() {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Файл '" << filename << "' не найден. Будет создан новый." << std::endl;
        return false;
    }
    
    clear();
    
    std::string line;
    if (!std::getline(file, line)) {
        std::cout << "Ошибка чтения файла!" << std::endl;
        file.close();
        return false;
    }
    
    try {
        next_id = std::stoi(line);
    } catch (...) {
        std::cout << "Ошибка формата файла!" << std::endl;
        file.close();
        return false;
    }
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Plant plant = Plant::fromString(line);
            if (plant.getId() != 0) {
                Plant* new_plant = new Plant(plant);
                
                if (head == nullptr) {
                    head = new_plant;
                    tail = new_plant;
                } else {
                    tail->setNext(new_plant);
                    tail = new_plant;
                }
                count++;
            }
        }
    }
    
    file.close();
    std::cout << "Данные успешно загружены из файла '" << filename << "'!" << std::endl;
    std::cout << "Загружено растений: " << count << std::endl;
    return true;
}

int GardenDB::getPlantCount() const {
    return count;
}

bool GardenDB::isEmpty() const {
    return head == nullptr;
}

void GardenDB::setFilename(const std::string& filename) {
    this->filename = filename;
}

std::string GardenDB::getFilename() const {
    return filename;
}

void GardenDB::showMenu() {
    std::cout << "\n========== МЕНЮ УПРАВЛЕНИЯ САДОМ ==========" << std::endl;
    std::cout << "1. Показать все растения" << std::endl;
    std::cout << "2. Добавить новое растение" << std::endl;
    std::cout << "3. Удалить растение" << std::endl;
    std::cout << "4. Редактировать растение" << std::endl;
    std::cout << "5. Найти растение по названию" << std::endl;
    std::cout << "6. Найти растение по виду" << std::endl;
    std::cout << "7. Сохранить изменения" << std::endl;
    std::cout << "8. Загрузить из файла" << std::endl;
    std::cout << "9. Выход" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Введите номер: ";
}

int GardenDB::getChoice() {
    int choice;
    std::cin >> choice;
    clearInputBuffer();
    return choice;
}

void GardenDB::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
