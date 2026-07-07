#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <iostream>
#include <string>
#include <limits>
#include "CaseManager.h"
#include "EvidenceVault.h"
using namespace std;

class ConsoleUI {
private:
    CaseManager& caseManager;
    EvidenceVault& vault;
    bool           running;

    // Helpers
    void clearScreen()    const;
    void printBanner()    const;
    void printDivider()   const;
    void pause()          const;
    int    getIntInput(const string& prompt, int mn, int mx) const;
    string getStringInput(const string& prompt)                 const;
    bool   confirm(const string& message)               const;

    // Menus
    void mainMenu();
    void caseMenu();
    void personMenu();
    void evidenceMenu();
    void searchMenu();
    void reportsMenu();

    // Case actions
    void fileNewCase();
    void viewActiveCases();
    void viewCaseDetail();
    void closeACase();
    void addTimelineEvent();

    // Person actions
    void registerMissingPerson();
    void registerWitness();
    void registerSuspect();
    void viewPersonDetail();

    // Evidence actions
    void addDigitalEvidence();
    void addSocialMediaTrace();
    void addPhysicalEvidence();
    void viewEvidenceForCase();
    void viewCustodyChain();

    // Search
    void searchByName();
    void searchByOfficer();
    void searchByPriority();

    // Reports
    void generateCaseReport();
    void viewDashboard();

public:
    ConsoleUI(CaseManager& cm, EvidenceVault& ev);
    void run();
};

#endif