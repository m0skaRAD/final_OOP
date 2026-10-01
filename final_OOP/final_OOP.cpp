#include <iostream>
using namespace std;

#include "raylib.h"
#include "raymath.h"
#include "function.h"

void Draw(const function& func, float xMin, float xMax, float zMin, float zMax, float step, Color color) {
    for (float x = xMin; x < xMax; x+=step) {
        for (float z = zMin; z < zMax; z+=step) {
            Vector3 curent = { x, func.create(x,z),z };
            Vector3 nextX = { x+step, func.create(x+step,z),z }; //x y z
            Vector3 nextZ = { x, func.create(x,z+step),z+step };

            DrawLine3D(curent, nextX, color);
            DrawLine3D(curent, nextZ, color);
        }
    }
}

void CreateAFunction(function& func) {
    cout << func.formula();
    cout << endl;
    cout << "Cin A - ";
    float a;
    cin >> a;
    func.setA(a);
    cout << "Cin B - ";
    float b;
    cin >> b;
    func.setB(b);
    cout << "Cin C - ";
    float c;
    cin >> c;
    func.setC(c);
}

int main() {

    InitWindow(1600, 900, "OOP");

    Camera3D camera = { 0 };
    camera.position = { 15, 15, 15 }; // pos
    camera.target = { 0, 0, 0 };       // pov
    camera.up = { 0, 1, 0 };           // up vector
    camera.fovy = 45;                                 // fov
    camera.projection = CAMERA_PERSPECTIVE;

    string f[7] = { "LinearFunction", "EllipticParaboloid", "Saddle", "Conus", "GaussBell", "LinearWave", "RadialWaves" };
    cout << "\n\n\n\n\n==== Program start ====" << endl;;
    cout << "Choose a formula: \n";
    cout << "\t Linear Function     = [1]\n";
    cout << "\t Elliptic Paraboloid = [2]\n";
    cout << "\t Saddle              = [3]\n";
    cout << "\t Conus               = [4]\n";
    cout << "\t Gauss Bell          = [5]\n";
    cout << "\t Linear Wave         = [6]\n";
    cout << "\t Radial Wave         = [7]\n";
    cout << "Choice: ";
    
        LinearFunction f1;
        EllipticParaboloid f2;
        Saddle f3;
        Conus f4;
        GaussBell f5;
        LinearWave f6;
        RadialWaves f7;
    
    function* ActiveFunction = nullptr;
    int ch;
    cin >> ch;
    cout << endl;
    switch (ch) {
        case 1:
            ActiveFunction = &f1;
            break;
        case 2:
            ActiveFunction = &f2;
            break;
        case 3:
            ActiveFunction = &f3;
            break;
        case 4:
            ActiveFunction = &f4;
            break;
        case 5:
            ActiveFunction = &f5;
            break;
        case 6:
            ActiveFunction = &f6;
            break;
        case 7:
            ActiveFunction = &f7;
            break;
        default:
            cout << "There are only 7 functions. \nChoosed Linear function \n";
            ActiveFunction = &f1;
    }
    CreateAFunction(*ActiveFunction);


    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            float angle = GetMouseDelta().x * 0.005f;
            camera.position = Vector3RotateByAxisAngle(camera.position, {0, 1, 0}, angle);
            float angle2 = GetMouseDelta().y * 0.005f;
            camera.position = Vector3RotateByAxisAngle(camera.position, { 1, 0, 0 }, angle2);
        }
        if (IsKeyDown(KEY_Q)) ActiveFunction->setA(ActiveFunction->getA() + 0.02);
        if (IsKeyDown(KEY_A)) ActiveFunction->setA(ActiveFunction->getA() - 0.02);
        
        if (IsKeyDown(KEY_W)) ActiveFunction->setB(ActiveFunction->getB() + 0.02);
        if (IsKeyDown(KEY_S)) ActiveFunction->setB(ActiveFunction->getB() - 0.02);
        
        if (IsKeyDown(KEY_E)) ActiveFunction->setC(ActiveFunction->getC() + 0.02);
        if (IsKeyDown(KEY_D)) ActiveFunction->setC(ActiveFunction->getC() - 0.02);
        camera.fovy -= GetMouseWheelMove() * 2.0f;

        BeginDrawing();
        ClearBackground(WHITE);

        BeginMode3D(camera);

            DrawGrid(40, 1);
            DrawCylinderEx({ 0, 0, 0 }, { 20, 0, 0 }, 0.05, 0.05, 8, BLUE);
            DrawCylinderEx({ 0, 0, 0 }, { 0, 20, 0 }, 0.05, 0.05, 8, RED);
            DrawCylinderEx({ 0, 0, 0 }, { 0, 0, 20 }, 0.05, 0.05, 8, GREEN);
            Draw(*ActiveFunction,-10, 10, -10, 10, 0.2, VIOLET);

        EndMode3D();
        DrawText(ActiveFunction->formula().c_str(), 20, 20, 20, DARKBLUE);
        
        string Sa = "A - " + to_string(ActiveFunction->getA()) + "   Q/A";
        string Sb = "B - " + to_string(ActiveFunction->getB()) + "   W/S";
        string Sc = "C - " + to_string(ActiveFunction->getC()) + "   E/D";
        DrawText(Sa.c_str(), 20, 50, 20, DARKBLUE);
        DrawText(Sb.c_str(), 20, 70, 20, DARKBLUE);
        DrawText(Sc.c_str(), 20, 90, 20, DARKBLUE);
        EndDrawing();
    }
    CloseWindow();
}