#include "Garden.h"

Plant::Plant() : id(0), name(""), type(""), growth_time_months(0) {}

Plant::Plant(int id, const string& name, const string& type, int growth_time)
    : id(id), name(name), type(type), growth_time_months(growth_time) {}

int Plant::getId() const {
    return id;
}

string Plant::getName() const {
    return name;
}

string Plant::getType() const {
    return type;
}

int Plant::getGrowthTime() const {
    return growth_time_months;
}

void Plant::setName(const string& new_name) {
    name = new_name;
}

void Plant::setType(const string& new_type) {
    type = new_type;
}

void Plant::setGrowthTime(int new_time) {
    growth_time_months = new_time;
}

void Plant::display() const {
    cout << "ID: " << id << endl;
    cout << "Название: " << name << endl;
    cout << "Вид: " << type << endl;
    cout << "Время роста: " << growth_time_months << " месяцев" << endl;
}

string Plant::toString() const {
    return to_string(id) + "|" + name + "|" + type + "|" + to_string(growth_time_months);
}

Plant Plant::fromString(const string& line) {
    stringstream ss(line);
    string token;
    vector<string> tokens;
    
    while (getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() == 4) {
        int id = stoi(tokens[0]);
        string name = tokens[1];
        string type = tokens[2];
        int growth_time = stoi(tokens[3]);
        return Plant(id, name, type, growth_time);
    }
    
    return Plant();
}

GardenDB::GardenDB() : next_id(1) {}

Plant* GardenDB::findPlantById(int id) {
    auto it = find_if(plants.begin(), plants.end(),
                      [id](const Plant& p) { return p.getId() == id; });
    
    if (it != plants.end()) {
        return &(*it);
    }
    return nullptr;
}

const Plant* GardenDB::findPlantById(int id) const {
    auto it = find_if(plants.begin(), plants.end(),
                      [id](const Plant& p) { return p.getId() == id; });
    
    if (it != plants.end()) {
        return &(*it);
    }
    return nullptr;
}

void GardenDB::addPlant() {
    string name, type;
    int growth_time;
    
    cout << "Введите название растения: ";
    getline(cin, name);
    
    cout << "Введите вид растения (дерево, кустарник, цветок и т.д.): ";
    getline(cin, type);
    
    cout << "Введите время роста в месяцах: ";
    cin >> growth_time;
    clearInputBuffer();
    
    Plant new_plant(next_id++, name, type, growth_time);
    plants.push_back(new_plant);
    
    cout << "Растение успешно добавлено! ID: " << new_plant.getId() << endl;
}

bool GardenDB::deletePlant(int id) {
    auto it = find_if(plants.begin(), plants.end(),
                      [id](const Plant& p) { return p.getId() == id; });
    
    if (it != plants.end()) {
        plants.erase(it);
        cout << "Растение с ID " << id << " успешно удалено!" << endl;
        return true;
    }
    
    cout << "Растение с ID " << id << " не найдено!" << endl;
    return false;
}

bool GardenDB::editPlant(int id) {
    Plant* plant = findPlantById(id);
    
    if (plant == nullptr) {
        cout << "Растение с ID " << id << " не найдено!" << endl;
        return false;
    }
    
    cout << "Редактирование растения (ID: " << id << "):" << endl;
    cout << "Текущее название: " << plant->getName() << endl;
    cout << "Введите новое название (или нажмите Enter для пропуска): ";
    
    string input;
    getline(cin, input);
    if (!input.empty()) {
        plant->setName(input);
    }
    
    cout << "Текущий вид: " << plant->getType() << endl;
    cout << "Введите новый вид (или нажмите Enter для пропуска): ";
    
    getline(cin, input);
    if (!input.empty()) {
        plant->setType(input);
    }
    
    cout << "Текущее время роста: " << plant->getGrowthTime() << " месяцев" << endl;
    cout << "Введите новое время роста (или -1 для пропуска): ";
    
    int new_time;
    if (cin >> new_time && new_time >= 0) {
        plant->setGrowthTime(new_time);
    }
    clearInputBuffer();
    
    cout << "Растение успешно обновлено!" << endl;
    return true;
}

void GardenDB::displayAllPlants() const {
    if (plants.empty()) {
        cout << "База данных пуста!" << endl;
        return;
    }
    
    cout << "\n=========================================" << endl;
    cout << "          БАЗА ДАННЫХ РАСТЕНИЙ" << endl;
    cout << "=========================================" << endl;
    cout << "ID  | Название               | Вид              | Время роста" << endl;
    cout << "----|------------------------|------------------|------------" << endl;
    
    for (const auto& plant : plants) {
        printf("%-3d | %-22s | %-16s | %d месяцев\n",
               plant.getId(),
               plant.getName().c_str(),
               plant.getType().c_str(),
               plant.getGrowthTime());
    }
    
    cout << "=========================================" << endl;
    cout << "Всего растений: " << plants.size() << endl;
}

const Plant* GardenDB::findPlantByName(const string& name) const {
    auto it = find_if(plants.begin(), plants.end(),
                      [&name](const Plant& p) { return p.getName() == name; });
    
    if (it != plants.end()) {
        return &(*it);
    }
    return nullptr;
}

const Plant* GardenDB::findPlantByType(const string& type) const {
    auto it = find_if(plants.begin(), plants.end(),
                      [&type](const Plant& p) { return p.getType() == type; });
    
    if (it != plants.end()) {
        return &(*it);
    }
    return nullptr;
}

vector<const Plant*> GardenDB::findAllPlantsByType(const string& type) const {
    vector<const Plant*> result;
    
    for (const auto& plant : plants) {
        if (plant.getType() == type) {
            result.push_back(&plant);
        }
    }
    
    return result;
}

bool GardenDB::saveToFile(const string& filename) const {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return false;
    }
    
    file << next_id << endl;
    
    for (const auto& plant : plants) {
        file << plant.toString() << endl;
    }
    
    file.close();
    cout << "Данные успешно сохранены в файл '" << filename << "'!" << endl;
    return true;
}

bool GardenDB::loadFromFile(const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Файл базы данных не найден. Будет создан новый." << endl;
        return false;
    }
    
    plants.clear();
    
    string line;
    if (!getline(file, line)) {
        cout << "Ошибка чтения файла!" << endl;
        file.close();
        return false;
    }
    
    try {
        next_id = stoi(line);
    } catch (...) {
        cout << "Ошибка формата файла!" << endl;
        file.close();
        return false;
    }
    
    while (getline(file, line)) {
        if (!line.empty()) {
            Plant plant = Plant::fromString(line);
            if (plant.getId() != 0) {
                plants.push_back(plant);
            }
        }
    }
    
    file.close();
    cout << "Данные успешно загружены из файла '" << filename << "'!" << endl;
    cout << "Загружено растений: " << plants.size() << endl;
    return true;
}

int GardenDB::getPlantCount() const {
    return plants.size();
}

bool GardenDB::isEmpty() const {
    return plants.empty();
}

void GardenDB::showMenu() {
    cout << "\n========== МЕНЮ УПРАВЛЕНИЯ САДОМ ==========" << endl;
    cout << "1. Показать все растения" << endl;
    cout << "2. Добавить новое растение" << endl;
    cout << "3. Удалить растение" << endl;
    cout << "4. Редактировать растение" << endl;
    cout << "5. Найти растение по названию" << endl;
    cout << "6. Найти растение по виду" << endl;
    cout << "7. Сохранить изменения" << endl;
    cout << "8. Загрузить из файла" << endl;
    cout << "9. Выход" << endl;
    cout << "===========================================" << endl;
    cout << "Введите номер: ";
}

int GardenDB::getChoice() {
    int choice;
    cin >> choice;
    clearInputBuffer();
    return choice;
}

void GardenDB::clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}