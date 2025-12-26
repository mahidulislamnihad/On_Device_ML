# On Device ML
# ESP32 Environment Classifier

## Overview
This project demonstrates an **ESP32-based environment classifier** using a **DHT11 sensor** and a **TensorFlow Lite (TFLite) model**. The ESP32 reads temperature and humidity, performs on-device inference, and predicts the environment condition (e.g., HOT_DRY, HOT_HUMID, COOL_DAMP).  

The goal is to explore **lightweight ML deployment** on resource-constrained devices, experiment with **quantized TFLite models**, and integrate real-time IoT sensing with ML inference.

---

## Project Journey

### Step 1: Data Collection and Labeling
- Used Synthesis Data to train the model actual data has not been collected since it is a demo project.

### Step 2: Model Training
- Built a **Keras Sequential model** with 4 input features:
  - Temperature, Humidity, ΔTemperature, ΔHumidity.
- Output: **12-class categorical environment labels**.
- Experimented with training, validation, and quantization for TFLite deployment.
- Achieved ~95% accuracy on the validation set.

### Step 3: TFLite Conversion
- Converted the trained model to **full integer quantized TFLite** for ESP32 deployment.
- Used a **representative dataset** from training samples for proper quantization.
- Verified input/output tensor types.

### Step 4: ESP32 Deployment
- Integrated **TFLite model** with ESP32 using **MicroTFLite**.
- Connected **DHT11 sensor** to ESP32 to read temperature and humidity.
- Implemented inference and mapped model outputs to environment labels.
- Added **serial output** for raw sensor readings and predicted environment.

---

## Project Status
- **Colab training code** will be added tommorow. 
- Current TFLite inference on ESP32 works, but output **accuracy may vary**; further model tuning and sensor calibration are ongoing.
- Experienced multiple issues in:
  - Library compatibility (ArduTFLite vs. MicroTFLite)
  - Quantization setup
  - Model data integration (`model_data.h` / `model_data.cpp`)
  - Output class mapping

---

## Repository Structure

esp32_env_classifier/
├─ include/
│ └─ model_data.h # TFLite model declaration
├─ src/
│ ├─ main.cpp # ESP32 main program
│ ├─ inference.cpp # TFLite inference logic
│ └─ model_data.cpp # TFLite model bytes
├─ platformio.ini # PlatformIO project config
├─ README.md # This document
└─ Colab/ # Training and conversion notebooks (to be added)

---

## Hardware
- **ESP32-S3**
- **DHT11 temperature and humidity sensor**
---

## Software / Libraries
- **PlatformIO** (Arduino framework tried with arduino IDE faced some libary issue don't know why then switched to PlatformIo Extention in Visual Studio)
- **MicroTFLite** for TFLite inference 
- **DHT sensor library** 

---

## Next Steps
- Accuracy in real implement is still bad first goal is to make this correct
- Future work involves learning Sensor Health prediction by ML, OTA update using free resource (google drive)

---

## Notes / Observations
- On-device ML requires careful attention to **quantization** and **model compatibility**.
- Libaries and device compabity can be very painful nothing seems to work not google not AI had to try number of libaries then **MicroTFLite** worked
- Sensor noise can affect classification accuracy; averaging or filtering may help.
- The project serves as a **learning reference** for IoT + ML integration on constrained devices.
