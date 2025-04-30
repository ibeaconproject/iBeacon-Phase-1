#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEBeacon.h>
#include <BLEAdvertising.h>

// Define beacon parameters
#define BEACON_UUID "12345678-1234-5678-1234-56789abcdef0" // Replace with your UUID
#define BEACON_MAJOR 1000
#define BEACON_MINOR 2000
#define BEACON_TX_POWER 0xC5  // Calibrated Tx Power at 1m

void setup() {
  Serial.begin(115200);
  Serial.println("Starting iBeacon...");

  // Initialize BLE
  BLEDevice::init("");

  // Create iBeacon object
  BLEBeacon beacon;
  beacon.setManufacturerId(0x004C);  // Apple's manufacturer ID
  beacon.setProximityUUID(BLEUUID(BEACON_UUID));
  beacon.setMajor(BEACON_MAJOR);
  beacon.setMinor(BEACON_MINOR);
  beacon.setSignalPower(BEACON_TX_POWER);

  // Configure advertising data
  BLEAdvertisementData advertisementData;
  advertisementData.setFlags(0x04);  // BR_EDR_NOT_SUPPORTED
  advertisementData.setManufacturerData(beacon.getData());

  // Start advertising
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->setAdvertisementData(advertisementData);
  advertising->setScanResponse(false);
  advertising->setMinPreferred(0x06);  // Power management
  advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("iBeacon started!");
}

void loop() {
  // Nothing to do here
}
