#ifndef CLOSEDCASE_H
#define CLOSEDCASE_H

#include "Case.h"

enum class ClosureReason {
    FOUND_SAFE, FOUND_DECEASED,
    CASE_WITHDRAWN, JURISDICTION_TRANSFER, OTHER
};

class ClosedCase : public Case {
private:
    DateTime      closedDate;
    ClosureReason closureReason;
    string        closureNotes;
    string        closedByOfficer;
    int           totalDaysOpen;

    string closureReasonToString() const;

public:
    ClosedCase(const string& id, const string& title,
        const string& officer, const string& missingPersonId,
        ClosureReason reason, const string& notes);

    // Convert ActiveCase to ClosedCase
    ClosedCase(const Case& activeCase, ClosureReason reason,
        const string& notes, const string& closingOfficer);

    ClosedCase(const ClosedCase& other);
    ~ClosedCase() override;

    void   displaySummary()          const override;
    string getCaseType()             const override { return "Closed Case"; }
    void   generateReport()          const override;
    void   saveToFile(ofstream& ofs) const override;

    ClosureReason getClosureReason() const { return closureReason; }
    string        getClosureNotes()  const { return closureNotes; }
    DateTime      getClosedDate()    const { return closedDate; }
    int           getTotalDaysOpen() const { return totalDaysOpen; }
};

#endif
