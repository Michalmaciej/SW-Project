#define i0 A2
#define i1 12
#define i2 11
#define i3 10
#define i4 9
#define i5 8
#define i6 A3
#define i7 A4
#define o0 7
#define o1 6
#define o2 5
#define o3 4
#define o4 3
#define o5 2
#define o6 A0
#define o7 A1
#define k13 13

void setup() {

 pinMode(k13, OUTPUT);
 pinMode(i0, INPUT);
 pinMode(i1, INPUT);
 pinMode(i2, INPUT);
 pinMode(i3, INPUT);
 pinMode(i4, INPUT);
 pinMode(i5, INPUT);
 pinMode(i6, INPUT);
 pinMode(i7, INPUT);
 pinMode(o0, OUTPUT);
 pinMode(o1, OUTPUT);
 pinMode(o2, OUTPUT);
 pinMode(o3, OUTPUT);
 pinMode(o4, OUTPUT);
 pinMode(o5, OUTPUT);
 pinMode(o6, OUTPUT);
 pinMode(o7, OUTPUT);
}

char LED; // LED na pĹytce ARDUINO
unsigned long stime;

char KZ1,KZ2,KZ3,KZ4;
char P1,P2,P3,P4;
char PGA,PDA;
char LED1,LED2,LED3,LED4;


//////////////////////////////////////////////////////////////////
// deklaracje uĹźytkownika

char P1_P=0;
char P2_P=0;
char P3_P=0;
char P4_P=0;
char stan=1;
int tim=0;
char ST_LED1=1;
char ST_LED2=1;
char ST_LED3=1;
char ST_LED4=1;


/////////////////////////////////////////////////////////////////


void loop() {
 stime=millis();

 // odczyt wejĹÄ 
 P1=!digitalRead(i0);
 P2=!digitalRead(i1);
 P3=!digitalRead(i2);
 P4=!digitalRead(i3);
 KZ1=!digitalRead(i4);
 KZ2=!digitalRead(i5);
 KZ4=!digitalRead(i6);
 KZ3=!digitalRead(i7);



///////////////////////////////////////////////////////////////
// kod uĹźytkownika
// UWAGA: pÄtla pracuje z cyklem 10ms (dla 1s wartoĹÄ timera powinna wynosiÄ 100)


switch (ST_LED1) {
    case 1: P1_P = 0; LED1 = 0;
        if ( P1 ) ST_LED1 = 2;
        break;
    case 2: P1_P = 1; LED1 = 1;
        if ( KZ1 ) ST_LED1 = 1;
        break;
}

switch (ST_LED2) {
    case 1: P2_P = 0; LED2 =0;
        if ( P2 ) ST_LED2=2;
        break;
    case 2: P2_P = 1; LED2 = 1;
        if ( KZ2 ) ST_LED2 = 1;
        break;
}

switch (ST_LED3) {
    case 1: P3_P = 0; LED3 = 0;
        if ( P3 ) ST_LED3 = 2;
        break;
    case 2: P3_P = 1; LED3 = 1;
        if ( KZ3 ) ST_LED3 = 1;
        break;
}

switch (ST_LED4) {
    case 1: P4_P = 0; LED4 = 0;
        if ( P4 ) ST_LED4 = 2;
        break;
    case 2: P4_P = 1; LED4 = 1;
        if ( KZ4 ) ST_LED4 = 1;
        break;
}

switch (stan) {

        case 1: PGA = 0; PDA = 0;
            if ( P2_P && !tim ) stan = 2;
            else if ( !P2_P && ( P3_P || P4_P ) && !tim) stan = 3;
            break;
        case 2: PGA = 1; PDA = 0; 
            if ( KZ2 ) { tim = 300; stan = 4; }   
            break;
         case 3: PGA=1; PDA=0;
            if ( KZ2 ) stan = 4; 
            break;

        case 4: PGA = 0; PDA = 0;
            if ( P1_P && !tim ) stan = 5;
            else if ( !P1_P && P3_P && !tim ) stan = 6;
            else if ( !P1_P && !P3_P && P4_P && !tim) stan=7;
            break;
        case 5: PGA = 0; PDA = 1; 
            if ( KZ1 ) { tim = 300; stan = 1; }
            break;
        case 6: PGA = 1; PDA = 0; 
            if ( KZ3 ) { tim = 300; stan = 8; }
            break;
        case 7: PGA = 1; PDA = 0;
            if ( KZ3 ) stan = 8; 
            break;

        case 8: PGA = 0; PDA = 0;
            if ( P4_P && !tim ) stan = 9;
            else if ( !P4_P && P2_P && !tim ) stan = 10;
            else if (P1_P && !P2_P && !P4_P && !tim) stan=11;
            break;
        case 9: PGA = 1; PDA = 0; 
            if ( KZ4 ) { tim = 300; stan = 12; }
            break;
        case 10: PGA = 0; PDA = 1; 
            if ( KZ2 ) { tim = 300; stan = 4; }
            break;
        case 11: PGA = 0; PDA = 1;
            if ( KZ2 ) stan = 4;
            break;

        case 12: PGA = 0; PDA = 0;
            if ( P3_P && !tim ) stan = 13;
            else if ( (P1_P || P2_P) && !P3_P && !tim) stan = 14;
            break;
        case 13: PGA = 0; PDA = 1; 
            if ( KZ3 ) { tim = 300; stan = 8; }
            break;
        case 14: PGA = 0; PDA = 1;
            if ( KZ3 ) stan = 8;
            break;
        }
if ( tim ) --tim;
/////////////////////////////////////////////////////////////// 


// aktualizacja wyjĹÄ
 digitalWrite(k13,LED);

 digitalWrite(o0,LED1);
 digitalWrite(o1,LED2);
 digitalWrite(o2,LED4);
 digitalWrite(o3,LED3);                                                                                                                                                                                                                  
 digitalWrite(o4,PDA);
 digitalWrite(o5,PGA);
 //digitalWrite(o6,pp6);
 //digitalWrite(o7,pp7);
 
 // oczekiwanie na koniec cyklu
// UWAGA: cykl trwa 10ms
 while(millis()-stime<10);


}