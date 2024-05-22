#include "AdafruitIO_WiFi.h"

#include "Secrets.h"


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Create feed objects
AdafruitIO_Feed *SliderPadTestValue = io.feed("SliderPadTestValue");

void setup() {
  // Start the serial connection
  Serial.begin(115200);
  
  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
  // Wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  // We are connected
  Serial.println();
  Serial.println(io.statusText());
  
  // Set up a message handler for the 'humidity' feed.

}

void loop() {
  // Ensure Adafruit IO connection is active
  io.run();
  
  
  // Send the data to Adafruit IO
  SliderPadTestValue->save(rand() % 100);
  
  // Print the values to the Serial Monitor
  
  // Delay before sending the next value
  delay(10000); // 10 seconds
}
