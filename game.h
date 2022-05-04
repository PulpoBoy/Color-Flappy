/*
 * This file is part of PulpoBoy Flappy Bird.
 *
 * PulpoBoy Flappy Bird is free software: you can redistribute it and/or modify it under the terms of the 
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or 
 * (at your option) any later version.
 *
 * PulpoBoy Flappy Bird is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar. If not, see 
 * <https://www.gnu.org/licenses/>.
 * 
 * Some parts of code taken from: https://create.arduino.cc/projecthub/Klausj/flappy-for-the-folks-bdbf1b?f=1
 * (like about 80% was rewritten from scratch).
 * 
 * 
 */

#include <Fonts/FreeSans9pt7b.h>

#include "colors.h"
#include "bird.h"

const int birdHeight = 24;
const int birdWidth =  32;

const int birdX = 30;

const int pipeGap = birdHeight+10;

int pipeX;
int topPipeY;



bool inMenu = true;

int birdY = 50;
int oldY = 50;
int birdMenuY = 50;
int birdMenuDirection = -1;



void setup_game(){
  
}

void game_over(){
  tft.setFont(&FreeMonoBold12pt7b);
  tft.setCursor(15,50);
  tft.setTextColor(BLACK);
  tft.invertDisplay(true);
  tft.print("Game Over");
  delay(200);
  tft.invertDisplay(false);
  tft.setTextColor(WHITE);
  delay(1000);
  tft.fillScreen(BLACK);
  inMenu=true;
  birdY = 50;
}

void draw_menu(){
  tft.setFont(&FreeMonoBold12pt7b);
  tft.setTextSize(1);
  tft.setCursor(0,20);
  tft.print("Flappy Bird");
  tft.fillRect(birdX, birdMenuY, birdWidth, birdHeight, BLACK);
  tft.setAddrWindow(birdX, birdMenuY, birdX + birdWidth, birdMenuY + birdHeight);
  for (int i = 0; i < birdWidth * birdHeight; i++)
   tft.pushColor(pgm_read_word(bird_black + i));

  tft.setCursor(70,70);
  tft.setFont(&FreeSans9pt7b);
  tft.print("Press start");
}

void draw_bird(int y, int oldY){
  tft.fillRect(birdX, oldY, birdWidth, birdHeight, CYAN);
  tft.fillRect(birdX, y, birdWidth, birdHeight, CYAN);
  tft.setAddrWindow(birdX, y, birdX + birdWidth, y + birdHeight);
  for (int i = 0; i < birdWidth * birdHeight; i++)
   tft.pushColor(pgm_read_word(bird + i));

}

void display_game_logo(){
  tft.fillScreen(BLACK);
}

void update_game(){
  if (inMenu){
     birdMenuY = birdMenuY + birdMenuDirection;

     if (birdMenuY == 80){
      birdMenuDirection = -1;
     }
     else if (birdMenuY == 40){
      birdMenuDirection = 1;
     }
    
    
    if (joystick->isPress()){
        inMenu = false;
        tft.fillScreen(CYAN);
    }
  }
  else{
    oldY = birdY;
    birdY = birdY + 2;
    if (birdY+birdHeight >= 128){
      game_over();
    }
    else if (birdY <= 0){
     game_over();
    }
    
    if (joystick->isPress()){
        birdY= birdY-10;
        
    }
  }
}

void draw_game(){
  if (inMenu){
      draw_menu();
    }
  else{
    draw_bird(birdY, oldY);
  }
  
}

void delay_game(){
  delay(50);
}
