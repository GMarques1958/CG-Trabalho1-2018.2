#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>
#include <vector>
#include <algorithm>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

///****Estrutura Point, parametros pos_x (posição em x) e pos_y (posição em y)****
struct Point{
    int pos_x, pos_y;
    Point(int pos_x, int pos_y){
        this->pos_x = pos_x;
        this->pos_y = pos_y;
    };
    Point(){
    }
    bool operator <(Point & p){
        return pos_y<p.pos_y;
    }
};
///*******************************************************************************

///****Estrutura Color****
struct Color{
    unsigned char R,G,B,A;
};
///***********************

///****Rasterizar Ponto na Tela****
void PutPixel(Point p, Color c){
    int adr = p.pos_x*4 + p.pos_y*4*IMAGE_WIDTH;
    FBptr[adr] = c.R;
    FBptr[adr+1] = c.G;
    FBptr[adr+2] = c.B;
    FBptr[adr+3] = 255;
}
///********************************

Color ColorInterpolation(float colorDist, Color ci, Color cf){

    Color actualColor;
    actualColor.R = ci.R - colorDist*(ci.R - cf.R);
    actualColor.G = ci.G - colorDist*(ci.G - cf.G);
    actualColor.B = ci.B - colorDist*(ci.B - cf.B);
    actualColor.A = 255;

    return actualColor;
}

void DrawLine(Point v1, Color c1, Point v2, Color c2){

    int signal = 1;
    int count = 0;
    float colorDist;
    Color actualColor;

    if (v2.pos_x<v1.pos_x){
        DrawLine(v2,c2,v1,c1);
        return;
    }
    int dx = v2.pos_x - v1.pos_x;
    int dy = v2.pos_y - v1.pos_y;

    if(v1.pos_y>v2.pos_y){
        signal = -1;
        dy = signal*dy;
    }

    if(dx<dy){
        int d = 2*dx - dy;
        int prox_e = 2*dx;
        int prox_ne = 2*(dx-dy);
        int x = v1.pos_x;
        int y = v1.pos_y;
        PutPixel(Point(x,y), c1);

        while (y != v2.pos_y){
            if (d<=0){
                d += prox_e;
                y += signal;
            }
            else {
                d += prox_ne;
                x++;
                y+=signal;
            }
            count++;
            colorDist = ((float)count/(float)dy);
            actualColor = ColorInterpolation(colorDist, c1, c2);
            PutPixel(Point(x,y), actualColor);
        }
    }
    else{
        int d = 2*dy - dx;
        int prox_e = 2*dy;
        int prox_ne = 2*(dy-dx);
        int x = v1.pos_x;
        int y = v1.pos_y;
        PutPixel(Point(x,y), c1);

        while (x != v2.pos_x){
            if (d<=0){
                d += prox_e;
                x++;
            }
            else {
                d += prox_ne;
                x++;
                y+=signal;
            }
            count++;
            colorDist = ((float)count/(float)dx);
            actualColor = ColorInterpolation(colorDist, c1, c2);
            PutPixel(Point(x,y), actualColor);
        }
    }
}

void DrawTriangle(Point v1, Color c1, Point v2, Color c2, Point v3, Color c3){
    DrawLine(v1,c1,v2,c2);
    DrawLine(v2,c2,v3,c3);
    DrawLine(v3,c3,v1,c1);

}


float toRadians(float degrees) {
  return (degrees * 3.1415926535) / 180.0f;
}

void DrawCircleArc(Point center, float radius, Color c1, float angle, float angle_var){


    PutPixel(center, c1);

    float angle_aux = 0.0f;

    while(angle_aux <= angle) {

        float theta = toRadians(angle_aux);

        int x = center.pos_x + round(radius * cos((theta+angle_var)));
        int y = center.pos_y - round(radius * sin((theta+angle_var)));

        PutPixel(Point(x,y), c1);
        angle_aux += 0.5f;

    }

}

void colorFillBottomTriangle(Point v1, Point v2, Point v3, Color c1){

    float L1, L2, X_begin, X_end;
    L1 = ((float)(v2.pos_x - v1.pos_x))/((float)(v2.pos_y - v1.pos_y));
    L2 = ((float)(v3.pos_x - v1.pos_x))/((float)(v3.pos_y - v1.pos_y));

    X_begin = v1.pos_x;
    X_end = v1.pos_x;

    for(int ScanLineY = v1.pos_y; ScanLineY <= v2.pos_y; ScanLineY++){

        DrawLine(Point(round(X_begin),ScanLineY), c1, Point(round(X_end), ScanLineY), c1);
        X_begin += L1;
        X_end += L2;

    }

}

void colorFillTopTriangle(Point v1, Point v2, Point v3, Color c1){

    float L1, L2, X_begin, X_end;
    L1 = ((float)(v3.pos_x - v1.pos_x))/((float)(v3.pos_y - v1.pos_y));
    L2 = ((float)(v3.pos_x - v2.pos_x))/((float)(v3.pos_y - v2.pos_y));

    X_begin = v3.pos_x;
    X_end = v3.pos_x;

    for(int ScanLineY = v3.pos_y; ScanLineY > v1.pos_y; ScanLineY--){

        DrawLine(Point(round(X_begin),ScanLineY), c1, Point(round(X_end), ScanLineY), c1);
        X_begin -= L1;
        X_end -= L2;

    }

}

void colorFillFullTriangle(Point v1, Point v2, Point v3, Color c1){

    std::vector<Point> Vertices;
    Vertices.push_back(v1);
    Vertices.push_back(v2);
    Vertices.push_back(v3);
    std::sort(Vertices.begin(),Vertices.end());

    if(Vertices[1].pos_y == Vertices[2].pos_y){
        colorFillBottomTriangle(v1, Vertices[1], Vertices[2], c1);
    }
    else if(Vertices[0].pos_y == Vertices[1].pos_y){
        colorFillTopTriangle(Vertices[0], Vertices[1], Vertices[2], c1);
    }
    else{
        Point v4;
        v4.pos_x = round((Vertices[0].pos_x + ((float)(Vertices[1].pos_y - Vertices[0].pos_y)/(float)(Vertices[2].pos_y - Vertices[0].pos_y))*(Vertices[2].pos_x - Vertices[0].pos_x)));
        v4.pos_y = Vertices[1].pos_y;

        colorFillBottomTriangle(Vertices[0], Vertices[1], v4, c1);
        colorFillTopTriangle(Vertices[1], v4, Vertices[2], c1);
    }
}


#endif // _MYGL_H_

