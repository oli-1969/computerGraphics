#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;
struct Color
{
    int r;
    int g;
    int b;
};

struct Scene
{
    string scene;
    Color skyTop;
    Color skyBottom;

    Color River;
    Color ground;

    Color treeLeft;
    Color treeRight;
    Color treeBase;
    Color riverMark;
    Color groundMark;
    Color tentRoof;
    Color tentRoofdark;
    Color tentFront;
    Color tentRope;
    Color boatSails;
    Color boatMast;
    Color boatBody;
};

float boatX = 0;
int factor = 1;
unsigned long long lastFrameTime = 0;
float cloudX = 0;
float cloud2X = 500;
float cloud3X = 1000;
float cloud4X = 200;

pair<float, float> P1[4] = {{670, 230}, {600, 220}, {590, 170}, {630, 130}};
pair<float, float> P2[4] = {{670, 230}, {620, 220}, {720, 170}, {680, 130}};
vector<pair<int,int>> starArray;
float f1 = 1, f2 = 1;
Scene day = {
    "day",
    {147, 236, 244},
    {243, 240, 189},

    {154, 242, 255},
    {46, 189, 143},



    {2, 110, 123},
    {2, 148, 138},
    {70, 38, 17},
    {99, 228, 234},
    {119, 217, 185},

    {231, 144, 34},
    {220, 121, 45},
    {254, 161, 35},
    {106, 90, 73},

    {255, 255, 255},
    {135, 196, 240},
    {1, 63, 86}
};




Scene currentScene = day;

void quad(float x1, float x2, float y1, float y2, Color color, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    glVertex2f(s * x1 + Tx, s * y1 + Ty);
    glVertex2f(s * x2 + Tx, s * y1 + Ty);
    glVertex2f(s * x2 + Tx, s * y2 + Ty);
    glVertex2f(s * x1 + Tx, s * y2 + Ty);
    glEnd();
}
void circle(float x, float y, float radius, float height, Color color)
{
    int triangleAmount = 360;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(color.r, color.g, color.b);
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= 360; i++)
        glVertex2f(x + (radius * cos(i * 2 * 3.1416 / triangleAmount)), y + (height * sin(i * 2 * 3.1416 / triangleAmount)));
    glEnd();
}
void quad(vector<pair<float, float>> coord, Color color = {255, 255, 255}, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    for (int i = 0; i < coord.size(); i++)
        glVertex2d(Tx + s * coord[i].first, Ty + s * coord[i].second);
    glEnd();
}
void triangle(vector<pair<float, float>> coord, Color color = {255, 255, 255}, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < coord.size(); i++)
        glVertex2d(Tx + s * coord[i].first, Ty + s * coord[i].second);
    glEnd();
}
void polygon(vector<pair<float, float>> coord, Color color = {255, 255, 255}, float Tx = 0, float Ty = 0, float s = 1)
{
    glColor3ub(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < coord.size(); i++)
        glVertex2d(Tx + s * coord[i].first, Ty + s * coord[i].second);
    glEnd();
}


void tree(float Tx, float Ty, float s = 1, Color treeleft = {2, 110, 123}, Color treeRight = {2, 148, 138}, Color treeBase = {70, 38, 17})
{
    //left
    polygon({{Tx + s * 0, Ty + s * 48.57}, {Tx + s * -39.01, Ty + s * 48.57}, {Tx + s * -34.88, Ty + s * 75.17}, {Tx + s * -24.92, Ty + s * 61.88}, {Tx + s * -33.42, Ty + s * 84.56}, {Tx + s * -31.06, Ty + s * 99.78}, {Tx + s * -15.47, Ty + s * 66.84}, {Tx + s * -30.11, Ty + s * 105.9}, {Tx + s * -27.82, Ty + s * 120.62}, {Tx + s * -19.83, Ty + s * 103.74}, {Tx + s * -27.33, Ty + s * 123.76}, {Tx + s * -19.55, Ty + s * 173.84}, {Tx + s * -0.71, Ty + s * 149.68}, {Tx + s * -16.68, Ty + s * 192.3}, {Tx + s * -12.7, Ty + s * 217.93}, {Tx + s * -5.3, Ty + s * 208.05}, {Tx + s * -11.62, Ty + s * 224.91}, {Tx + s * -9.11, Ty + s * 241.04}, {Tx + s * -0.71, Ty + s * 226}, {Tx + s * -8.3, Ty + s * 246.25}, {Tx + s * 0, Ty + s * 299.76}}, treeleft);
    //right
    polygon({{Tx + s * 0, Ty + s * 48.57}, {Tx + s * 39.04, Ty + s * 48.57}, {Tx + s * 31.32, Ty + s * 98.28}, {Tx + s * 12.13, Ty + s * 79.1}, {Tx + s * 28.64, Ty + s * 115.48}, {Tx + s * 22.52, Ty + s * 154.9}, {Tx + s * 12.13, Ty + s * 144.51}, {Tx + s * 21.93, Ty + s * 158.73}, {Tx + s * 14.78, Ty + s * 204.74}, {Tx + s * 7.39, Ty + s * 197.36}, {Tx + s * 13.75, Ty + s * 211.36}, {Tx + s * 0, Ty + s * 299.76}}, treeRight);
    //base
    triangle({{Tx + s * 4.59, Ty + s * -0.03}, {Tx + s * -0.71, Ty + s * 219.82}, {Tx + s * -10.07, Ty + s * 0.02}, {Tx + s * -0.89, Ty + s * 46.87}, {Tx + s * -25.93, Ty + s * 98.64}, {Tx + s * -0.89, Ty + s * 61.32}, {Tx + s * -0.71, Ty + s * 64.41}, {Tx + s * 16.71, Ty + s * 100.43}, {Tx + s * -0.71, Ty + s * 74.46}, {Tx + s * -0.71, Ty + s * 86.87}, {Tx + s * 16.71, Ty + s * 122.89}, {Tx + s * -0.89, Ty + s * 96.67}, {Tx + s * -0.89, Ty + s * 109.64}, {Tx + s * -18.48, Ty + s * 146.01}, {Tx + s * -0.89, Ty + s * 119.79}, {Tx + s * -0.71, Ty + s * 148.71}, {Tx + s * 11.97, Ty + s * 175.2}, {Tx + s * -0.71, Ty + s * 156.29}, {Tx + s * -0.89, Ty + s * 169.09}, {Tx + s * -12.39, Ty + s * 192.88}, {Tx + s * -0.89, Ty + s * 175.73}, {Tx + s * -0.89, Ty + s * 132.44}, {Tx + s * -12.39, Ty + s * 156.22}, {Tx + s * -0.71, Ty + s * 138.82}}, treeBase);
}

void woodfire(float Tx = 0, float Ty = 0)
{
    polygon({{Tx+605.94,Ty+50.56},{Tx+693.96,Ty+75.16},{Tx+700.23,Ty+74.32},{Tx+702.83,Ty+71.09},{Tx+704.02,Ty+65},{Tx+701.3,Ty+58.08},{Tx+608.52,Ty+29.7}},{141,103,58});
    polygon({{Tx+700.68,Ty+50.35},{Tx+610.76,Ty+75.3},{Tx+606.1,Ty+75.09},{Tx+601.71,Ty+70.16},{Tx+601.05,Ty+63.61},{Tx+606.08,Ty+55.96},{Tx+694.57,Ty+29.17}}, {171,123,74});
    circle(697.31,105.88,5,10,{141,103,58});
    circle(607.09,105.78,5,10,{141,103,58});
}
void tent(float Tx = 0, float Ty = 0, float m = 1, Color tentRoof = {231, 144, 34}, Color tentRoofdark = {220, 121, 45}, Color tentFront = {254, 161, 35}, Color tentRope = {106, 90, 73})
{
    polygon({{Tx + m * 133.68, Ty + 209.63}, {Tx + m * 259.04, Ty + 48.56}, {Tx + m * 338.81, Ty + 90.11}, {Tx + m * 244.79, Ty + 207.92}}, tentRoof);
    polygon({{Tx + m * 106.9, Ty + 171.5}, {Tx + m * 259.04, Ty + 48.56}, {Tx + m * 133.68, Ty + 209.63}}, tentRoofdark);
    polygon({{Tx + m * 106.9, Ty + 171.5}, {Tx + m * 35.39, Ty + 69.68}, {Tx + m * 48.76, Ty + 74.43}, {Tx + m * 112.63, Ty + 166.87}}, tentRoof);
    polygon({{Tx + m * 35.39, Ty + 69.68}, {Tx + m * 46.37, Ty + 65.9}, {Tx + m * 61.53, Ty + 28.05}, {Tx + m * 65.69, Ty + 28.29}, {Tx + m * 48.76, Ty + 74.43}}, tentRoof);
    polygon({{Tx + m * 65.69, Ty + 28.29}, {Tx + m * 235.44, Ty + 15.1}, {Tx + m * 243.29, Ty + 61.29}, {Tx + m * 112.72, Ty + 167}, {Tx + m * 48.76, Ty + 74.43}}, tentFront);
    polygon({{Tx + m * 129.34, Ty + 24.23}, {Tx + m * 133.46, Ty + 141.46}, {Tx + m * 135.84, Ty + 139.65}, {Tx + m * 137.52, Ty + 23.71}}, tentRoofdark);
    polygon({{Tx + m * 243.29, Ty + 61.29}, {Tx + m * 235.44, Ty + 15.1}, {Tx + m * 314.05, Ty + 53.57}, {Tx + m * 317.81, Ty + 79.15}, {Tx + m * 259.04, Ty + 48.56}}, tentRoofdark);
    triangle({{Tx + m * 361.32, Ty + 79.37}, {Tx + m * 368.56, Ty + 79.37}, {Tx + m * 365.2, Ty + 57.39}, {Tx + m * 292.93, Ty + 26.69}, {Tx + m * 300.17, Ty + 26.69}, {Tx + m * 296.86, Ty + 2.61}, {Tx + m * 2.67, Ty + 53.7}, {Tx + m * 9.91, Ty + 53.7}, {Tx + m * 6.59, Ty + 29.62}}, tentRope);
    quad({{Tx + m * 36.47, Ty + 69.31}, {Tx + m * 2.54, Ty + 44.22}, {Tx + m * 3.54, Ty + 42.45}, {Tx + m * 37.5, Ty + 68.95}, {Tx + m * 260.36, Ty + 49.25}, {Tx + m * 300.9, Ty + 18.44}, {Tx + m * 301.29, Ty + 19.75}, {Tx + m * 261.43, Ty + 49.8}, {Tx + m * 337.36, Ty + 89.35}, {Tx + m * 368.73, Ty + 70.34}, {Tx + m * 368.98, Ty + 72.55}, {Tx + m * 338.4, Ty + 89.89}, {Tx + m * 337.36, Ty + 89.35}}, tentRope);
    glFlush();
}
void boat(float Tx = 0, float Ty = 0, float m = 1, Color boatSails = {58, 59, 95}, Color boatMast = {10, 24, 32}, Color boatBody = {98, 41, 61})
{
    polygon({{Tx + m * 0.34, Ty + 14.87}, {Tx + m * 128.31, Ty + 14.87}, {Tx + m * 138.12, Ty + 20.12}, {Tx + m * 138.12, Ty + 8.16}, {Tx + m * 137.79, Ty + 6.26}, {Tx + m * 136.91, Ty + 3.95}, {Tx + m * 135.59, Ty + 2.48}, {Tx + m * 134.24, Ty + 1.43}, {Tx + m * 132.48, Ty + 0.87}, {Tx + m * 129.5, Ty + 0.38}, {Tx + m * 126.76, Ty + 0.11}, {Tx + m * 4.1, Ty + 0.11}, {Tx + m * 0.34, Ty + 14.87}}, boatBody);
    triangle({{Tx + m * 62.27, Ty + 121.69}, {Tx + m * 2.06, Ty + 27.62}, {Tx + m * 62.27, Ty + 27.62}}, boatSails);
    triangle({{Tx + m * 62.82, Ty + 163.64}, {Tx + m * 66.01, Ty + 14.48}, {Tx + m * 121.62, Ty + 47.07}}, boatSails);
    triangle({{Tx + m * 62.82, Ty + 163.64}, {Tx + m * 44.85, Ty + 160.68}, {Tx + m * 62.8, Ty + 154.21}}, boatMast);
    triangle({{Tx + m * 62.82, Ty + 163.64}, {Tx + m * 62.49, Ty + 13.76}, {Tx + m * 66.02, Ty + 13.79}}, boatMast);
}
void plane(float Tx, float Ty, float m, Color color)
{

polygon({{Tx + m * 24.66, Ty + 14.48}, {Tx + m * 22.3, Ty + 20.41}, {Tx + m * 26.4, Ty + 21.04}, {Tx + m * 35.39, Ty + 15.27}, {Tx + m * 52.27, Ty + 16.53}, {Tx + m * 54.2, Ty + 16.33}, {Tx + m * 55.69, Ty + 15.61}, {Tx + m * 57.39, Ty + 14.16}, {Tx + m * 59.97, Ty + 13}, {Tx + m * 60.68, Ty + 11.96}, {Tx + m * 60.67, Ty + 11.21}, {Tx + m * 59.36, Ty + 10.29}, {Tx + m * 36.98, Ty + 8.35}, {Tx + m * 27.61, Ty + 0.26}, {Tx + m * 23.49, Ty + 0.3}, {Tx + m * 25.63, Ty + 7.86}, {Tx + m * 10.7, Ty + 7.96}, {Tx + m * 8.16, Ty + 8.42}, {Tx + m * 6.31, Ty + 9.62}, {Tx + m * 0.24, Ty + 17.64}, {Tx + m * 4.63, Ty + 17.82}, {Tx + m * 7.29, Ty + 15.48}, {Tx + m * 8.58, Ty + 14.35}, {Tx + m * 9.93, Ty + 13.71}, {Tx + m * 13.2, Ty + 13.62}}, {color.r, color.g, color.b});
}


void cloud1(float Tx, float Ty, float s)
{

    circle(Tx + s * 16, Ty + s * 20, 15, 15, {255, 255, 255});
    circle(Tx + s * 29, Ty + s * 31, 9, 9, {255, 255, 255});
    circle(Tx + s * 58, Ty + s * 30, 27, 27, {255, 255, 255});
    circle(Tx + s * 85, Ty + s * 21, 20, 20, {255, 255, 255});
    quad({{17, 23}, {85, 23}, {85, 1}, {17, 5}}, {255, 255, 255}, Tx, Ty, s);
}
void cloud2(float Tx, float Ty, float s)
{

    circle(Tx + s * 13, Ty + s * 16, 7, 7, {255, 255, 255});
    circle(Tx + s * 24, Ty + s * 24, 9, 9, {255, 255, 255});
    circle(Tx + s * 40, Ty + s * 32, 12, 12, {255, 255, 255});
    circle(Tx + s * 54, Ty + s * 36, 7, 7, {255, 255, 255});
    circle(Tx + s * 74, Ty + s * 40, 16, 16, {255, 255, 255});
    circle(Tx + s * 95, Ty + s * 40, 10, 10, {255, 255, 255});
    circle(Tx + s * 108, Ty + s * 34, 6, 6, {255, 255, 255});
    circle(Tx + s * 122, Ty + s * 31, 10, 10, {255, 255, 255});
    circle(Tx + s * 132, Ty + s * 25, 10, 10, {255, 255, 255});
    circle(Tx + s * 144, Ty + s * 16, 6, 6, {255, 255, 255});
    quad({{12, 18}, {146, 18}, {146, 11}, {11, 10}}, {255, 255, 255}, Tx, Ty, s);
    quad({{20, 32}, {138, 32}, {138, 17}, {20, 17}}, {255, 255, 255}, Tx, Ty, s);
}
void cloud3(float Tx, float Ty, float s)
{
    circle(Tx + s * 23, Ty + s * 33, 21, 21, {255, 255, 255});
    circle(Tx + s * 50, Ty + s * 49, 20, 20, {255, 255, 255});
    circle(Tx + s * 80, Ty + s * 43, 14, 14, {255, 255, 255});
    circle(Tx + s * 90, Ty + s * 32, 17, 17, {255, 255, 255});
    circle(Tx + s * 68, Ty + s * 23, 21, 21, {255, 255, 255});
    circle(Tx + s * 43, Ty + s * 17, 17, 17, {255, 255, 255});
    circle(Tx + s * 23, Ty + s * 33, 22, 22, {255, 255, 255});
}
int random(int low, int high)
{
    int r = rand();
    r = r % (high-low+1);
    return r+low;
}
void stars(int x1, int x2, int y1, int y2)
{
    if(starArray.size() == 0){
        for(int i=0;i<50;i++)
        {
            int size = random(2,4);

            int x = random(x1, x2), y = random(y1, y2);
            glPointSize(size);

            if(x>=1100 && x<= 1300 && y<=1000 && y>=800)
            {
                i--;
                continue;
            }
            starArray.push_back({x,y});
        }
    }
    glColor3ub(255, 255, 255);
    for(int i=0;i<starArray.size(); i++){
        glPointSize(i%3+3);
        glBegin(GL_POINTS);
        glVertex2i(starArray[i].first, starArray[i].second);
        glEnd();
    }
    glPointSize(1);
}
void display()
{

    glBegin(GL_QUADS);
    glColor3ub(currentScene.skyBottom.r, currentScene.skyBottom.g, currentScene.skyBottom.b);
    glVertex2f(0, 400);
    glVertex2f(1920,400);
    glColor3ub(currentScene.skyTop.r, currentScene.skyTop.g, currentScene.skyTop.b);
    glVertex2f(1920, 1080);
    glVertex2f(0, 1080);
    glEnd();

    if (currentScene.scene == "day")
        circle(1169, 715, 100, 100, {255, 196, 62}); //sun



    cloud1(cloudX, 950, 1);
    cloud2(cloud2X, 900, 1);
    cloud3(cloud3X, 850, 1);
    cloud3(cloud4X, 800, 1);


    quad(0, 1920, 215, 415, currentScene.River);


    polygon({{0, 415}, {0, 379.94}, {15.08, 380.05}, {53.25, 379.1}, {98.68, 377.49}, {151.66, 377.26}, {181.72, 380.16}, {208.34, 382.73}, {263.43, 388.14}, {295.28, 390.21}, {347.75, 392.74}, {372.98, 392.56}, {465.02, 391.67}, {548.34, 390.86}, {560.19, 390.93}, {622.69, 391.28}, {655.75, 391.47}, {682.28, 392.62}, {730.36, 392.72}, {785.19, 392.76}, {853.15, 392.43}, {960.38, 391.91}, {982.27, 392.74}, {1025.71, 394.38}, {1063.35, 398.64}, {1085.81, 403.06}, {1136.05, 402.43}, {1191.42, 400.79}, {1245.69, 399.33}, {1289.73, 397.87}, {1415.95, 396.25}, {1697.03, 394.75}, {1883.57, 395.43}, {1920.95, 394.11}, {1920.95, 415}}, currentScene.ground);


    tree(12, 397, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(35, 397, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(56, 397, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(88, 397, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(120, 397, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(140, 397, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(165, 397, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(180, 397, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(200, 397, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(230, 397, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(265, 410, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(355, 410, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(380, 397, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(400, 397, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(425, 397, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(445, 410, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);

    tree(700, 407, 0.25, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(720, 407, 0.35, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(740, 407, 0.30, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);

    tree(760, 407, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(790, 410, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(810, 415, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(835, 410, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(865, 410, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1020, 412, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1050, 402, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1070, 410, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);


    tree(1352, 410, 0.18, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1238, 410, 0.18, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1485, 405, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1500, 410, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1520, 405, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1550, 405, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1570, 410, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1600, 405, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);

    tree(1622, 405, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1655, 405, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1688, 410, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1720, 405, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1740, 410, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1765, 410, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1780, 405, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1800, 410, 0.5, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1830, 405, 0.4, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1865, 410, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1890, 400, 0.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1910, 410, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);


    polygon({{376.19, 358.48}, {419.81, 358.58}, {576.24, 359.22}, {556.84, 357.92}, {535.97, 357.27}, {324.01, 351.07}, {312.76, 352.21}, {305.75, 354.33}, {302.65, 356.45}, {303.81, 359.22}, {372.32, 359.29}}, currentScene.riverMark);
    polygon({{371.56, 326.76}, {401.72, 325.62}, {471.68, 328.03}, {532.49, 327.62}, {544.1, 325.67}, {551.81, 324.02}, {557.67, 319.81}, {385.19, 315.65}, {342.03, 314.88}, {338.49, 314.17}, {269.1, 314.3}, {196.6, 317.61}, {129.52, 321.47}, {4.94, 321.47}, {5.01, 326.48}, {9.06, 327.83}, {349.4, 330.36}, {366.78, 329.43}}, currentScene.riverMark);
    polygon({{722.99, 303.15}, {738.56, 302.14}, {801.07, 303.5}, {864.44, 304.45}, {891.52, 302.76}, {904.53, 299.59}, {907.92, 296.42}, {765.56, 292.61}, {613.27, 290.67}, {552.92, 293.89}, {464.39, 298.62}, {346.93, 298.56}, {346.81, 299.81}, {359.93, 304.18}, {606.62, 304.34}, {649.1, 306.2}, {717.74, 305.86}}, currentScene.riverMark);
    polygon({{662.01, 353.46}, {742.91, 353}, {934.56, 353.67}, {898.04, 351.66}, {859.69, 350.73}, {803.1, 348.92}, {760.74, 347.52}, {682.15, 345.25}, {671.42, 346.21}, {662.64, 348.75}, {660.49, 351.4}}, currentScene.riverMark);
    polygon({{830.6, 318.74}, {960.09, 319.18}, {1094.99, 315.51}, {1067.92, 307.21}, {933.51, 308.38}, {869.89, 309.96}, {847.8, 310.51}, {835.44, 312.53}, {829.84, 315.02}}, currentScene.riverMark);
    polygon({{1514.12, 326.91}, {1685.36, 325.75}, {1697.7, 321.36}, {1698.59, 319.56}, {1391.89, 314.8}, {1262.23, 321.76}, {1230.33, 321.98}, {1219.42, 321.44}, {1203.92, 321.39}, {1154.4, 321.22}, {1137.28, 322.11}, {1137.15, 323.41}, {1150.62, 327.86}, {1509.18, 329.36}}, currentScene.riverMark);
    polygon({{1444.95, 359.54}, {1717.25, 359.72}, {1677.3, 357.73}, {1594.59, 354.74}, {1474.09, 351.21}, {1457, 351.99}, {1445.33, 354.76}, {1443.81, 357.06}}, currentScene.riverMark);
    polygon({{1864.31, 303.37}, {1915.04, 302.51}, {1914.93, 292.75}, {1748.05, 290.93}, {1604.49, 298.77}, {1553.8, 297.75}, {1487.91, 298.06}, {1500.63, 304.42}, {1748.27, 304.48}, {1824.69, 306.86}, {1852.49, 307.01}, {1860.58, 305.37}}, currentScene.riverMark);
    polygon({{1803.1, 353.47}, {1801.78, 350.48}, {1810.2, 346.56}, {1827.13, 344.56}, {1914.52, 347.29}, {1914.7, 352.56}}, currentScene.riverMark);
    polygon({{1187.36, 270.55}, {1185.55, 268.53}, {1187.71, 266.2}, {1196.22, 263.62}, {1208.8, 262.16}, {1280.47, 264.54}, {1460.98, 271.41}}, currentScene.riverMark);


    if(currentScene.scene!="snow")
        boat(boatX, 250, factor, currentScene.boatSails, currentScene.boatMast, currentScene.boatBody);


    quad(0, 1920, 0, 215, currentScene.ground);


    polygon({{99.52, 76.46}, {128.62, 68.42}, {209.72, 58.32}, {141.62, 45.32}, {143.06, 38.93}, {165.97, 30.06}, {231.51, 16.77}, {230.18, 10.81}, {194.09, 1.88}, {4.7, 2.21}, {5.01, 211.23}, {35.76, 214.12}, {187.22, 209.79}, {136.87, 196.8}, {69.51, 167.05}, {141.41, 143.39}, {141.62, 121.11}, {113.14, 119.46}}, currentScene.groundMark);
    polygon({{299.17, 75.57}, {299.17, 71.6}, {390.36, 67.62}, {340.29, 60}, {300.83, 59}, {227.88, 60.99}, {235.18, 66.62}, {221.58, 73.58}, {188.75, 76.23}, {189.42, 85.84}, {302.82, 86.18}, {413.24, 81.54}}, currentScene.groundMark);
    polygon({{474.64, 10.6}, {502.9, 0.59}, {359.9, 0.73}, {325.97, 6.38}, {362.62, 9.94}, {442.64, 14.13}, {408.08, 17.26}, {296.51, 21.85}, {461.09, 31.68}, {549.82, 28.35}, {576.23, 24.71}, {543.15, 17.91}}, currentScene.groundMark);
    polygon({{807.17, 49.91}, {828.74, 48.21}, {863.17, 46.81}, {886.27, 44.18}, {859.23, 39.89}, {835.78, 38.33}, {805.44, 38.3}, {763.08, 39.98}, {782.46, 46.76}, {750.77, 50.35}, {730.82, 53.16}, {713.48, 56.93}, {730.22, 59.69}, {777.45, 61.56}, {809.1, 61.08}, {892.17, 56.96}, {909.43, 55.71}, {886.31, 53.26}, {829.61, 52.31}, {813.73, 51.01}}, currentScene.groundMark);
    polygon({{1305, 125.94}, {1372.99, 122.19}, {1401.47, 118.17}, {1339.11, 111.54}, {1247.54, 113.13}, {1275.21, 122.41}, {1214.34, 129.13}, {1186.08, 134.46}, {1213.95, 138.61}, {1293.05, 140.77}, {1431.68, 133.45}, {1396.7, 129.89}, {1316.07, 127.72}}, currentScene.groundMark);
    polygon({{1272.2, 69.89}, {1287.07, 64.06}, {1302.94, 59.43}, {1220.25, 56.5}, {1157.94, 60.53}, {1122.91, 65.33}, {1161.07, 69.36}, {1239.53, 73.27}, {1226.92, 75.41}, {1129.75, 78.32}, {1093.94, 82.56}, {1251.64, 90.19}, {1341.11, 88.15}, {1373.66, 83.54}, {1314.39, 73.7}}, currentScene.groundMark);


    tree(150, 155, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(180, 165, 0.85, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(60, 155, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(110, 70, 1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(75, 60, 0.9, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(30, 40, 1.3, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);

    tree(1900, 165, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1775, 155, 0.9, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1700, 155, 0.9, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1650, 155, 1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1550, 145, 1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1850, 140, 1, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1740, 135, 0.75, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1610, 115, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1810, 100, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1570, 90, 0.6, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1530, 80, 0.7, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1880, 70, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1730, 50, 0.75, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1650, 45, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1850, 35, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1690, 30, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1765, 25, 0.75, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1800, 20, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1610, 15, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);
    tree(1890, 10, 0.8, currentScene.treeLeft, currentScene.treeRight, currentScene.treeBase);

    tent(710, 120, 1, currentScene.tentRoof, currentScene.tentRoofdark, currentScene.tentFront, currentScene.tentRope);
    tent(590, 120, -1, currentScene.tentRoof, currentScene.tentRoofdark, currentScene.tentFront, currentScene.tentRope);



    if(currentScene.scene!="afternoon")
    {

        woodfire(0,66);
    }

    glutSwapBuffers();
}

void idle()
{
    float frameTime = 1000 / 60.0, currentTime = GetTickCount();
    if (currentTime - lastFrameTime >= frameTime)
    {
        lastFrameTime = currentTime;

        cloudX += 0.5;
        cloud2X += 0.8;
        cloud3X += 1.2;
        cloud4X += 0.7;
        if (cloudX > 1920)
        {
            cloudX = -60*3*0.5;
        }
        if(cloud2X>1920) cloud2X = -60*3*0.8;
        if(cloud3X>1920) cloud3X = -60*3*1.2;
        if(cloud4X>1920) cloud4X = -60*3*0.7;

        boatX += 3.5 * factor;
        if (boatX > 1920 + 60 * 4 * 1.5)
        {
            factor = -1;
        }
        if (boatX < -60 * 4 * 2)
        {
            factor = 1;
        }

    }

    glutPostRedisplay();
}

void init(void)
{
    glClearColor(0.0F, 0.0F, 0.0F, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1920, 0, 1080, -100, 100);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Mountain Landscape");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
}
