#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Initialize I2C LCD (20x4)
LiquidCrystal_I2C lcd(0x27, 20, 4); // Address may vary (0x27 or 0x3F)

// GSM module connected to Arduino's RX and TX
SoftwareSerial gsmSerial(0, 1); // RX, TX

// Button pin
const int resetButton = 2;

// Vote counters
int voteA = 0;
int voteB = 0;
int voteC = 0;
int voteD = 0;

void setup() {
  // Initialize I2C LCD
  lcd.begin();
  lcd.backlight();
  lcd.print("Electronic Voting");
  lcd.setCursor(0, 1);
  lcd.print("System Ready!");
  delay(2000);
  lcd.clear();

  // Initialize GSM module
  gsmSerial.begin(9600);
  delay(1000);
  lcd.print("Initializing GSM...");
  delay(2000);
  lcd.clear();

  // Initialize reset button
  pinMode(resetButton, INPUT_PULLUP);

  // Set GSM to text mode
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  gsmSerial.println("AT+CNMI=2,2,0,0,0"); // Set GSM to notify on new SMS
  delay(1000);
}

void loop() {
  // Check for new SMS
  if (gsmSerial.available()) {
    String sms = gsmSerial.readString();
    processSMS(sms);
  }

  // Display voting results on LCD
  displayResults();

  // Reset votes if button is pressed
  if (digitalRead(resetButton) == LOW) {
    resetVotes();
    lcd.clear();
    lcd.print("Votes Reset!");
    delay(2000);
    lcd.clear();
  }
}

void processSMS(String sms) {
  // Check if the SMS contains a valid vote
  if (sms.indexOf("VOTE A") != -1) {
    voteA++;
    lcd.clear();
    lcd.print("Vote for A Received");
    delay(1000);
  } else if (sms.indexOf("VOTE B") != -1) {
    voteB++;
    lcd.clear();
    lcd.print("Vote for B Received");
    delay(1000);
  } else if (sms.indexOf("VOTE C") != -1) {
    voteC++;
    lcd.clear();
    lcd.print("Vote for C Received");
    delay(1000);
  } else if (sms.indexOf("VOTE D") != -1) {
    voteD++;
    lcd.clear();
    lcd.print("Vote for D Received");
    delay(1000);
  }
}

void displayResults() {
  lcd.setCursor(0, 0);
  lcd.print("Results:");
  lcd.setCursor(0, 1);
  lcd.print("A: ");
  lcd.print(voteA);
  lcd.setCursor(10, 1);
  lcd.print("B: ");
  lcd.print(voteB);
  lcd.setCursor(0, 2);
  lcd.print("C: ");
  lcd.print(voteC);
  lcd.setCursor(10, 2);
  lcd.print("D: ");
  lcd.print(voteD);
}

void resetVotes() {
  voteA = 0;
  voteB = 0;
  voteC = 0;
  voteD = 0;
}