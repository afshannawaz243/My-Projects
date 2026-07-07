#ifndef SOCIALMEDIATRACE_H
#define SOCIALMEDIATRACE_H

#include <vector>
#include "Evidence.h"

enum class Platform { FACEBOOK, INSTAGRAM, TWITTER, WHATSAPP, TIKTOK, SNAPCHAT, OTHER };

struct SocialPost {
    string   postId;
    string   content;
    string   location;
    DateTime timestamp;
    bool     isDeleted;
};

class SocialMediaTrace : public Evidence {
private:
    Platform           platform;
    string             username;
    string             profileUrl;
    string             ipAddress;
    string             deviceFingerprint;
    DateTime           lastActivityDate;
    vector<SocialPost> recoveredPosts;
    bool               accountActive;

    string platformToString() const;

public:
    SocialMediaTrace(const string& id, const string& caseId,
        const string& collectedBy, const string& description,
        Platform platform, const string& username,
        const string& profileUrl);

    SocialMediaTrace(const SocialMediaTrace& other);
    ~SocialMediaTrace() override;

    void   displayInfo()             const override;
    string getEvidenceType()         const override { return "Social Media Trace"; }
    double analyzeRelevance()              override;
    void   saveToFile(ofstream& ofs) const override;

    void addRecoveredPost(const SocialPost& post);
    void setIpAddress(const string& ip);
    void setDeviceFingerprint(const string& fp);
    void setLastActivity(const DateTime& dt);
    void setAccountActive(bool active);

    string             getUsername()     const { return username; }
    string             getIpAddress()    const { return ipAddress; }
    Platform           getPlatform()     const { return platform; }
    vector<SocialPost> getPosts()        const { return recoveredPosts; }
    DateTime           getLastActivity() const { return lastActivityDate; }
};

#endif
