//=======LIBRARY================
#include <PZEM004Tv30.h>
#include <ModbusMaster.h>

//=======INISIALISASI SERIAL====
HardwareSerial PZEMSerial1(2);
PZEM004Tv30 pzemPLN(Serial2, 4, 5);

HardwareSerial PZEMSerial2(1);
PZEM004Tv30 pzemPLTS(Serial1, 16, 17);

HardwareSerial PZEMSerial(0);

//======PIN PZEM-017===========
#define MAX485_RO  26
#define MAX485_RE  22
#define MAX485_DE  23
#define MAX485_DI  27

// Address PZEM-017 : 0x01–0xF7
static uint8_t pzemSlaveAddr = 0x03;

// Shunt setting: 0x0000-100A, 0x0001-50A, 0x0002-200A, 0x0003-300A
static uint16_t NewshuntAddr = 0x0003;

//Objek dari modbusmaster dengan nama Node
ModbusMaster node;

//Variabel Pembacaan dari Baterai, PLN, dan PLTS
float PZEMVoltage, PZEMCurrent, PZEMPower, PZEMEnergy;
float voltagePLN, currentPLN, powerPLN, energyPLN, frequencyPLN, pfPLN;
float voltagePLTS, currentPLTS, powerPLTS, energyPLTS, frequencyPLTS, pfPLTS;

//Millis
unsigned long startMillisPZEM;
unsigned long currentMillisPZEM;
const unsigned long periodPZEM = 1000;
unsigned long startMillisReadData;
unsigned long startMillis1;


//====FUNGSI PEMBACAAN DARI PLN(AC)=====
void readPLN(){
  Serial.print("Custom Address: ");
  Serial.println(pzemPLN.readAddress(), HEX);
  voltagePLN = pzemPLN.voltage();
  currentPLN = pzemPLN.current();
  powerPLN = pzemPLN.power();
  energyPLN = pzemPLN.energy();
  frequencyPLN = pzemPLN.frequency();
  pfPLN = pzemPLN.pf();
  if(isnan(voltagePLN)){
    Serial.println("⚠️Error reading voltage PLN");
  } else if(isnan(currentPLN)){
    Serial.println("Error reading current PLN");
  } else if(isnan(powerPLN)){
    Serial.println("Error reading power PLN");
  } else if(isnan(energyPLN)){
    Serial.println("Error reading energy PLN");
  } else if(isnan(frequencyPLN)){
    Serial.println("Error frequency PLN");
  } else{
    Serial.println("===PLN===");
    Serial.print("VoltagePLN: ");    Serial.print(voltagePLN);      Serial.println("V");
    Serial.print("CurrentPLN: ");    Serial.print(currentPLN);      Serial.println("A");
    Serial.print("PowerPLN: ");      Serial.print(powerPLN);        Serial.println("W");
    Serial.print("EnergyPLN: ");     Serial.print(energyPLN,3);     Serial.println("kWh");
    Serial.print("FrequencyPLN: ");  Serial.print(frequencyPLN, 1); Serial.println("Hz");
    Serial.print("PFPLN: ");         Serial.println(pfPLN);
  }
  Serial.println();
  delay(3000);
}


//====FUNGSI PEMBACAAN DARI PLTS(AC)========
void readPLTS(){
  Serial.print("Custom Address: ");
  Serial.println(pzemPLTS.readAddress(), HEX);
  voltagePLTS = pzemPLTS.voltage();
  currentPLTS = pzemPLTS.current();
  powerPLTS = pzemPLTS.power();
  energyPLTS = pzemPLTS.energy();
  frequencyPLTS = pzemPLTS.frequency();
  pfPLTS = pzemPLTS.pf();
  if(isnan(voltagePLTS)){
    Serial.println("⚠️Error reading voltage PLTS");
  } else if(isnan(currentPLTS)){
    Serial.println("Error reading current PLTS");
  } else if(isnan(powerPLTS)){
    Serial.println("Error reading power PLTS");
  } else if(isnan(energyPLTS)){
    Serial.println("Error reading energy PLTS");
  } else if(isnan(frequencyPLTS)){
    Serial.println("Error frequency PLTS");
  } else{
    Serial.println("===PLTS===");
    Serial.print("VoltagePLTS: ");    Serial.print(voltagePLTS);      Serial.println("V");
    Serial.print("CurrentPLTS: ");    Serial.print(currentPLTS);      Serial.println("A");
    Serial.print("PowerPLTS: ");      Serial.print(powerPLTS);        Serial.println("W");
    Serial.print("EnergyPLTS: ");     Serial.print(energyPLTS,3);     Serial.println("kWh");
    Serial.print("FrequencyPLTS: ");  Serial.print(frequencyPLTS, 1); Serial.println("Hz");
    Serial.print("PFPLTS: ");         Serial.println(pfPLTS);
  }
  Serial.println();
  delay(3000);
}


//====FUNGSI PEMBACAAN DARI BATERAI 12V 100Ah(DC)=====
void readBattery(){
  currentMillisPZEM = millis();

  if (currentMillisPZEM - startMillisPZEM >= periodPZEM) {
    uint8_t result = node.readInputRegisters(0x0000, 6);

    if (result == node.ku8MBSuccess) {
      uint32_t tempdouble = 0x00000000;
      PZEMVoltage = node.getResponseBuffer(0x0000) / 100.0;
      PZEMCurrent = node.getResponseBuffer(0x0001) / 100.0;

      tempdouble = (node.getResponseBuffer(0x0003) << 16) + node.getResponseBuffer(0x0002);
      PZEMPower = tempdouble / 10.0;

      tempdouble = (node.getResponseBuffer(0x0005) << 16) + node.getResponseBuffer(0x0004);
      PZEMEnergy = tempdouble;
    } else {
      PZEMVoltage = NAN;
      PZEMCurrent = NAN;
      PZEMPower = NAN;
      PZEMEnergy = NAN;
    }

    // Tampilkan di Serial Monitor
    Serial.println("===Baterai===");
    Serial.print("Vdc : "); Serial.print(PZEMVoltage); Serial.println(" V");
    Serial.print("Idc : "); Serial.print(PZEMCurrent); Serial.println(" A");
    Serial.print("Power : "); Serial.print(PZEMPower); Serial.println(" W");
    Serial.print("Energy : "); Serial.print(PZEMEnergy); Serial.println(" Wh");
    Serial.println();
    startMillisPZEM = currentMillisPZEM;
  }
}
void preTransmission() {
  if (millis() - startMillis1 > 5000) {
    digitalWrite(MAX485_RE, HIGH);
    digitalWrite(MAX485_DE, HIGH);
    delay(1);
  }
}

void postTransmission() {
  if (millis() - startMillis1 > 5000) {
    delay(3);
    digitalWrite(MAX485_RE, LOW);
    digitalWrite(MAX485_DE, LOW);
  }
}

void setShunt(uint8_t slaveAddr) {
  static uint8_t SlaveParameter = 0x06;
  static uint16_t registerAddress = 0x0003;

  uint16_t u16CRC = 0xFFFF;
  u16CRC = crc16_update(u16CRC, slaveAddr);
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewshuntAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewshuntAddr));

  preTransmission();
  PZEMSerial.write(slaveAddr);
  PZEMSerial.write(SlaveParameter);
  PZEMSerial.write(highByte(registerAddress));
  PZEMSerial.write(lowByte(registerAddress));
  PZEMSerial.write(highByte(NewshuntAddr));
  PZEMSerial.write(lowByte(NewshuntAddr));
  PZEMSerial.write(lowByte(u16CRC));
  PZEMSerial.write(highByte(u16CRC));
  delay(10);
  postTransmission();
  delay(100);
}

void resetEnergy() {
  uint16_t u16CRC = 0xFFFF;
  static uint8_t resetCommand = 0x42;
  uint8_t slaveAddr = pzemSlaveAddr;

  u16CRC = crc16_update(u16CRC, slaveAddr);
  u16CRC = crc16_update(u16CRC, resetCommand);
  preTransmission();
  PZEMSerial.write(slaveAddr);
  PZEMSerial.write(resetCommand);
  PZEMSerial.write(lowByte(u16CRC));
  PZEMSerial.write(highByte(u16CRC));
  delay(10);
  postTransmission();
  delay(100);
}

void changeAddress(uint8_t OldslaveAddr, uint8_t NewslaveAddr) {
  static uint8_t SlaveParameter = 0x06;
  static uint16_t registerAddress = 0x0002;
  uint16_t u16CRC = 0xFFFF;

  u16CRC = crc16_update(u16CRC, OldslaveAddr);
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewslaveAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewslaveAddr));

  preTransmission();
  PZEMSerial.write(OldslaveAddr);
  PZEMSerial.write(SlaveParameter);
  PZEMSerial.write(highByte(registerAddress));
  PZEMSerial.write(lowByte(registerAddress));
  PZEMSerial.write(highByte(NewslaveAddr));
  PZEMSerial.write(lowByte(NewslaveAddr));
  PZEMSerial.write(lowByte(u16CRC));
  PZEMSerial.write(highByte(u16CRC));
  delay(10);
  postTransmission();
  delay(100);
}

void setup() {
  startMillis1 = millis();
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 4, 5);
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  PZEMSerial.begin(9600, SERIAL_8N2, MAX485_RO, MAX485_DI);
  pinMode(MAX485_RE, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE, LOW);
  digitalWrite(MAX485_DE, LOW);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  node.begin(pzemSlaveAddr, PZEMSerial);
  while (millis() - startMillis1 < 5000) {
    delay(500);
    Serial.print(".");
  }
  delay(1000);
  Serial.println("Starting PZEM readings...");
  setShunt(pzemSlaveAddr);
  changeAddress(0xF8, pzemSlaveAddr);
}

//=====LOOP=========
void loop() {
  readPLN();
  delay(500);
  readPLTS();
  delay(500);
  readBattery();
  delay(500);
}
