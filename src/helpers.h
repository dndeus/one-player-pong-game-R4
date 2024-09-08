void itHitBottomWall(byte currentRow, byte currentCol, int *rDirection, int *cDirection) {
    if (currentRow < (maxRows - 1) ) {
        return;
    }

    if ( *rDirection > 0 && *cDirection > 0 ) {
        *rDirection = -1;
        *cDirection = 1;
    }

    if ( *rDirection > 0 && *cDirection < 0 ) {
        *rDirection = -1;
        *cDirection = -1;
    }
}

void itHitTopWall(byte currentRow, byte currentCol, int *rDirection, int *cDirection) {
    if (currentRow > 0) {
        return;
    }

    if (*rDirection < 0 && *cDirection > 0 ) {
        *rDirection = 1;
        *cDirection = 1;
    }

    if (*rDirection < 0 && *cDirection < 0 ) {
        *rDirection = 1;
        *cDirection = -1;
    }
}

void itHitRightWall(byte currentRow, byte currentCol, int *rDirection, int *cDirection) {
    if (currentCol < (maxCols - 1)) {
        return;
    }

    if (*rDirection > 0 && *cDirection > 0 ) {
        *rDirection = 1;
        *cDirection = -1;
    }

    if (*rDirection < 0 && *cDirection > 0 ) {
        *rDirection = -1;
        *cDirection = -1;
    }
}

void itHitLeftWall(byte currentRow, byte currentCol, int *rDirection, int *cDirection) {
    if (currentCol > 0) {
        return;
    }

    if (*rDirection < 0 && *cDirection < 0 ) {
        *rDirection = -1;
        *cDirection = 1;
    }

    if (*rDirection > 0 && *cDirection < 0 ) {
        *rDirection = 1;
        *cDirection = 1;
    }
}

void itHitTheCorners(byte currentRow, byte currentCol, int *rDirection, int *cDirection) {
    if (currentRow == 0 && currentCol == 0) {
        *rDirection = 1;
        *cDirection = 1;
    }

    if (currentRow == 0 && currentCol == (maxCols - 1)) {
        *rDirection = 1;
        *cDirection = -1;
    }

    if (currentRow == (maxRows - 1) && currentCol == 0) {
        *rDirection = -1;
        *cDirection = 1;
    }

    if (currentRow == (maxRows - 1) && currentCol == (maxCols - 1)) {
        *rDirection = -1;
        *cDirection = -1;
    }

}

void initBall(ArduinoLEDMatrix *matrix) {
    matrix->begin();
    for (int i = 0; i < maxRows; i++) {
        for (int j = 0; j < maxCols; j++) {
            frame[i][j] = 0;
        }
    }

//    frame[currentRow][currentCol] = 1;
    matrix->renderBitmap(frame, 8, 12);
}

void handleDrawingBouncingBall(ArduinoLEDMatrix *matrix) {

}