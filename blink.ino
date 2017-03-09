int WAITFOR = 500;

void setup(){
   pinMode(15, OUTPUT); 
}

void loop(){

   digitalWrite(15, HIGH);
   delay(WAITFOR);
   digitalWrite(15, LOW);
   delay(WAITFOR);

}
