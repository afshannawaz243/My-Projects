#include "Witness.h"
#include <iostream>
#include <fstream>
using namespace std;

Witness::Witness(const string& id, const string& nm, int a,
    const string& g, const string& nat,
    const string& phone, const string& addr,
    const string& stmt, const string& caseId, bool anon)
    : Person(id, nm, a, g, nat, phone, addr),
    statement(stmt), reliability(WitnessReliability::MEDIUM),
    statementDate(DateTime::now()), linkedCaseId(caseId),
    isAnonymous(anon), credibilityScore(5.0) {
}

Witness::Witness(const Witness& other)
    : Person(other),
    statement(other.statement),
    reliability(other.reliability),
    statementDate(other.statementDate),
    linkedCaseId(other.linkedCaseId),
    isAnonymous(other.isAnonymous),
    credibilityScore(other.credibilityScore) {
}

Witness::~Witness() {}

void Witness::displayInfo() const {
    cout << "\n========================================\n";
    cout << "           WITNESS RECORD\n";
    cout << "========================================\n";
    cout << " ID          : " << personId << "\n";
    cout << " Name        : " << (isAnonymous ? "[ANONYMOUS]" : name) << "\n";
    cout << " Age         : " << age << "\n";
    cout << " Case ID     : " << linkedCaseId << "\n";
    cout << " Reliability : " << reliabilityToString() << "\n";
    cout << " Credibility : " << credibilityScore << "/10" << "\n";
    cout << " Statement   : " << getStatement() << "\n";
    cout << " Date        : " << statementDate << "\n";
    cout << "========================================\n";
}

string Witness::reliabilityToString() const {
    switch (reliability) {
    case WitnessReliability::LOW:      return "LOW";
    case WitnessReliability::MEDIUM:   return "MEDIUM";
    case WitnessReliability::HIGH:     return "HIGH";
    case WitnessReliability::VERIFIED: return "VERIFIED";
    default:                           return "UNKNOWN";
    }
}

void Witness::updateStatement(const string& newStatement) {
    if (newStatement.empty())
        throw InvalidInputException("statement cannot be empty");
    statement = newStatement;
    statementDate = DateTime::now();
}

void Witness::setReliability(WitnessReliability r) {
    reliability = r;
    switch (r) {
    case WitnessReliability::LOW:      credibilityScore = 2.0;  break;
    case WitnessReliability::MEDIUM:   credibilityScore = 5.0;  break;
    case WitnessReliability::HIGH:     credibilityScore = 8.0;  break;
    case WitnessReliability::VERIFIED: credibilityScore = 10.0; break;
    }
}

void Witness::setCredibilityScore(double score) {
    if (score < 0.0 || score > 10.0)
        throw InvalidInputException("credibility score must be 0-10");
    credibilityScore = score;
}

void Witness::saveToFile(ofstream& ofs) const {
    ofs << "WITNESS\n";
    ofs << personId << "\n";
    ofs << name << "\n";
    ofs << age << "\n";
    ofs << gender << "\n";
    ofs << nationality << "\n";
    ofs << contactPhone << "\n";
    ofs << address << "\n";
    ofs << statement << "\n";
    ofs << linkedCaseId << "\n";
    ofs << isAnonymous << "\n";
    ofs << credibilityScore << "\n";
    ofs << (int)reliability << "\n";
}