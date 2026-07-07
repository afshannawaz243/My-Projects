#ifndef WITNESS_H
#define WITNESS_H

#include "Person.h"

enum class WitnessReliability { LOW, MEDIUM, HIGH, VERIFIED };

class Witness : public Person {
private:
    string             statement;
    WitnessReliability reliability;
    DateTime           statementDate;
    string             linkedCaseId;
    bool               isAnonymous;
    double             credibilityScore;

public:
    Witness(const string& id, const string& name, int age,
        const string& gender, const string& nationality,
        const string& phone, const string& address,
        const string& statement, const string& caseId,
        bool anonymous = false);

    Witness(const Witness& other);
    ~Witness() override;

    // Overrides
    void   displayInfo()             const override;
    string getRole()                 const override { return "Witness"; }
    double getRiskScore()            const override { return credibilityScore; }
    void   saveToFile(ofstream& ofs) const override;

    // Specific methods
    void   updateStatement(const string& newStatement);
    void   setReliability(WitnessReliability r);
    void   setCredibilityScore(double score);
    string reliabilityToString() const;

    // Getters
    string getStatement()  const { return isAnonymous ? "[ANONYMOUS]" : statement; }
    string getLinkedCase() const { return linkedCaseId; }
    bool   getIsAnonymous()const { return isAnonymous; }
};

#endif
