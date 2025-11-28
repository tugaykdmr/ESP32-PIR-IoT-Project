# ESP32-PIR-IoT-Project
**ESP32 ve HC-SR501 PIR sensörü kullanılarak Blynk IoT üzerinden gerçek zamanlı hareket algılama ve bildirim gönderme sistemi.**

Bu proje, temel elektronik öğreten, IoT kavramlarını tanıtan ve mobil bildirim altyapısı ile akıllı güvenlik sistemlerine giriş sağlayan **eğitim amaçlı bir akıllı hareket algılama projesidir**.

---

## 📌 Projenin Amacı
Bu proje;
- Öğrencilerin **ESP32**, **sensörler**, **IoT**, **mobil bildirim**, **bulut bağlantısı** konularını gerçek bir uygulama ile öğrenmesini,
- Ev otomasyonu için bir **akıllı hareket algılama sistemi** geliştirilmesini,
- Öğretmenlerin kullanabileceği bir **Robotik Kodlama Eğitim Kiti** oluşturulmasını hedefler.

---

## 🔧 Kullanılan Donanımlar
| Donanım | Açıklama |
|--------|----------|
| **ESP32 DevKit V1** | Wi-Fi destekli IoT geliştirme kartı |
| **HC-SR501 PIR Sensörü** | Hareket algılama sensörü |
| Jumper kablolar | Bağlantı için |
| Breadboard | Devre kurulum alanı |
| USB Type-C/B kablosu | ESP32 programlama |

---

## 🔌 Bağlantı Şeması
**ESP32 → PIR sensörü bağlantıları:**

| PIR Sensörü | ESP32 |
|-------------|-------|
| VCC | 3.3V |
| OUT | GPIO23 |
| GND | GND |

---

## 📲 Yazılım Arayüzü: Blynk IoT
Bu sistem, hareket algılandığında **telefonunuza anlık bildirim yollayan** bir IoT yapısı içerir.

**Blynk üzerinde kullanılan event adı:**  
pir_sensor

---

## 🧠 Projenin Çalışma Mantığı
1. ESP32 açılır → Wi-Fi’ye bağlanır  
2. PIR sensörü 30 saniye kalibrasyon yapar  
3. Hareket algılanırsa:  
   - Serial monitörde mesaj yazılır  
   - Blynk üzerinden **anlık mobil bildirim** gönderilir  
4. Sistem, spam engeli için 10 saniye cooldown süresi kullanır

---

## 💻 Kullanılan Kod

```cpp
#define BLYNK_TEMPLATE_ID "XXXX"
#define BLYNK_TEMPLATE_NAME "TugayAkdemir Pır Sensor"
#define BLYNK_AUTH_TOKEN "XXXX"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Tugay";   
char pass[] = "tugayay1";  

const int PIR_PIN = 13;

int lastPir = LOW;
unsigned long lastSend = 0;
const unsigned long COOLDOWN_MS = 10000;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  Serial.println("[WIFI] Baglaniyor...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("[BLYNK] Baglandi!");

  Serial.println("[PIR] 30s kalibrasyon suresi...");
  delay(30000);
  Serial.println("[PIR] Kalibrasyon tamam, hareket bekleniyor...");
}

void loop() {
  Blynk.run();

  int pirValue = digitalRead(PIR_PIN);

  if (pirValue == HIGH && lastPir == LOW && (millis() - lastSend > COOLDOWN_MS)) {
    Serial.println("HAREKET ALGILANDI -> Bildirim gonderildi");
    Blynk.logEvent("pir_sensor", "Hareket algilandi!");
    lastSend = millis();
  }

  lastPir = pirValue;
  delay(100);
}
📦 Kurulum Adımları
1️⃣ PlatformIO Kurulumu
VS Code indir

Extensions → PlatformIO IDE yükle

Yeni proje oluştur

Board: ESP32 DevKit V1

Framework: Arduino

2️⃣ Gerekli Kütüphane
PlatformIO platformio.ini dosyasına ekle:

lib_deps = 
  blynkkk/Blynk@^1.3.2
3️⃣ Kodları proje klasörüne yapıştır
src/main.cpp içine tüm kodu ekleyin.

4️⃣ ESP32'yi USB ile bağla
“Upload” tuşuna bas → Kod karta yüklenir.

5️⃣ Serial Monitor aç
ESP32'nin bağlandığını “IP Adresi…” mesajından anlarsın.

6️⃣ Blynk App
Template oluştur

Device oluştur

Event ekle (pir_sensor)

Artık telefon bildirim alır.

🎯 Gerçek Hayat Kullanım Alanları
Akıllı ev güvenlik sistemi

Sınıflarda hareket takibi

Robotik kodlama eğitim seti

Depo ve ofis hareket kontrolü

IoT eğitim projeleri

📦 Eğitim Kiti Olarak Değeri
Bu proje;

Çocuklara elektronik + yazılım + IoT + bulut mantığını öğretir

Uygulamalı STEM projesidir

Çok düşük maliyetle yüksek eğitim değeri sağlar

Okullar için ideal robotik eğitim içeriğidir

📄 Lisans
MIT License
Bu proje özgürce kullanılabilir.

👤 Geliştirici
Tugay Akdemir
GitHub: https://github.com/tugaykdmr
