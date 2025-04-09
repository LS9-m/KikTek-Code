
// KikTek Prototype Code - Gyroscope + RemoteXY Integration
// Developed for ESP32 with MPU6050 and RemoteXY Dashboard
// Author: SportNology Team

#include <Wire.h>
#include <MPU6050.h>
#include <WiFi.h>
#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_WIFI_SSID "KikTek_WIFI"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

// RemoteXY GUI configuration
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = {
  255,1,0,0,0,58,0,16,13,1,
  1,1,22,20,20,6,2,26,31,31
};
struct {
  int8_t gyroX;
  int8_t gyroY;
  int8_t gyroZ;
} RemoteXY;
#pragma pack(pop)

// MPU6050 initialization
MPU6050 gyro;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  RemoteXY_Init();

  gyro.initialize();
  if (!gyro.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  Serial.println("KikTek Initialized: Gyroscope + RemoteXY");
}

void loop() {
  RemoteXY_Handler();

  int16_t gx, gy, gz;
  gyro.getRotation(&gx, &gy, &gz);

  // Scale values for display (adjust if needed)
  RemoteXY.gyroX = gx / 100;
  RemoteXY.gyroY = gy / 100;
  RemoteXY.gyroZ = gz / 100;

  // Debug output
  Serial.print("Gyro X: "); Serial.print(RemoteXY.gyroX);
  Serial.print(" | Y: "); Serial.print(RemoteXY.gyroY);
  Serial.print(" | Z: "); Serial.println(RemoteXY.gyroZ);

  delay(200);
}
