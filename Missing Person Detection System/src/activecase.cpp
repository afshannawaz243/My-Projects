#include "ActiveCase.h"
#include <iostream>
#include <fstream>
using namespace std;

ActiveCase::ActiveCase(const string& id, const string& t,
    const string& officer, const string& personId,
    CasePriority p)
    : Case(id, t, officer, personId, p),
    lastUpdated(DateTime::now()),
    currentLeads(""), mediaAlert(false), daysMissing(0) {
}

ActiveCase::ActiveCase(const ActiveCase& other)
    : Case(other),
    timeline(other.timeline),
    lastUpdated(other.lastUpdated),
    currentLeads(other.currentLeads),
    mediaAlert(other.mediaAlert),
    daysMissing(other.daysMissing) {
}

ActiveCase::~ActiveCase() {}

void ActiveCase::addTimelineEvent(const string& type,
    const string& desc,
    const string& addedBy) {
    TimelineEvent evt;
    evt.timestamp = DateTime::now();
    evt.eventType = type;
    evt.description = desc;
    evt.addedBy = addedBy;
    timeline.push_back(evt);
    lastUpdated = DateTime::now();
}

void ActiveCase::setMediaAlert(bool active) { mediaAlert = active; }
void ActiveCase::setCurrentLeads(const string& leads) { currentLeads = leads; }

void ActiveCase::displaySummary() const {
    cout << "\n========================================\n";
    cout << "         ACTIVE CASE SUMMARY\n";
    cout << "========================================\n";
    cout << " Case ID     : " << caseId << "\n";
    cout << " Title       : " << title << "\n";
    cout << " Officer     : " << assignedOfficer << "\n";
    cout << " Priority    : " << priorityToString() << "\n";
    cout << " Opened      : " << openedDate << "\n";
    cout << " Last Updated: " << lastUpdated << "\n";
    cout << " Missing ID  : " << missingPersonId << "\n";
    cout << " Evidence    : " << evidenceIds.size() << " items\n";
    cout << " Suspects    : " << suspectIds.size() << "\n";
    cout << " Witnesses   : " << witnessIds.size() << "\n";
    cout << " Media Alert : " << (mediaAlert ? "ACTIVE" : "None") << "\n";
    if (!currentLeads.empty())
        cout << " Current Lead: " << currentLeads << "\n";
    cout << " Timeline    : " << timeline.size() << " events\n";
    cout << "========================================\n";
}

void ActiveCase::displayTimeline() const {
    cout << "\n========================================\n";
    cout << "       INVESTIGATION TIMELINE\n";
    cout << "========================================\n";
    if (timeline.empty()) {
        cout << "  No events recorded yet.\n";
    }
    else {
        for (const auto& e : timeline) {
            cout << " [" << e.timestamp << "] " << e.eventType << "\n";
            cout << "   " << e.description << "\n";
            cout << "   By: " << e.addedBy << "\n";
            cout << "----------------------------------------\n";
        }
    }
    cout << "========================================\n";
}

void ActiveCase::generateReport() const {
    cout << "\n====== CASE REPORT: " << caseId << " ======\n";
    displaySummary();
    displayTimeline();
}

void ActiveCase::saveToFile(ofstream& ofs) const {
    ofs << "ACTIVE_CASE\n";
    ofs << caseId << "\n" << title << "\n"
        << assignedOfficer << "\n" << missingPersonId << "\n"
        << (int)priority << "\n" << currentLeads << "\n"
        << mediaAlert << "\n" << daysMissing << "\n";
    ofs << evidenceIds.size() << "\n";
    for (const auto& e : evidenceIds) ofs << e << "\n";
    ofs << suspectIds.size() << "\n";
    for (const auto& s : suspectIds)  ofs << s << "\n";
    ofs << witnessIds.size() << "\n";
    for (const auto& w : witnessIds)  ofs << w << "\n";
    ofs << timeline.size() << "\n";
    for (const auto& t : timeline) {
        ofs << t.eventType << "\n"
            << t.description << "\n"
            << t.addedBy << "\n";
    }
}