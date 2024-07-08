unsigned int uiMSec;
unsigned char ucFlag, ucCount;

void setup() 
{
  // put your setup code here, to run once:
  //DDRB = 0b00000011;
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  
  uiMSec = 0;
  ucFlag = 0;
  ucCount = 0;
  cli();
  SREG = 0X80;//(1 << GIE);
  TCNT0 = 0;
  TCCR0A = 0;
  TCCR0B = 0;
  OCR0A = 156;
  TCCR0A |= 0X82; // set entire TCCR0A register to 0
  TCCR0B |= 0X85; // same for TCCR0B
  TIMSK |= (1 << OCIE0A);
  sei();
}
void pulse(unsigned int uiPulse)
{
  unsigned int i;
  for(i=0; i< uiPulse; i++)
  {  
    digitalWrite(1, HIGH);
    //delayMicroseconds(1);
    delayMicroseconds(12);
    digitalWrite(1, LOW);
    //delayMicroseconds(1); 
    delayMicroseconds(6);  
  }
}
void loop() 
{
    //delayMicroseconds(1000);
    pulse(1000);
    delayMicroseconds(1000);    
    pulse(1000);
    for(uiMSec=3; uiMSec<450; uiMSec++)
    {
      delayMicroseconds(1000);
    }
   if((ucFlag))// == 0)
   {
    //digitalWrite(0, LOW);
    if((ucCount>0)&&(ucCount<150))   
    digitalWrite(0, LOW);
    else if (ucCount > 150) 
    {
      ucFlag = 0;
      ucCount = 0;
      }
   }
   else
   {
     digitalWrite(0, HIGH);
     ucFlag = 0;
     ucCount = 0;
    }
   //delay(1000);
}
ISR(TIMER0_COMPA_vect)
{
  TCNT0 = 0;
  if((digitalRead(2)==0)&& (ucFlag==0))
  {
     //digitalWrite(0, LOW); 
     ucFlag = 1;
     //ucCount ++;
  }
  if((ucFlag==0)&&(ucCount==0))
  {
     digitalWrite(0, HIGH); 
     ucFlag = 0;
     //ucCount = 0;
  }      
  if(ucFlag)
  {
     ucCount ++;
     //digitalWrite(0, LOW); 
//     if((ucCount>0)&&(ucCount<4))
//     {
//        digitalWrite(0, LOW); 
//     }
//     if(ucCount>4)
//     {
//        digitalWrite(0, HIGH); 
//        ucCount = 0;
//     }
   }  
}
