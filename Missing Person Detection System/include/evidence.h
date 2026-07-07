#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <string>
#include <iostream>
#include <fstream>
#include "DateTime.h"
#include "Exceptions.h"
using namespace std;

enum class EvidenceStatus { COLLECTED, UNDER_ANALYSIS, VERIFIED, DISCARDED };

class Evidence {
protected:
    string         evidenceId;
    string         linkedCaseId;
    string         collectedBy;
    DateTime       collectionDate;
    EvidenceStatus status;
    string         description;
    double         relevanceScore;

public:
    Evidence(const string& id, const string& caseId,
        const string& collectedBy, const string& description);

    Evidence(const Evidence& other);
    Evidence& operator=(const Evidence& other);
    virtual ~Evidence();

    // Pure virtual
    virtual void   displayInfo()             const = 0;
    virtual string getEvidenceType()         const = 0;
    virtual double analyzeRelevance() = 0;
    virtual void   saveToFile(ofstream& ofs) const = 0;

    // Getters
    string         getId()             const { return evidenceId; }
    string         getCaseId()         const { return linkedCaseId; }
    string         getCollectedBy()    const { return collectedBy; }
    EvidenceStatus getStatus()         const { return status; }
    double         getRelevanceScore() const { return relevanceScore; }

    void   updateStatus(EvidenceStatus newStatus);
    string statusToString() const;

    bool operator==(const Evidence& other) const;
    bool operator<(const Evidence& other)  const;
    friend ostream& operator<<(ostream& os, const Evidence& e);
};

#endif
