# FlowerGuard 2000 – Okos gondoskodás növényeidnek! 🌞

### Valós idejű adatok és figyelmeztetések a fényerőről, hőmérsékletről és páratartalomról – mindig a legjobb gondoskodást nyújthatod.

# Ár: 99,95 $$
## Vedd meg most, és tartsd növényeidet boldogan!


# FlowerGuard 2000 Projektleírás

## Áttekintés
A FlowerGuard 2000 egy okos növényápoló rendszer, amely az ESP32 mikrokontrollert használva valós idejű adatokat gyűjt a környezeti fényerőről, hőmérsékletről és páratartalomról. Az adatokat a Blynk platform segítségével juttatja el az okoseszközökre. Az eszköz LED-ekkel és hangjelzővel figyelmeztet a kritikus állapotokra.

## Funkcionalitás

1. **Fényintenzitás mérése:**
   - A rendszer a BH1750 szenzorral méri a környezeti fényerőt (luxban).
   - LED-ekkel és hangjelzővel figyelmeztet a fényintenzitás szintje alapján: 
     - Alacsony: Sárga LED.
     - Optimális: Zöld LED.
     - Túl magas: Piros LED és hangjelzés.

2. **Hőmérséklet és páratartalom mérése:**
   - A DHT11 szenzor méri a hőmérsékletet (°C) és a páratartalmat (%).

3. **Adatok gyűjtése és elemzése:**
   - Nyomon követi a fényintenzitás túllépések számát.
   - Kiszámolja a túllépések átlagos időtartamát.

4. **Blynk integráció:**
   - Valós idejű adatok feltöltése a Blynk alkalmazásba: 
     - Lux érték (V21).
     - Túllépések száma (V22).
     - Átlagos túllépési idő (V33).
     - Hőmérséklet (V34).
     - Páratartalom (V35).

## Hardverelemek

- **ESP32 DevKitC**
- **BH1750 fényszenzor**
- **DHT11 hőmérséklet- és páratartalom-érzékelő**
- **LED-ek:** Sárga, Zöld, Piros
- **Hangjelző (buzzer)**
- **Huzalok és ellenállások**

## Szoftverkomponensek

1. **Könyvtárak:**
   - `Wire.h`: BH1750 kommunikációhoz.
   - `BH1750.h`: Fényszenzor vezérléséhez.
   - `DHT.h`: Hőmérséklet- és páratartalom-érzékeléshez.
   - `BlynkSimpleEsp32.h`: Blynk platform támogatáshoz.

2. **Wi-Fi beállítások:**
   - SSID: ********
   - Jelszó: *********

3. **Blynk azonosítás:**
   - Template ID: **********
   - Template Name: Teszt
   - Auth Token: ***************

## Működés

1. **Indítás:**
   - Az ESP32 csatlakozik a Wi-Fi hálózathoz.
   - Inicializálja a szenzorokat (BH1750 és DHT11).

2. **Adatgyűjtés:**
   - A BH1750 méri a környezeti fényerőt, a DHT11 pedig a hőmérsékletet és páratartalmat.

3. **Fényintenzitás alapú visszajelzés:**
   - A LED-ek és a buzzer állapota a mért lux értéktől függ.

4. **Blynk kommunikáció:**
   - Az ESP32 folyamatosan frissíti az adatokat a Blynk felületére.

## Kódrészletek magyarázata

### Fényintenzitás LED és buzzer vezérlése

```cpp
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
  tone(BUZZER, 4000);
  delay(1000);
  noTone(BUZZER);
}
```

### Adatok feltöltése a Blynk platformra

```cpp
Blynk.virtualWrite(V21, lux);
Blynk.virtualWrite(V22, luxThresholdExceeds);
Blynk.virtualWrite(V33, luxThresholdExceeds > 0 ? totalExceedTime / luxThresholdExceeds / 1000 / 60 : 0);
Blynk.virtualWrite(V34, temp);
Blynk.virtualWrite(V35, hum);
```

A FlowerGuard 2000 ideális társ lehet a növények gondozásában, automatizált figyelmeztetésekkel és valós idejű adatmegosztással!

