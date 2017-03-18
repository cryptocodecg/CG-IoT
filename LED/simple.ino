/*
Enter - Exit

Public Domain
September 2016
Budi Rahardjo (@rahard)

*/

// pin configuration for DycodeX ESPectro board
//int led[] = {15, 2, 0, 4, 5, 3};
// pin configuration for Arduino UNU board
//int led[] = {13, 12, 11, 10, 9, 8};
int led[] = {6, 8, 10, 2, 0, 4};

int x[] = {0, 0, 0, 0, 0, 0};
int NUMLED = 6; // number of LEDS
int WAITFOR = 100;
int i;

void setup() {
   // setup pins for output and reset low
   //for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
   pinMode(2, OUTPUT);
}

void display() { for (i=0; i < NUMLED ; i++) {
      digitalWrite(led[i], x[i]);
   }
}

void loop() {
   digitalWrite(2, LOW);
}
