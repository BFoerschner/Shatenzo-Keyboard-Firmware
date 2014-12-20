// Shatenzo.ino

const byte NUMBER_OF_ROWS = 2;
const byte NUMBER_OF_COLUMNS = 1;

byte rowPins[NUMBER_OF_ROWS] = {0, 1};
byte columnPins[NUMBER_OF_COLUMNS] = {5};

int keyValues[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
    {KEY_A},
    {KEY_B}
};

boolean keyPressed[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
    {false},
    {false}
};

void initKeys (
    const byte rowPins[],
    const byte rowPinsSize, 
    const byte columnPins[], 
    const byte columnPinsSize
) {
    int i = 0;

    for (i = 0;, i < rowPinsSize; ++i) {
        pinMode(rowPins[i], OUTPUT);
    }

    for (i = 0;, i < columnPinsSize; ++i) {
        pinMode(columnPins[i], INPUT);
    }
}

void setup() {
	Serial.begin(9600);
}

void loop() {
}

