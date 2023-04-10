
#include <stdio.h>

char SM_STATE_OFF = 1;
char SM_STATE_ON = 2;
char SM_STATE_PROTECTED = 3;
char LOCAL_STATE = SM_STATE_OFF;  /*Inital state*/

int buttonPin = 7;//Define buttonPin digital pin 7
int ledPin = 10;//Define ledPin digital pin 10
int Button_Pressed = 0;//

static int timer_in_state = 0;
static int timer_button_pressed = 0;

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
  Description: compute the timer in a state
  Inputs:  Reset_Flag
  Outputs: count value
 **************************************************/
int Local_Timer(char reset)
{
  if (reset)
  {
    timer_in_state = 0;          /*Reset the count*/
  }
  else
  {
    timer_in_state ++;
  }
  delay(10);
  return (timer_in_state);  /*Return the count value in seconds*/
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
    LOCAL_STATE = SM_STATE_ON;        /*Change the FSM state to SM_STATE_ON*/
    Local_Timer(true);                /*Reset the timer just after the state is changed*/
  }

  if (!Button_Pressed &&
      LOCAL_STATE == SM_STATE_ON &&
      LOCAL_STATE != SM_STATE_PROTECTED)
  {
    LOCAL_STATE = SM_STATE_PROTECTED;  /*Change the FSM state to SM_STATE_PROTECTED*/
    Local_Timer(true);                 /*Reset the timer just after the state is changed*/
  }

  if (LOCAL_STATE == SM_STATE_PROTECTED && timer_in_state > 1000) /*check if is in protected mode and if the timer is up*/
  {
    LOCAL_STATE = SM_STATE_OFF;        /*Change the FSM state to SM_STATE_OFF*/
    Local_Timer(true);                 /*Reset the timer just after the state is changed*/
  }

  Action_each_state(); /*Calls the actions of each state*/
}

/***************************************************
  Function: Action_each_state(void)
  Description: Handles the actions of each state
  Inputs:  None
  Outputs: None
 **************************************************/
void Action_each_state(void)
{
  if (LOCAL_STATE == SM_STATE_OFF)  /*Actions of the OFF state*/
  {
    digitalWrite(ledPin , LOW);    /*Just to view the state*/
  }
  if (LOCAL_STATE == SM_STATE_ON)
  {
    digitalWrite(ledPin , HIGH); /*Just to view the state*/
    timer_button_pressed = timer_in_state; /*saves the time the button kept pressed*/
  }
  Local_Timer(false); /*Run the local Timer*/
}

/*Main function loop*/
void loop() {
  Button_State();

}
