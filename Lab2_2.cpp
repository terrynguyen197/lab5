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

    ~Country()
    {
        delete[] name;
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

};

struct Node
{
    Country* ptr;
    Node* next;
};

struct Node* head = nullptr;

void addCountry(int key, const char* name, long population)
{
    Node* temp = head;
    while (temp != nullptr)
    {
        if (temp->ptr->getKey() == key)
        {
            temp->ptr->print();
            std::cout << "Population updated to " << population << std::endl;
            temp->ptr->refPopulation() = population;
            return;
        }
        temp = temp->next;
    }

    Country* new_country = new Country(key, name, population);
    Node* new_node = new Node{new_country, nullptr};
    if (head == nullptr)
    {
        head = new_node;
    }
    else
    {
        new_node->next = head;
        head = new_node;
    }
}

long& updateCountry(int key, const char* name)
{
    Node* temp = head;
    while (temp != nullptr)
    {
        if (temp->ptr->getKey() == key)
        {
            if (strcmp(temp->ptr->name, name) != 0)
            {
                delete[] temp->ptr->name;
                temp->ptr->name = new char[strlen(name) + 1];
                strcpy(temp->ptr->name, name);
            }
            return temp->ptr->refPopulation();
        }
        temp = temp->next;
    }

    Country* new_country = new Country(key, name, 0);
    Node* new_node = new Node{new_country, nullptr};
    if (head == nullptr)
    {
        head = new_node;
    }
    else
    {
        new_node->next = head;
        head = new_node;
    }
    return new_country->refPopulation();
}

void removeCountry(int key)
{
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr)
    {
        if (curr->ptr->getKey() == key)
        {
            if (prev == nullptr)
            {
                head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr->ptr;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
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

    long& usa_pop = updateCountry(1, "United States");
    usa_pop += 2000000;
