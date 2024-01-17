#include <IRremote.h>
#include <LiquidCrystal.h>
#include "Definitions.h"

// lcd
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const unsigned long inputInterval = 1000; // Input interval in milliseconds
unsigned long lastInputTime = 0;

void setup()
{
  pinMode(3, INPUT);

  lcd.begin(16, 2);
  // lcd.print("Arduino Ready!  ");
  lcd.print("Arduino Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Start the music!");
  lcd.setCursor(0, 0);

  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.begin(9600);
}

int thing = NONE;

void loop()
{
  int sensorReading = analogRead(A0);
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);

  if (millis() - lastInputTime >= inputInterval)
  {
    if (IrReceiver.decode())
    {
      IrReceiver.resume();
      int command = IrReceiver.decodedIRData.command;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.noAutoscroll();
      switch (command)
      {
      case IR_FASTFW:
        send(thing, IR_FASTFW);
        break;
      case IR_REWIND:
        send(thing, IR_REWIND);
        break;
      case IR_PLAY_PAUSE:
        send(thing, IR_PLAY_PAUSE);
        break;
      default:
        Serial.println("Not configured");
        thing = NONE;
        break;
      }
    }
    lastInputTime = millis();
  }

  if (Serial.available() > 0)
  {
    switch (thing)
    {
    case IR_FASTFW:
      now_playing();
      break;
    case IR_REWIND:
      now_playing();
      break;
    case IR_PLAY_PAUSE:
      play_pause();
      break;
    default:
      Serial.println("nothing");
      break;
    }
    thing = NONE;
  }
}

void send(int &button, int ir)
{
  Serial.println(ir);
  button = ir;
}
void play_pause()
{
  read_msg();
}

void now_playing()
{
  // diff both into saying previous track/ skipped track : now playing
  lcd.print("Now Playing");
  lcd.setCursor(0, 1);
  read_msg();
}

void read_msg()
{
  int len = 0;
  while (Serial.available() > 0)
  {
    char incomingByte = Serial.read();
    len += 1;
    lcd.print(incomingByte);
    delay(DELAY);
  }
}