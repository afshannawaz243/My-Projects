#ifndef CASEMANAGER_H
#define CASEMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ActiveCase.h"
#include "ClosedCase.h"
#include "MissingPerson.h"
#include "Witness.h"
#include "Suspect.h"
using namespace std;

// Template search function
template<typename T>
vector<T*> searchByField(vector<unique_ptr<T>>& items,
    function<bool(const T&)> predicate) {
    vector<T*> results;
    for (auto& item : items)
        if (predicate(*item))
            results.push_back(item.get());
    return results;
}

class CaseManager {
private:
    vector<unique_ptr<ActiveCase>>    activeCases;
    vector<unique_ptr<ClosedCase>>    closedCases;
    vector<unique_ptr<MissingPerson>> persons;
    vector<unique_ptr<Witness>>       witnesses;
    vector<unique_ptr<Suspect>>       suspects;

    string dataDirectory;
    int    nextCaseNumber;
    int    nextPersonNumber;

    string generateCaseId();
    string generatePersonId(const string& role);

public:
    explicit CaseManager(const string& dataDir = "data/");
    ~CaseManager();

    // Case operations
    string      addActiveCase(const string& title, const string& officer,
        const string& personId,
        CasePriority priority = CasePriority::HIGH);
    void        closeCase(const string& caseId, ClosureReason reason,
        const string& notes, const string& officer);
    ActiveCase* getActiveCase(const string& caseId);
    ClosedCase* getClosedCase(const string& caseId);
    void        displayAllActive()  const;
    void        displayAllClosed()  const;

    // Person operations
    string addMissingPerson(const string& name, int age,
        const string& gender, const string& nat,
        const string& phone, const string& addr,
        const string& lastLoc, const DateTime& lastSeen,
        const string& desc);
    string addWitness(const string& name, int age,
        const string& gender, const string& nat,
        const string& phone, const string& addr,
        const string& stmt, const string& caseId,
        bool anon = false);
    string addSuspect(const string& name, int age,
        const string& gender, const string& nat,
        const string& phone, const string& addr,
        const string& caseId,
        ThreatLevel threat = ThreatLevel::LOW);

    MissingPerson* getMissingPerson(const string& id);
    Witness* getWitness(const string& id);
    Suspect* getSuspect(const string& id);

    // Search using template
    vector<ActiveCase*>    searchCasesByOfficer(const string& officer);
    vector<ActiveCase*>    searchCasesByPriority(CasePriority p);
    vector<MissingPerson*> searchPersonByName(const string& name);

    // Sorting
    void sortActiveCasesByPriority();
    void sortActiveCasesByDate();

    // File I/O
    void saveAll() const;
    void loadAll();

    // Stats
    void displayStats() const;

    int getActiveCaseCount()   const { return (int)activeCases.size(); }
    int getClosedCaseCount()   const { return (int)closedCases.size(); }
    int getMissingPersonCount()const { return (int)persons.size(); }
    int getWitnessCount()      const { return (int)witnesses.size(); }
    int getSuspectCount()      const { return (int)suspects.size(); }
};

#endif
