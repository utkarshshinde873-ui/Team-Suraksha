# Team-Suraksha
team Surakhsha public information repository
🚨 Smart SOS Emergency Device

A compact and reliable SOS emergency device built using Arduino that helps users send their real-time location via SMS during emergencies with a single button press.

⸻

📌 Problem Statement

In emergency situations, people often struggle to quickly share their location with family or authorities. This delay can lead to serious consequences.

This project provides a one-click solution to instantly send location details and alerts.

⸻

💡 Solution

The Smart SOS Device uses GPS + GSM modules to:

* Detect the user’s real-time location
* Send an SOS message to predefined contacts
* Optionally make an emergency call

⸻

⚙️ Features

* 📍 Real-time GPS location tracking
* 📩 Automatic SMS alerts with coordinates
* 📞 Emergency calling (optional)
* 🔘 One-button activation (SOS button)
* 🔋 Portable and easy to use

⸻

🛠️ Components Used

* Arduino Nano / Uno
* GPS Module (e.g., Neo-6M)
* GSM Module (e.g., SIM800/A9G)
* Push Button (SOS Trigger)
* Power Supply (Battery)
* Connecting Wires
* ⸻

💻 Working Principle

1. User presses the SOS button
2. Arduino detects long press
3. GPS module fetches latitude & longitude
4. GSM module sends SMS with location
5. (Optional) Initiates a phone call

⸻

🚀 How to Run

1. Connect all components as per circuit diagram
2. Insert SIM card into GSM module
3. Upload Arduino code using Arduino IDE
4. Power the device
5. Press SOS button to trigger alert
