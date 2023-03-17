#include <iostream>
#include <cstring>

class Country
{
    int key;
    char* name;
    long population;

public:
    Country(int key, const char* name, long population)
    {
        this->key = key;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->population = population;
    }

    int getKey()
    {
        return key;
    }

    long& refPopulation()
    {
        return population;
    }

    void print()
    {
        std::cout << "Country key: " << key << ", Name: " << name << ", Population: " << population << std::endl;
    }

    void updateName(const char* newName)
    {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }
};

struct Node
{
    Country* ptr;
    Node* next;
};

struct Node* head = nullptr;

long& findPopulation(int key)
{
    Node* temp = head;
    while (temp != nullptr)
    {
        if (temp->ptr->getKey() == key)
        {
            return temp->ptr->refPopulation();
        }
        temp = temp->next;
    }
    Country* new_country = new Country(key, "New Country", 0);
    Node* new_node = new Node{new_country, nullptr};
    new_node->next = head;
    head = new_node;
    return new_country->refPopulation();
}

int& updateCountry(int key, const char* name)
{
    long& population = findPopulation(key);
    if (strcmp(name, head->ptr->name) != 0)
    {
        head->ptr->updateName(name);
    }
    return population;
}

void removeCountry(int key)
{
    Node* temp = head;
    Node* prev = nullptr;
    while (temp != nullptr)
    {
        if (temp->ptr->getKey() == key)
        {
            if (prev == nullptr)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            delete temp->ptr;
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void addCountry(int key, const char* name, long population)
{
    long& countryPopulation = findPopulation(key);
    countryPopulation = population;
    if (strcmp(name, head->ptr->name) != 0)
    {
        head->ptr->updateName(name);
    }
}

void print()
{
    Node* temp = head;
    while (temp != nullptr)
    {
        temp->ptr->print();
        temp = temp->next;
    }
}

int main()
{
    print();

    addCountry(1, "USA", 328200000);
    addCountry(2, "China", 1393000000);
    addCountry(3, "Japan", 126500000);
    addCountry(1, "USA", 330000000);
    addCountry(2, "China", 1443000000);
    addCountry(3, "Update Japan", 130500000);

    print();

    std::cout << "Population of USA before update: " << findPopulation(1) << std::endl;
    updateCountry(1, "United States of America");
    std::cout << "Population of USA after update: " << findPopulation(1) << std::endl;

    removeCountry(2);
    std::cout << "After removing China:"
