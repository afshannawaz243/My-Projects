#include "ClosedCase.h"
#include <iostream>
#include <fstream>
using namespace std;

ClosedCase::ClosedCase(const string& id, const string& t,
    const string& officer, const string& personId,
    ClosureReason reason, const string& notes)
    : Case(id, t, officer, personId),
    closedDate(DateTime::now()), closureReason(reason),
    closureNotes(notes), closedByOfficer(officer),
    totalDaysOpen(0) {
}

ClosedCase::ClosedCase(const Case& ac, ClosureReason reason,
    const string& notes, const string& closingOfficer)
    : Case(ac),
    closedDate(DateTime::now()), closureReason(reason),
    closureNotes(notes), closedByOfficer(closingOfficer),
    totalDaysOpen(0) {
}

ClosedCase::ClosedCase(const ClosedCase& other)
    : Case(other),
    closedDate(other.closedDate),
    closureReason(other.closureReason),
    closureNotes(other.closureNotes),
    closedByOfficer(other.closedByOfficer),
    totalDaysOpen(other.totalDaysOpen) {
}

ClosedCase::~ClosedCase() {}

string ClosedCase::closureReasonToString() const {
    switch (closureReason) {
    case ClosureReason::FOUND_SAFE:            return "FOUND SAFE";
    case ClosureReason::FOUND_DECEASED:        return "FOUND DECEASED";
    case ClosureReason::CASE_WITHDRAWN:        return "CASE WITHDRAWN";
    case ClosureReason::JURISDICTION_TRANSFER: return "JURISDICTION TRANSFER";
    case ClosureReason::OTHER:                 return "OTHER";
    default:                                   return "UNKNOWN";
    }
}

void ClosedCase::displaySummary() const {
    cout << "\n========================================\n";
    cout << "         CLOSED CASE SUMMARY\n";
    cout << "========================================\n";
    cout << " Case ID       : " << caseId << "\n";
    cout << " Title         : " << title << "\n";
    cout << " Opened By     : " << assignedOfficer << "\n";
    cout << " Closed By     : " << closedByOfficer << "\n";
    cout << " Opened        : " << openedDate << "\n";
    cout << " Closed        : " << closedDate << "\n";
    cout << " Days Open     : " << totalDaysOpen << "\n";
    cout << " Closure Reason: " << closureReasonToString() << "\n";
    cout << " Evidence Items: " << evidenceIds.size() << "\n";
    cout << " Notes         : " << closureNotes << "\n";
    cout << "========================================\n";
}

void ClosedCase::generateReport() const {
    cout << "\n====== CLOSED CASE REPORT: " << caseId << " ======\n";
    displaySummary();
}

void ClosedCase::saveToFile(ofstream& ofs) const {
    ofs << "CLOSED_CASE\n";
    ofs << caseId << "\n" << title << "\n"
        << assignedOfficer << "\n" << missingPersonId << "\n"
        << (int)priority << "\n" << closedByOfficer << "\n"
        << (int)closureReason << "\n" << closureNotes << "\n"
        << totalDaysOpen << "\n";
    ofs << evidenceIds.size() << "\n";
    for (const auto& e : evidenceIds) ofs << e << "\n";
}