#include <iostream>
#include <cstdlib>
#include <raylib.h>



class Player{

    float speed = 20.0f;

    Vector3 position{};

    Vector3 rotation{};

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

    void MovePlayer(float delta){ //velocity is not normalized as of now

        

        if(IsKeyDown(KEY_W)){ 
            this->velocity.z = 1;
        }
        if(IsKeyDown(KEY_S)){
            this->velocity.z = -1;
        }
        if(IsKeyDown(KEY_A)){
            this->velocity.x = -1;
        }
        if(IsKeyDown(KEY_D)){
            this->velocity.x = 1;
        }

        //if(IsKeyUp(KEY_W) && IsKeyUp(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D)){
        //    this->velocity = Vector3{};
        //}



        this->velocity.x *= this->speed * delta; this->velocity.y *= this->speed * delta; this->velocity.z *= this->speed * delta; 

        this->position.x += this->velocity.x;
        this->position.y += this->velocity.y;
        this->position.z += this->velocity.z;


    }


    void UpdateCam(float delta){

        this->camera.position = this->position;
        this->camera.position.y = this->position.y + 1;



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

        system("clear");

        player.MovePlayer(GetFrameTime());

        //updating the camera
        player.UpdateCam(GetFrameTime());

    

    }



    return 0;
}