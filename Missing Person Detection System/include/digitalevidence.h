#ifndef DIGITALEVIDENCE_H
#define DIGITALEVIDENCE_H

#include "Evidence.h"

enum class DeviceType { SMARTPHONE, LAPTOP, TABLET, CCTV, SERVER, USB, OTHER };
enum class RecoveryStatus { INTACT, PARTIAL, CORRUPTED, ENCRYPTED };

class DigitalEvidence : public Evidence {
private:
    DeviceType     deviceType;
    RecoveryStatus recoveryStatus;
    string         deviceModel;
    string         serialNumber;
    string         md5Hash;
    string         extractedData;
    bool           isEncrypted;
    string         encryptionType;

    string deviceTypeToString()    const;
    string recoveryStatusToString()const;

public:
    DigitalEvidence(const string& id, const string& caseId,
        const string& collectedBy, const string& description,
        DeviceType device, const string& model,
        const string& serial);

    DigitalEvidence(const DigitalEvidence& other);
    ~DigitalEvidence() override;

    void   displayInfo()             const override;
    string getEvidenceType()         const override { return "Digital Evidence"; }
    double analyzeRelevance()              override;
    void   saveToFile(ofstream& ofs) const override;

    void setMd5Hash(const string& hash);
    void setExtractedData(const string& data);
    void setEncryption(bool encrypted, const string& type = "");
    void setRecoveryStatus(RecoveryStatus rs);

    bool           getIsEncrypted()    const { return isEncrypted; }
    string         getMd5Hash()        const { return md5Hash; }
    RecoveryStatus getRecoveryStatus() const { return recoveryStatus; }
    DeviceType     getDeviceType()     const { return deviceType; }
};

#endif
