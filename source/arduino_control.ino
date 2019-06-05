/*
* Parts of a message:
* S~ - Pass away
* S - Start of message
* . - End of message
*
* An example message:
* "S0|o7|h7|." - For all arduino (0), set 7 to OUPUT (o7), and turn it on (h7)
* "S1|o1|h1|o2|l2|." - 
*     For the arduino numbered with 1 (1), set 1 to OUPUT (o1), and turn it on (h1),
*     then set 2 to OUTPUT (o2), and turn it off (l2)
*/
#define AC_ID 1


void ac_listen() {
  // open with default baudrate
  ac_listen(9600);
}

void ac_listen(int baudrate) {
  if (Serial.available() <= 0) return;  // wait for connection
  String got = Serial.readStringUntil('.');

  if (got[0] == 'S') {
    got = got.substring(1, got.length());
  } else {
    return;  // ignore unproper message
  }

  if (got[0] == '~') {  // Pass it away without processing
    Serial.write(('S' + got + '.').c_str());
    return;
  }
  else if ((int)got[0] == 0) {  // Pass it away, but process command
    Serial.write(('S' + got + '.').c_str());
  }
  else if ((int)got[0] != AC_ID) {  // Not relevant for this board, pass it away
    Serial.write(('S' + got + '.').c_str());
  }

  if (got[0] == '0' || got[0] == AC_ID) {
    got.replace('.', ' ');
    got.trim();
    got.toLowerCase();
    ac_decode(got.substring(2, got.length()));
    
    Serial.end();
    Serial.begin(baudrate);
  }
}


// String got = commands separated with '|'
void ac_decode(String got) {
  String cmd_part = "";

  for (uint16_t i = 0; i < got.length(); i++) {
    if (got[i] == '|') {
      ac_use_cmd(cmd_part);
      cmd_part = "";
      continue;
    }

    cmd_part += got[i];
  }
}

/*
   Examples:
   "1|o13|h13" -> The 1 ID board | pinMode(13, OUTPUT) | digitalWrite(13, HIGH)
   "0|ao1|ah1" -> For all board | pinMode(A1, OUTPUT) | analogWrite(A1, HIGH)
   "0|ao1|ap2|ah1" -> For all board | pinMode(A1, OUTPUT) | pinMode(A2, INPUT_PULLUP) | analogWrite(A1, HIGH)
*/
void ac_use_cmd(String command) {
  if (command == "" || command == '|' || command == '.') return;

  if (command[0] == 'o') {
    pinMode(command.substring(1, command.length()).toInt(), OUTPUT);
  }
  else if (command[0] == 'i') {
    pinMode(command.substring(1, command.length()).toInt(), INPUT);
  }
  else if (command[0] == 'p') {
    pinMode(command.substring(1, command.length()).toInt(), INPUT_PULLUP);
  }
  else if (command[0] == 'h') {
    digitalWrite(command.substring(1, command.length()).toInt(), HIGH);
  }
  else if (command[0] == 'l') {
    digitalWrite(command.substring(1, command.length()).toInt(), LOW);
  }
  else if (command[0] == 'a') {
    if (command[1] == 'o') {
      pinMode(command.substring(2, command.length()).toInt() + 14, OUTPUT);
    }
    else if (command[1] == 'i') {
      pinMode(command.substring(2, command.length()).toInt() + 14, INPUT);
    }
    else if (command[1] == 'p') {
      pinMode(command.substring(2, command.length()).toInt() + 14, INPUT_PULLUP);
    }
    else if (command[1] == 'h') {
      analogWrite(command.substring(2, command.length()).toInt() + 14, HIGH);
    }
    else if (command[1] == 'l') {
      analogWrite(command.substring(2, command.length()).toInt() + 14, LOW);
    }
  }
}

