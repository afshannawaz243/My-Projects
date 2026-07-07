#include "SocialMediaTrace.h"
#include <iostream>
#include <fstream>
using namespace std;

SocialMediaTrace::SocialMediaTrace(const string& id, const string& caseId,
    const string& collected, const string& desc,
    Platform plat, const string& user,
    const string& url)
    : Evidence(id, caseId, collected, desc),
    platform(plat), username(user), profileUrl(url),
    ipAddress(""), deviceFingerprint(""),
    lastActivityDate(DateTime::now()), accountActive(true) {
}

SocialMediaTrace::SocialMediaTrace(const SocialMediaTrace& other)
    : Evidence(other),
    platform(other.platform),
    username(other.username),
    profileUrl(other.profileUrl),
    ipAddress(other.ipAddress),
    deviceFingerprint(other.deviceFingerprint),
    lastActivityDate(other.lastActivityDate),
    recoveredPosts(other.recoveredPosts),
    accountActive(other.accountActive) {
}

SocialMediaTrace::~SocialMediaTrace() {}

string SocialMediaTrace::platformToString() const {
    switch (platform) {
    case Platform::FACEBOOK:  return "Facebook";
    case Platform::INSTAGRAM: return "Instagram";
    case Platform::TWITTER:   return "Twitter/X";
    case Platform::WHATSAPP:  return "WhatsApp";
    case Platform::TIKTOK:    return "TikTok";
    case Platform::SNAPCHAT:  return "Snapchat";
    case Platform::OTHER:     return "Other";
    default:                  return "Unknown";
    }
}

double SocialMediaTrace::analyzeRelevance() {
    double score = 3.0;
    if (!ipAddress.empty())         score += 2.0;
    if (!deviceFingerprint.empty()) score += 1.5;
    if (!recoveredPosts.empty())    score += (double)recoveredPosts.size() * 0.5;
    if (!accountActive)             score += 1.0;
    if (score > 10.0) score = 10.0;
    relevanceScore = score;
    return score;
}

void SocialMediaTrace::displayInfo() const {
    cout << "\n========================================\n";
    cout << "        SOCIAL MEDIA TRACE\n";
    cout << "========================================\n";
    cout << " ID            : " << evidenceId << "\n";
    cout << " Case ID       : " << linkedCaseId << "\n";
    cout << " Platform      : " << platformToString() << "\n";
    cout << " Username      : " << username << "\n";
    cout << " Profile URL   : " << profileUrl << "\n";
    cout << " IP Address    : " << (ipAddress.empty() ? "Unknown" : ipAddress) << "\n";
    cout << " Last Activity : " << lastActivityDate << "\n";
    cout << " Account Active: " << (accountActive ? "YES" : "NO") << "\n";
    cout << " Posts Found   : " << recoveredPosts.size() << "\n";
    cout << " Relevance     : " << relevanceScore << "/10\n";
    if (!recoveredPosts.empty()) {
        cout << "----------------------------------------\n";
        cout << " RECOVERED POSTS:\n";
        for (const auto& p : recoveredPosts) {
            cout << "  [" << p.timestamp << "] " << p.content << "\n";
            if (!p.location.empty())
                cout << "  Location: " << p.location << "\n";
            if (p.isDeleted)
                cout << "  [DELETED POST - RECOVERED]\n";
        }
    }
    cout << "========================================\n";
}

void SocialMediaTrace::addRecoveredPost(const SocialPost& post) {
    recoveredPosts.push_back(post);
}
void SocialMediaTrace::setIpAddress(const string& ip) { ipAddress = ip; }
void SocialMediaTrace::setDeviceFingerprint(const string& fp) { deviceFingerprint = fp; }
void SocialMediaTrace::setLastActivity(const DateTime& dt) { lastActivityDate = dt; }
void SocialMediaTrace::setAccountActive(bool active) { accountActive = active; }

void SocialMediaTrace::saveToFile(ofstream& ofs) const {
    ofs << "SOCIAL_MEDIA_TRACE\n";
    ofs << evidenceId << "\n" << linkedCaseId << "\n"
        << collectedBy << "\n" << description << "\n"
        << (int)platform << "\n" << username << "\n"
        << profileUrl << "\n" << ipAddress << "\n"
        << deviceFingerprint << "\n" << accountActive << "\n"
        << (int)status << "\n" << relevanceScore << "\n"
        << recoveredPosts.size() << "\n";
    for (const auto& p : recoveredPosts) {
        ofs << p.postId << "\n" << p.content << "\n"
            << p.location << "\n" << p.isDeleted << "\n";
    }
}