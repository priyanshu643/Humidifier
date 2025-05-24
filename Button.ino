// Pin assignments
const int buttonPin = 3;          // Pushbutton connected to digital pin 3
const int ledPin = 9;             // LED connected to digital pin 9
const int humidifierPin = 8;      // Humidifier relay/module connected to digital pin 8

// State variables
bool isHumidifierOn = false;      // Keeps track of whether the humidifier is on or off
int previousButtonState = LOW;    // Stores the last button state to detect button press

void setup() {
  // Set up pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(humidifierPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Start serial communication for receiving commands
  Serial.begin(9600);

  // Make sure the device starts in a known state
  updateDeviceState();
}

void loop() {
  // Check if any data is available over Serial
  if (Serial.available() > 0) {
    char receivedCommand = Serial.read();  // Read the incoming character

    // Turn on or off the humidifier based on received command
    if (receivedCommand == '1') {
      isHumidifierOn = true;
    } else if (receivedCommand == '0') {
      isHumidifierOn = false;
    }

    // Update the actual device state to match the command
    updateDeviceState();
  }

  // Read the current state of the button
  int currentButtonState = digitalRead(buttonPin);

  // Detect button press (rising edge: from LOW to HIGH)
  if (previousButtonState == LOW && currentButtonState == HIGH) {
    isHumidifierOn = !isHumidifierOn;  // Toggle humidifier state
    updateDeviceState();               // Apply the new state
    delay(50);                         // Simple debounce delay
  }

  // Save the current button state for next loop iteration
  previousButtonState = currentButtonState;
}

// This function updates the LED and humidifier based on the current state
void updateDeviceState() {
  if (isHumidifierOn) {
    digitalWrite(humidifierPin, HIGH);  // Turn on humidifier
    digitalWrite(ledPin, HIGH);         // Turn on LED
  } else {
    digitalWrite(humidifierPin, LOW);   // Turn off humidifier
    digitalWrite(ledPin, LOW);          // Turn off LED
  }
}
