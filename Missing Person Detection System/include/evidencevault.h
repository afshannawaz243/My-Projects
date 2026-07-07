#ifndef EVIDENCEVAULT_H
#define EVIDENCEVAULT_H

#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "DigitalEvidence.h"
#include "SocialMediaTrace.h"
#include "PhysicalEvidence.h"
using namespace std;

struct CustodyRecord {
    DateTime timestamp;
    string   handledBy;
    string   action;
    string   notes;
};

class EvidenceVault {
private:
    vector<unique_ptr<DigitalEvidence>>  digitalItems;
    vector<unique_ptr<SocialMediaTrace>> socialItems;
    vector<unique_ptr<PhysicalEvidence>> physicalItems;
    map<string, vector<CustodyRecord>>   custodyChain;
    string dataDirectory;
    int    nextEvidenceNumber;

    string generateEvidenceId(const string& prefix);

public:
    explicit EvidenceVault(const string& dataDir = "data/");
    ~EvidenceVault();

    // Add evidence
    string addDigitalEvidence(const string& caseId, const string& collectedBy,
        const string& description, DeviceType device,
        const string& model, const string& serial);
    string addSocialMediaTrace(const string& caseId, const string& collectedBy,
        const string& description, Platform platform,
        const string& username, const string& profileUrl);
    string addPhysicalEvidence(const string& caseId, const string& collectedBy,
        const string& description, const string& location,
        const string& itemType, Condition condition);

    // Retrieval
    DigitalEvidence* getDigitalEvidence(const string& id);
    SocialMediaTrace* getSocialMediaTrace(const string& id);
    PhysicalEvidence* getPhysicalEvidence(const string& id);
    vector<Evidence*> getEvidenceForCase(const string& caseId);

    // Chain of custody
    void addCustodyRecord(const string& evidenceId, const string& handledBy,
        const string& action, const string& notes = "");
    void displayCustodyChain(const string& evidenceId) const;

    // Analysis
    void   analyzeAllForCase(const string& caseId);
    double getCaseEvidenceScore(const string& caseId) const;

    // Display
    void displayAllEvidence()                        const;
    void displayEvidenceForCase(const string& caseId)const;

    // File I/O
    void saveAll() const;
    void loadAll();

    int getTotalCount() const {
        return (int)(digitalItems.size() +
            socialItems.size() +
            physicalItems.size());
    }
};

#endif
