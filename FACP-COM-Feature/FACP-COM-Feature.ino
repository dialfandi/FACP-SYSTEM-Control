#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Konfigurasi WiFi & MQTT
const char* ssid = "";        
const char* password = ""; 
const char* mqttServer = "";
const int mqttPort = 1883;
const char* mqttUsername = "";
const char* mqttPassword = "";
const char* mqttTopic = ""; 

WiFiClient espClient;
PubSubClient client(espClient);

// RFID
#define SS_PIN 5
#define RST_PIN 22
#define RELAY_PIN 4

// Konfigurasi Serial2 untuk komunikasi dengan STM32F1
#define RXD2 16  // RX pin (koneksi dari TX STM32)
#define TXD2 17  // TX pin (koneksi ke RX STM32)

// Konstanta paket data
const uint8_t PACKET_SIZE = 19;
const uint8_t HEADER_VALUE = 0xFF;
const uint8_t FOOTER_VALUE = 0xFE;

uint8_t rx_buffer[PACKET_SIZE];
uint8_t packet_idx = 0;
uint8_t is_receiving_packet = 0;

// Buffer data
uint8_t data_packet[PACKET_SIZE];
uint8_t s_data1[16];
uint8_t sensingMode;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    SPI.begin();

    pinMode(RST_PIN, OUTPUT);
    digitalWrite(RST_PIN, HIGH);
    
    mfrc522.PCD_Init();
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    // Koneksi WiFi & MQTT
    WiFi.begin(ssid, password);
    Serial.println("Mencoba koneksi WiFi di background...");
    client.setServer(mqttServer, mqttPort);
    client.connect("ESP32Client", mqttUsername, mqttPassword);
    Serial.println("Mencoba koneksi MQTT di background...");

    Serial.println("ESP32 Receiver Ready...");
}

void loop() {
    checkWiFi();
    checkMQTT();
    checkRFID();
    receiveData();
}

// Fungsi cek WiFi
void checkWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi terputus! Mencoba reconnect...");
        WiFi.begin(ssid, password);
    }
}

// Fungsi cek MQTT
void checkMQTT() {
    if (!client.connected()) {
        Serial.print("Menghubungkan ke MQTT...");
        if (client.connect("ESP32Client", mqttUsername, mqttPassword)) {
            Serial.println(" Berhasil terhubung!");
        } else {
            Serial.println(" Gagal! Coba lagi...");
        }
    }
    client.loop();
}

void receiveData() {
    while (Serial2.available()) {
        uint8_t byteRead = Serial2.read();

        if (!is_receiving_packet) {
            // Cari HEADER
            if (byteRead == HEADER_VALUE) {
                is_receiving_packet = 1;
                packet_idx = 0;
                rx_buffer[packet_idx++] = byteRead; // Simpan HEADER
            }
            // Jika belum ketemu HEADER, abaikan byte
        } else {
            // Sedang dalam proses terima paket
            rx_buffer[packet_idx++] = byteRead;

            if (packet_idx >= PACKET_SIZE) {
                // Paket lengkap diterima, cek FOOTER
                if (rx_buffer[PACKET_SIZE - 1] == FOOTER_VALUE) {
                    // Paket valid
                    memcpy(data_packet, rx_buffer, PACKET_SIZE); // Copy ke paket final
                    parseDataPacket();  // Proses data
                    uploadToMQTT();     // Kirim ke MQTT
                } else {
                    // Paket tidak valid, print debug
                    Serial.println("Invalid Packet (Footer Mismatch)!");
                    Serial.print("Received Data: ");
                    for (uint8_t i = 0; i < PACKET_SIZE; i++) {
                        Serial.print("0x");
                        if (rx_buffer[i] < 0x10) Serial.print("0");
                        Serial.print(rx_buffer[i], HEX);
                        Serial.print(" ");
                    }
                    Serial.println();
                }
                // Reset untuk terima paket baru
                is_receiving_packet = 0;
                packet_idx = 0;
            }
        }
    }
}

// Fungsi parsing paket data ke array s_data1
void parseDataPacket() {
    sensingMode = data_packet[1];
    memcpy(s_data1, &data_packet[2], 16);
    
    Serial.println("Valid Packet Received and Parsed:");
    Serial.print("Sensing Mode: "); Serial.println(sensingMode);
    
    Serial.println("Data (s_data1[16]):");
    for (int i = 0; i < 16; i++) {
        Serial.printf("Data [%d]: %d\n", i, s_data1[i]);
    }
    Serial.println("==================================");
}

// Fungsi upload data ke MQTT
void uploadToMQTT() {
    char payload[5];

    for (int j = 0; j < 16; j++) {
        char topic[20];
        sprintf(topic, "FACP CH %d", j + 1);
        sprintf(payload, "%d", s_data1[j]);
        client.publish(topic, payload);
        Serial.printf("Mengirim %d ke %s\n", s_data1[j], topic);
    }

    // Kirim sensingMode ke MQTT
    client.publish("FACP Sensing Mode", String(sensingMode).c_str());
    Serial.printf("Mengirim Sensing Mode: %d ke FACP Sensing Mode\n", sensingMode);
}

// Fungsi reset RFID jika freeze
void resetRFID() {
    Serial.println("RFID mengalami freeze! Mereset RFID...");
    digitalWrite(RST_PIN, LOW);
    delay(10);
    digitalWrite(RST_PIN, HIGH);
    delay(50);
    mfrc522.PCD_Init();
}

// Fungsi cek RFID
void checkRFID() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

    Serial.print("UID Kartu: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    if (isAuthorizedCard(mfrc522.uid.uidByte)) {
        Serial.println("Akses Diterima! Membuka door lock...");
        digitalWrite(RELAY_PIN, HIGH);
        delay(5000);
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Door lock terkunci kembali.");
    } else {
        Serial.println("Akses Ditolak!");
    }

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}

// Fungsi cek kartu RFID sesuai database
bool isAuthorizedCard(byte *uid) {
    const byte authorizedUIDs[][4] = {
        {0x82, 0xBA, 0x28, 0x03}, {0x8E, 0xF3, 0xA8, 0x9F}, {0xB9, 0x05, 0xA9, 0x9F},
        {0x57, 0x2F, 0xA9, 0x9F}, {0x30, 0x5C, 0xB2, 0x9F}, {0x4B, 0xC1, 0xA8, 0x9F}
    };
    const int numAuthorizedCards = sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]);

    for (int i = 0; i < numAuthorizedCards; i++) {
        if (memcmp(uid, authorizedUIDs[i], 4) == 0) return true;
    }
    return false;
}
