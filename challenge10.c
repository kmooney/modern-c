#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<tgmath.h>
#include "raylib.h"


#define NUM_PROCESSES 8

typedef enum {
  NONE = 0,
  COLOR_GRAYSCALE = 1,
  COLOR_TINT = 2,
  COLOR_INVERT = 4,
  COLOR_CONTRAST = 8,
  COLOR_BRIGHTNESS = 16,
  FLIP_VERTICAL = 32,
  FLIP_HORIZONTAL = 64
} ImageProcess;

static const char* processText[] = {
  "RESET",
  "GRAYSCALE",
  "TINT",
  "INVERT",
  "CONTRAST",
  "BRIGHTNESS",
  "VERTICAL FLIP",
  "HORIZONTAL FLIP",
};

typedef struct Amounts {
  long contrast;
  long brightness;
} Amounts;

int main(int argc, char* argv[1]) {
  assert(argc == 2);

	Image imOrigin = LoadImage(argv[1]);

	const int screenWidth = imOrigin.width + (imOrigin.width / 3);
	const int screenHeight = imOrigin.height;
	InitWindow(screenWidth, screenHeight, "Modern C - Challenge 10");
	ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	Texture2D texture = LoadTextureFromImage(imOrigin);
	Image imCopy = ImageCopy(imOrigin);
	int currentProcess = NONE;
	bool textureReload = false;

	Rectangle toggleRecs[NUM_PROCESSES] = { 0 };
	int mouseHoverRec = -1;

	for (int i = 0; i < NUM_PROCESSES; i++) toggleRecs[i] = (Rectangle){ 40.0f, (float)(50 + 32*i), 150.0f, 30.0f };
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		for (int i = 0; i < NUM_PROCESSES; i++) {
			if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i])) {
				mouseHoverRec = i;
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
          if (i) {
					  currentProcess ^= (int)exp2(i-1);
          } else {
            currentProcess = i;
          }
					textureReload = true;
				}
				break;
			} else { 
				mouseHoverRec = -1;
			}
		}

		if (textureReload) {
			UnloadImage(imCopy);
			imCopy = ImageCopy(imOrigin);
      if (currentProcess) {
         if (currentProcess & COLOR_GRAYSCALE) ImageColorGrayscale(&imCopy);
         if (currentProcess & COLOR_TINT) ImageColorTint(&imCopy, GREEN);
         if (currentProcess & COLOR_INVERT) ImageColorInvert(&imCopy);
         if (currentProcess & COLOR_CONTRAST) ImageColorContrast(&imCopy, 50);
         if (currentProcess & COLOR_BRIGHTNESS) ImageColorBrightness(&imCopy, -50);
         if (currentProcess & FLIP_VERTICAL) ImageFlipVertical(&imCopy);
         if (currentProcess & FLIP_HORIZONTAL) ImageFlipHorizontal(&imCopy);
      }
			Color *pixels = LoadImageColors(imCopy); // Load pixel data from image (RGBA 32bit)
			UpdateTexture(texture, pixels);
			UnloadImageColors(pixels);
			textureReload = false;
		}

		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("Image Processing:", 40, 30, 10, DARKGRAY);
    char str[100];
    sprintf(str, "0x%X", currentProcess);
		DrawText(str, 40, screenHeight - 100, 10, DARKGRAY);

		DrawTexture(texture, screenWidth - texture.width - 60, screenHeight/2 - texture.height/2, WHITE);
		DrawRectangleLines(screenWidth - texture.width - 60, screenHeight/2 - texture.height/2, texture.width, texture.height, BLACK);

		// draw rects
		for (int i = 0; i < NUM_PROCESSES; i++) {
			DrawRectangleRec(toggleRecs[i], currentProcess & (int)exp2(i-1) || (i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY);
			DrawRectangleLines(
					(int) toggleRecs[i].x,
					(int) toggleRecs[i].y,
					(int) toggleRecs[i].width,
					(int) toggleRecs[i].height,
					((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY
					);
			DrawText(
        processText[i], 
        (int)(toggleRecs[i].x + toggleRecs[i].width/2 - MeasureText(processText[i], 10)/2),
        (int)toggleRecs[i].y + 11,
        10, 
        ((currentProcess & (int)exp2(i-1)) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY
			);
		}


		EndDrawing();
	}
	UnloadTexture(texture);
	UnloadImage(imOrigin);
	UnloadImage(imCopy);
	CloseWindow();

	return EXIT_SUCCESS;
}
