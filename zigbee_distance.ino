#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LED 9
int maximumRange= 200; // Maximum range needed
int minimumRange= 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
float outputValue= 0.0;
void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
if (distance >= maximumRange|| distance <= minimumRange){
Serial.println("0");
} 
else if(distance <=100 && distance >minimumRange)
{
  Serial.println("1");
  analogWrite(LED,255);
  delay(100);
  analogWrite(LED,0);
  delay(100);
}
else {
Serial.println("0");
//outputValue= map(distance,0,200,0,255);
//analogWrite(LED,outputValue);
}
delay(40);
}
