#include <Wire.h>
#include <MPU6050.h>
#include <RemoteXY.h>

// RemoteXY connection configuration for ESP32 BLE
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define REMOTEXY_BLUETOOTH_NAME "KikTek_Device"

// RemoteXY UI configuration generated from RemoteXY editor
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = 
  { 255,4,0,0,0,32,1,8,0,1,
  1,24,23,12,12,2,31,31,79,78,
  0,79,70,70 }; // Basic UI configuration (can be customized in RemoteXY)
#pragma pack(pop)

struct {
  uint8_t switch_1;
} RemoteXY;

MPU6050 mpu;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Initialize RemoteXY Bluetooth interface
  RemoteXY_Init();

  // Initialize MPU6050 gyroscope sensor
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 successfully connected.");
  } else {
    Serial.println("MPU6050 connection failed.");
  }
}

void loop() {
  RemoteXY_Handler(); // Handle communication with RemoteXY app

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read accelerometer and gyroscope data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Print gyroscope data to serial monitor (for testing/logging)
  Serial.print("Gyro X: "); Serial.print(gx);
  Serial.print(" | Gyro Y: "); Serial.print(gy);
  Serial.print(" | Gyro Z: "); Serial.println(gz);

  delay(200); // Short delay to avoid flooding output
}
