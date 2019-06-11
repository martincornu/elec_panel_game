static int nb_pairs = 5;

static int first_input = 8;   //Num. of first arduino input.
static int first_output = 2;  //Num. of first arduino output.

int8_t index = -1;

void setup() {
  Serial.begin(9600);
  
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
}

void loop() {

  bool isPlugOk = true;

  for (int i = 0; i<nb_pairs; i++) {
    //Set i_output to low - like connected to ground for pullup inputs.
    digitalWrite(first_output+i, LOW);
    //Scan inputs for i_output
    index = scan_inputs();
    Serial.print(first_output+i);
    Serial.print("eme elec tab input plug to : ");
    Serial.print(index);
    digitalWrite(first_output+i, HIGH);

    if (index != ((first_output+i)+6)) {
      isPlugOk = false;
      Serial.print(" -> false");
    }
  }

  if (isPlugOk == true) {
    Serial.println();
    Serial.println("OKKKKKKK !");
  }
  
  Serial.println();
  delay(1000);
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
  
  Serial.println("");

  return res;
}


