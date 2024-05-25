#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define RFID_SDA_PIN 10
#define RFID_RST_PIN 9
#define SERVO_PIN 8
#define BUZZER_PIN 6
#define GROUND_PIN 7  // Pin to act as ground

MFRC522 mfrc522(RFID_SDA_PIN, RFID_RST_PIN); // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);          // Set the LCD address to 0x27 for a 16 chars and 2 line display
Servo servo;

const String desiredTag = "01020304"; // Desired RFID tag UID

void setup() {
    Serial.begin(9600);         // Initialize serial communications with the PC
    SPI.begin();                // Init SPI bus
    mfrc522.PCD_Init();         // Init MFRC522 card

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Use keycard!");

    servo.attach(SERVO_PIN);
    servo.write(0);  // Ensure the servo starts at 0 degrees

    pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as an output
    pinMode(GROUND_PIN, OUTPUT); // Set the ground pin as an output
    digitalWrite(GROUND_PIN, LOW); // Set the ground pin to LOW, acting as ground
}

void loop() {
    // Check for the presence of a new card
    if (card_detection()) {
        // Show UID on serial monitor
        String tag = get_card_id();
        // Check if the read RFID tag matches the desired tag
        if (is_desired_tag(tag)) {
            effect_desired_tag();
            tone(BUZZER_PIN, 1000, 750); // Play a 1000 Hz tone for 750 ms
            servo.write(90);  // Rotate servo to 90 degrees
            delay(3000);      // Wait for 3 seconds
            servo.write(0);   // Rotate servo back to 0 degrees
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Use keycard!");
        } else {
            effect_denied_tag();
            tone(BUZZER_PIN, 400, 750); // Play a 400 Hz tone for 500 ms
            delay(2000); // Display "Denied access!" for 2 seconds
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Use keycard!");
        }
    }
}

bool card_detection() {
    return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}

bool is_desired_tag(String tag) {
    return tag == desiredTag;
}

String get_card_id() {
    Serial.print("UID tag : ");
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase(); // Convert content to uppercase
    Serial.println(content);
    return content;
}

void effect_desired_tag() {
    Serial.println("Opened door!");
    lcd.clear();
    lcd.setCursor(3, 0); // Center "Opened door!" on the display
    lcd.print("Opened door!");
}

void effect_denied_tag() {
    Serial.println("Denied access!");
    lcd.clear();
    lcd.setCursor(1, 0); // Center "Denied access!" on the display
    lcd.print("Denied access!");
}
