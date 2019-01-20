#define LEDDIMMERCONTROL_VERSION "0.10"

const char compile_date[] = __DATE__ " " __TIME__;

const uint8_t UPDATES_PER_SECOND = 15;
const uint8_t BUTTON_PIN = 4;
const uint8_t ENCODER_A = 2;
const uint8_t ENCODER_B = 3;
const uint8_t LED_PIN = 10;

int16_t encoderPos = 0;
int16_t encoderMove = 0;

const uint8_t NUM_MODES = 2;
uint8_t curMode = 0;

const uint16_t SLEEP_DELAY = 7000UL;
uint8_t powerSave = 0;
uint8_t asleep = 0;
uint8_t sleepTimer;

const uint16_t SPLASH_DELAY = 5000UL;

/*
   Modes:
    0: Brightness
    1: Off Timer setup
*/

uint8_t refreshTimer;
uint8_t displayDirty = true;
uint8_t ledDirty = true;
uint8_t knobAction = 0; // 0 means knob is up, change the Value upon turn
// 1 means knob is down, change the mode upon turn

void updateDisplay();
void drawSplash();
void draw();
void encoderHandle();
void fallAsleep();
void wakeUp();
