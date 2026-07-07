# Missing Persons Investigation & Digital Forensics System

A comprehensive, terminal-driven investigative database system built in C++20. This system integrates traditional criminal investigation tracking (missing individuals, witnesses, and suspects) with advanced digital forensics logging, mimicking real-world investigative frameworks.

## 🌟 Core Features

* **Polymorphic Architecture:** Uses advanced Object-Oriented Programming (OOP) with abstract base layers (`Person`, `Case`, `Evidence`) to manage data seamlessly at runtime.
* **Cyber Forensics Logging:** Includes specialized tracking for `DigitalEvidence` (MD5/SHA256 data validation hashes), `PhysicalEvidence` (lab status, forensic tags), and `SocialMediaTrace` (IP logs, device fingerprints, and recovered deleted posts).
* **Dynamic Urgency Scoring:** Automatically calculates investigative priority values based on critical risk factors (such as the missing person's age or suspect threat levels).
* **Data Security & Integrity:** Implements dedicated hierarchical runtime exceptions and structured file serialization for saving and loading active case files.

## 🛠️ How to Compile and Run

This project requires a compiler that supports **C++17** or **C++20** (such as Visual Studio 2022, GCC 11+, or Clang 13+).

### Using Visual Studio (Windows)
1. Double-click the `missing person system project.slnx` or `.vcxproj` file to open it in Visual Studio.
2. Ensure your build configuration is set to **Debug** or **Release** on an **x64** or **x86** platform.
3. Press `Ctrl + F5` to compile and launch the interactive terminal menu.

### Using the Command Line (GCC)
```bash
g++ -std=c++20 src/*.cpp -I ./include -o ForensicsSystem
./ForensicsSystem