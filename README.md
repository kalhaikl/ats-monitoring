ESP32 Monitoring dengan 2 PZEM004T v3 dan 1 PZEM017

Proyek ini bertujuan untuk melakukan monitoring parameter listrik dari tiga sumber daya: PLN, PLTS (Panel Surya), dan Baterai, menggunakan modul sensor PZEM004T v3 dan PZEM017 yang terhubung dengan mikrokontroler ESP32. Data ditampilkan secara real-time melalui Serial Monitor dan tidak melibatkan fungsi kontrol atau switching otomatis.

📌 Fitur Utama

Monitoring tegangan, arus, daya, energi, frekuensi, dan faktor daya PLN serta PLTS menggunakan PZEM004T v3

Monitoring arus dan tegangan baterai menggunakan PZEM017 berbasis Modbus RS485

Komunikasi:

UART untuk PZEM004T v3

Modbus RTU via MAX485 untuk PZEM017

Output tampil pada Serial Monitor Arduino IDE

Sistem hanya untuk monitoring, tidak ada fungsi kendali beban

🧰 Daftar Komponen
No	Komponen	Jumlah	Keterangan
1	ESP32 Dev Board	1	Mikrokontroler utama
2	PZEM004T v3	2	Sensor PLN dan PLTS
3	PZEM017	1	Sensor baterai (arus DC)
4	Modul MAX485	1	Konverter RS485 ke UART
5	Shunt Resistor	1	Untuk PZEM017 sesuai rating arus
6	Kabel jumper	-	Koneksi antarmodul
7	Power Supply 5V	1	Untuk ESP32 dan sensor jika dibutuhkan
🔧 Library yang Digunakan

Instalasi library melalui Library Manager Arduino IDE:

PZEM004Tv30 by Olehs
ModbusMaster by Doc Walker

🔌 Konfigurasi Pin ESP32
PZEM004T v3 (PLN)
ESP32	PZEM004T v3
TX	RX
RX	TX
PZEM004T v3 (PLTS)
ESP32	PZEM004T v3
TX	RX
RX	TX
PZEM017 via MAX485
ESP32 Pin	MAX485 Pin	Keterangan
GPIO 26	RO	Receive Data
GPIO 22	RE/DE	Enable Transceiver
GPIO xx	DI	Transmit Data (TX)
GND	GND	Ground
VCC 5V	VCC	Daya modul MAX485

Catatan: Sesuaikan pin RX/TX dengan program aktual di file PZEM-INTEGRATION.ino.

▶️ Cara Menggunakan

Hubungkan modul sesuai tabel di atas.

Buka Arduino IDE dan pilih:

Board: ESP32 Dev Module

Port: sesuaikan dengan COM yang terdeteksi

Upload program PZEM-INTEGRATION.ino

Buka Serial Monitor dengan baudrate yang sesuai (misal 115200)

Pantau data secara real-time

📟 Contoh Tampilan Serial Monitor
=== MONITORING PLN ===
Voltage: 220.50 V
Current: 0.45 A
Power: 98.20 W
Energy: 0.123 kWh
Frequency: 50.01 Hz
PF: 0.98

=== MONITORING PLTS ===
Voltage: 18.40 V
Current: 1.25 A
Power: 23.00 W
Energy: 0.045 kWh

=== MONITORING BATERAI ===
Voltage: 12.50 V
Current: 2.10 A
Power: 26.25 W
Energy: 0.200 kWh

🧪 Fungsi Program

Melakukan pembacaan berkala menggunakan millis()

Menghindari penggunaan delay() agar pembacaan tetap responsif

Menampilkan hasil pembacaan setiap periode tertentu
