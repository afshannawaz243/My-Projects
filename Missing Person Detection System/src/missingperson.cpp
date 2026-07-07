#include "MissingPerson.h"
#include <iostream>
#include <fstream>
using namespace std;

MissingPerson::MissingPerson(const string& id, const string& nm, int a,
    const string& g, const string& nat,
    const string& phone, const string& addr,
    const string& lastLoc, const DateTime& lastSeen,
    const string& desc)
    : Person(id, nm, a, g, nat, phone, addr),
    lastSeenLocation(lastLoc), lastSeenDate(lastSeen),
    physicalDescription(desc), biometricHash(""),
    status(CaseStatus::ACTIVE), linkedCaseId(""),
    urgencyScore(0.0) {
    calculateUrgency();
}

MissingPerson::MissingPerson(const MissingPerson& other)
    : Person(other),
    lastSeenLocation(other.lastSeenLocation),
    lastSeenDate(other.lastSeenDate),
    physicalDescription(other.physicalDescription),
    biometricHash(other.biometricHash),
    status(other.status),
    linkedCaseId(other.linkedCaseId),
    knownFrequentPlaces(other.knownFrequentPlaces),
    urgencyScore(other.urgencyScore) {
}

MissingPerson::~MissingPerson() {}

void MissingPerson::calculateUrgency() {
    urgencyScore = 5.0;
    if (age < 18 || age > 65) urgencyScore += 3.0;
    if (status == CaseStatus::ACTIVE) urgencyScore += 2.0;
    if (urgencyScore > 10.0) urgencyScore = 10.0;
}

void MissingPerson::displayInfo() const {
    cout << "\n========================================\n";
    cout << "        MISSING PERSON RECORD\n";
    cout << "========================================\n";
    cout << " ID          : " << personId << "\n";
    cout << " Name        : " << name << "\n";
    cout << " Age         : " << age << "\n";
    cout << " Gender      : " << gender << "\n";
    cout << " Nationality : " << nationality << "\n";
    cout << " Last Seen   : " << lastSeenLocation << "\n";
    cout << " Date        : " << lastSeenDate << "\n";
    cout << " Status      : " << statusToString() << "\n";
    cout << " Urgency     : " << urgencyScore << "/10\n";
    cout << " Description : " << physicalDescription << "\n";
    if (!linkedCaseId.empty())
        cout << " Case ID     : " << linkedCaseId << "\n";
    cout << "========================================\n";
}

string MissingPerson::statusToString() const {
    switch (status) {
    case CaseStatus::ACTIVE:         return "ACTIVE";
    case CaseStatus::FOUND_SAFE:     return "FOUND SAFE";
    case CaseStatus::FOUND_DECEASED: return "FOUND DECEASED";
    case CaseStatus::CLOSED:         return "CLOSED";
    default:                         return "UNKNOWN";
    }
}

void MissingPerson::updateStatus(CaseStatus newStatus) {
    status = newStatus;
    calculateUrgency();
}

void MissingPerson::addFrequentPlace(const string& place) {
    knownFrequentPlaces.push_back(place);
}

void MissingPerson::linkCase(const string& caseId) {
    linkedCaseId = caseId;
}

void MissingPerson::setBiometricHash(const string& hash) {
    biometricHash = hash;
}

void MissingPerson::saveToFile(ofstream& ofs) const {
    ofs << "MISSING_PERSON\n";
    ofs << personId << "\n";
    ofs << name << "\n";
    ofs << age << "\n";
    ofs << gender << "\n";
    ofs << nationality << "\n";
    ofs << contactPhone << "\n";
    ofs << address << "\n";
    ofs << lastSeenLocation << "\n";
    ofs << physicalDescription << "\n";
    ofs << biometricHash << "\n";
    ofs << linkedCaseId << "\n";
    ofs << (int)status << "\n";
    ofs << urgencyScore << "\n";
}