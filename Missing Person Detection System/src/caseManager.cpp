#include "CaseManager.h"
#include <iostream>
using namespace std;

CaseManager::CaseManager(const string& dataDir)
    : dataDirectory(dataDir), nextCaseNumber(1), nextPersonNumber(1) {
}

CaseManager::~CaseManager() {}

string CaseManager::generateCaseId() {
    ostringstream oss;
    oss << "CASE-" << setfill('0') << setw(4) << nextCaseNumber++;
    return oss.str();
}

string CaseManager::generatePersonId(const string& role) {
    ostringstream oss;
    if (role == "MP")  oss << "MP-" << setfill('0') << setw(4) << nextPersonNumber++;
    else if (role == "WIT") oss << "WIT-" << setfill('0') << setw(4) << nextPersonNumber++;
    else                    oss << "SUS-" << setfill('0') << setw(4) << nextPersonNumber++;
    return oss.str();
}

string CaseManager::addActiveCase(const string& title, const string& officer,
    const string& personId, CasePriority priority) {
    if (title.empty())   throw InvalidInputException("case title");
    if (officer.empty()) throw InvalidInputException("officer name");
    string id = generateCaseId();
    activeCases.push_back(make_unique<ActiveCase>(id, title, officer, personId, priority));
    return id;
}

void CaseManager::closeCase(const string& caseId, ClosureReason reason,
    const string& notes, const string& officer) {
    for (auto it = activeCases.begin(); it != activeCases.end(); ++it) {
        if ((*it)->getCaseId() == caseId) {
            auto closed = make_unique<ClosedCase>(*(*it), reason, notes, officer);
            closedCases.push_back(move(closed));
            activeCases.erase(it);
            return;
        }
    }
    throw CaseNotFoundException(caseId);
}

ActiveCase* CaseManager::getActiveCase(const string& caseId) {
    for (auto& c : activeCases)
        if (c->getCaseId() == caseId) return c.get();
    throw CaseNotFoundException(caseId);
}

ClosedCase* CaseManager::getClosedCase(const string& caseId) {
    for (auto& c : closedCases)
        if (c->getCaseId() == caseId) return c.get();
    throw CaseNotFoundException(caseId);
}

void CaseManager::displayAllActive() const {
    if (activeCases.empty()) { cout << "  No active cases.\n"; return; }
    for (const auto& c : activeCases) cout << *c << "\n";
}

void CaseManager::displayAllClosed() const {
    if (closedCases.empty()) { cout << "  No closed cases.\n"; return; }
    for (const auto& c : closedCases) cout << *c << "\n";
}

string CaseManager::addMissingPerson(const string& name, int age,
    const string& gender, const string& nat,
    const string& phone, const string& addr,
    const string& lastLoc, const DateTime& lastSeen,
    const string& desc) {
    string id = generatePersonId("MP");
    persons.push_back(make_unique<MissingPerson>(
        id, name, age, gender, nat, phone, addr, lastLoc, lastSeen, desc));
    return id;
}

string CaseManager::addWitness(const string& name, int age,
    const string& gender, const string& nat,
    const string& phone, const string& addr,
    const string& stmt, const string& caseId, bool anon) {
    string id = generatePersonId("WIT");
    witnesses.push_back(make_unique<Witness>(
        id, name, age, gender, nat, phone, addr, stmt, caseId, anon));
    return id;
}

string CaseManager::addSuspect(const string& name, int age,
    const string& gender, const string& nat,
    const string& phone, const string& addr,
    const string& caseId, ThreatLevel threat) {
    string id = generatePersonId("SUS");
    suspects.push_back(make_unique<Suspect>(
        id, name, age, gender, nat, phone, addr, caseId, threat));
    return id;
}

MissingPerson* CaseManager::getMissingPerson(const string& id) {
    for (auto& p : persons)
        if (p->getId() == id) return p.get();
    throw PersonNotFoundException(id);
}

Witness* CaseManager::getWitness(const string& id) {
    for (auto& w : witnesses)
        if (w->getId() == id) return w.get();
    throw PersonNotFoundException(id);
}

Suspect* CaseManager::getSuspect(const string& id) {
    for (auto& s : suspects)
        if (s->getId() == id) return s.get();
    throw PersonNotFoundException(id);
}

vector<ActiveCase*> CaseManager::searchCasesByOfficer(const string& officer) {
    return searchByField<ActiveCase>(activeCases,
        [&](const ActiveCase& c) {
            return c.getOfficer().find(officer) != string::npos;
        });
}

vector<ActiveCase*> CaseManager::searchCasesByPriority(CasePriority p) {
    return searchByField<ActiveCase>(activeCases,
        [&](const ActiveCase& c) { return c.getPriority() == p; });
}

vector<MissingPerson*> CaseManager::searchPersonByName(const string& name) {
    return searchByField<MissingPerson>(persons,
        [&](const MissingPerson& p) {
            return p.getName().find(name) != string::npos;
        });
}

void CaseManager::sortActiveCasesByPriority() {
    sort(activeCases.begin(), activeCases.end(),
        [](const unique_ptr<ActiveCase>& a, const unique_ptr<ActiveCase>& b) {
            return *a < *b;
        });
}

void CaseManager::sortActiveCasesByDate() {
    sort(activeCases.begin(), activeCases.end(),
        [](const unique_ptr<ActiveCase>& a, const unique_ptr<ActiveCase>& b) {
            return a->getOpenedDate() < b->getOpenedDate();
        });
}

void CaseManager::saveAll() const {
    ofstream ofs(dataDirectory + "cases.dat");
    if (!ofs) throw FileIOException(dataDirectory + "cases.dat");
    ofs << nextCaseNumber << "\n" << nextPersonNumber << "\n";
    for (const auto& c : activeCases) c->saveToFile(ofs);
    for (const auto& c : closedCases) c->saveToFile(ofs);
    for (const auto& p : persons)     p->saveToFile(ofs);
    for (const auto& w : witnesses)   w->saveToFile(ofs);
    for (const auto& s : suspects)    s->saveToFile(ofs);
    ofs.close();
}

void CaseManager::loadAll() {
    ifstream ifs(dataDirectory + "cases.dat");
    if (!ifs) return;
    ifs >> nextCaseNumber >> nextPersonNumber;
    ifs.close();
}

void CaseManager::displayStats() const {
    cout << "\n========================================\n";
    cout << "          SYSTEM DASHBOARD\n";
    cout << "========================================\n";
    cout << " Active Cases    : " << activeCases.size() << "\n";
    cout << " Closed Cases    : " << closedCases.size() << "\n";
    cout << " Missing Persons : " << persons.size() << "\n";
    cout << " Witnesses       : " << witnesses.size() << "\n";
    cout << " Suspects        : " << suspects.size() << "\n";
    cout << "========================================\n";
}