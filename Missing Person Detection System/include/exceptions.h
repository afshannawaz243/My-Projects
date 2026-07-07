#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>
using namespace std;

// Base exception for the entire system
class ForensicsException : public runtime_error {
public:
    explicit ForensicsException(const string& msg)
        : runtime_error("[FORENSICS ERROR] " + msg) {
    }
};

// Thrown when a case ID is not found
class CaseNotFoundException : public ForensicsException {
public:
    explicit CaseNotFoundException(const string& caseId)
        : ForensicsException("Case not found: " + caseId) {
    }
};

// Thrown when a person ID is not found
class PersonNotFoundException : public ForensicsException {
public:
    explicit PersonNotFoundException(const string& personId)
        : ForensicsException("Person not found: " + personId) {
    }
};

// Thrown when evidence is missing or corrupt
class EvidenceException : public ForensicsException {
public:
    explicit EvidenceException(const string& msg)
        : ForensicsException("Evidence error: " + msg) {
    }
};

// Thrown on file read/write failure
class FileIOException : public ForensicsException {
public:
    explicit FileIOException(const string& filename)
        : ForensicsException("File I/O failed: " + filename) {
    }
};

// Thrown when input fails validation
class InvalidInputException : public ForensicsException {
public:
    explicit InvalidInputException(const string& field)
        : ForensicsException("Invalid input for field: " + field) {
    }
};

// Thrown when trying to modify a closed case
class CaseClosedException : public ForensicsException {
public:
    explicit CaseClosedException(const string& caseId)
        : ForensicsException("Cannot modify closed case: " + caseId) {
    }
};

#endif
