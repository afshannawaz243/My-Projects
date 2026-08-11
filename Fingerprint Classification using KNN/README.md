# Fingerprint Classification Using K-Nearest Neighbors (KNN)

## Overview
This project is a machine learning pipeline designed to classify fingerprint images into three fundamental pattern types: **Arch**, **Loop**, and **Whorl**. Using the public SOCOFing (Sokoto Coventry Fingerprint Dataset), raw images are preprocessed and flattened into feature vectors to train a K-Nearest Neighbors classifier.

---

## Project Structure
```text
Fingerprint-Classification-KNN/
│
├── src/                       # Source code and dependencies
│   ├── fingerprint_classification.ipynb
│   └── requirements.txt
│
└── README.md                  # Project overview and instructions

---

## Features & Technical Stack
* **Language:** Python
* **Libraries:** OpenCV (`cv2`), Scikit-Learn, NumPy, Matplotlib
* **Dataset:** SOCOFing (Sokoto Coventry Fingerprint Dataset)
* **Image Preprocessing:** Grayscale conversion, image resizing (64x64 pixels), and 1D pixel vector flattening.
* **Classifier:** K-Nearest Neighbors (k=5).

---

## Results & Performance
* **Model Accuracy:** **63.08%**
* **Train/Test Split:** 4,800 training samples / 1,200 testing samples.
* **Key Observations:**
  * Highest classification precision achieved on **Arch** patterns due to distinct spatial ridges.
  * Minor classification overlap observed between **Loop** and **Whorl** patterns due to pixel-level density similarity when flattened.

---

## How to Run Locally
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/afshannawaz243/My-Projects.git](https://github.com/afshannawaz243/My-Projects.git)
   cd My-Projects/Fingerprint-Classification-KNN
pip install -r requirements.txt
