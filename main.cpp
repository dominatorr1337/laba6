#include "Garden.h"

int main() {
    GardenDB db;
    const string FILENAME = "garden_db.txt";
    
    db.loadFromFile(FILENAME);
    
    bool running = true;
    
    cout << "Добро пожаловать в программу управления садом!" << endl;
    
    while (running) {
        GardenDB::showMenu();
        int choice = GardenDB::getChoice();
        
        switch (choice) {
            case 1:
                db.displayAllPlants();
                break;
                
            case 2:
                db.addPlant();
                break;
                
            case 3:
                if (!db.isEmpty()) {
                    cout << "Введите ID растения для удаления: ";
                    int id;
                    cin >> id;
                    GardenDB::clearInputBuffer();
                    db.deletePlant(id);
                } else {
                    cout << "База данных пуста!" << endl;
                }
                break;
                
            case 4:
                if (!db.isEmpty()) {
                    cout << "Введите ID растения для редактирования: ";
                    int id;
                    cin >> id;
                    GardenDB::clearInputBuffer();
                    db.editPlant(id);
                } else {
                    cout << "База данных пуста!" << endl;
                }
                break;
                
            case 5:
                if (!db.isEmpty()) {
                    cout << "Введите название для поиска: ";
                    string name;
                    getline(cin, name);
                    
                    const Plant* found = db.findPlantByName(name);
                    if (found != nullptr) {
                        cout << "\nНайдено растение:" << endl;
                        found->display();
                    } else {
                        cout << "Растение с названием '" << name << "' не найдено!" << endl;
                    }
                } else {
                    cout << "База данных пуста!" << endl;
                }
                break;
                
            case 6:
                if (!db.isEmpty()) {
                    cout << "Введите вид для поиска: ";
                    string type;
                    getline(cin, type);
                    
                    vector<const Plant*> found = db.findAllPlantsByType(type);
                    if (!found.empty()) {
                        cout << "\nНайдено растений: " << found.size() << endl;
                        for (const auto* plant : found) {
                            cout << "------------------------" << endl;
                            plant->display();
                        }
                    } else {
                        cout << "Растения вида '" << type << "' не найдены!" << endl;
                    }
                } else {
                    cout << "База данных пуста!" << endl;
                }
                break;
                
            case 7:
                db.saveToFile(FILENAME);
                break;
                
            case 8:
                db.loadFromFile(FILENAME);
                break;
                
            case 9:
                cout << "Сохранить изменения перед выходом? (y/n): ";
                char answer;
                cin >> answer;
                GardenDB::clearInputBuffer();
                
                if (answer == 'y' || answer == 'Y') {
                    db.saveToFile(FILENAME);
                }
                
                running = false;
                cout << "До свидания!" << endl;
                break;
                
            default:
                cout << "Неверный выбор! Пожалуйста, введите число от 1 до 9." << endl;
        }
    }
    
    return 0;
}