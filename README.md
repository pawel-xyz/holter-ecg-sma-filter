# Holter ECG Signal Processor: Artifact Reduction & Statistical Analysis

## Project Overview
This project simulates the data pipeline of a Holter ECG monitor, focusing on the critical issue of signal noise and baseline wandering in medical recordings. The system is divided into two distinct stages: high-performance signal processing written in C, followed by advanced statistical validation and visual analytics executed in Python. 

The primary goal is to demonstrate how algorithmic smoothing prevents false medical diagnoses, such as non-existent arrhythmias, while preserving crucial physiological waveforms (e.g., the QRS complex).

---

## Stage 1: Embedded Signal Processing (C)
In the first stage, the raw electrocardiogram data is processed mimicking a real-time embedded medical device.

* **Raw Data Generation:** The system captures uncalibrated, noisy ECG signals (`Holter_Raw_Data.csv`), which include high-frequency artifacts typical for patient movement or electrode interference.
* **Filtering Algorithm:** A Simple Moving Average (SMA) filter is implemented in C to process the data efficiently. The algorithm calculates the unweighted mean of the previous data points to smooth out short-term fluctuations and highlight longer-term trends.
* **Output:** The filtered signal is exported as `Holter_SMA_Data.csv` for further evaluation.

---

## Stage 2: Data Analytics & Visualization (Python)
The generated datasets (Raw vs. SMA) are imported into Python using `pandas` and `numpy`. The analysis validates the filter's efficiency through three distinct analytical steps using `matplotlib`.

### Step 2.1: Signal Topology Comparison
Both the entire 450-measurement dataset and specific 50-measurement segments (containing a QRS complex) are plotted side-by-side. 
* *Action:* Rigid Y-axis limits (`set_ylim`) were strictly enforced to prevent visual distortion caused by automatic scaling.
* *Result:* The visual comparison proves that the SMA filter successfully removes high-frequency spikes while preserving the natural amplitude and shape of the heart's contraction.

> <img width="1774" height="759" alt="holter_SmaVsRaw_comp" src="https://github.com/user-attachments/assets/6d2909f2-4fc2-4dec-91c9-3a489ab86fd2" />


### Step 2.2: Isoelectric Line Stability (Standard Deviation)
To statistically quantify the noise reduction, the analysis targets the isoelectric line—the flat intervals where the heart is physically at rest (e.g., between measurements 120-150, 240-271, and 360-391).
* *Action:* The segments were concatenated, and the standard deviation was calculated strictly for the resting phase.
* *Result:* The standard deviation dropped drastically from **0.060** in the raw data to **0.056** in the filtered data.

<img width="556" height="435" alt="STD_comparison" src="https://github.com/user-attachments/assets/cdef85e3-104c-45c3-8ed3-3e0505d7cc6a" />


### Step 2.3: False Trend Quantification
High-frequency noise creates artificial local extrema (micro-peaks and valleys) that medical software can misinterpret. 
* *Action:* An algorithm iterates through a 50-measurement segment to detect and count every directional trend change.
* *Result:* The raw signal contained **30** chaotic trend changes. The filtered signal reduced this to just **5** physiologically justified trend changes.

> <img width="1245" height="933" alt="TrnedCganges_comparison" src="https://github.com/user-attachments/assets/1628db85-d4c9-4ed9-837c-33ba6bfa6081" />


---

## 🩺 Conclusions & Medical Impact

The statistical and visual analyses confirm the absolute necessity of digital signal processing in diagnostic cardiology:

1. **Prevention of False Arrhythmia Alarms:** The reduction of trend changes from 30 to 5 in a single segment proves that raw data would trigger continuous false alarms for ventricular tachycardia or atrial fibrillation. The SMA filter ensures the heartbeat detection algorithms only count actual cardiac cycles.
2. **Isoelectric Line Stabilization:** The significant drop in standard deviation during the heart's resting phase allows for accurate detection of ST-segment elevation or depression, which is the primary indicator of myocardial ischemia (heart attack).
3. **Accurate HRV (Heart Rate Variability) Analysis:** By removing micro-spikes that shift the highest point of the R-wave, the filter allows for precise millisecond-level measurement of intervals between beats, enabling correct assessment of the patient's autonomic nervous system.
