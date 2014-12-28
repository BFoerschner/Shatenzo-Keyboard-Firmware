// Shatenzo.ino

const byte NUMBER_OF_ROWS = 5;
const byte NUMBER_OF_COLUMNS = 14;

byte rowPins[NUMBER_OF_ROWS] = {0, 1, 2, 3, 4};
byte columnPins[NUMBER_OF_COLUMNS] = {21, 20, 19, 18, 17, 16, 15, 14, 12, 11, 10, 9, 8, 7};
byte lastKnownState[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

byte currentState[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void checkForKeypresses(    
    const byte rowPins[],
    const byte rowPinsSize, 
    const byte columnPins[], 
    const byte columnPinsSize
) {
    int i = 0;
    int k = 0;

    for (i = 0; i < rowPinsSize; ++i) {
        for (k = 0; k < columnPinsSize; ++k) {
            currentState[i][k] = 0;
            pinMode(rowPins[i], HIGH);

            boolean columnPressed = digitalRead(columnPins[k]) == 0;
            if (columnPressed) {
                pinMode(rowPins[i], LOW);

                boolean currentKeyDown = (digitalRead(columnPins[k]) == 0);
                if (currentKeyDown) {
                    // Serial.print(rowPins[i]); Serial.print(":"); Serial.println(columnPins[k]);
                    currentState[i][k] = 1;
                }
                pinMode(rowPins[i], HIGH);
            }
            pinMode(rowPins[i], LOW);
        }
        pinMode(rowPins[i], LOW);
    }
    handleStateChange();
    debounce();
    // debugKeyboard();
}

void debounce() {
    delay(10);
}

void handleStateChange() {
    int i;
    int k;

    for (i = 0; i < NUMBER_OF_ROWS; ++i) {
        for (k = 0; k < NUMBER_OF_COLUMNS; ++k) {
            if (currentState[i][k] != lastKnownState[i][k]) {
                if (currentState[i][k] == 1) {
                    keyDown(i, k);
                } else {
                    keyUp(i, k);
                }
            }
            lastKnownState[i][k] = currentState[i][k];
            currentState[i][k] = 0;
        }
    }
}

void keyUp(const int i, const int k) {
    Serial.print("Key "); Serial.print(i); Serial.print(":"); Serial.print(k); Serial.println(" up");
}

void keyDown(const int i, const int k) {
    Serial.print("Key "); Serial.print(i); Serial.print(":"); Serial.print(k); Serial.println(" down");
}

void debugKeyboard() {
    int i=0;
    int k=0;

    for (i = 0; i < NUMBER_OF_ROWS; ++i) {
        for (k = 0; k < NUMBER_OF_COLUMNS; ++k) {
            Serial.print(currentState[i][k]); Serial.print(" ");
        }
        Serial.println("");
    }
    Serial.println("");
    Serial.println("--------------------------------------------------------");
}

void initKeys (
    const byte rowPins[],
    const byte rowPinsSize, 
    const byte columnPins[], 
    const byte columnPinsSize
) {
    int i = 0;

    for (i = 0; i < rowPinsSize; ++i) {
        pinMode(rowPins[i], OUTPUT);
    }

    for (i = 0; i < columnPinsSize; ++i) {
        pinMode(columnPins[i], INPUT_PULLUP);
    }
}

void setup() {
    Serial.begin(9600);
    initKeys(rowPins, NUMBER_OF_ROWS, columnPins, NUMBER_OF_COLUMNS);
}

void loop() {
    checkForKeypresses(rowPins, NUMBER_OF_ROWS, columnPins, NUMBER_OF_COLUMNS);
}