#define BLYNK_TEMPLATE_ID "TMPL6Oix91rB2"
#define BLYNK_TEMPLATE_NAME "Smart Agri Monitor"
#define BLYNK_AUTH_TOKEN "Token Blynk"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


const char* ssid = "SSID WIFI";
const char* password = "PASSWORD WIFI";


//==== PIN SENSOR ====
#define DHTPIN  D3
#define DHTTYPE DHT22
#define SOIL_PIN A0
#define LDR_PIN  D1
#define MQ_PIN   D0  // MQ-135 tetap D0 digital (hanya status, bukan adc)


//==== RELAY ====
#define RELAY_PIN D2    // relay aktif LOW


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Pompa OFF awal
  timer.setInterval(2000L, sendSensorData);
}


void sendSensorData() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();
  int soilRaw = analogRead(SOIL_PIN);
  int ldrRaw  = analogRead(LDR_PIN);
  int airRaw  = analogRead(MQ_PIN);


  // Soil percent (mapping basah - kering)
  int soilPercent = map(soilRaw, 900, 300, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);


  // Kirim ke Blynk
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, soilPercent);
  Blynk.virtualWrite(V3, ldrRaw);
  Blynk.virtualWrite(V4, airRaw);


  // === PARAMETER KONDISI ===
  bool soilDry   = (soilPercent <= 30);
  bool soilVeryDry = (soilPercent <= 20);
  bool lowLight  = (ldrRaw < 300);     // cahaya rendah = baik untuk menyiram
  bool highLight = (ldrRaw >= 300);    // cahaya tinggi = tunda penyiraman
  bool tooHot    = (temp > 32 && hum < 40);
  bool extremeHot = (temp > 35 && hum < 30);
  bool badAir    = (airRaw > 900);


  bool decisionToIrrigate = false;


  //=== LOGIKA UTAMA === (hemat air & efisien)
  if (soilDry) {
    if (lowLight) {
      decisionToIrrigate = true;  // tanah kering & cahaya rendah --> nyiram
    } else {
      decisionToIrrigate = false; // tanah kering tapi cahaya tinggi --> tunda
    }
  }


  //=== MODE DARURAT — kemarau / panas ekstrem ===
  if (soilVeryDry && extremeHot) {
    decisionToIrrigate = true; // override, tanaman terancam mati
    Blynk.virtualWrite(V7, "MODE DARURAT: Panas ekstrem, penyiraman dipaksa aktif");
  } else {
    Blynk.virtualWrite(V7, "Normal");
  }


  //=== KONTROL POMPA ===
  if (decisionToIrrigate) {
    digitalWrite(RELAY_PIN, LOW);  // pompa ON
    Blynk.virtualWrite(V5, "Penyiraman aktif — tanaman membutuhkan air");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // pompa OFF
    Blynk.virtualWrite(V5, "Kondisi aman — penyiraman tidak diperlukan");
  }


  //=== NOTIFIKASI KUALITAS UDARA (tidak menghalangi penyiraman) ===
  if (badAir) {
    Blynk.virtualWrite(V6, "Kualitas udara buruk — cek lingkungan!");
  } else {
    Blynk.virtualWrite(V6, "Kualitas udara normal");
  }


  //=== MONITOR SERIAL ===
  Serial.println("======== SENSOR STATUS ========");
  Serial.printf("Temp: %.2f°C, Hum: %.2f%%\n", temp, hum);
  Serial.printf("Soil: %d%% | Light: %d | Air: %d\n", soilPercent, ldrRaw, airRaw);
  Serial.println(decisionToIrrigate ? "Pompa: ON" : "Pompa: OFF");
  Serial.println("================================");
}


void loop() {
  Blynk.run();
  timer.run();
} 



