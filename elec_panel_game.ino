/************************************************************************************************** 
  12/06/2019 - Martin C.
  Electrical panel game : the goal is to plug inputs in the right ouputs, by pairs.
  There are nb_pairs to plug.
  System: For each input of the electrical panel :
            - Send a signal into the input (LOW because pullup for noise)
            - Scan all elec panel outputs until found the one plug (= LOW) OR scan all of them.
            - Return the number of the output plug or -1 if no plug.
            - Check if it is the good one.
          Turn on a lamp if all pairs are well plugged.
**************************************************************************************************/

static uint8_t nb_pairs = 5;      //Num. of pairs to plug.

static uint8_t first_input = 8;   //Num. of first arduino input.
static uint8_t first_output = 2;  //Num. of first arduino output.

static uint8_t relais = 13;

int8_t index = -1;

void setup() {  
  //Outputs 2-6
  pinMode(first_output,OUTPUT);
  pinMode(first_output+1,OUTPUT);
  pinMode(first_output+2,OUTPUT);
  pinMode(first_output+3,OUTPUT);
  pinMode(first_output+4,OUTPUT);

  //Inputs 8-12
  pinMode(first_input,INPUT_PULLUP);
  pinMode(first_input+1,INPUT_PULLUP);
  pinMode(first_input+2,INPUT_PULLUP);
  pinMode(first_input+3,INPUT_PULLUP);
  pinMode(first_input+4,INPUT_PULLUP);

  digitalWrite(relais, LOW);
}

void loop() {

  bool isPlugOk = true;

  for (int i = 0; i<nb_pairs; i++) {
    //Set i_output to low - like connected to ground for pullup inputs.
    digitalWrite(first_output+i, LOW);
    //Scan inputs for i_output
    index = scan_inputs();
    digitalWrite(first_output+i, HIGH);

    if (index != ((first_output+i)+6)) {
      isPlugOk = false;
    }
  }

  if (isPlugOk == true) {
    digitalWrite(relais, HIGH);
  } else {
    digitalWrite(relais, LOW);
  }
  
  delay(10);
}

int8_t scan_inputs() {
  int i = 0;
  int res = -1;

  bool isPlug = false;

  while (i < nb_pairs && !isPlug) {
    if (digitalRead(i+first_input) == 0) {
      isPlug = true;
      res = i+first_input;
    }
    i++;
  }

  return res;
}


