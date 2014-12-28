// Shatenzo.ino

const byte NUMBER_OF_ROWS = 5;
const byte NUMBER_OF_COLUMNS = 14;
int currentKeyDowns[] = {0,0,0,0,0,0};
byte currentNumberOfKeyPresses = 0;

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

int keys[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
    {KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE},
    {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH},
    {KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_ENTER},
    {MODIFIERKEY_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_MINUS, 0, MODIFIERKEY_SHIFT},
    {MODIFIERKEY_CTRL, MODIFIERKEY_ALT, MODIFIERKEY_ALT, 0, 0, KEY_SPACE, 0, 0, 0, MODIFIERKEY_ALT, MODIFIERKEY_ALT, MODIFIERKEY_ALT, MODIFIERKEY_CTRL}
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
                    Serial.print(i); Serial.print(":"); Serial.println(k);
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
    // debugKey(i, k, "UP");
    if (keys[i][k] == MODIFIERKEY_CTRL || keys[i][k] == MODIFIERKEY_SHIFT || keys[i][k] == MODIFIERKEY_ALT || keys[i][k] == MODIFIERKEY_GUI) {
        Keyboard.set_modifier(0);
    } else {
        int n = 0;
        for (n = 0; n < 6; ++n) {
            if (currentKeyDowns[n] == keys[i][k]) {
                switch(n) {
                    case 0: 
                        Keyboard.set_key1(0);
                        currentKeyDowns[n] = 0;
                        currentNumberOfKeyPresses--;
                        break;
                    case 1: 
                        Keyboard.set_key2(0);
                        currentKeyDowns[n] = 0;
                        currentNumberOfKeyPresses--;
                        break;
                    case 2: 
                        Keyboard.set_key3(0);
                        currentKeyDowns[n] = 0;
                        currentNumberOfKeyPresses--;
                        break;
                    case 3: 
                        Keyboard.set_key4(0);
                        currentKeyDowns[n] = 0;
                        currentNumberOfKeyPresses--;
                        break;
                    case 4: 
                        Keyboard.set_key5(0);
                        currentKeyDowns[n] = 0;
                        currentNumberOfKeyPresses--;
                        break;
                    case 5: 
                        Keyboard.set_key6(0);
                        currentKeyDowns[n] = 0;
                        currentNumberOfKeyPresses--;
                        break;
                }
            }
        }
    }
    Keyboard.send_now();
}

void keyDown(const int i, const int k) {
    // debugKey(i, k, "DOWN");
    if (keys[i][k] == MODIFIERKEY_CTRL || keys[i][k] == MODIFIERKEY_SHIFT || keys[i][k] == MODIFIERKEY_ALT || keys[i][k] == MODIFIERKEY_GUI) {
        Keyboard.set_modifier(keys[i][k]);
    } else {
        if (currentNumberOfKeyPresses < 6) {
            currentKeyDowns[currentNumberOfKeyPresses++] = keys[i][k];

            switch(currentNumberOfKeyPresses) {
                case 1:
                    Keyboard.set_key1(keys[i][k]);
                    break;
                case 2:
                    Keyboard.set_key2(keys[i][k]);
                    break;
                case 3:
                    Keyboard.set_key3(keys[i][k]);
                    break;
                case 4:
                    Keyboard.set_key4(keys[i][k]);
                    break;
                case 5:
                    Keyboard.set_key5(keys[i][k]);
                    break;
                case 6: 
                    Keyboard.set_key6(keys[i][k]);
                    break;
            }
        }
    }
    Keyboard.send_now();
}

void debugKey(const int i, const int k, const char* message) {
    Serial.print("Key "); Serial.print(i); Serial.print(":"); Serial.print(k); Serial.print(" "); Serial.println(message);
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