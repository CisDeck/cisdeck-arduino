const int numRows = 4;
const int numCols = 4;
const int debounceTime = 50;

const char keymap[numRows][numCols] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[numRows] = {5, 6, 7, 8}; 
byte colPins[numCols] = {9, 10, 11, 12}; 

void setup() {
  Serial.begin(9600);
  for (int row = 0; row < numRows; row++) {
    pinMode(rowPins[row],INPUT);
    digitalWrite(rowPins[row],HIGH);
  }
  for (int column = 0; column < numCols; column++) {
    pinMode(colPins[column],OUTPUT);
    digitalWrite(colPins[column],HIGH);
  }
}

void loop() {
  char key = getKey();
  if( key != 0) {
    Serial.println(key);
    delay(10);
  }
}

// getKey() returns pushed key or 0 if no key was pushed
char getKey(){
  char key = 0;
  for(int column = 0; column < numCols; column++) {
    digitalWrite(colPins[column],LOW);
    for(int row = 0; row < numRows; row++){
      if(digitalRead(rowPins[row]) == LOW){
        delay(debounceTime);
        while(digitalRead(rowPins[row]) == LOW) ;
        key = keymap[row][column];
      } 
    }
    digitalWrite(colPins[column],HIGH);
  }
  return key;
}

