# 🚀 ATS Monitoring System berbasis ESP32

ATS Monitoring adalah proyek **monitoring otomatis sistem Automatic Transfer Switch (ATS)** yang menggunakan **ESP32** untuk membaca data listrik dari **PZEM-004T v3 dan PZEM-017**, dengan output ditampilkan pada **Serial Monitor**. Sistem ini dirancang untuk memantau parameter penting seperti **tegangan, arus, daya, frekuensi, dan energi**, sehingga pengguna dapat mengetahui kondisi sumber listrik (PLN dan Genset) secara real-time.

---

## 🔧 **Fitur Utama**
✅ Monitoring **dua sumber listrik (PLN & Genset)** secara bersamaan  
✅ Menggunakan sensor **PZEM-004T v3** untuk PLN dan **PZEM-017** untuk arus DC (Genset atau baterai)  
✅ Pembacaan **tegangan, arus, daya, dan energi** real-time  
✅ Output langsung ke **Serial Monitor** (monitoring saja)  
✅ Berbasis **ESP32** yang mendukung konektivitas LAN/WiFi (dapat dikembangkan menjadi IoT)

---

## 📦 **Perangkat Keras yang Digunakan**
| No | Komponen         | Jumlah | Keterangan         |
|----|------------------|--------|--------------------|
| 1  | ESP32 Dev Board  | 1      | Mikrokontroler utama |
| 2  | PZEM-004T v3     | 2      | Untuk pengukuran PLN |
| 3  | PZEM-017         | 1      | Untuk pengukuran DC (Genset/Baterai) |
| 4  | Kabel & Power Supply | -  | Pendukung sistem |

---

## ⚙️ **Cara Kerja Sistem**
1. ESP32 menginisialisasi komunikasi UART ke masing-masing modul PZEM.
2. Setiap modul membaca nilai dari sumber listrik.
3. Data dikirim dan ditampilkan pada Serial Monitor secara berkala.
4. Output digunakan sebagai parameter monitoring kondisi PLN dan Genset.

---

## 🧪 **Tujuan Proyek**
Proyek ini dibuat untuk keperluan **monitoring ATS (Automatic Transfer Switch)** agar pengguna dapat melihat:
- Kondisi sumber utama (PLN)
- Kondisi sumber cadangan (Genset)
- Status tegangan/daya apakah dalam batas normal
- Data historis energi listrik (kWh)

> **Catatan:** Saat ini, proyek fokus pada monitoring saja. Pengembangan selanjutnya dapat mencakup pengiriman data ke dashboard IoT atau aplikasi mobile.

---

---

## 📌 **Instalasi & Penggunaan**
### 1️⃣ Clone Repository
```bash
git clone https://github.com/kalhaikl/ats-monitoring.git
```
### Contoh Output pada Serial Monitor ###
PLN Voltage : 220.5 V
PLN Current : 1.23 A
PLN Power   : 270.15 W

GENSET Voltage : 48.2 V
GENSET Current : 3.10 A
GENSET Power   : 149.42 W

---------------------------

