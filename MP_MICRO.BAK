#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

void delay_asm();
void drawPlant();
void drawPot();
void drawTank();
void drawPipe(int flow);
void drawDroplet(int x, int y);
void displayMoisture(float moisture);
void drawMoistureStatusBar(float moisture);
void clearScreenWithAssembly();

void clearScreenWithAssembly()
{
    asm {
        mov ah, 06h
        mov al, 00h
        mov bh, 07h
        mov cx, 0000h
        mov dx, 184Fh
        int 10h
    }
}

void delay_asm()
{
    asm mov ah, 0
    asm int 1Ah
    asm mov bx, dx

delay_lp:
    asm int 1Ah
    asm cmp dx, bx
    asm je delay_lp
}

void drawPlant()
{
    setcolor(GREEN);
    line(500, 350, 500, 300);
    line(500, 320, 490, 310);
    line(500, 320, 510, 310);
    line(500, 300, 490, 290);
    line(500, 300, 510, 290);
}

void drawPot()
{
    int pot[] = {470, 350, 530, 350, 510, 390, 490, 390, 470, 350};
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    fillpoly(5, pot);
}

void drawTank()
{
    int left=150, right=230, top=150, bottom=250;
    setcolor(WHITE);
    ellipse((left+right)/2, top, 0, 360, (right-left)/2, 10);
    rectangle(left, top, right, bottom);
    ellipse((left+right)/2, bottom, 0, 360, (right-left)/2, 10);
    setfillstyle(SOLID_FILL, BLUE);
    bar(left+1, top+10, right-1, bottom-1);
    setcolor(WHITE);
    outtextxy(155, 260, "Water Tank");
}

void drawPipe(int flow)
{
    setcolor(WHITE);
    rectangle(230, 190, 500, 210);
    if(flow)
    {
        setfillstyle(SOLID_FILL, BLUE);
        bar(231, 191, 499, 209);
    }
}

void drawDroplet(int x, int y)
{
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x, y, 3, 5);
}

void displayMoisture(float moisture)
{
    char txt[40];
    sprintf(txt, "Soil Moisture: %.1f%%", moisture);
    setcolor(WHITE);
    outtextxy(250, 50, txt);
}

void drawMoistureStatusBar(float moisture)
{
    setcolor(WHITE);
    rectangle(250, 70, 450, 90);

    if(moisture < 30.0)
    {
        setfillstyle(SOLID_FILL, RED);
        bar(251, 71, 449, 89);
        outtextxy(460, 75, "Dry Soil");
    }
    else if(moisture > 70.0)
    {
        setfillstyle(SOLID_FILL, BLUE);
        bar(251, 71, 449, 89);
        outtextxy(460, 75, "Over Moist");
    }
    else
    {
        setfillstyle(SOLID_FILL, GREEN);
        bar(251, 71, 449, 89);
        outtextxy(460, 75, "Normal");
    }
}

int main()
{
    int gd = DETECT, gm;
    float moisture;
    int dropletX, dropletYStart, dropletYEnd;
    int steps, totalDroplets, i, step, flow;
    float dy, y;
    int timeChoice;
    struct time t;

    clrscr();
    clearScreenWithAssembly();

    printf("Enter current soil moisture (in percentage): ");
    scanf("%f", &moisture);

    gettime(&t);
    if(t.ti_hour >= 19 || t.ti_hour < 6)
    {
        timeChoice = 2;
        totalDroplets = 5;
    }
    else
    {
        timeChoice = 1;
        totalDroplets = 10;
    }

    initgraph(&gd, &gm, "C:\\TC\\BGI");

    if(timeChoice == 2)
    {
        setbkcolor(DARKGRAY);
        cleardevice();
        setcolor(WHITE);
        outtextxy(260, 20, "Mode: Night");
    }
    else
    {
        setbkcolor(LIGHTBLUE);
        cleardevice();
        setcolor(WHITE);
        outtextxy(260, 20, "Mode: Day");
    }

    dropletX = 500;
    dropletYStart = 210;
    dropletYEnd = 350;
    steps = 18;
    flow = 0;

    drawPot();
    drawPlant();
    drawTank();
    drawPipe(flow);
    displayMoisture(moisture);
    drawMoistureStatusBar(moisture);
    delay(1000);

    if(moisture < 30.0)
    {
        outtextxy(250, 120, "Soil Dry! Watering Plant...");
        flow = 1;

        for(i = 0; i < totalDroplets; i++)
        {
            dy = (float)(dropletYEnd - dropletYStart) / steps;
            y = dropletYStart;

            for(step = 0; step <= steps; step++)
            {
                cleardevice();
                if(timeChoice == 2)
                    setbkcolor(DARKGRAY);
                else
                    setbkcolor(LIGHTBLUE);

                setcolor(WHITE);
                if(timeChoice == 2)
                    outtextxy(260, 20, "Mode: Night");
                else
                    outtextxy(260, 20, "Mode: Day");

                drawPot();
                drawPlant();
                drawTank();
                drawPipe(flow);
                displayMoisture(moisture);
                drawMoistureStatusBar(moisture);
                outtextxy(250, 120, "Soil Dry! Watering Plant...");
                drawDroplet(dropletX, (int)y);
                y += dy;
                delay_asm();
            }
        }
        outtextxy(250, 420, "Watering Complete!");
    }
    else if(moisture > 70.0)
    {
        outtextxy(250, 120, "Soil Over Moist - Draining...");
        flow = 1;

        for(i = 0; i < totalDroplets; i++)
        {
            dy = (float)(dropletYEnd - dropletYStart) / steps;
            y = dropletYEnd;

            for(step = 0; step <= steps; step++)
            {
                cleardevice();
                if(timeChoice == 2)
                    setbkcolor(DARKGRAY);
                else
                    setbkcolor(LIGHTBLUE);

                setcolor(WHITE);
                if(timeChoice == 2)
                    outtextxy(260, 20, "Mode: Night");
                else
                    outtextxy(260, 20, "Mode: Day");

                drawPot();
                drawPlant();
                drawTank();
                drawPipe(flow);
                displayMoisture(moisture);
                drawMoistureStatusBar(moisture);
                outtextxy(250, 120, "Soil Over Moist - Draining...");
                drawDroplet(dropletX, (int)y);
                y -= dy;
                delay_asm();
            }
        }
        outtextxy(250, 420, "Drainage Complete!");
    }
    else
    {
        outtextxy(250, 120, "Soil Moisture Normal - No Action Needed.");
    }

    getch();
    closegraph();
    return 0;
}
