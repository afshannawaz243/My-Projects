# IoT Forensic Gateway & Intrusion Detection System

An integrated network monitoring platform designed to inspect IoT telemetry, detect signature-based intrusions, and maintain cryptographic integrity for digital evidence collection.

## Project Architecture
* **`gateway/`**: Contains core packet sniffer, SHA-256 evidence hasher, and web server interface.
* **`emulators/`**: Endpoint simulation nodes for smart home devices (HVAC, lighting, smart locks).

## Default Port Allocations
* **HVAC Node**: Port 5000
* **Light Controller**: Port 5001
* **Lock Panel**: Port 5002

## Setup & Run Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/afshannawaz243/My-Projects.git
   cd My-Projects/"IOT Forensic Gateway"
   
   ```bash
pip install -r requirements.txt```

   ```bash
python emulators/hvac_emulator.py
python emulators/light_emulator.py
python emulators/lock_emulator.py```

  ```bash
python gateway/ids_gateway.py
python gateway/dashboard.py```

