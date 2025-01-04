#define BLYNK_TEMPLATE_ID "*******"  // Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Teszt"
#define BLYNK_AUTH_TOKEN "*******-*******-By"    // Blynk Auth Token

#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

// BH1750 és DHT11 beállítások
BH1750 lightMeter;
#define DHTPIN 33
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LED és hangjelző
#define LED_YELLOW 14
#define LED_GREEN 12
#define LED_RED 13
#define BUZZER 27

// WiFi adatok
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "*******-*******";       // A Wi-Fi hálózat neve
char pass[] = "*******";   // A Wi-Fi hálózat jelszava

// Globális változók
float totalLight = 0;
float lightReadings = 0;
float luxThresholdExceeds = 0;
float exceedStartTime = 0;
float totalExceedTime = 0;

void setup() {
  Serial.begin(115200);

  // Blynk és szenzorok inicializálása
  Blynk.begin(auth, ssid, pass);
  Wire.begin(19,18);
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  dht.begin();

  // LED és hangjelző
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  Blynk.run();
  pinMode(BUZZER, OUTPUT);
  // Fényintenzitás mérése
  float lux = lightMeter.readLightLevel();
  totalLight += lux;
  lightReadings++;

  // LED-ek vezérlése
  if (lux < 3000) {
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
  } else if (lux < 8000) {
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(BUZZER, HIGH);
    tone(BUZZER, 4000);  // 1000 Hz-es frekvenciával megszólaltatjuk
    delay(1000);  // 1 másodpercig szól
     noTone(BUZZER);  // Leállítjuk a hangot
    delay(1);  // 1 másodperc szünet

    if (exceedStartTime == 0) {
      exceedStartTime = millis();
    }
  }

  // Túlcsordulások rögzítése
  if (lux < 8000 && exceedStartTime > 0) {
    luxThresholdExceeds++;
    totalExceedTime += millis() - exceedStartTime;
    exceedStartTime = 0;
    digitalWrite(BUZZER, LOW);
  }

  // DHT11 mérések
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

//Blynk frissítések
Blynk.virtualWrite(V21, lux);
Blynk.virtualWrite(V22, luxThresholdExceeds);
Blynk.virtualWrite(V33, luxThresholdExceeds > 0 ? totalExceedTime / luxThresholdExceeds/1000/60 : 0);
Blynk.virtualWrite(V34, temp);
Blynk.virtualWrite(V35, hum);
  Serial.print("jelenlegi fényerő");
  Serial.println(lux);
  Serial.print("eddigi fényerő tullépesek száma");
  Serial.println(luxThresholdExceeds);
  Serial.print("tullépések átlag ideje:");
  
  Serial.println(luxThresholdExceeds > 0 ? totalExceedTime / luxThresholdExceeds/1000/60 : 0);
  Serial.print("hőmérséklet:");
  Serial.println(temp);
  Serial.print("páratartoalom:");
  Serial.println(hum);


  delay(1000);
}
