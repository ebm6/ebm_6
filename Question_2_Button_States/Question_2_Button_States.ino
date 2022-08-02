
#include <stdio.h>

char SM_STATE_OFF = 1;
char SM_STATE_ON = 2;
char SM_STATE_PROTECTED = 3;
char LOCAL_STATE = SM_STATE_OFF;  /*Inital state*/

int buttonPin = 7;//Define buttonPin digital pin 7
int ledPin = 10;//Define ledPin digital pin 10
int Button_Pressed = 0;//

/***************************************************
  Function: setup(void)
  Description: put your setup code here, to run once:
  Inputs:  None
  Outputs: None
 **************************************************/
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin , OUTPUT);//Define ledPin (pino 10) como saída
  pinMode(buttonPin , INPUT);//Define buttonPin (pino 7) como entrada
}

/***************************************************
  Function: Local_Timer(void)
  Description: compute the timer in a function
  Inputs:  Reset_Flag
  Outputs: count value
 **************************************************/
int Local_Timer(char reset)
{
  static int count = 0;  /*Initialize the count variable just one with zero*/
  if (LOCAL_STATE == SM_STATE_PROTECTED)
  {
    count ++;
  }
  if (reset)
  {
    count = 0;          /*Reset the count*/
  }
  delay(10);
  return (count);  /*Return the count value in seconds*/

}

/***************************************************
  Function: Button_State(void)
  Description: Verifys if the stated is on, off or
               in the Protected state.
  Inputs:  None
  Outputs: None
 **************************************************/
void Button_State (void)
{
  Button_Pressed = digitalRead(buttonPin);

  if (Button_Pressed &&
      LOCAL_STATE == SM_STATE_OFF &&
      LOCAL_STATE != SM_STATE_PROTECTED)
  {
    LOCAL_STATE = SM_STATE_ON;
    digitalWrite(ledPin , HIGH); /*Just to view the state*/
  }

  if (!Button_Pressed &&
      LOCAL_STATE == SM_STATE_ON &&
      LOCAL_STATE != SM_STATE_PROTECTED)
  {
    LOCAL_STATE = SM_STATE_PROTECTED;
  }

  if (LOCAL_STATE == SM_STATE_PROTECTED && Local_Timer(false) > 1000)
  {
    LOCAL_STATE = SM_STATE_OFF;
    Local_Timer(true);             /*Reset the timer*/
    digitalWrite(ledPin , LOW); /*Just to view the state*/
  }

}

void loop() {
  Button_State();

}
