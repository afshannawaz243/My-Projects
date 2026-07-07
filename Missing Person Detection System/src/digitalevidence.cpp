#include "DigitalEvidence.h"
#include <iostream>
#include <fstream>
using namespace std;

DigitalEvidence::DigitalEvidence(const string& id, const string& caseId,
    const string& collected, const string& desc,
    DeviceType device, const string& model,
    const string& serial)
    : Evidence(id, caseId, collected, desc),
    deviceType(device), recoveryStatus(RecoveryStatus::INTACT),
    deviceModel(model), serialNumber(serial),
    md5Hash(""), extractedData(""),
    isEncrypted(false), encryptionType("") {
}

DigitalEvidence::DigitalEvidence(const DigitalEvidence& other)
    : Evidence(other),
    deviceType(other.deviceType),
    recoveryStatus(other.recoveryStatus),
    deviceModel(other.deviceModel),
    serialNumber(other.serialNumber),
    md5Hash(other.md5Hash),
    extractedData(other.extractedData),
    isEncrypted(other.isEncrypted),
    encryptionType(other.encryptionType) {
}

DigitalEvidence::~DigitalEvidence() {}

string DigitalEvidence::deviceTypeToString() const {
    switch (deviceType) {
    case DeviceType::SMARTPHONE: return "Smartphone";
    case DeviceType::LAPTOP:     return "Laptop";
    case DeviceType::TABLET:     return "Tablet";
    case DeviceType::CCTV:       return "CCTV";
    case DeviceType::SERVER:     return "Server";
    case DeviceType::USB:        return "USB Drive";
    case DeviceType::OTHER:      return "Other";
    default:                     return "Unknown";
    }
}

string DigitalEvidence::recoveryStatusToString() const {
    switch (recoveryStatus) {
    case RecoveryStatus::INTACT:    return "INTACT";
    case RecoveryStatus::PARTIAL:   return "PARTIAL";
    case RecoveryStatus::CORRUPTED: return "CORRUPTED";
    case RecoveryStatus::ENCRYPTED: return "ENCRYPTED";
    default:                        return "UNKNOWN";
    }
}

double DigitalEvidence::analyzeRelevance() {
    double score = 4.0;
    if (recoveryStatus == RecoveryStatus::INTACT)  score += 3.0;
    if (recoveryStatus == RecoveryStatus::PARTIAL) score += 1.5;
    if (!extractedData.empty())                    score += 2.0;
    if (isEncrypted)                               score -= 1.5;
    if (!md5Hash.empty())                          score += 0.5;
    if (score > 10.0) score = 10.0;
    if (score < 0.0)  score = 0.0;
    relevanceScore = score;
    return score;
}

void DigitalEvidence::displayInfo() const {
    cout << "\n========================================\n";
    cout << "         DIGITAL EVIDENCE\n";
    cout << "========================================\n";
    cout << " ID          : " << evidenceId << "\n";
    cout << " Case ID     : " << linkedCaseId << "\n";
    cout << " Device      : " << deviceTypeToString() << "\n";
    cout << " Model       : " << deviceModel << "\n";
    cout << " Serial      : " << serialNumber << "\n";
    cout << " Recovery    : " << recoveryStatusToString() << "\n";
    cout << " Encrypted   : " << (isEncrypted ? "YES (" + encryptionType + ")" : "NO") << "\n";
    cout << " MD5 Hash    : " << (md5Hash.empty() ? "Not computed" : md5Hash) << "\n";
    cout << " Status      : " << statusToString() << "\n";
    cout << " Collected By: " << collectedBy << "\n";
    cout << " Description : " << description << "\n";
    if (!extractedData.empty())
        cout << " Extracted   : " << extractedData << "\n";
    cout << " Relevance   : " << relevanceScore << "/10\n";
    cout << "========================================\n";
}

void DigitalEvidence::setMd5Hash(const string& hash) { md5Hash = hash; }
void DigitalEvidence::setExtractedData(const string& data) { extractedData = data; }
void DigitalEvidence::setRecoveryStatus(RecoveryStatus rs) { recoveryStatus = rs; }
void DigitalEvidence::setEncryption(bool enc, const string& type) {
    isEncrypted = enc;
    encryptionType = type;
}

void DigitalEvidence::saveToFile(ofstream& ofs) const {
    ofs << "DIGITAL_EVIDENCE\n";
    ofs << evidenceId << "\n" << linkedCaseId << "\n"
        << collectedBy << "\n" << description << "\n"
        << (int)deviceType << "\n" << deviceModel << "\n"
        << serialNumber << "\n" << md5Hash << "\n"
        << extractedData << "\n" << isEncrypted << "\n"
        << encryptionType << "\n" << (int)recoveryStatus << "\n"
        << (int)status << "\n" << relevanceScore << "\n";
}