#include "EvidenceVault.h"
#include <iostream>
using namespace std;

EvidenceVault::EvidenceVault(const string& dataDir)
    : dataDirectory(dataDir), nextEvidenceNumber(1) {
}

EvidenceVault::~EvidenceVault() {}

string EvidenceVault::generateEvidenceId(const string& prefix) {
    ostringstream oss;
    oss << prefix << "-" << setfill('0') << setw(4) << nextEvidenceNumber++;
    return oss.str();
}

string EvidenceVault::addDigitalEvidence(const string& caseId,
    const string& collectedBy,
    const string& description,
    DeviceType device,
    const string& model,
    const string& serial) {
    string id = generateEvidenceId("DIG");
    auto ev = make_unique<DigitalEvidence>(
        id, caseId, collectedBy, description, device, model, serial);
    ev->analyzeRelevance();
    addCustodyRecord(id, collectedBy, "Collected", "Initial intake");
    digitalItems.push_back(move(ev));
    return id;
}

string EvidenceVault::addSocialMediaTrace(const string& caseId,
    const string& collectedBy,
    const string& description,
    Platform platform,
    const string& username,
    const string& profileUrl) {
    string id = generateEvidenceId("SMT");
    auto ev = make_unique<SocialMediaTrace>(
        id, caseId, collectedBy, description, platform, username, profileUrl);
    ev->analyzeRelevance();
    addCustodyRecord(id, collectedBy, "Collected", "Social media account identified");
    socialItems.push_back(move(ev));
    return id;
}

string EvidenceVault::addPhysicalEvidence(const string& caseId,
    const string& collectedBy,
    const string& description,
    const string& location,
    const string& itemType,
    Condition condition) {
    string id = generateEvidenceId("PHY");
    auto ev = make_unique<PhysicalEvidence>(
        id, caseId, collectedBy, description, location, itemType, condition);
    ev->analyzeRelevance();
    addCustodyRecord(id, collectedBy, "Collected", "Found at scene");
    physicalItems.push_back(move(ev));
    return id;
}

DigitalEvidence* EvidenceVault::getDigitalEvidence(const string& id) {
    for (auto& e : digitalItems)
        if (e->getId() == id) return e.get();
    throw EvidenceException("Digital evidence not found: " + id);
}

SocialMediaTrace* EvidenceVault::getSocialMediaTrace(const string& id) {
    for (auto& e : socialItems)
        if (e->getId() == id) return e.get();
    throw EvidenceException("Social media trace not found: " + id);
}

PhysicalEvidence* EvidenceVault::getPhysicalEvidence(const string& id) {
    for (auto& e : physicalItems)
        if (e->getId() == id) return e.get();
    throw EvidenceException("Physical evidence not found: " + id);
}

vector<Evidence*> EvidenceVault::getEvidenceForCase(const string& caseId) {
    vector<Evidence*> results;
    for (auto& e : digitalItems)
        if (e->getCaseId() == caseId) results.push_back(e.get());
    for (auto& e : socialItems)
        if (e->getCaseId() == caseId) results.push_back(e.get());
    for (auto& e : physicalItems)
        if (e->getCaseId() == caseId) results.push_back(e.get());
    sort(results.begin(), results.end(),
        [](Evidence* a, Evidence* b) { return *a < *b; });
    return results;
}

void EvidenceVault::addCustodyRecord(const string& evidenceId,
    const string& handledBy,
    const string& action,
    const string& notes) {
    CustodyRecord rec;
    rec.timestamp = DateTime::now();
    rec.handledBy = handledBy;
    rec.action = action;
    rec.notes = notes;
    custodyChain[evidenceId].push_back(rec);
}

void EvidenceVault::displayCustodyChain(const string& evidenceId) const {
    auto it = custodyChain.find(evidenceId);
    if (it == custodyChain.end()) {
        cout << "  No custody records for " << evidenceId << "\n";
        return;
    }
    cout << "\n========================================\n";
    cout << "  CHAIN OF CUSTODY: " << evidenceId << "\n";
    cout << "========================================\n";
    for (const auto& r : it->second) {
        cout << " [" << r.timestamp << "] " << r.action << "\n";
        cout << "  By: " << r.handledBy << "\n";
        if (!r.notes.empty())
            cout << "  Notes: " << r.notes << "\n";
        cout << "----------------------------------------\n";
    }
}

void EvidenceVault::analyzeAllForCase(const string& caseId) {
    cout << "\n  Analyzing evidence for case " << caseId << "...\n";
    for (auto& e : digitalItems)
        if (e->getCaseId() == caseId) {
            e->analyzeRelevance();
            addCustodyRecord(e->getId(), "SYSTEM", "Analyzed", "Auto scoring");
        }
    for (auto& e : socialItems)
        if (e->getCaseId() == caseId) {
            e->analyzeRelevance();
            addCustodyRecord(e->getId(), "SYSTEM", "Analyzed", "Social media analysis");
        }
    for (auto& e : physicalItems)
        if (e->getCaseId() == caseId) {
            e->analyzeRelevance();
            addCustodyRecord(e->getId(), "SYSTEM", "Analyzed", "Physical assessment");
        }
    cout << "  Analysis complete.\n";
}

double EvidenceVault::getCaseEvidenceScore(const string& caseId) const {
    double total = 0.0;
    int    count = 0;
    for (const auto& e : digitalItems)
        if (e->getCaseId() == caseId) { total += e->getRelevanceScore(); count++; }
    for (const auto& e : socialItems)
        if (e->getCaseId() == caseId) { total += e->getRelevanceScore(); count++; }
    for (const auto& e : physicalItems)
        if (e->getCaseId() == caseId) { total += e->getRelevanceScore(); count++; }
    return count > 0 ? total / count : 0.0;
}

void EvidenceVault::displayAllEvidence() const {
    cout << "\n=== ALL EVIDENCE IN VAULT ===\n";
    for (const auto& e : digitalItems)  e->displayInfo();
    for (const auto& e : socialItems)   e->displayInfo();
    for (const auto& e : physicalItems) e->displayInfo();
}

void EvidenceVault::displayEvidenceForCase(const string& caseId) const {
    cout << "\n=== EVIDENCE FOR CASE: " << caseId << " ===\n";
    bool found = false;
    for (const auto& e : digitalItems)
        if (e->getCaseId() == caseId) { e->displayInfo(); found = true; }
    for (const auto& e : socialItems)
        if (e->getCaseId() == caseId) { e->displayInfo(); found = true; }
    for (const auto& e : physicalItems)
        if (e->getCaseId() == caseId) { e->displayInfo(); found = true; }
    if (!found) cout << "  No evidence found for this case.\n";
}

void EvidenceVault::saveAll() const {
    ofstream ofs(dataDirectory + "evidence.dat");
    if (!ofs) throw FileIOException(dataDirectory + "evidence.dat");
    ofs << nextEvidenceNumber << "\n";
    for (const auto& e : digitalItems)  e->saveToFile(ofs);
    for (const auto& e : socialItems)   e->saveToFile(ofs);
    for (const auto& e : physicalItems) e->saveToFile(ofs);
    ofs.close();
}

void EvidenceVault::loadAll() {
    ifstream ifs(dataDirectory + "evidence.dat");
    if (!ifs) return;
    ifs >> nextEvidenceNumber;
    ifs.close();
}