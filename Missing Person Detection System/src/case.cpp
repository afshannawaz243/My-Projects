#include "Case.h"
using namespace std;

Case::Case(const string& id, const string& t, const string& officer,
    const string& personId, CasePriority p)
    : caseId(id), title(t), assignedOfficer(officer),
    openedDate(DateTime::now()), priority(p),
    missingPersonId(personId) {
}

Case::Case(const Case& other)
    : caseId(other.caseId), title(other.title),
    assignedOfficer(other.assignedOfficer),
    openedDate(other.openedDate), priority(other.priority),
    missingPersonId(other.missingPersonId),
    evidenceIds(other.evidenceIds),
    suspectIds(other.suspectIds),
    witnessIds(other.witnessIds),
    description(other.description) {
}

Case& Case::operator=(const Case& other) {
    if (this != &other) {
        this->caseId = other.caseId;
        this->title = other.title;
        this->assignedOfficer = other.assignedOfficer;
        this->openedDate = other.openedDate;
        this->priority = other.priority;
        this->missingPersonId = other.missingPersonId;
        this->evidenceIds = other.evidenceIds;
        this->suspectIds = other.suspectIds;
        this->witnessIds = other.witnessIds;
        this->description = other.description;
    }
    return *this;
}

Case::~Case() {}

void Case::addEvidence(const string& evidenceId) {
    if (!hasEvidence(evidenceId))
        evidenceIds.push_back(evidenceId);
}

void Case::addSuspect(const string& suspectId) {
    suspectIds.push_back(suspectId);
}

void Case::addWitness(const string& witnessId) {
    witnessIds.push_back(witnessId);
}

bool Case::hasEvidence(const string& evidenceId) const {
    return find(evidenceIds.begin(), evidenceIds.end(), evidenceId) != evidenceIds.end();
}

string Case::priorityToString() const {
    switch (priority) {
    case CasePriority::LOW:      return "LOW";
    case CasePriority::MEDIUM:   return "MEDIUM";
    case CasePriority::HIGH:     return "HIGH";
    case CasePriority::CRITICAL: return "CRITICAL";
    default:                     return "UNKNOWN";
    }
}

bool Case::operator==(const Case& other) const {
    return caseId == other.caseId;
}

bool Case::operator<(const Case& other) const {
    return (int)priority > (int)other.priority;
}

ostream& operator<<(ostream& os, const Case& c) {
    os << "[" << c.getCaseType() << "] " << c.caseId
        << " | " << c.title
        << " | Priority: " << c.priorityToString()
        << " | Officer: " << c.assignedOfficer;
    return os;
}