#include <RCSwitch.h>
//joystick values
#define UP_X 1023
#define UP_Y 511
#define DOWN_X 0
#define DOWN_Y 511
#define RIGHT_X 511
#define RIGHT_Y 1023
#define LEFT_X 511
#define LEFT_Y 0
#define JOYSTICK_DEVIATION 50

//joistick anlogs enters
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_MS A2

typedef enum Directions{
  UP,
  DOWN,
  RIGHT,
  LEFT,
  ILEGAL
} Directions;




Directions getDirection(int x,int y);


Directions getDirection(int x,int y){
  if ((x >= UP_X - JOYSTICK_DEVIATION && x <= UP_X) && (y >= UP_Y - JOYSTICK_DEVIATION && y <= UP_Y) + JOYSTICK_DEVIATION){
    return Directions::UP;
  }
  else if ((x >= DOWN_X && x <= DOWN_X + JOYSTICK_DEVIATION) && (y >= DOWN_Y - JOYSTICK_DEVIATION && y <= DOWN_Y + JOYSTICK_DEVIATION)){
    return Directions::DOWN;
  }
  else if ((x >= RIGHT_X - JOYSTICK_DEVIATION && x <= RIGHT_X + JOYSTICK_DEVIATION) && (y >= RIGHT_Y - JOYSTICK_DEVIATION && y <= RIGHT_Y)){
    return Directions::RIGHT;
  }
  else if ((x >= LEFT_X - JOYSTICK_DEVIATION && x <= LEFT_X + JOYSTICK_DEVIATION ) && (y >= LEFT_Y && y <= LEFT_Y + JOYSTICK_DEVIATION)){
    return Directions::LEFT;
  }
  else {
    return Directions::ILEGAL;
  }
}

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
RCSwitch mySwitch = RCSwitch();

void setup()
{
  Serial.begin(9600);
  
  mySwitch.enableTransmit(10);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_MS, INPUT_PULLUP);
}

void loop()
{
  xPosition = analogRead(JOYSTICK_X);
  yPosition = analogRead(JOYSTICK_Y);
  SW_state = digitalRead(JOYSTICK_MS);

  switch (getDirection(xPosition, yPosition)){
    case Directions::UP:
      mySwitch.send(1, 3);
      Serial.println("up");
      break;
    case Directions::DOWN:
      mySwitch.send(2,  3);
      Serial.println("down");
      break;
    case Directions::RIGHT:
      mySwitch.send(3,  3);
      Serial.println("right");
      break;
    case Directions::LEFT:
      mySwitch.send(4,  3);
      Serial.println("left");
      break;
    case Directions::ILEGAL:
      mySwitch.send(5,  3);
      Serial.println("ILEGAL");
      break;
  }
  delay(1000);  
  
  Serial.print("x: ");
  Serial.println(xPosition);
  Serial.print("y: ");
  Serial.println(yPosition);

  Serial.print(" | Button: ");
  Serial.println(SW_state);

  delay(1000);
}
