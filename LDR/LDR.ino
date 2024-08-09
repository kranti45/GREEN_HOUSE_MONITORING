const int LDR = A0; // Defining LDR PIN
int input_val = 0; // Varible to store Input values

int LED=16;

void setup() {
Serial.begin(9600);
pinMode(LDR,INPUT);
pinMode(LED,OUTPUT);
}

void loop() {
input_val = analogRead(LDR); // Reading Input
Serial.print("LDR value is : " );
Serial.println(input_val); // Writing input on serial monitor.
delay(1000);
if (analogRead(LDR) <1000){
digitalWrite(LED,HIGH);
}
else
{
digitalWrite(LED,LOW);
}

}
