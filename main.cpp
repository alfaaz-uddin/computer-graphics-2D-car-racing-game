#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <cmath>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

    bool gameStarted = false;
    bool isPaused = false;
    bool gameOver = false;

    float playerX = 0.0f;
    float playerY = -0.65f;

    float enemy1X = -0.55f;
    float enemy2X = 0.55f;

    float enemy1Y = 1.30f;
    float enemy2Y = 1.80f;

    float speed = 0.014f;

    int score = 0;

    float CAR_SCALE = 0.75f;

    int enemy1Type = 0;
    int enemy2Type = 1;

    bool isRaining = false;
    bool nightMode = false;

    bool crashState = false;
    float explosionRadius = 0.0f;

    float sceneryY = 0.0f;

    const int MAX_RAINDROPS = 100;
    float rainX[MAX_RAINDROPS];
    float rainY[MAX_RAINDROPS];

    class Rect {
    public:
        float left, right, top, bottom;

        Rect(float l, float r, float t, float b) {
            left = l;
            right = r;
            top = t;
            bottom = b;
        }

        void draw(float r, float g, float b) {
            glColor3f(r, g, b);

            glBegin(GL_POLYGON);
            glVertex2f(left, top);
            glVertex2f(right, top);
            glVertex2f(right, bottom);
            glVertex2f(left, bottom);
            glEnd();
        }


        bool checkCollision(Rect other) {
            if (other.right < left ||
                other.left > right ||
                other.top < bottom ||
                other.bottom > top)
                return false;

            return true;
        }
    };

    void drawRectangle(float left, float right,
                       float top, float bottom,
                       float r, float g, float b) {
        glColor3f(r, g, b);

        glBegin(GL_POLYGON);

        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
        glVertex2f(left, bottom);

        glEnd();
    }

    void drawCircle(float cx, float cy, float radius,
                    float r, float g, float b) {
        glColor3f(r, g, b);

        glBegin(GL_POLYGON);

        for (int i = 0; i < 360; i += 10) {
            float theta = i * 3.14159f / 180.0f;

            glVertex2f(cx + radius * cos(theta),
                       cy + radius * sin(theta));
        }

        glEnd();
    }

    void drawText(float x, float y, string text) {
        glColor3f(1.0f, 1.0f, 1.0f);

        glRasterPos2f(x, y);

        for (int i = 0; i < text.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        }
    }

    void drawStartScreen() {
        drawRectangle(-1.0f, 1.0f, 1.0f, -1.0f,
                      0.05f, 0.05f, 0.10f);

        drawText(-0.35f, 0.60f, "2D CAR RACING");

        drawText(-0.25f, 0.30f, "INSTRUCTIONS:");

        drawText(-0.55f, 0.15f, "- WASD or Arrow Keys to move");
        drawText(-0.55f, 0.05f, "- P to Pause / Resume");
        drawText(-0.55f, -0.05f, "- V to Toggle Rain");
        drawText(-0.55f, -0.15f, "- R to Restart");
        drawText(-0.55f, -0.25f, "- X to Exit");

        glColor3f(0.0f, 1.0f, 0.0f);

        drawText(-0.35f, -0.50f,
                 "PRESS SPACEBAR TO START");
    }

    void drawHUD() {
        drawRectangle(-1.0f, 1.0f, 1.0f, 0.88f,
                      0.10f, 0.10f, 0.10f);

        drawRectangle(-1.0f, 1.0f, 0.88f, 0.86f,
                      0.80f, 0.00f, 0.00f);

        stringstream ss;
        ss << "SCORE: " << score;

        drawText(-0.95f, 0.92f, ss.str());

        if (nightMode)
            drawText(0.60f, 0.92f, "NIGHT");
        else
            drawText(0.60f, 0.92f, "DAY");

        if (isRaining)
            drawText(0.25f, 0.92f, "RAIN");
    }


    void drawTree(float x, float y) {
        glPushMatrix();

        glTranslatef(x, y, 0.0f);

        drawRectangle(-0.035f, 0.035f,
                      0.15f, -0.15f,
                      0.45f, 0.22f, 0.05f);

        drawCircle(0.0f, 0.22f, 0.14f,
                   0.05f, 0.45f, 0.08f);

        drawCircle(-0.10f, 0.12f, 0.12f,
                   0.04f, 0.38f, 0.06f);

        drawCircle(0.10f, 0.12f, 0.12f,
                   0.04f, 0.40f, 0.07f);

        glPopMatrix();
    }

    void drawBuilding(float x, float y) {
        glPushMatrix();

        glTranslatef(x, y, 0.0f);

        drawRectangle(-0.10f, 0.10f,
                      0.30f, -0.30f,
                      0.30f, 0.30f, 0.35f);

        if (nightMode) {
            drawRectangle(-0.06f, -0.02f,
                          0.20f, 0.10f,
                          1.0f, 1.0f, 0.2f);

            drawRectangle(0.02f, 0.06f,
                          0.20f, 0.10f,
                          1.0f, 1.0f, 0.2f);

            drawRectangle(-0.06f, -0.02f,
                          0.00f, -0.10f,
                          1.0f, 1.0f, 0.2f);

            drawRectangle(0.02f, 0.06f,
                          0.00f, -0.10f,
                          1.0f, 1.0f, 0.2f);
        }
        else {
            drawRectangle(-0.06f, -0.02f,
                          0.20f, 0.10f,
                          0.20f, 0.20f, 0.40f);

            drawRectangle(0.02f, 0.06f,
                          0.20f, 0.10f,
                          0.20f, 0.20f, 0.40f);

            drawRectangle(-0.06f, -0.02f,
                          0.00f, -0.10f,
                          0.20f, 0.20f, 0.40f);

            drawRectangle(0.02f, 0.06f,
                          0.00f, -0.10f,
                          0.20f, 0.20f, 0.40f);
        }

        glPopMatrix();
    }

    void drawStreetlight(float x, float y) {
        glPushMatrix();

        glTranslatef(x, y, 0.0f);

        drawRectangle(-0.01f, 0.01f,
                      0.30f, -0.10f,
                      0.10f, 0.10f, 0.10f);

        drawRectangle(-0.01f, 0.10f,
                      0.30f, 0.28f,
                      0.10f, 0.10f, 0.10f);

        if (nightMode) {
            drawCircle(0.10f, 0.28f, 0.05f,
                       1.0f, 1.0f, 0.5f);
        }

        glPopMatrix();
    }

    void drawRoad() {
        nightMode = ((score / 10) % 2 == 1);

        if (nightMode) {
            drawRectangle(-1.0f, 1.0f,
                          1.0f, -1.0f,
                          0.02f, 0.06f, 0.12f);
        }
        else {
            drawRectangle(-1.0f, 1.0f,
                          1.0f, -1.0f,
                          0.12f, 0.55f, 0.12f);
        }

        drawRectangle(-0.80f, 0.80f,
                      1.0f, -1.0f,
                      0.20f, 0.20f, 0.20f);

        drawRectangle(-0.85f, -0.80f,
                      1.0f, -1.0f,
                      0.80f, 0.00f, 0.00f);

        drawRectangle(0.80f, 0.85f,
                      1.0f, -1.0f,
                      0.80f, 0.80f, 0.80f);

        for (float i = -1.2f; i <= 1.2f; i += 0.4f) {
            float markY = i + sceneryY;

            if (markY > 1.0f)
                markY -= 2.0f;

            if (markY < -1.0f)
                markY += 2.0f;

            drawRectangle(-0.27f, -0.25f,
                          markY + 0.10f,
                          markY - 0.10f,
                          0.90f, 0.90f, 0.90f);

            drawRectangle(0.25f, 0.27f,
                          markY + 0.10f,
                          markY - 0.10f,
                          0.90f, 0.90f, 0.90f);
        }

        if (nightMode) {
            drawCircle(0.70f, 0.78f, 0.10f,
                       1.0f, 1.0f, 0.75f);
        }
        else {
            drawCircle(0.72f, 0.78f, 0.10f,
                       1.0f, 0.85f, 0.0f);
        }

        for (float i = -1.5f; i <= 1.5f; i += 0.8f) {
            float sy = i + sceneryY;

            if (sy > 1.2f)
                sy -= 2.4f;

            if (sy < -1.2f)
                sy += 2.4f;

            drawTree(-0.92f, sy);
            drawBuilding(0.92f, sy + 0.3f);
            drawStreetlight(-0.88f, sy - 0.2f);
        }
    }


    void drawBaseCar(float x, float y,
                     float r, float g, float b,
                     bool police) {
        glPushMatrix();

        glTranslatef(x, y, 0.0f);
        glScalef(CAR_SCALE, CAR_SCALE, 1.0f);

        drawRectangle(-0.13f, 0.13f,
                      0.18f, -0.18f,
                      r, g, b);

        drawRectangle(-0.09f, 0.09f,
                      0.12f, 0.02f,
                      r * 0.80f,
                      g * 0.80f,
                      b * 0.80f);

        drawRectangle(-0.07f, 0.07f,
                      0.08f, 0.01f,
                      0.20f, 0.60f, 0.90f);

        drawRectangle(-0.10f, -0.06f,
                      0.18f, 0.14f,
                      1.0f, 1.0f, 0.2f);

        drawRectangle(0.06f, 0.10f,
                      0.18f, 0.14f,
                      1.0f, 1.0f, 0.2f);

        drawRectangle(-0.17f, -0.11f,
                      0.12f, -0.11f,
                      0.05f, 0.05f, 0.05f);

        drawRectangle(0.11f, 0.17f,
                      0.12f, -0.11f,
                      0.05f, 0.05f, 0.05f);

        if (police) {
            drawRectangle(-0.13f, 0.13f,
                          0.05f, -0.04f,
                          0.05f, 0.15f, 0.55f);

            drawRectangle(-0.04f, 0.04f,
                          0.16f, 0.12f,
                          0.90f, 0.00f, 0.00f);
        }

        glPopMatrix();
    }

    void drawPlayerCar() {
        glPushMatrix();

        glTranslatef(playerX, playerY, 0.0f);
        glScalef(CAR_SCALE, CAR_SCALE, 1.0f);

        drawRectangle(-0.13f, 0.13f,
                      0.18f, -0.18f,
                      0.0f, 0.25f, 1.0f);

        drawRectangle(-0.10f, 0.10f,
                      0.23f, 0.10f,
                      0.0f, 0.35f, 1.0f);

        drawRectangle(-0.08f, 0.08f,
                      0.08f, -0.01f,
                      0.45f, 0.80f, 1.0f);

        drawRectangle(-0.105f, -0.065f,
                      0.18f, 0.14f,
                      1.0f, 1.0f, 0.3f);

        drawRectangle(0.065f, 0.105f,
                      0.18f, 0.14f,
                      1.0f, 1.0f, 0.3f);

        drawRectangle(-0.17f, -0.11f,
                      0.13f, -0.10f,
                      0.02f, 0.02f, 0.02f);

        drawRectangle(0.11f, 0.17f,
                      0.13f, -0.10f,
                      0.02f, 0.02f, 0.02f);

        glPopMatrix();
    }

    void drawEnemyCar(float x, float y, int type) {
        if (type == 0)
            drawBaseCar(x, y, 0.90f, 0.02f, 0.02f,false);

        else if (type == 1)
            drawBaseCar(x, y,1.0f, 0.75f, 0.0f,false);

        else if (type == 2)
            drawBaseCar(x, y,0.85f, 0.85f, 0.85f,true);

        else
            drawBaseCar(x,y,0.0, 0.0, 0.0, false);
    }

    void drawRain() {
        if (!isRaining)
            return;

        glColor3f(0.50f, 0.70f, 1.0f);

        glBegin(GL_LINES);

        for (int i = 0; i < MAX_RAINDROPS; i++) {
            glVertex2f(rainX[i], rainY[i]);
            glVertex2f(rainX[i] - 0.02f,
                       rainY[i] - 0.08f);
        }

        glEnd();
    }

    void drawExplosion() {
        if (!crashState)
            return;

        drawCircle(playerX, playerY,
                    explosionRadius,
                    1.0f, 0.50f, 0.0f);

        drawCircle(playerX, playerY,
                    explosionRadius * 0.70f,
                    1.0f, 0.20f, 0.0f);

        drawCircle(playerX, playerY,
                    explosionRadius * 0.40f,
                    1.0f, 1.0f, 0.0f);
    }

    float randomLane() {
        int lane = rand() % 3;

        if (lane == 0)
            return -0.55f;

        if (lane == 1)
            return 0.0f;

        return 0.55f;
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT);

        if (!gameStarted) {
            drawStartScreen();
        }
        else {
            drawRoad();

            drawEnemyCar(enemy1X, enemy1Y, enemy1Type);
            drawEnemyCar(enemy2X, enemy2Y, enemy2Type);

            if (!crashState)
                drawPlayerCar();

            drawExplosion();
            drawRain();
            drawHUD();

            if (isPaused && !gameOver) {
                drawRectangle(-0.30f, 0.30f,
                              0.10f, -0.10f,
                              0.0f, 0.0f, 0.0f);

                drawText(-0.10f, -0.02f, "PAUSED");
            }

            if (gameOver) {
                drawRectangle(-0.40f, 0.40f,
                              0.20f, -0.20f,
                              0.0f, 0.0f, 0.0f);

                drawText(-0.18f, 0.05f, "GAME OVER");
                drawText(-0.25f, -0.05f, "Press R to Restart");
                drawText(-0.20f, -0.15f, "Press X to Exit");
            }
        }

        glutSwapBuffers();
    }

    void keyboard(unsigned char key, int x, int y) {
        switch (key) {
        case ' ':
            if (!gameStarted) {
                gameStarted = true;
                PlaySound(NULL, NULL, 0);
                PlaySound(TEXT("background.wav"), NULL,
                          SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
            }
            break;

        case 'p':
        case 'P':
            if (gameStarted && !gameOver)
                isPaused = !isPaused;
            break;

        case 'a':
        case 'A':
            if (gameStarted && !isPaused && !gameOver &&
                playerX > -0.65f)
                playerX -= 0.07f;

            break;

        case 'd':
        case 'D':
            if (gameStarted && !isPaused && !gameOver &&
                playerX < 0.65f)
                playerX += 0.05f;
            break;

        case 'w':
        case 'W':
            if (gameStarted && !isPaused && !gameOver &&
                playerY < 0.70f)
                playerY += 0.05f;
            break;

        case 's':
        case 'S':
            if (gameStarted && !isPaused && !gameOver &&
                playerY > -0.85f)
                playerY -= 0.05f;
            break;

        case 'v':
        case 'V':
            isRaining = !isRaining;
            break;

        case 'r':
        case 'R':
            playerX = 0.0f;
            playerY = -0.65f;

            enemy1X = -0.55f;
            enemy2X = 0.55f;

            enemy1Y = 1.30f;
            enemy2Y = 1.80f;

            enemy1Type = 0;
            enemy2Type = 1;

            score = 0;

            speed = 0.014f;

            gameOver = false;
            crashState = false;
            explosionRadius = 0.0f;
            isPaused = false;

            PlaySound(NULL, NULL, 0);
            if (gameStarted)
                PlaySound(TEXT("background.wav"), NULL,
                          SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
            break;

        case 'x':
        case 'X':
            PlaySound(NULL, NULL, 0);
            exit(0);
            break;
        }

        glutPostRedisplay();
    }

    void specialKeyboard(int key, int x, int y) {
        if (!gameStarted || isPaused || gameOver)
            return;

        switch (key) {
        case GLUT_KEY_LEFT:
            if (playerX > -0.65f)
                playerX -= 0.07f;
            break;

        case GLUT_KEY_RIGHT:
            if (playerX < 0.65f)
                playerX += 0.07f;
            break;

        case GLUT_KEY_UP:
            if (playerY < 0.70f)
                playerY += 0.05f;
            break;

        case GLUT_KEY_DOWN:
            if (playerY > -0.85f)
                playerY -= 0.05f;
            break;
        }

        glutPostRedisplay();
    }

    void update(int value) {
        if (gameStarted && !isPaused) {

            if (!gameOver) {

                sceneryY -= speed;

                if (sceneryY < -0.8f)
                    sceneryY += 0.8f;

                enemy1Y -= speed;
                enemy2Y -= speed;

                if (enemy1Type == 2) {
                    if (enemy1X < playerX)
                        enemy1X += 0.006f;
                    else
                        enemy1X -= 0.006f;
                }

                if (enemy2Type == 2) {
                    if (enemy2X < playerX)
                        enemy2X += 0.006f;
                    else
                        enemy2X -= 0.006f;
                }

                if (enemy1Y < -1.25f) {
                    enemy1Y = 1.25f;
                    enemy1X = randomLane();
                    enemy1Type = rand() % 4;
                    score++;
                }

                if (enemy2Y < -1.25f) {
                    enemy2Y = 1.55f;
                    enemy2X = randomLane();
                    enemy2Type = rand() % 4;
                    score++;
                }

                if (score >= 10)
                    speed = 0.018f;

                if (score >= 20)
                    speed = 0.020f;

                if (score >= 30)
                    speed = 0.021f;

                if (score >= 40)
                    speed = 0.022f;

                Rect player(playerX - 0.09f,
                            playerX + 0.09f,
                            playerY + 0.10f,
                            playerY - 0.10f);

                Rect enemy1(enemy1X - 0.10f,
                            enemy1X + 0.10f,
                            enemy1Y + 0.14f,
                            enemy1Y - 0.14f);

                Rect enemy2(enemy2X - 0.10f,
                            enemy2X + 0.10f,
                            enemy2Y + 0.14f,
                            enemy2Y - 0.14f);

                if (player.checkCollision(enemy1) ||
                    player.checkCollision(enemy2)) {

                    gameOver = true;
                    crashState = true;
                    explosionRadius = 0.0f;

                    PlaySound(NULL, NULL, 0);
                    PlaySound(TEXT("over.wav"),
                              NULL,
                              SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
                }
            }
            else if (crashState) {

                explosionRadius += 0.02f;

                if (explosionRadius > 0.40f)
                    crashState = false;
            }

            if (isRaining) {

                for (int i = 0; i < MAX_RAINDROPS; i++) {

                    rainY[i] -= 0.06f;
                    rainX[i] -= 0.01f;

                    if (rainY[i] < -1.0f) {
                        rainY[i] = 1.0f;

                        rainX[i] =
                            ((float)(rand() % 200) / 100.0f) - 1.0f;
                    }
                }
            }
        }

        glutPostRedisplay();

        glutTimerFunc(16, update, 0);
    }

    int main(int argc, char** argv) {

        srand(time(0));

        for (int i = 0; i < MAX_RAINDROPS; i++) {
            rainX[i] =
                ((float)(rand() % 200) / 100.0f) - 1.0f;

            rainY[i] =
                ((float)(rand() % 200) / 100.0f) - 1.0f;
        }

        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

        glutInitWindowSize(850, 850);

        glutCreateWindow("2D Car Racing Game");

        //PlaySound(TEXT("start.wav"), NULL,
                 //0.014 SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKeyboard);

        glutTimerFunc(0, update, 0);

        glutMainLoop();

        return 0;
}
