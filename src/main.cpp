#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <MPU6050.h>

// WiFi (Wokwi uses open WiFi)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ThingsBoard server
String serverName = "http://eu.thingsboard.cloud/api/v1/398ivt80xy0LTwezhuKC/telemetry";

MPU6050 mpu;

void setup() {

  Serial.begin(115200);
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);   // stop execution
  }

  Serial.println("MPU6050 Connected");

  // Connect WiFi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    // Read sensor data
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Convert to real units
    float accX = ax / 16384.0;
    float accY = ay / 16384.0;
    float accZ = az / 16384.0;

    float gyroX = gx / 131.0;
    float gyroY = gy / 131.0;
    float gyroZ = gz / 131.0;

    // Riding behaviour detection
int hard_brake = 0;
int sudden_acceleration = 0;
int sharp_turn = 0;
int pothole = 0;

// Pothole - triggers when Z slider near max
if(accZ > 1.8){
  pothole = 1;
}

// Hard braking - triggers when Y slider near -max  
if(accY < -1.8){
  hard_brake = 1;
}

// Sudden acceleration
if(accY > 1.8){
  sudden_acceleration = 1;
}

// Sharp turn (keep as is, already working)
if(abs(gyroZ) > 150){
  sharp_turn = 1;
}
    // Create JSON telemetry
   String payload = "{";
payload += "\"acc_x\":" + String(accX) + ",";
payload += "\"acc_y\":" + String(accY) + ",";
payload += "\"acc_z\":" + String(accZ) + ",";
payload += "\"gyro_x\":" + String(gyroX) + ",";
payload += "\"gyro_y\":" + String(gyroY) + ",";
payload += "\"gyro_z\":" + String(gyroZ) + ",";
payload += "\"hard_brake\":" + String(hard_brake) + ",";
payload += "\"sudden_acceleration\":" + String(sudden_acceleration) + ",";
payload += "\"sharp_turn\":" + String(sharp_turn) + ",";
payload += "\"pothole\":" + String(pothole);
payload += "}";
    // Send data to ThingsBoard
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(payload);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    Serial.println("Data Sent:");
    Serial.println(payload);

    http.end();
  }

  delay(2000);
}