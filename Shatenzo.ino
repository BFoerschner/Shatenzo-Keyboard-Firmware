// Shatenzo.ino

const byte NUMBER_OF_ROWS = 5;
const byte NUMBER_OF_COLUMNS = 3;

byte rowPins[NUMBER_OF_ROWS] = {0,1,2,3,4};
byte columnPins[NUMBER_OF_COLUMNS] = {5,6,7};

void checkForKeypresses(    
    const byte rowPins[],
    const byte rowPinsSize, 
    const byte columnPins[], 
    const byte columnPinsSize
) {
    int i = 0;
    int k = 0;

    for (i = 0; i < rowPinsSize; ++i) {
        pinMode(rowPins[i], HIGH);

        for (k = 0; k < columnPinsSize; ++k) {
            boolean keyDown = (digitalRead(columnPins[k]) == 0);
            
            if (keyDown) {
                pinMode(rowPins[i], LOW);

                boolean exactKeyDown = (digitalRead(columnPins[k]) == 0);
                if (exactKeyDown) {
                    Serial.print(i); Serial.print(":"); Serial.println(k);
                }
            }
        }

        pinMode(rowPins[i], LOW);
    }
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
    delay(1500);
}