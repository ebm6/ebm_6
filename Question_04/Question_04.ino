/*Ex-04*/
/*It was implemented 2 ID messages for the tests, ID1=01 and ID2=02 and it is the first 2 inputs bytes from the Arduinos's UART serial. 
 * EX: Message: 010255 -> the Id will be 01 and the payload 0255. negatives values are acceptable for the payload.
 */

/*Global Variables*/
char MSG[6] = {};
char ID[2] = {};
char PayLoad[4] = {};
unsigned short addr = 0;

/***************************************************
  Function: setup(void)
  Description: put your setup code here, to run once:
  Inputs:  None
  Outputs: None
 **************************************************/
void setup()
{
  Serial.begin(115200);
}

/*Main function of Arduino*/
void loop()
{
  // put your main code here, to run repeatedly:

  delay(1000);
  parser();

}

/***************************************************
  Function: parser(void)
  Description: To act depending on the message,
  colects the payload and de ID message.
  Inputs:  None
  Outputs: None
 **************************************************/
void parser()
{
  /*Extract the PayLoad from message*/
  for (int i = 0; i < 4; i++)
  {
    PayLoad[i] = MSG[2 + i];
  }

  /*Command 01 can be a temperature Alert*/
  if (MSG[0] == '0' && MSG[1] == '1')
  {
    Serial.print("\nTemp Alert\n");
    for (int i = 0; i < 4; i++)
    {
      Serial.print(PayLoad[i]);
    }
    Serial.print(" Graus");
  }

  /*Command 02 can be cooler speed up*/
  if (MSG[0] == '0' && MSG[1] == '2')
  {
    Serial.print("\nCooler speed up!");
    Serial.print("\nSpeed value: ");
    
    /*Display the payload value for UART*/
    for (int i = 0; i < 4; i++)
    {
      Serial.print(PayLoad[i]);
    }
  }

  /*Message reset*/
  for (int c = 0; c <= 5; c++)
  {

    MSG[c] = {};

  }
}

/***************************************************
  Function: serialEvent(void)
  Description: Serial UART function,
  Inputs:  None
  Outputs: None
 **************************************************/
void serialEvent() {
  while (Serial.available()) {

    char BUFFER;
    BUFFER = (char)Serial.read();

    if ( addr >= 6)
    {
      addr = 0;

    }
    else
    {
      MSG[addr] = BUFFER;
      addr ++;
    }

  }
}
