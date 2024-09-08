#include <Arduino.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

int br = 9600;
int dt = 100;
const byte maxRows = 8;
const byte maxCols = 12;
int rDirection = 1;
int cDirection = 1;

byte frame[maxRows][maxCols] = {};
byte currentRow = 0;
byte currentCol = 0;

byte upBtn = D2;
byte upVal = 0;
byte downBtn = D12;
byte downVal = 0;
byte basePos = 4;

int timesToLose = 3;

ArduinoLEDMatrix matrix;
#include "helpers.h"

void setup() {
    delay(1500);
    Serial.begin(br);
    pinMode(upBtn, INPUT_PULLUP);
    pinMode(downBtn, INPUT_PULLUP);
    initBall(&matrix);
    delay(dt);
}

void message(String message, int x = 4, int y = 2) {
    matrix.clear();
    matrix.beginDraw();
    matrix.textFont(Font_4x6);
    matrix.beginText(x,y, 255,0,0);
    matrix.print(message);
    matrix.endText(SCROLL_RIGHT);
    matrix.endDraw();
    delay(1500);
}

void loop() {
    int prevRow = currentRow;
    int prevCol = currentCol;

    upVal = digitalRead(upBtn);
    downVal = digitalRead(downBtn);

    itHitBottomWall(currentRow, currentCol, &rDirection, &cDirection);
    itHitTopWall(currentRow, currentCol, &rDirection, &cDirection);
    itHitRightWall(currentRow, currentCol, &rDirection, &cDirection);
    itHitLeftWall(currentRow, currentCol, &rDirection, &cDirection);
    itHitTheCorners(currentRow, currentCol, &rDirection, &cDirection);

    // Draw ball
    currentRow = currentRow + rDirection;
    currentCol = currentCol + cDirection;
    frame[prevRow][prevCol] = 0;
    frame[currentRow][currentCol] = 1;
    matrix.renderBitmap(frame, 8, 12);

    // Draw base
    if (upVal == LOW && basePos > 0) {
        frame[basePos][0] = 0;
        basePos--;
    }

    if (downVal == LOW && basePos < 7) {
        frame[basePos][0] = 0;
        basePos++;
    }
    frame[basePos][0] = 1;
    matrix.renderBitmap(frame, 8, 12);

    if (currentRow != basePos && currentCol == 0) {
        delay(150);
        timesToLose--;
        if (timesToLose == 0) {
            message("L");
            timesToLose = 3;
        } else {
            message(String(timesToLose));
        }
    }

    delay(dt);
}