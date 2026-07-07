#include "Evidence.h"
using namespace std;

Evidence::Evidence(const string& id, const string& caseId,
    const string& collected, const string& desc)
    : evidenceId(id), linkedCaseId(caseId), collectedBy(collected),
    collectionDate(DateTime::now()), status(EvidenceStatus::COLLECTED),
    description(desc), relevanceScore(0.0) {
}

Evidence::Evidence(const Evidence& other)
    : evidenceId(other.evidenceId), linkedCaseId(other.linkedCaseId),
    collectedBy(other.collectedBy), collectionDate(other.collectionDate),
    status(other.status), description(other.description),
    relevanceScore(other.relevanceScore) {
}

Evidence& Evidence::operator=(const Evidence& other) {
    if (this != &other) {
        this->evidenceId = other.evidenceId;
        this->linkedCaseId = other.linkedCaseId;
        this->collectedBy = other.collectedBy;
        this->collectionDate = other.collectionDate;
        this->status = other.status;
        this->description = other.description;
        this->relevanceScore = other.relevanceScore;
    }
    return *this;
}

Evidence::~Evidence() {}

void Evidence::updateStatus(EvidenceStatus newStatus) {
    status = newStatus;
}

string Evidence::statusToString() const {
    switch (status) {
    case EvidenceStatus::COLLECTED:      return "COLLECTED";
    case EvidenceStatus::UNDER_ANALYSIS: return "UNDER ANALYSIS";
    case EvidenceStatus::VERIFIED:       return "VERIFIED";
    case EvidenceStatus::DISCARDED:      return "DISCARDED";
    default:                             return "UNKNOWN";
    }
}

bool Evidence::operator==(const Evidence& other) const {
    return evidenceId == other.evidenceId;
}

bool Evidence::operator<(const Evidence& other) const {
    return relevanceScore > other.relevanceScore;
}

ostream& operator<<(ostream& os, const Evidence& e) {
    os << "[" << e.getEvidenceType() << "] ID: " << e.evidenceId
        << " | Case: " << e.linkedCaseId
        << " | Score: " << e.relevanceScore;
    return os;
}