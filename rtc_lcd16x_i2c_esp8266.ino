/*
🔹 2. Wiring ESP8266 ke RTC DS1307 & LCD I2C
Komponen	ESP8266 (NodeMCU/Wemos D1 Mini)	Pin Modul
RTC DS1307		
VCC	3.3V / Vin	VCC
GND	GND	GND
SDA	GPIO4 (D2)	SDA
SCL	GPIO5 (D1)	SCL
LCD I2C		
VCC	3.3V / Vin	VCC
GND	GND	GND
SDA	GPIO4 (D2)	SDA
SCL	GPIO5 (D1)	SCL
📌 Jika LCD hanya mendukung 5V, gunakan Level Shifter atau cek apakah bekerja di 3.3V.

salam hangat dari comunity PusatTerbuka dan Author
*/
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_PCF8574.h>

// Atur alamat I2C
RTC_DS1307 rtc;
LiquidCrystal_PCF8574 lcd(0x26);  // Sesuaikan dengan alamat LCD

void setup() {
    Serial.begin(115200);
    Wire.begin(4, 5);  // SDA = GPIO4 (D2), SCL = GPIO5 (D1)

    // Inisialisasi LCD
    lcd.begin(16, 2);
    lcd.setBacklight(255);

    // Cek RTC
    if (!rtc.begin()) {
        Serial.println("RTC tidak ditemukan!");
        lcd.setCursor(0, 0);
        lcd.print("RTC ERROR!");
        while (1);
    }

    if (!rtc.isrunning()) {
        Serial.println("RTC tidak berjalan, mengatur waktu...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set waktu sesuai waktu komputer saat upload
    }
}

void loop() {
    DateTime now = rtc.now();

    // Format waktu
    char buffer[20];
    sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

    // Tampilkan di LCD
    lcd.setCursor(0, 0);
    lcd.print("Waktu:");
    lcd.setCursor(0, 1);
    lcd.print(buffer);

    // Tampilkan di Serial Monitor
    Serial.print("Waktu: ");
    Serial.println(buffer);

    delay(1000);
}
