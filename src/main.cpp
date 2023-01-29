#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

uint16_t send_data[] = {4095, 1001, 0, 1995, 4095};
size_t send_size = sizeof(send_data);
uint8_t recv_data[5] = {0}; // initialises all elements to zero

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32greg"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
    // Client sends data continuously unless serial.available()=true, i.e. data is available to receive
    if (SerialBT.available()) {
        Serial.println("Data available!");
    } else {
        Serial.println("Sending data:");
        Serial.write(reinterpret_cast<uint8_t*>(send_data), send_size);
        Serial.println("\n");
        SerialBT.write(reinterpret_cast<uint8_t*>(send_data), send_size);
    }
    // SerialBT.println("Hi there");
    delay(1000);
}