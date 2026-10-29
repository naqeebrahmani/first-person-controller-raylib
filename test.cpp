/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "raymath.h"

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	Camera3D cam = { 0 };

	cam.fovy = 45.0f;
	cam.up.y = 1;
	cam.target.x = 1;
	cam.position.x = -10;
	cam.position.y = 1;

	Vector2 viewAngles = { 0,0 };

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// rotate the camera
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			viewAngles.x += GetMouseDelta().x * 0.1f;
			viewAngles.y -= GetMouseDelta().y * 0.1f;
		}

		// clamp the up /down
		float upLimit = -89.995f;
		float downLimit = 89.995f;
		if (viewAngles.y > downLimit) viewAngles.y = downLimit;
		if (viewAngles.y < upLimit) viewAngles.y = upLimit;

		// compute the vector in the XZ plane for the forward direction and the vector in the perpendicular plane for the tilt direction
		Vector2 forward = Vector2Rotate((Vector2) { 1, 0 }, viewAngles.x* DEG2RAD);
		Vector2 tilt = Vector2Rotate((Vector2) { 1, 0 }, viewAngles.y* DEG2RAD);

		// compute a new target
		Vector3 target = cam.position;
		target.x += forward.x;
		target.y += tilt.y;
		target.z += forward.y;

		cam.target = target;

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		BeginMode3D(cam);
		DrawGrid(10, 1.0f);
		DrawCube((Vector3) { 0, 0.5f, 0 }, 1.0f, 1.0f, 1.0f, RED);
		EndMode3D();
		// end the frame and get ready for the next one  (display frame, poll input, etc...)

		DrawText(TextFormat("Camera Position: (%.2f, %.2f, %.2f)", cam.position.x, cam.position.y, cam.position.z), 10, 10, 20, WHITE);
		DrawText(TextFormat("Camera Vector: (%.2f, %.2f, %.2f)", forward.x, tilt, forward.y), 10, 40, 20, WHITE);
		DrawText(TextFormat("Camera Angles: (%.2f, %.2f, %.2f)", viewAngles.x, viewAngles.y), 10, 70, 20, WHITE);
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}