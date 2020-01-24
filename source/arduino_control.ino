/*
*
* ArduinoControl
*
* Example messages:
* "S0|o7|h7|." - For all arduino (0), set 7 to OUPUT (o7), and turn it on (h7)
* "S1|o1|h1|o2|l2|." - 
*     For the arduino numbered with 1 (1), set 1 to OUPUT (o1), and turn it on (h1),
*     then set 2 to OUTPUT (o2), and turn it off (l2)
* "S1|ra1|." - For the arduino numbered with 1 print analogRead(A1)
* "S2|r1|." - For the arduino numbered with 2 print digitalRead(1)
*/
#define AC_ID 1  // Set this ID, if you use multiple Arduinos connected in a ring
String ac_input = "";  // Stores the got serial message


void ac_listen()
{
  ac_listen(9600);  // Open with default baudrate
}

bool ac_listen(int baudrate)
{
  if (Serial.available() <= 0) 
  {
    return false;  // Wait for connection
  } 
  
  /*
  * Parts of a message:
  * S~ - Pass away
  * S - Start of message
  * . - End of message
  */
  ac_input = Serial.readStringUntil('.');  // Will be a string witout the '.'


  if (ac_input[1] == '~')
  { 
    // Pass it away without processing
    Serial.write((ac_input + '.').c_str());
    return false;
  }


  if (ac_input[0] == 'S')
  {
    // Cut the 'S' from the beginning
    ac_input = ac_input.substring(1, ac_input.length());
  }
  else
  {
    // Ignore unproper message
    return true;
  }

  
  if (ac_input[0] == '0')
  { 
    // Pass it away, but process command
    Serial.write(('S' + ac_input + '.').c_str());
  }
  else if ((unsigned int) ac_input[0] != AC_ID)
  { 
    // Not relevant for this board, pass it away
    Serial.write(('S' + ac_input + '.').c_str());
  }


  if (ac_input[0] == '0' || (unsigned int) ac_input[0] == AC_ID)
  {
    ac_input.toLowerCase();
    ac_input = ac_input.substring(2, ac_input.length());
    ac_decode();  // Remove the "N|" form the beginning
    
    // Clear serial
    /*
    while (Serial.available() > 0)
    {
      Serial.read();
    }
    */
    // Serial.end();
    // Serial.begin(baudrate);
  }
}

void ac_decode()
{
  String cmd_part = "";

  for (unsigned int i = 0; i < ac_input.length(); i++)
  {
    if (ac_input[i] == '|')
    {
      ac_use_cmd(cmd_part);
      cmd_part = "";
      continue;
    }

    cmd_part += ac_input[i];
  }
}

/*
   Examples:
   "1|o13|h13" -> The 1 ID board | pinMode(13, OUTPUT) | digitalWrite(13, HIGH)
   "0|ao1|ah1" -> For all board | pinMode(A1, OUTPUT) | analogWrite(A1, HIGH)
   "0|ao1|ap2|ah1" -> For all board | pinMode(A1, OUTPUT) | pinMode(A2, INPUT_PULLUP) | analogWrite(A1, HIGH)
   "1|ra1" -> The 1 ID board | a = analogRead(A1) | Serial.println(a)
   "2|r1" -> The 2 ID board | b = digitalRead(1) | Serial.println(b)
*/
void ac_use_cmd(String command)
{
  if (command == "" || command == '|' || command == '.') 
  {
    return;
  }

  if (command[0] == 'o')
  {
    pinMode(command.substring(1, command.length()).toInt(), OUTPUT);
  }
  else if (command[0] == 'i')
  {
    pinMode(command.substring(1, command.length()).toInt(), INPUT);
  }
  else if (command[0] == 'p')
  {
    pinMode(command.substring(1, command.length()).toInt(), INPUT_PULLUP);
  }
  else if (command[0] == 'h')
  {
    digitalWrite(command.substring(1, command.length()).toInt(), HIGH);
  }
  else if (command[0] == 'l')
  {
    digitalWrite(command.substring(1, command.length()).toInt(), LOW);
  }
  else if (command[0] == 'a')
  {
    if (command[1] == 'o')
    {
      pinMode(command.substring(2, command.length()).toInt() + 14, OUTPUT);
    }
    else if (command[1] == 'i')
    {
      pinMode(command.substring(2, command.length()).toInt() + 14, INPUT);
    }
    else if (command[1] == 'p')
    {
      pinMode(command.substring(2, command.length()).toInt() + 14, INPUT_PULLUP);
    }
    else if (command[1] == 'h')
    {
      analogWrite(command.substring(2, command.length()).toInt() + 14, HIGH);
    }
    else if (command[1] == 'l')
    {
      analogWrite(command.substring(2, command.length()).toInt() + 14, LOW);
    }
  }
  else if (command[0] == 'r')
  {
    if (command[1] == 'a')
    {
      Serial.write(("|" + String(analogRead(command.substring(2, command.length()).toInt() + 14)) + ";").c_str());
    }
    else
    {
      Serial.write(("|" + String(digitalRead(command.substring(1, command.length()).toInt())) + ";").c_str());
    }
  }
}

