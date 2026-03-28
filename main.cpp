#include "Garden.h"
#include <iostream>

void printUsage(const char* program_name) {
    std::cout << "Использование: " << program_name << " [имя_файла_базы_данных]" << std::endl;
    std::cout << "Пример: " << program_name << " my_garden.txt" << std::endl;
    std::cout << "Если имя файла не указано, используется garden_db.txt" << std::endl;
}

int main(int argc, char* argv[]) {
    GardenDB db;
    
    if (argc > 1) {
        db.setFilename(argv[1]);
        std::cout << "Используется файл базы данных: " << argv[1] << std::endl;
    } else {
        std::cout << "Используется файл базы данных по умолчанию: garden_db.txt" << std::endl;
        std::cout << "Для указания своего файла запустите: " << argv[0] << " имя_файла.txt" << std::endl;
    }
    
    std::cout << "Загрузка базы данных..." << std::endl;
    db.loadFromFile();
    
    bool running = true;
    
    std::cout << "\nДобро пожаловать в программу управления садом!" << std::endl;
    
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
                    std::cout << "Введите ID растения для удаления: ";
                    int id;
                    std::cin >> id;
                    GardenDB::clearInputBuffer();
                    db.deletePlant(id);
                } else {
                    std::cout << "База данных пуста!" << std::endl;
                }
                break;
                
            case 4:
                if (!db.isEmpty()) {
                    std::cout << "Введите ID растения для редактирования: ";
                    int id;
                    std::cin >> id;
                    GardenDB::clearInputBuffer();
                    db.editPlant(id);
                } else {
                    std::cout << "База данных пуста!" << std::endl;
                }
                break;
                
            case 5: {
                if (!db.isEmpty()) {
                    std::cout << "Введите название для поиска: ";
                    std::string name;
                    std::getline(std::cin, name);
                    
                    const Plant& found = db.findPlantByName(name);
                    if (found.getId() != 0) {
                        std::cout << "\nНайдено растение:" << std::endl;
                        found.display();
                    } else {
                        std::cout << "Растение с названием '" << name << "' не найдено!" << std::endl;
                    }
                } else {
                    std::cout << "База данных пуста!" << std::endl;
                }
                break;
            }
                
            case 6: {
                if (!db.isEmpty()) {
                    std::cout << "Введите вид для поиска: ";
                    std::string type;
                    std::getline(std::cin, type);
                    
                    const Plant& found = db.findPlantByType(type);
                    if (found.getId() != 0) {
                        std::cout << "\nНайдено растение:" << std::endl;
                        found.display();
                    } else {
                        std::cout << "Растение вида '" << type << "' не найдено!" << std::endl;
                    }
                } else {
                    std::cout << "База данных пуста!" << std::endl;
                }
                break;
            }
                
            case 7:
                db.saveToFile();
                break;
                
            case 8:
                db.loadFromFile();
                break;
                
            case 9: {
                std::cout << "Сохранить изменения перед выходом? (y/n): ";
                char answer;
                std::cin >> answer;
                GardenDB::clearInputBuffer();
                
                if (answer == 'y' || answer == 'Y') {
                    db.saveToFile();
                }
                
                running = false;
                std::cout << "До свидания!" << std::endl;
                break;
            }
                
            default:
                std::cout << "Неверный выбор! Пожалуйста, введите число от 1 до 9." << std::endl;
        }
    }
    
    return 0;
}
