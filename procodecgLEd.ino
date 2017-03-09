/* NodeMCU + procodeCG LED */

int led[] = {14, 12, 13, 15, 3, 1};
int NUMLED = 6; // number of LEDS
int WAITFOR = 50;
int LEDON=0;
int direction=1;
int i;

void setup(){
   for (i=0; i<NUMLED; i++) { pinMode(led[i], OUTPUT); }
}

void loop(){
   for (i=0; i<NUMLED; i++) { digitalWrite(led[i], LOW); }

   digitalWrite(led[LEDON], HIGH);
   delay(WAITFOR);

   LEDON = LEDON + direction;
   if (LEDON>=NUMLED) {
     direction = -1;
     LEDON = NUMLED-1;
   }

   if (LEDON<0) {
     direction = 1;
     LEDON = 0;
   }
}
