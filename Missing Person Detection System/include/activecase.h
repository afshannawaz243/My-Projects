#ifndef ACTIVECASE_H
#define ACTIVECASE_H

#include "Case.h"

struct TimelineEvent {
    DateTime timestamp;
    string   eventType;
    string   description;
    string   addedBy;
};

class ActiveCase : public Case {
private:
    vector<TimelineEvent> timeline;
    DateTime              lastUpdated;
    string                currentLeads;
    bool                  mediaAlert;
    int                   daysMissing;

public:
    ActiveCase(const string& id, const string& title,
        const string& officer, const string& missingPersonId,
        CasePriority priority = CasePriority::HIGH);

    ActiveCase(const ActiveCase& other);
    ~ActiveCase() override;

    void   displaySummary()          const override;
    string getCaseType()             const override { return "Active Case"; }
    void   generateReport()          const override;
    void   saveToFile(ofstream& ofs) const override;

    void addTimelineEvent(const string& type,
        const string& desc,
        const string& addedBy);
    void setMediaAlert(bool active);
    void setCurrentLeads(const string& leads);
    void displayTimeline() const;

    vector<TimelineEvent> getTimeline()    const { return timeline; }
    bool                  getMediaAlert()  const { return mediaAlert; }
    int                   getDaysMissing() const { return daysMissing; }
};

#endif
