#include <raylib.h>


class Player{

    Vector3 position;

    Vector3 velocity{0, 0, 0};

    Camera3D camera;

    public:

    Player(Vector3 position){
        this->position = position;

        this->camera.fovy = 90;
        this->camera.position = position;
        this->camera.position.y = position.y + 1.0;
        this->camera.target = Vector3{0, 0, 10};
        this->camera.up = {0, 1, 0};
        this->camera.projection = CAMERA_PERSPECTIVE;

        SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
        DisableCursor();

    
    }


    Camera3D *ReturnCamera(){
        return &this->camera;
    }

    void UpdateCam(){

        

    }

};



int main(){

    InitWindow(1280, 720, "FPS-CONTROLLER");

    Player player{Vector3{0, 0, 0}};


    while(!WindowShouldClose()){


        //2d drawing
        BeginDrawing();

        ClearBackground(WHITE);


        //3d drawing
        BeginMode3D(*player.ReturnCamera());

        //drawing the floor
        DrawCube(Vector3{0, -0.5, 0}, 25, 1, 25, GRAY); 


        EndMode3D();

        //more 2d drawing

        //the crosshair
        DrawLineEx(Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f - 10}, Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f + 10}, 3.0f, BLACK);
         DrawLineEx(Vector2{GetScreenWidth()/2.0f - 10.0f, GetScreenHeight()/2.0f}, Vector2{GetScreenWidth()/2.0f + 10.0f, GetScreenHeight()/2.0f}, 3.0f, BLACK);
        //////////////

        EndDrawing();

        //updating the camera
        player.UpdateCam();

    

    }



    return 0;
}