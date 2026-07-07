#include <iostream>
#include "CaseManager.h"
#include "EvidenceVault.h"
#include "ConsoleUI.h"
using namespace std;

int main() {
    try {
        CaseManager   caseManager("data/");
        EvidenceVault vault("data/");

        caseManager.loadAll();
        vault.loadAll();

        ConsoleUI ui(caseManager, vault);
        ui.run();
    }
    catch (const ForensicsException& e) {
        cout << "\n[FATAL] " << e.what() << "\n";
        return 1;
    }
    catch (const exception& e) {
        cout << "\n[FATAL] " << e.what() << "\n";
        return 1;
    }
    return 0;
}