const int buttonPin = 7;    
const int ledPin =  13;      
const int positionPin = A0;
const int motor1Pin = 9;
const int motor2Pin = 10;

const int onValue  = 345;
const int offValue = 765; 

int buttonState = 0;        
int movementState = 0;
int isMoving = 0;

int pos = 0;    

void setup() {
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT);     
  pinMode(positionPin, INPUT);
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  pos = analogRead(positionPin);
  if(movementState == 0){
    moveArm(offValue);
    digitalWrite(ledPin, HIGH);
  }else{
    moveArm(onValue);
    digitalWrite(ledPin, LOW);
  }
  Serial.println(pos);
  delay(2);
 
  handleButton();
}

void handleButton()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if(movementState == 0){
      movementState = 1;
    }else{
      movementState = 0;
    }
    delay(300);
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }
}

void foward(int value)
{
  analogWrite(motor1Pin, value);
  analogWrite(motor2Pin, 0);
}

void reverse(int value)
{
  analogWrite(motor1Pin, 0);
  analogWrite(motor2Pin, value);
}

void despin(boolean useBrake = true)
{
  if(useBrake){
    digitalWrite(motor1Pin, HIGH);
    digitalWrite(motor2Pin, HIGH);
  }else{
    digitalWrite(motor1Pin, LOW);
    digitalWrite(motor2Pin, LOW);
  }
}

void moveArm(int dest){
  int diff = pos - dest;
  int aDiff = abs(diff);
  if(aDiff < 5){
    despin(true);
    return;
  }
  
  int velocity = 100 + map(aDiff, 0, 800, 0, 185);
  if(diff > 0){
    reverse(velocity);
  }else if(diff < 0){
    foward(velocity);
  }
}
