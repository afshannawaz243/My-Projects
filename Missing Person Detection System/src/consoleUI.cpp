#include "ConsoleUI.h"
using namespace std;

ConsoleUI::ConsoleUI(CaseManager& cm, EvidenceVault& ev)
    : caseManager(cm), vault(ev), running(true) {
}

void ConsoleUI::clearScreen() const {
    system("cls");
}

void ConsoleUI::printDivider() const {
    cout << "  ========================================\n";
}

void ConsoleUI::printBanner() const {
    clearScreen();
    cout << "  ============================================\n";
    cout << "    MISSING PERSON INVESTIGATION SYSTEM      \n";
    cout << "       Digital Forensics & Evidence          \n";
    cout << "  ============================================\n";
}

void ConsoleUI::pause() const {
    cout << "\n  Press ENTER to continue...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

int ConsoleUI::getIntInput(const string& prompt, int mn, int mx) const {
    int val;
    while (true) {
        cout << "  " << prompt << " ";
        if (cin >> val && val >= mn && val <= mx) {
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << "  Invalid! Enter a number between "
            << mn << " and " << mx << ".\n";
    }
}

string ConsoleUI::getStringInput(const string& prompt) const {
    string val;
    cout << "  " << prompt << " ";
    getline(cin, val);
    return val;
}

bool ConsoleUI::confirm(const string& msg) const {
    cout << "  " << msg << " (y/n): ";
    char c;
    cin >> c;
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    return (c == 'y' || c == 'Y');
}

// ============================================================
//  MAIN MENU
// ============================================================
void ConsoleUI::run() {
    while (running) mainMenu();
    cout << "\n  Saving data...\n";
    try {
        caseManager.saveAll();
        vault.saveAll();
        cout << "  Saved. Goodbye!\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Save failed: " << e.what() << "\n";
    }
}

void ConsoleUI::mainMenu() {
    printBanner();
    caseManager.displayStats();
    cout << "\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |           MAIN MENU               |\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |  [1]  Case Management             |\n";
    cout << "  |  [2]  Person Registry             |\n";
    cout << "  |  [3]  Evidence Vault              |\n";
    cout << "  |  [4]  Search                      |\n";
    cout << "  |  [5]  Reports & Timeline          |\n";
    cout << "  |  [0]  Exit                        |\n";
    cout << "  +-----------------------------------+\n";
    int choice = getIntInput("Select option:", 0, 5);
    switch (choice) {
    case 1: caseMenu();     break;
    case 2: personMenu();   break;
    case 3: evidenceMenu(); break;
    case 4: searchMenu();   break;
    case 5: reportsMenu();  break;
    case 0: running = false; break;
    }
}

// ============================================================
//  CASE MENU
// ============================================================
void ConsoleUI::caseMenu() {
    printBanner();
    cout << "\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |        CASE MANAGEMENT            |\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |  [1]  File New Case               |\n";
    cout << "  |  [2]  View All Active Cases       |\n";
    cout << "  |  [3]  View Case Detail            |\n";
    cout << "  |  [4]  Close a Case                |\n";
    cout << "  |  [5]  Add Timeline Event          |\n";
    cout << "  |  [6]  View Closed Cases           |\n";
    cout << "  |  [0]  Back                        |\n";
    cout << "  +-----------------------------------+\n";
    int choice = getIntInput("Select option:", 0, 6);
    switch (choice) {
    case 1: fileNewCase();      break;
    case 2: viewActiveCases();  break;
    case 3: viewCaseDetail();   break;
    case 4: closeACase();       break;
    case 5: addTimelineEvent(); break;
    case 6:
        printBanner();
        cout << "\n  --- CLOSED CASES ---\n";
        caseManager.displayAllClosed();
        pause();
        break;
    case 0: break;
    }
}

void ConsoleUI::fileNewCase() {
    printBanner();
    cout << "\n  --- FILE NEW CASE ---\n";
    printDivider();
    string title = getStringInput("Case Title:");
    string officer = getStringInput("Assigned Officer:");
    string personId = getStringInput("Missing Person ID (leave blank if none):");
    cout << "  Priority: [1] Low  [2] Medium  [3] High  [4] Critical\n";
    int pri = getIntInput("Priority:", 1, 4);
    try {
        string id = caseManager.addActiveCase(
            title, officer, personId, (CasePriority)(pri - 1));
        cout << "\n  Case filed! Case ID: " << id << "\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::viewActiveCases() {
    printBanner();
    cout << "\n  --- ACTIVE CASES ---\n";
    printDivider();
    caseManager.sortActiveCasesByPriority();
    caseManager.displayAllActive();
    pause();
}

void ConsoleUI::viewCaseDetail() {
    printBanner();
    string id = getStringInput("Enter Case ID:");
    try {
        ActiveCase* c = caseManager.getActiveCase(id);
        c->displaySummary();
        c->displayTimeline();
        double score = vault.getCaseEvidenceScore(id);
        cout << "\n  Overall Evidence Score: " << score << "/10\n";
    }
    catch (const ForensicsException& e) {
        cout << "  " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::closeACase() {
    printBanner();
    cout << "\n  --- CLOSE A CASE ---\n";
    printDivider();
    string id = getStringInput("Enter Case ID to close:");
    cout << "  Reason:\n";
    cout << "  [1] Found Safe\n";
    cout << "  [2] Found Deceased\n";
    cout << "  [3] Case Withdrawn\n";
    cout << "  [4] Jurisdiction Transfer\n";
    cout << "  [5] Other\n";
    int r = getIntInput("Reason:", 1, 5);
    string notes = getStringInput("Closure Notes:");
    string officer = getStringInput("Closing Officer:");
    if (!confirm("Confirm case closure?")) { pause(); return; }
    try {
        caseManager.closeCase(id, (ClosureReason)(r - 1), notes, officer);
        cout << "\n  Case closed successfully.\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::addTimelineEvent() {
    printBanner();
    string caseId = getStringInput("Enter Case ID:");
    try {
        ActiveCase* c = caseManager.getActiveCase(caseId);
        string type = getStringInput("Event Type (e.g. Suspect Identified):");
        string desc = getStringInput("Description:");
        string officer = getStringInput("Your Name:");
        c->addTimelineEvent(type, desc, officer);
        cout << "\n  Event added to timeline.\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

// ============================================================
//  PERSON MENU
// ============================================================
void ConsoleUI::personMenu() {
    printBanner();
    cout << "\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |        PERSON REGISTRY            |\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |  [1]  Register Missing Person     |\n";
    cout << "  |  [2]  Register Witness            |\n";
    cout << "  |  [3]  Register Suspect            |\n";
    cout << "  |  [4]  View Person Detail          |\n";
    cout << "  |  [0]  Back                        |\n";
    cout << "  +-----------------------------------+\n";
    int choice = getIntInput("Select option:", 0, 4);
    switch (choice) {
    case 1: registerMissingPerson(); break;
    case 2: registerWitness();       break;
    case 3: registerSuspect();       break;
    case 4: viewPersonDetail();      break;
    case 0: break;
    }
}

void ConsoleUI::registerMissingPerson() {
    printBanner();
    cout << "\n  --- REGISTER MISSING PERSON ---\n";
    printDivider();
    string name = getStringInput("Full Name:");
    int    age = getIntInput("Age:", 0, 130);
    string gender = getStringInput("Gender:");
    string nat = getStringInput("Nationality:");
    string phone = getStringInput("Contact Phone:");
    string addr = getStringInput("Home Address:");
    string lastLoc = getStringInput("Last Seen Location:");
    string desc = getStringInput("Physical Description:");
    try {
        string id = caseManager.addMissingPerson(
            name, age, gender, nat, phone, addr,
            lastLoc, DateTime::now(), desc);
        cout << "\n  Registered! Person ID: " << id << "\n";
        cout << "  Use this ID when filing a case.\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::registerWitness() {
    printBanner();
    cout << "\n  --- REGISTER WITNESS ---\n";
    printDivider();
    string name = getStringInput("Full Name:");
    int    age = getIntInput("Age:", 0, 130);
    string gender = getStringInput("Gender:");
    string nat = getStringInput("Nationality:");
    string phone = getStringInput("Phone:");
    string addr = getStringInput("Address:");
    string stmt = getStringInput("Witness Statement:");
    string caseId = getStringInput("Linked Case ID:");
    bool   anon = confirm("Register as anonymous?");
    try {
        string id = caseManager.addWitness(
            name, age, gender, nat, phone,
            addr, stmt, caseId, anon);
        try {
            ActiveCase* c = caseManager.getActiveCase(caseId);
            c->addWitness(id);
            c->addTimelineEvent("Witness Registered",
                "New witness added", "SYSTEM");
        }
        catch (...) {}
        cout << "\n  Witness registered! ID: " << id << "\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::registerSuspect() {
    printBanner();
    cout << "\n  --- REGISTER SUSPECT ---\n";
    printDivider();
    string name = getStringInput("Full Name:");
    int    age = getIntInput("Age:", 0, 130);
    string gender = getStringInput("Gender:");
    string nat = getStringInput("Nationality:");
    string phone = getStringInput("Phone:");
    string addr = getStringInput("Address:");
    string caseId = getStringInput("Linked Case ID:");
    cout << "  Threat: [1] Low  [2] Moderate  [3] High  [4] Critical\n";
    int tl = getIntInput("Threat Level:", 1, 4);
    try {
        string id = caseManager.addSuspect(
            name, age, gender, nat, phone, addr,
            caseId, (ThreatLevel)(tl - 1));
        try {
            ActiveCase* c = caseManager.getActiveCase(caseId);
            c->addSuspect(id);
            c->addTimelineEvent("Suspect Identified",
                "New suspect: " + name, "SYSTEM");
        }
        catch (...) {}
        cout << "\n  Suspect registered! ID: " << id << "\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::viewPersonDetail() {
    printBanner();
    cout << "  Type: [1] Missing Person  [2] Witness  [3] Suspect\n";
    int    type = getIntInput("Type:", 1, 3);
    string id = getStringInput("Enter Person ID:");
    try {
        if (type == 1) caseManager.getMissingPerson(id)->displayInfo();
        else if (type == 2) caseManager.getWitness(id)->displayInfo();
        else                caseManager.getSuspect(id)->displayInfo();
    }
    catch (const ForensicsException& e) {
        cout << "  " << e.what() << "\n";
    }
    pause();
}

// ============================================================
//  EVIDENCE MENU
// ============================================================
void ConsoleUI::evidenceMenu() {
    printBanner();
    cout << "\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |         EVIDENCE VAULT            |\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |  [1]  Add Digital Evidence        |\n";
    cout << "  |  [2]  Add Social Media Trace      |\n";
    cout << "  |  [3]  Add Physical Evidence       |\n";
    cout << "  |  [4]  View Evidence for Case      |\n";
    cout << "  |  [5]  View Chain of Custody       |\n";
    cout << "  |  [6]  Analyze All for Case        |\n";
    cout << "  |  [0]  Back                        |\n";
    cout << "  +-----------------------------------+\n";
    int choice = getIntInput("Select option:", 0, 6);
    switch (choice) {
    case 1: addDigitalEvidence();  break;
    case 2: addSocialMediaTrace(); break;
    case 3: addPhysicalEvidence(); break;
    case 4: viewEvidenceForCase(); break;
    case 5: viewCustodyChain();    break;
    case 6: {
        string cid = getStringInput("Case ID:");
        vault.analyzeAllForCase(cid);
        pause();
        break;
    }
    case 0: break;
    }
}

void ConsoleUI::addDigitalEvidence() {
    printBanner();
    cout << "\n  --- ADD DIGITAL EVIDENCE ---\n";
    printDivider();
    string caseId = getStringInput("Case ID:");
    string officer = getStringInput("Collected By:");
    string desc = getStringInput("Description:");
    string model = getStringInput("Device Model:");
    string serial = getStringInput("Serial Number:");
    cout << "  Device:\n";
    cout << "  [1] Smartphone  [2] Laptop  [3] Tablet\n";
    cout << "  [4] CCTV        [5] Server  [6] USB  [7] Other\n";
    int dt = getIntInput("Device Type:", 1, 7);
    try {
        string id = vault.addDigitalEvidence(
            caseId, officer, desc,
            (DeviceType)(dt - 1), model, serial);
        try {
            ActiveCase* c = caseManager.getActiveCase(caseId);
            c->addEvidence(id);
            c->addTimelineEvent("Digital Evidence Added", desc, officer);
        }
        catch (...) {}
        cout << "\n  Evidence logged! ID: " << id << "\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::addSocialMediaTrace() {
    printBanner();
    cout << "\n  --- ADD SOCIAL MEDIA TRACE ---\n";
    printDivider();
    string caseId = getStringInput("Case ID:");
    string officer = getStringInput("Collected By:");
    string desc = getStringInput("Description:");
    string uname = getStringInput("Username/Handle:");
    string url = getStringInput("Profile URL:");
    cout << "  Platform:\n";
    cout << "  [1] Facebook  [2] Instagram  [3] Twitter\n";
    cout << "  [4] WhatsApp  [5] TikTok     [6] Snapchat  [7] Other\n";
    int pl = getIntInput("Platform:", 1, 7);
    try {
        string id = vault.addSocialMediaTrace(
            caseId, officer, desc,
            (Platform)(pl - 1), uname, url);
        try {
            ActiveCase* c = caseManager.getActiveCase(caseId);
            c->addEvidence(id);
            c->addTimelineEvent("Social Media Trace Added",
                "Account: " + uname, officer);
        }
        catch (...) {}
        cout << "\n  Trace logged! ID: " << id << "\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::addPhysicalEvidence() {
    printBanner();
    cout << "\n  --- ADD PHYSICAL EVIDENCE ---\n";
    printDivider();
    string caseId = getStringInput("Case ID:");
    string officer = getStringInput("Collected By:");
    string desc = getStringInput("Description:");
    string location = getStringInput("Found At Location:");
    string itemType = getStringInput("Item Type (e.g. clothing, ID card):");
    cout << "  Condition:\n";
    cout << "  [1] Pristine  [2] Good  [3] Damaged  [4] Degraded\n";
    int cond = getIntInput("Condition:", 1, 4);
    try {
        string id = vault.addPhysicalEvidence(
            caseId, officer, desc, location,
            itemType, (Condition)(cond - 1));
        try {
            ActiveCase* c = caseManager.getActiveCase(caseId);
            c->addEvidence(id);
            c->addTimelineEvent("Physical Evidence Added",
                itemType + " found at " + location, officer);
        }
        catch (...) {}
        cout << "\n  Evidence logged! ID: " << id << "\n";
    }
    catch (const ForensicsException& e) {
        cout << "  Error: " << e.what() << "\n";
    }
    pause();
}

void ConsoleUI::viewEvidenceForCase() {
    printBanner();
    string caseId = getStringInput("Enter Case ID:");
    vault.displayEvidenceForCase(caseId);
    pause();
}

void ConsoleUI::viewCustodyChain() {
    printBanner();
    string evidenceId = getStringInput("Enter Evidence ID:");
    vault.displayCustodyChain(evidenceId);
    pause();
}

// ============================================================
//  SEARCH MENU
// ============================================================
void ConsoleUI::searchMenu() {
    printBanner();
    cout << "\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |            SEARCH                 |\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |  [1]  Search Person by Name       |\n";
    cout << "  |  [2]  Search Cases by Officer     |\n";
    cout << "  |  [3]  Search Cases by Priority    |\n";
    cout << "  |  [0]  Back                        |\n";
    cout << "  +-----------------------------------+\n";
    int choice = getIntInput("Select option:", 0, 3);
    switch (choice) {
    case 1: searchByName();     break;
    case 2: searchByOfficer();  break;
    case 3: searchByPriority(); break;
    case 0: break;
    }
}

void ConsoleUI::searchByName() {
    printBanner();
    string name = getStringInput("Enter name to search:");
    auto results = caseManager.searchPersonByName(name);
    cout << "\n  Found " << results.size() << " result(s):\n";
    for (auto* p : results) p->displayInfo();
    pause();
}

void ConsoleUI::searchByOfficer() {
    printBanner();
    string officer = getStringInput("Enter officer name:");
    auto results = caseManager.searchCasesByOfficer(officer);
    cout << "\n  Found " << results.size() << " case(s):\n";
    for (auto* c : results) c->displaySummary();
    pause();
}

void ConsoleUI::searchByPriority() {
    printBanner();
    cout << "  Priority: [1] Low  [2] Medium  [3] High  [4] Critical\n";
    int pri = getIntInput("Priority:", 1, 4);
    auto results = caseManager.searchCasesByPriority((CasePriority)(pri - 1));
    cout << "\n  Found " << results.size() << " case(s):\n";
    for (auto* c : results) c->displaySummary();
    pause();
}

// ============================================================
//  REPORTS MENU
// ============================================================
void ConsoleUI::reportsMenu() {
    printBanner();
    cout << "\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |      REPORTS & TIMELINE           |\n";
    cout << "  +-----------------------------------+\n";
    cout << "  |  [1]  Generate Case Report        |\n";
    cout << "  |  [2]  View System Dashboard       |\n";
    cout << "  |  [0]  Back                        |\n";
    cout << "  +-----------------------------------+\n";
    int choice = getIntInput("Select option:", 0, 2);
    switch (choice) {
    case 1: generateCaseReport(); break;
    case 2: viewDashboard();      break;
    case 0: break;
    }
}

void ConsoleUI::generateCaseReport() {
    printBanner();
    string caseId = getStringInput("Enter Case ID:");
    try {
        ActiveCase* c = caseManager.getActiveCase(caseId);
        c->generateReport();
        vault.displayEvidenceForCase(caseId);
    }
    catch (...) {
        try {
            ClosedCase* c = caseManager.getClosedCase(caseId);
            c->generateReport();
        }
        catch (const ForensicsException& e) {
            cout << "  " << e.what() << "\n";
        }
    }
    pause();
}

void ConsoleUI::viewDashboard() {
    printBanner();
    caseManager.displayStats();
    pause();
}