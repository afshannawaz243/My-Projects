#ifndef PHYSICALEVIDENCE_H
#define PHYSICALEVIDENCE_H

#include "Evidence.h"

enum class Condition { PRISTINE, GOOD, DAMAGED, DEGRADED };

class PhysicalEvidence : public Evidence {
private:
    string    foundLocation;
    Condition condition;
    string    forensicTag;
    string    itemType;
    bool      sentToLab;
    string    labReport;
    DateTime  foundDate;

    string conditionToString() const;

public:
    PhysicalEvidence(const string& id, const string& caseId,
        const string& collectedBy, const string& description,
        const string& foundLocation, const string& itemType,
        Condition condition);

    PhysicalEvidence(const PhysicalEvidence& other);
    ~PhysicalEvidence() override;

    void   displayInfo()             const override;
    string getEvidenceType()         const override { return "Physical Evidence"; }
    double analyzeRelevance()              override;
    void   saveToFile(ofstream& ofs) const override;

    void setForensicTag(const string& tag);
    void setSentToLab(bool sent);
    void setLabReport(const string& report);

    string    getFoundLocation() const { return foundLocation; }
    string    getForensicTag()   const { return forensicTag; }
    Condition getCondition()     const { return condition; }
    bool      getSentToLab()     const { return sentToLab; }
};

#endif
