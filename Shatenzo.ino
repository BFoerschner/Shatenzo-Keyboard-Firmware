// Shatenzo.ino

// Public Constants to mess around with ---------------------------------------
const byte NUMBER_OF_ROWS = 5;
const byte NUMBER_OF_COLUMNS = 14;

byte rowPins[NUMBER_OF_ROWS] = {0, 1, 2, 3, 4};
byte columnPins[NUMBER_OF_COLUMNS] = {21, 20, 19, 18, 17, 16, 15, 14, 12, 11, 10, 9, 8, 7};

const byte debounceValue = 35;  // Increase the value if you have multiple keyDowns/-Ups on one Keypress, Decrease if you have performance-issues
// ----------------------------------------------------------------------------

// Public Keyboard stuff, change this here for your needs ---------------------
int layer1[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
    {KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE},
    {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH},
    {KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_ENTER},
    {MODIFIERKEY_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, 0, MODIFIERKEY_SHIFT},
    {MODIFIERKEY_CTRL, MODIFIERKEY_ALT, MODIFIERKEY_ALT, 0, 0, KEY_SPACE, 0, 0, 0, MODIFIERKEY_ALT, MODIFIERKEY_ALT, MODIFIERKEY_ALT, MODIFIERKEY_CTRL}
};
// ----------------------------------------------------------------------------

// Private Keyboard stuff -----------------------------------------------------
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

void loop() {
    checkForKeypresses();
}

void checkForKeypresses() {
    int i = 0;
    int k = 0;

    for (i = 0; i < NUMBER_OF_ROWS; ++i) {
        for (k = 0; k < NUMBER_OF_COLUMNS; ++k) {
            currentState[i][k] = 0;
            pinMode(rowPins[i], HIGH);

            boolean columnPressed = digitalRead(columnPins[k]) == 0;
            if (columnPressed) {
                pinMode(rowPins[i], LOW);

                boolean currentKeyDown = (digitalRead(columnPins[k]) == 0);
                if (currentKeyDown) {\
                    currentState[i][k] = 1;
                    // Debug stuff
                    // Serial.print(i); Serial.print(":"); Serial.println(k);
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
    delay(debounceValue);
}

void keyUp(const int i, const int k) {
    // debugKey(i, k, "UP");
    Keyboard.release(layer1[i][k]);
    Keyboard.send_now();
}

void keyDown(const int i, const int k) {
    // debugKey(i, k, "DOWN");
    Keyboard.press(layer1[i][k]);
    Keyboard.send_now();
}
// ----------------------------------------------------------------------------

void setup() {
    initIO();
}

void initIO () {
    int i = 0;

    for (i = 0; i < NUMBER_OF_ROWS; ++i) {
        pinMode(rowPins[i], OUTPUT);
    }

    for (i = 0; i < NUMBER_OF_COLUMNS; ++i) {
        pinMode(columnPins[i], INPUT_PULLUP);
    }
}