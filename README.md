# 🌐 ESP32 Smart Weather Station & Remote Control System

Sistem pemantauan cuaca lokal (Suhu & Kelembapan) dan kendali saklar jarak jauh berbasis **ESP32 DevKit V1**. Sistem ini membaca data presisi dari sensor **DHT22**, menampilkan status indikator visual/suara lokal, mengunggah data telemetri melalui jaringan **Wi-Fi**, serta memungkinkan pengguna mengontrol **Relay 5V** secara nirkabel dari smartphone/web browser.

---

## 📸 Fitur Utama

1. **Pemantauan Suhu & Kelembapan Real-Time**: Membaca sensor presisi tinggi **DHT22** (suhu -40 s/d 80°C ±0.5°C, kelembapan 0-100% ±2-5% RH).
2. **Sistem Peringatan Ambang Batas (Over-Temperature Alarm)**:
   * **Suhu Normal (≤ 30°C)**: **LED Hijau** menyala, sistem dalam status aman.
   * **Suhu Tinggi (> 30°C)**: **LED Merah** menyala, **Active Buzzer** berbunyi, dan notifikasi dikirimkan via antarmuka jaringan.
3. **Remote Control Saklar Relay**: Pengguna dapat menyalakan/mematikan **Relay 1-Channel** (simulasi kipas/lampu) secara jarak jauh melalui Web Server / Aplikasi HP.

---

## 🛠️ Daftar Komponen (Hardware Inventory)

| Komponen | Kategori | Spesifikasi & Deskripsi |
| :--- | :--- | :--- |
| **ESP32 DevKit V1** | Mikrokontroler | Tensilica Xtensa Dual-Core 240MHz, Wi-Fi 802.11 b/g/n, Bluetooth, Logika 3.3V |
| **DHT22 (AM2302)** | Sensor Suhu/Kelembapan | Pembacaan suhu & kelembapan digital presisi tinggi |
| **Relay 1-Channel Optocoupler** | Aktuator | Saklar daya terisolasi (Koil 5V DC, Beban Maks AC 250V/10A & DC 30V/10A) |
| **LED Hijau & LED Merah** | Indikator Visual | Seri dengan Resistor 220Ω sebagai indikator status |
| **Active Buzzer 5V** | Indikator Suara | Alarm peringatan batas suhu tinggi |
| **Resistor 10kΩ & 220Ω** | Komponen Pasif | Pull-up data DHT22 (10kΩ) & Pembatas arus LED (220Ω) |
| **Breadboard 830P & Jumper** | Aksesoris | Sirkuit tanpa solder & Kabel Male-to-Female / Male-to-Male |

---

## 🔌 Skema Pengabelan (Pinout Diagram)

| Komponen | Pin Modul | Pin ESP32 GPIO | Keterangan Jalur & Tegangan |
| :--- | :--- | :--- | :--- |
| **DHT22 Sensor** | VCC | **3.3V / VIN (5V)** | Catu daya sensor |
| | DATA / Out | **GPIO 23 (D23)** | Jalur Data Digital (Pull-up 10kΩ ke 3.3V) |
| | GND | **GND** | Ground bersama (*Common Ground*) |
| **Relay 1-Channel** | VCC | **VIN (5V External)** | Power koil relay (Suplai 5V DC) |
| | IN / Signal | **GPIO 19 (D19)** | Sinyal kontrol pemicu relay |
| | GND | **GND** | Common Ground dengan ESP32 |
| **LED Hijau** | Anoda (+) | **GPIO 18 (D18)** | Resistor Seri 220Ω (Indikator Normal) |
| **LED Merah** | Anoda (+) | **GPIO 5 (D5)** | Resistor Seri 220Ω (Indikator Warning Suhu) |
| **Active Buzzer** | (+) VCC | **GPIO 17 (D17)** | Alarm Suara Peringatan |

> **Perhatian Logika Tegangan (3.3V Logic)**: Pin GPIO ESP32 bekerja pada tegangan logika **3.3V**. Untuk modul Relay 5V, pin VIN wajib dipasok daya 5V dari USB/Power Supply Eksternal dengan kabel GND terhubung bersama (*Common Ground*).

---
