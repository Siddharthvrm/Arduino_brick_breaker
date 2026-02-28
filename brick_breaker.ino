#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Controls
#define JOY_X A0
#define JOY_BTN 2

// Paddle
int paddleWidth = 20;
int paddleHeight = 4;
float paddleX;

// Ball
float ballX, ballY;
float ballSpeedX, ballSpeedY;
int ballRadius = 2;
bool ballMoving = false;

// Game
int score = 0;
byte level = 1;
const byte maxLevel = 15; // 15 levels

// Bricks
#define MAX_ROWS 8
#define MAX_COLS 10

byte bricks[MAX_ROWS][MAX_COLS];

byte brickRows;
byte brickCols;
byte brickWidth;
byte brickHeight;
byte brickSpacing = 2;
byte brickOffsetX;

// ----------------------------

void configureLevel() {
  brickWidth  = 18 - level;
  brickHeight = 8 - (level / 2);

  if (brickWidth < 4) brickWidth = 4;
  if (brickHeight < 3) brickHeight = 3;

  brickCols = 5 + level / 2;
  if (brickCols > MAX_COLS) brickCols = MAX_COLS;

  brickRows = 3 + level / 3;
  if (brickRows > MAX_ROWS) brickRows = MAX_ROWS;

  int totalWidth = brickCols * brickWidth +
                   (brickCols - 1) * brickSpacing;

  brickOffsetX = (SCREEN_WIDTH - totalWidth) / 2;
  if (brickOffsetX < 0) brickOffsetX = 0;
}

void initBricks() {
  for (byte r = 0; r < MAX_ROWS; r++)
    for (byte c = 0; c < MAX_COLS; c++)
      bricks[r][c] = 0;

  for (byte r = 0; r < brickRows; r++)
    for (byte c = 0; c < brickCols; c++)
      bricks[r][c] = 1;
}

void resetBall() {
  ballMoving = false;
  ballX = paddleX + paddleWidth / 2;
  ballY = SCREEN_HEIGHT - 12;

  float speed = 2.0 + level * 0.3;
  if (speed > 5.0) speed = 5.0;

  ballSpeedX = speed;
  ballSpeedY = -speed;
}

bool allBricksCleared() {
  for (byte r = 0; r < brickRows; r++)
    for (byte c = 0; c < brickCols; c++)
      if (bricks[r][c]) return false;
  return true;
}

// ----------------------------

void setup() {

  pinMode(JOY_BTN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.display();

  paddleX = (SCREEN_WIDTH - paddleWidth) / 2;

  configureLevel();
  initBricks();
  resetBall();
}

// ----------------------------

void loop() {

  int joyX = analogRead(JOY_X);
  float targetX = map(joyX, 0, 1023, 0, SCREEN_WIDTH - paddleWidth);
  paddleX += (targetX - paddleX) * 0.25;

  if (paddleX < 0) paddleX = 0;
  if (paddleX > SCREEN_WIDTH - paddleWidth)
    paddleX = SCREEN_WIDTH - paddleWidth;

  if (!ballMoving && digitalRead(JOY_BTN) == LOW) {
    ballMoving = true;
  }

  if (!ballMoving) {
    ballX = paddleX + paddleWidth / 2;
    ballY = SCREEN_HEIGHT - 12;
  }

  if (ballMoving) {

    ballX += ballSpeedX;
    ballY += ballSpeedY;

    if (ballX <= ballRadius || ballX >= SCREEN_WIDTH - ballRadius)
      ballSpeedX = -ballSpeedX;

    if (ballY <= ballRadius)
      ballSpeedY = -ballSpeedY;

    if (ballY + ballRadius >= SCREEN_HEIGHT - 10 &&
        ballX >= paddleX &&
        ballX <= paddleX + paddleWidth) {

      ballY = SCREEN_HEIGHT - 10 - ballRadius;
      ballSpeedY = -abs(ballSpeedY);
    }

    for (byte r = 0; r < brickRows; r++) {
      for (byte c = 0; c < brickCols; c++) {
        if (!bricks[r][c]) continue;

        int brickX = brickOffsetX + c * (brickWidth + brickSpacing);
        int brickY = 5 + r * (brickHeight + brickSpacing);

        if (ballX + ballRadius >= brickX &&
            ballX - ballRadius <= brickX + brickWidth &&
            ballY + ballRadius >= brickY &&
            ballY - ballRadius <= brickY + brickHeight) {

          bricks[r][c] = 0;
          ballSpeedY = -ballSpeedY;
          score += 10;
        }
      }
    }

    if (ballY - ballRadius > SCREEN_HEIGHT) {
      resetBall(); // no lives, just reset ball
    }
  }

  // ---------------- LEVEL CLEAR ----------------
  if (allBricksCleared()) {
    level++;
    if (level > maxLevel) level = 1; // loop back to level 1
    configureLevel();
    initBricks();
    resetBall();
  }

  // ---------------- DRAW ----------------
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("S:");
  display.print(score);

  display.setCursor(85, 0);
  display.print("Lv:");
  display.print(level);

  display.fillRect(paddleX, SCREEN_HEIGHT - 10,
                   paddleWidth, paddleHeight, SSD1306_WHITE);

  display.fillCircle(ballX, ballY, ballRadius, SSD1306_WHITE);

  for (byte r = 0; r < brickRows; r++) {
    for (byte c = 0; c < brickCols; c++) {

      if (!bricks[r][c]) continue;

      int brickX = brickOffsetX + c * (brickWidth + brickSpacing);
      int brickY = 5 + r * (brickHeight + brickSpacing);

      display.fillRect(brickX, brickY,
                       brickWidth, brickHeight,
                       SSD1306_WHITE);
    }
  }

  display.display();
  delay(16);
}