#include "Person.h"
using namespace std;

Person::Person(const string& id, const string& nm, int a,
    const string& g, const string& nat,
    const string& phone, const string& addr)
    : personId(id), name(nm), age(a), gender(g),
    nationality(nat), contactPhone(phone), address(addr),
    registeredAt(DateTime::now()) {
    validate();
}

Person::Person(const Person& other)
    : personId(other.personId), name(other.name), age(other.age),
    gender(other.gender), nationality(other.nationality),
    contactPhone(other.contactPhone), address(other.address),
    registeredAt(other.registeredAt) {
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        this->personId = other.personId;
        this->name = other.name;
        this->age = other.age;
        this->gender = other.gender;
        this->nationality = other.nationality;
        this->contactPhone = other.contactPhone;
        this->address = other.address;
        this->registeredAt = other.registeredAt;
    }
    return *this;
}

Person::~Person() {}

void Person::validate() const {
    if (name.empty())
        throw InvalidInputException("name cannot be empty");
    if (age < 0 || age > 130)
        throw InvalidInputException("age must be between 0 and 130");
    if (personId.empty())
        throw InvalidInputException("personId cannot be empty");
}

void Person::updateContact(const string& phone, const string& newAddress) {
    if (phone.empty())
        throw InvalidInputException("phone number");
    contactPhone = phone;
    address = newAddress;
}

bool Person::operator==(const Person& other) const {
    return personId == other.personId;
}

bool Person::operator!=(const Person& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, const Person& p) {
    os << "[" << p.getRole() << "] "
        << p.name
        << " (ID: " << p.personId
        << ", Age: " << p.age << ")";
    return os;
}