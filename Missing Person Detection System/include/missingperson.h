#ifndef MISSINGPERSON_H
#define MISSINGPERSON_H

#include <vector>
#include "Person.h"

enum class CaseStatus { ACTIVE, FOUND_SAFE, FOUND_DECEASED, CLOSED };

class MissingPerson : public Person {
private:
    string     lastSeenLocation;
    DateTime   lastSeenDate;
    string     physicalDescription;
    string     biometricHash;
    CaseStatus status;
    string     linkedCaseId;
    vector<string> knownFrequentPlaces;
    double     urgencyScore;

    void calculateUrgency();

public:
    MissingPerson(const string& id, const string& name, int age,
        const string& gender, const string& nationality,
        const string& phone, const string& address,
        const string& lastLocation, const DateTime& lastSeen,
        const string& description);

    MissingPerson(const MissingPerson& other);
    ~MissingPerson() override;

    // Overrides
    void   displayInfo()              const override;
    string getRole()                  const override { return "Missing Person"; }
    double getRiskScore()             const override { return urgencyScore; }
    void   saveToFile(ofstream& ofs)  const override;

    // Specific methods
    void   updateStatus(CaseStatus newStatus);
    void   addFrequentPlace(const string& place);
    void   linkCase(const string& caseId);
    void   setBiometricHash(const string& hash);
    string statusToString() const;

    // Getters
    string     getLastSeenLocation() const { return lastSeenLocation; }
    DateTime   getLastSeenDate()     const { return lastSeenDate; }
    CaseStatus getStatus()           const { return status; }
    string     getLinkedCaseId()     const { return linkedCaseId; }
};

#endif