/*
 * Project: Soil Moisture–Based Automatic Watering System
 * Language: C (Turbo C Graphics)
 * Author: Niharika Kharche
 * Description:
 * A graphical simulation that automatically waters a plant based on
 * soil moisture levels and time of day (Day/Night). Uses C graphics
 * to visualize a tank, pipe, plant, and animated water droplets.
 */

#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>

// Function Declarations
void delay_asm();
void drawPlant();
void drawPot();
void drawTank();
void drawPipe(int flow);
void drawDroplet(int x, int y);
void displayMoisture(float moisture);
void drawMoistureStatusBar(float moisture);
void clearScreenWithAssembly();

/* 
 * Clears the console screen using BIOS interrupt (INT 10h)
 * for faster low-level screen reset.
 */
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

/*
 * Custom delay function using BIOS timer interrupt.
 * Provides hardware-timed animation delay.
 */
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

/*
 * Draws a simple green plant with a stem and leaves.
 */
void drawPlant()
{
    setcolor(GREEN);
    line(500, 350, 500, 300);
    line(500, 320, 490, 310);
    line(500, 320, 510, 310);
    line(500, 300, 490, 290);
    line(500, 300, 510, 290);
}

/*
 * Draws the brown pot for the plant.
 */
void drawPot()
{
    int pot[] = {470, 350, 530, 350, 510, 390, 490, 390, 470, 350};
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    fillpoly(5, pot);
}

/*
 * Draws a blue water tank with elliptical top and bottom.
 */
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

/*
 * Draws the connecting horizontal pipe.
 * When 'flow' is 1, fills it with blue to indicate water flow.
 */
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

/*
 * Draws a dark blue droplet used for animation.
 */
void drawDroplet(int x, int y)
{
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(x, y, 3, 5);
}

/*
 * Displays the current soil moisture percentage on screen.
 */
void displayMoisture(float moisture)
{
    char txt[40];
    sprintf(txt, "Soil Moisture: %.1f%%", moisture);
    setcolor(WHITE);
    outtextxy(250, 50, txt);
}

/*
 * Displays a color-coded soil condition bar:
 * Red = Dry, Green = Normal, Blue = Over Moist.
 */
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

/*
 * Main Function
 * Controls program flow: input, display, watering logic,
 * and droplet animation according to soil moisture and time of day.
 */
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

    // Determine Day/Night based on system time
    gettime(&t);
    if(t.ti_hour >= 19 || t.ti_hour < 6)
    {
        timeChoice = 2;     // Night mode
        totalDroplets = 5;  // Fewer drops at night
    }
    else
    {
        timeChoice = 1;     // Day mode
        totalDroplets = 10; // More drops during day
    }

    initgraph(&gd, &gm, "C:\\TC\\BGI");

    // Set background color based on mode
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

    // Initial setup
    dropletX = 500;
    dropletYStart = 210;
    dropletYEnd = 350;
    steps = 18;
    flow = 0;

    // Draw initial components
    drawPot();
    drawPlant();
    drawTank();
    drawPipe(flow);
    displayMoisture(moisture);
    drawMoistureStatusBar(moisture);
    delay(1000);

    // Watering / Draining Logic
    if(moisture < 30.0)     // Dry soil
    {
        outtextxy(250, 120, "Soil Dry! Watering Plant...");
        flow = 1;

        // Animate water drops
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

                // Redraw UI elements each frame
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
    else if(moisture > 70.0)  // Over-moist soil
    {
        outtextxy(250, 120, "Soil Over Moist - Draining...");
        flow = 1;

        // Animate reverse flow (draining)
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
    else   // Normal condition
    {
        outtextxy(250, 120, "Soil Moisture Normal - No Action Needed.");
    }

    getch();
    closegraph();
    return 0;
}

