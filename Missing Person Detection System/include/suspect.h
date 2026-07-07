#ifndef SUSPECT_H
#define SUSPECT_H

#include <vector>
#include "Person.h"

enum class ThreatLevel { LOW, MODERATE, HIGH, CRITICAL };

class Suspect : public Person {
private:
    ThreatLevel    threatLevel;
    vector<string> aliases;
    vector<string> knownLocations;
    string         criminalHistory;
    string         linkedCaseId;
    double         threatScore;
    bool           isArrested;
    string         lastKnownDevice;

public:
    Suspect(const string& id, const string& name, int age,
        const string& gender, const string& nationality,
        const string& phone, const string& address,
        const string& caseId,
        ThreatLevel threat = ThreatLevel::LOW);

    Suspect(const Suspect& other);
    ~Suspect() override;

    // Overrides
    void   displayInfo()             const override;
    string getRole()                 const override { return "Suspect"; }
    double getRiskScore()            const override { return threatScore; }
    void   saveToFile(ofstream& ofs) const override;

    // Specific methods
    void   addAlias(const string& alias);
    void   addKnownLocation(const string& location);
    void   setThreatLevel(ThreatLevel level);
    void   setArrested(bool arrested);
    void   setLastKnownDevice(const string& device);
    void   setCriminalHistory(const string& history);
    string threatLevelToString() const;

    // Getters
    ThreatLevel    getThreatLevel()    const { return threatLevel; }
    bool           getIsArrested()     const { return isArrested; }
    vector<string> getAliases()        const { return aliases; }
    vector<string> getKnownLocations() const { return knownLocations; }
    string         getLastKnownDevice()const { return lastKnownDevice; }
};

#endif