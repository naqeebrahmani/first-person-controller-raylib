#include <cmath>
#include <iostream>
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>



class Player{

    float speed = 10.0f;

    Vector3 position{};

    Vector3 rotation{};

    Vector3 velocity{0, 0, 0};

    Camera3D camera;

    float sensitivity = 1.0f;

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

        Vector3 direction{};

        //trying to get where the camera is looking at
        Vector3 cameratarget = this->camera.target; //this is "front"

        

        if(IsKeyDown(KEY_W)){ 
            direction.z = 1;
        }
        if(IsKeyDown(KEY_S)){
            direction.z = -1;
        }
        if(IsKeyDown(KEY_A)){
            direction.x = -1;
        }
        if(IsKeyDown(KEY_D)){
            direction.x = 1;
        }

        //saving the direction in velocity
        this->velocity.x = direction.x; 
        this->velocity.y = direction.y;
        this->velocity.z = direction.z;

        //adding speed
        this->velocity.x *= this->speed;
        this->velocity.y *= this->speed;
        this->velocity.z *= this->speed; 

        //moving the player
        this->position.x += this->velocity.x * delta;
        this->position.y += this->velocity.y * delta;
        this->position.z += this->velocity.z * delta;


    }


    void UpdateCam(){


        Vector2 md = GetMouseDelta();

        this->rotation.x -= md.x * sensitivity;
        this->rotation.y -= md.y * sensitivity;

        if(this->rotation.y > 90) this->rotation.y = 90;
        if(this->rotation.y < -90) this->rotation.y = -90;


        
        //finding the distance between the camera's x,z and the target's
        float d = Vector2Distance(Vector2{this->camera.position.x, this->camera.position.z}, {Vector2{this->camera.target.x, this->camera.target.z}});

        //d, d2 and d3 are the different sides of a triangle

        float d2 = sin(this->rotation.x * DEG2RAD) * d;


        float d3 = cos(this->rotation.x * DEG2RAD) * d;


        this->camera.target.x = this->camera.position.x + d2;
        this->camera.target.z = this->camera.position.z + d3;


        //d, d2 and d3 are the different sides of a triangle

        //using the sphere equation x^2 + y^2 + z^2 = r^2
        //r is distance to target
        float dx = this->camera.position.x - this->camera.target.x; float dy = this->camera.position.y - this->camera.target.y; float dz = this->camera.position.z - this->camera.target.z;
        float r = sqrt(dx*dx + dy*dy + dz*dz);
        
        

        d2 = sin(this->rotation.y * DEG2RAD) * r;

        
        this->camera.target.y = this->camera.position.y + d2;

        

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

        DrawCube(Vector3{5, 0, 7}, 1, 2, 1, RED);

        EndMode3D();

        //more 2d drawing

        //the crosshair
        DrawLineEx(Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f - 10}, Vector2{GetScreenWidth()/2.0f, GetScreenHeight()/2.0f + 10}, 3.0f, BLACK);
        DrawLineEx(Vector2{GetScreenWidth()/2.0f - 10.0f, GetScreenHeight()/2.0f}, Vector2{GetScreenWidth()/2.0f + 10.0f, GetScreenHeight()/2.0f}, 3.0f, BLACK);
        //////////////

        EndDrawing();

        system("clear");

        //player.MovePlayer(GetFrameTime());

        //updating the camera
        player.UpdateCam();

    

    }



    return 0;
}