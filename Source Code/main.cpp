#include "main.h"
#include "mygl.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
    Point v1;
    v1.pos_x = 420;
    v1.pos_y = 50;

    Point v2;
    v2.pos_x = 255;
    v2.pos_y = 450;

    Point v3;
    v3.pos_x = 90;
    v3.pos_y = 50;

    Point v4;
    v4.pos_x = 450;
    v4.pos_y = 280;

    Point v5;
    v5.pos_x = 60;
    v5.pos_y = 280;

    Point v6;
    v6.pos_x = 501;
    v6.pos_y = 10;

    Color c1;
    c1.R = 255;
    c1.G = 0;
    c1.B = 0;
    c1.A = 255;

    Color c2;
    c2.R = 0;
    c2.G = 255;
    c2.B = 0;
    c2.A = 255;

    Color c3;
    c3.R = 0;
    c3.G = 0;
    c3.B = 255;
    c3.A = 255;

    Color c4;
    c4.R = 255;
    c4.G = 255;
    c4.B = 0;
    c4.A = 255;

    Color c5;
    c5.R = 255;
    c5.G = 0;
    c5.B = 255;
    c5.A = 255;

    Point center;
    center.pos_x = 150;
    center.pos_y = 150;

    float angle = 45.0f;
    float angle_var = 90.0f;
    float radius = 60.0f;

//    for(int j=0; j<100;j++){
//        PutPixel(v1,c1);
//        PutPixel(v2,c2);
//        PutPixel(v3,c3);
//        PutPixel(v4,c4);
//        v1.pos_y += 5;
//        v3.pos_x += 5;
//        v2.pos_y -= 5;
//        v2.pos_x -= 5;
//        v4.pos_x += 5;
//        v4.pos_y -= 5;
//    }
//    DrawLine(v1, c1, v2, c2);
//    DrawLine(v2, c2, v3, c3);
//    DrawLine(v3, c3, v4, c4);
//    DrawLine(v4, c4, v5, c5);
//    DrawLine(v5, c5, v1, c1);
//    DrawTriangle(v1,c1,v2,c2,v3,c3);
//    DrawTriangle(v5, c3, v6, c2, v1, c1);
    int j=0;
//
    while (j<8){
        DrawCircleArc(center, radius+j*10.0, c1, angle, angle_var);
        DrawCircleArc(center, radius+(j+1)*10.0, c2, angle, angle_var);
        DrawCircleArc(center, radius+(j+2)*10.0, c3, angle, angle_var);
        DrawCircleArc(center, radius+(j+3)*10, c4, angle, angle_var);
        j = j+4;
    }
    //colorFillFullTriangle(v1,v2,v3,c1);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

