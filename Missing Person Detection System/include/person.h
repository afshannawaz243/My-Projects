#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <fstream>
#include "DateTime.h"
#include "Exceptions.h"
using namespace std;

class Person {
protected:
    string   personId;
    string   name;
    int      age;
    string   gender;
    string   nationality;
    string   contactPhone;
    string   address;
    DateTime registeredAt;

public:
    // Constructor
    Person(const string& id, const string& name, int age,
        const string& gender, const string& nationality,
        const string& phone, const string& address);

    // Copy constructor
    Person(const Person& other);

    // Assignment operator
    Person& operator=(const Person& other);

    // Virtual destructor (IMPORTANT for polymorphism)
    virtual ~Person();

    // Pure virtual methods — makes Person abstract
    virtual void   displayInfo()              const = 0;
    virtual string getRole()                  const = 0;
    virtual double getRiskScore()             const = 0;
    virtual void   saveToFile(ofstream& ofs)  const = 0;

    // Getters
    string getName()    const { return name; }
    string getId()      const { return personId; }
    int    getAge()     const { return age; }
    string getGender()  const { return gender; }
    string getPhone()   const { return contactPhone; }
    string getAddress() const { return address; }

    // Concrete methods
    void updateContact(const string& phone, const string& newAddress);
    void validate() const;

    // Operator overloading
    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;
    friend ostream& operator<<(ostream& os, const Person& p);
};

#endif