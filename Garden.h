#ifndef GARDEN_H
#define GARDEN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

class Plant {
private:
    int id;
    string name;
    string type;
    int growth_time_months;

public:
    Plant();
    Plant(int id, const string& name, const string& type, int growth_time);
    
    int getId() const;
    string getName() const;
    string getType() const;
    int getGrowthTime() const;
    
    void setName(const string& new_name);
    void setType(const string& new_type);
    void setGrowthTime(int new_time);
    
    void display() const;
    string toString() const;
    
    static Plant fromString(const string& line);
};

class GardenDB {
private:
    vector<Plant> plants;
    int next_id;
    
    Plant* findPlantById(int id);
    const Plant* findPlantById(int id) const;
    
public:
    GardenDB();
    
    void addPlant();
    bool deletePlant(int id);
    bool editPlant(int id);
    void displayAllPlants() const;
    
    const Plant* findPlantByName(const string& name) const;
    const Plant* findPlantByType(const string& type) const;
    vector<const Plant*> findAllPlantsByType(const string& type) const;
    
    bool saveToFile(const string& filename) const;
    bool loadFromFile(const string& filename);
    
    int getPlantCount() const;
    bool isEmpty() const;
    
    static void showMenu();
    static int getChoice();
    static void clearInputBuffer();
};

#endif