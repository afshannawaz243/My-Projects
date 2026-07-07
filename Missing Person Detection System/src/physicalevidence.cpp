#include "PhysicalEvidence.h"
#include <iostream>
#include <fstream>
using namespace std;

PhysicalEvidence::PhysicalEvidence(const string& id, const string& caseId,
    const string& collected, const string& desc,
    const string& location, const string& type,
    Condition cond)
    : Evidence(id, caseId, collected, desc),
    foundLocation(location), condition(cond),
    forensicTag(""), itemType(type),
    sentToLab(false), labReport(""),
    foundDate(DateTime::now()) {
}

PhysicalEvidence::PhysicalEvidence(const PhysicalEvidence& other)
    : Evidence(other),
    foundLocation(other.foundLocation),
    condition(other.condition),
    forensicTag(other.forensicTag),
    itemType(other.itemType),
    sentToLab(other.sentToLab),
    labReport(other.labReport),
    foundDate(other.foundDate) {
}

PhysicalEvidence::~PhysicalEvidence() {}

string PhysicalEvidence::conditionToString() const {
    switch (condition) {
    case Condition::PRISTINE: return "PRISTINE";
    case Condition::GOOD:     return "GOOD";
    case Condition::DAMAGED:  return "DAMAGED";
    case Condition::DEGRADED: return "DEGRADED";
    default:                  return "UNKNOWN";
    }
}

double PhysicalEvidence::analyzeRelevance() {
    double score = 3.0;
    if (condition == Condition::PRISTINE) score += 3.5;
    if (condition == Condition::GOOD)     score += 2.0;
    if (condition == Condition::DAMAGED)  score += 1.0;
    if (sentToLab)                        score += 2.0;
    if (!labReport.empty())               score += 1.5;
    if (score > 10.0) score = 10.0;
    relevanceScore = score;
    return score;
}

void PhysicalEvidence::displayInfo() const {
    cout << "\n========================================\n";
    cout << "         PHYSICAL EVIDENCE\n";
    cout << "========================================\n";
    cout << " ID           : " << evidenceId << "\n";
    cout << " Case ID      : " << linkedCaseId << "\n";
    cout << " Item Type    : " << itemType << "\n";
    cout << " Found At     : " << foundLocation << "\n";
    cout << " Condition    : " << conditionToString() << "\n";
    cout << " Forensic Tag : " << (forensicTag.empty() ? "Not tagged" : forensicTag) << "\n";
    cout << " Sent to Lab  : " << (sentToLab ? "YES" : "NO") << "\n";
    cout << " Collected By : " << collectedBy << "\n";
    cout << " Date Found   : " << foundDate << "\n";
    cout << " Status       : " << statusToString() << "\n";
    if (!labReport.empty())
        cout << " Lab Report   : " << labReport << "\n";
    cout << " Relevance    : " << relevanceScore << "/10\n";
    cout << "========================================\n";
}

void PhysicalEvidence::setForensicTag(const string& tag) { forensicTag = tag; }
void PhysicalEvidence::setSentToLab(bool sent) { sentToLab = sent; }
void PhysicalEvidence::setLabReport(const string& report) { labReport = report; }

void PhysicalEvidence::saveToFile(ofstream& ofs) const {
    ofs << "PHYSICAL_EVIDENCE\n";
    ofs << evidenceId << "\n" << linkedCaseId << "\n"
        << collectedBy << "\n" << description << "\n"
        << foundLocation << "\n" << itemType << "\n"
        << (int)condition << "\n" << forensicTag << "\n"
        << sentToLab << "\n" << labReport << "\n"
        << (int)status << "\n" << relevanceScore << "\n";
}