#ifndef CASE_H
#define CASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "DateTime.h"
#include "Exceptions.h"
using namespace std;

enum class CasePriority { LOW, MEDIUM, HIGH, CRITICAL };

class Case {
protected:
    string         caseId;
    string         title;
    string         assignedOfficer;
    DateTime       openedDate;
    CasePriority   priority;
    string         missingPersonId;
    vector<string> evidenceIds;
    vector<string> suspectIds;
    vector<string> witnessIds;
    string         description;

public:
    Case(const string& id, const string& title,
        const string& officer, const string& missingPersonId,
        CasePriority priority = CasePriority::MEDIUM);

    Case(const Case& other);
    Case& operator=(const Case& other);
    virtual ~Case();

    // Pure virtual
    virtual void   displaySummary()          const = 0;
    virtual string getCaseType()             const = 0;
    virtual void   generateReport()          const = 0;
    virtual void   saveToFile(ofstream& ofs) const = 0;

    // Concrete methods
    void addEvidence(const string& evidenceId);
    void addSuspect(const string& suspectId);
    void addWitness(const string& witnessId);
    bool hasEvidence(const string& evidenceId) const;

    // Getters
    string         getCaseId()          const { return caseId; }
    string         getTitle()           const { return title; }
    string         getOfficer()         const { return assignedOfficer; }
    CasePriority   getPriority()        const { return priority; }
    string         getMissingPersonId() const { return missingPersonId; }
    vector<string> getEvidenceIds()     const { return evidenceIds; }
    vector<string> getSuspectIds()      const { return suspectIds; }
    vector<string> getWitnessIds()      const { return witnessIds; }
    DateTime       getOpenedDate()      const { return openedDate; }

    void setPriority(CasePriority p) { priority = p; }
    void setOfficer(const string& officer) { assignedOfficer = officer; }

    string priorityToString() const;

    bool operator==(const Case& other) const;
    bool operator<(const Case& other)  const;
    friend ostream& operator<<(ostream& os, const Case& c);
};

#endif
