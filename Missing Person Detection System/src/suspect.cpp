#include "Suspect.h"
#include <iostream>
#include <fstream>
using namespace std;

Suspect::Suspect(const string& id, const string& nm, int a,
    const string& g, const string& nat,
    const string& phone, const string& addr,
    const string& caseId, ThreatLevel threat)
    : Person(id, nm, a, g, nat, phone, addr),
    threatLevel(threat), linkedCaseId(caseId),
    threatScore(3.0), isArrested(false), lastKnownDevice("") {
    switch (threat) {
    case ThreatLevel::LOW:      threatScore = 2.0;  break;
    case ThreatLevel::MODERATE: threatScore = 5.0;  break;
    case ThreatLevel::HIGH:     threatScore = 7.5;  break;
    case ThreatLevel::CRITICAL: threatScore = 10.0; break;
    }
}

Suspect::Suspect(const Suspect& other)
    : Person(other),
    threatLevel(other.threatLevel),
    aliases(other.aliases),
    knownLocations(other.knownLocations),
    criminalHistory(other.criminalHistory),
    linkedCaseId(other.linkedCaseId),
    threatScore(other.threatScore),
    isArrested(other.isArrested),
    lastKnownDevice(other.lastKnownDevice) {
}

Suspect::~Suspect() {}

void Suspect::displayInfo() const {
    cout << "\n========================================\n";
    cout << "           SUSPECT RECORD\n";
    cout << "========================================\n";
    cout << " ID           : " << personId << "\n";
    cout << " Name         : " << name << "\n";
    cout << " Age          : " << age << "\n";
    cout << " Case ID      : " << linkedCaseId << "\n";
    cout << " Threat Level : " << threatLevelToString() << "\n";
    cout << " Threat Score : " << threatScore << "/10" << "\n";
    cout << " Arrested     : " << (isArrested ? "YES" : "NO") << "\n";
    cout << " Last Device  : " << (lastKnownDevice.empty()
        ? "Unknown" : lastKnownDevice) << "\n";
    if (!aliases.empty()) {
        cout << " Aliases      : ";
        for (const auto& a : aliases) cout << a << "  ";
        cout << "\n";
    }
    if (!knownLocations.empty()) {
        cout << " Known Locs   : ";
        for (const auto& l : knownLocations) cout << l << "  ";
        cout << "\n";
    }
    if (!criminalHistory.empty())
        cout << " Crim History : " << criminalHistory << "\n";
    cout << "========================================\n";
}

string Suspect::threatLevelToString() const {
    switch (threatLevel) {
    case ThreatLevel::LOW:      return "LOW";
    case ThreatLevel::MODERATE: return "MODERATE";
    case ThreatLevel::HIGH:     return "HIGH";
    case ThreatLevel::CRITICAL: return "CRITICAL";
    default:                    return "UNKNOWN";
    }
}

void Suspect::addAlias(const string& alias) {
    if (!alias.empty()) aliases.push_back(alias);
}

void Suspect::addKnownLocation(const string& location) {
    if (!location.empty()) knownLocations.push_back(location);
}

void Suspect::setThreatLevel(ThreatLevel level) {
    threatLevel = level;
    switch (level) {
    case ThreatLevel::LOW:      threatScore = 2.0;  break;
    case ThreatLevel::MODERATE: threatScore = 5.0;  break;
    case ThreatLevel::HIGH:     threatScore = 7.5;  break;
    case ThreatLevel::CRITICAL: threatScore = 10.0; break;
    }
}

void Suspect::setArrested(bool arrested) { isArrested = arrested; }
void Suspect::setLastKnownDevice(const string& d) { lastKnownDevice = d; }
void Suspect::setCriminalHistory(const string& hist) { criminalHistory = hist; }

void Suspect::saveToFile(ofstream& ofs) const {
    ofs << "SUSPECT\n";
    ofs << personId << "\n";
    ofs << name << "\n";
    ofs << age << "\n";
    ofs << gender << "\n";
    ofs << nationality << "\n";
    ofs << contactPhone << "\n";
    ofs << address << "\n";
    ofs << linkedCaseId << "\n";
    ofs << (int)threatLevel << "\n";
    ofs << threatScore << "\n";
    ofs << isArrested << "\n";
    ofs << lastKnownDevice << "\n";
    ofs << criminalHistory << "\n";
    ofs << aliases.size() << "\n";
    for (const auto& a : aliases)        ofs << a << "\n";
    ofs << knownLocations.size() << "\n";
    for (const auto& l : knownLocations) ofs << l << "\n";
}