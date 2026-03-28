#ifndef GARDEN_H
#define GARDEN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>

class Plant {
private:
    int id;
    std::string name;
    std::string type;
    int growth_time_months;
    Plant* next;

public:
    Plant();
    Plant(int id, const std::string& name, const std::string& type, int growth_time);
    ~Plant();
    
    Plant(const Plant& other);
    Plant& operator=(const Plant& other);
    
    int getId() const;
    std::string getName() const;
    std::string getType() const;
    int getGrowthTime() const;
    
    void setName(const std::string& new_name);
    void setType(const std::string& new_type);
    void setGrowthTime(int new_time);
    
    Plant* getNext() const;
    void setNext(Plant* next);
    
    void display() const;
    std::string toString() const;
    
    static Plant fromString(const std::string& line);
    
    friend class GardenDB;
};

class GardenDB {
private:
    Plant* head;
    Plant* tail;
    int count;
    int next_id;
    std::string filename;
    
    Plant* findPlantById(int id);
    const Plant* findPlantById(int id) const;
    
    void clear();

public:
    GardenDB();
    explicit GardenDB(const std::string& filename);
    ~GardenDB();
    
    GardenDB(const GardenDB& other) = delete;
    GardenDB& operator=(const GardenDB& other) = delete;
    
    void addPlant();
    bool deletePlant(int id);
    bool editPlant(int id);
    void displayAllPlants() const;
    
    const Plant& findPlantByName(const std::string& name) const;
    const Plant& findPlantByType(const std::string& type) const;
    
    bool saveToFile() const;
    bool loadFromFile();
    
    int getPlantCount() const;
    bool isEmpty() const;
    
    void setFilename(const std::string& filename);
    std::string getFilename() const;
    
    static void showMenu();
    static int getChoice();
    static void clearInputBuffer();
};

#endif
