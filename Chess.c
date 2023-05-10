#include <stdio.h>

/// Names- 
// Hariomkant sharma(2101CS31)
// Abhijeet kumar (2101CS02)
// Aishez singh (2101CS06)

// CHESS game for miniproject CS209 course

// it is a 2- player chess game.
// game can be played in real-time open-board style and for each turn player need to input his move as 2 coordinates, of initial and final box. like A1 A2 to move piece from A1 to A2, if there is a piece on A2 then it will be captured. first letter should be capital and input should be exactly in this formate- "A2 B4" etc. charactor ranging for A to H and number from 1 to 8.
// both players have to bind to rules of chess to ensure smooth going of game, as input mathod may generate some invalid move if player do not follow rules of chess. ( this is to be able to perform some special moves)
//moves like 'Castling' and 'en-passion' can also be performed using this input mathod( succesive input can be taken by same player to make these moves). in the end if a king is being checked and it can not defend it self  in next move, opponent have to capture king to ensure victory. to start new game at any stage , you need to reload programm.
// it is tried to keep it as simple and efficient and make it able to perform each move possible in chess. for referance, display array of piece positions is also printed in terminal at starting and after each turn.



//declaring functions to be used 
/// functions to clear screen and character buffer, setting color of a pixel and printin a character on the screen
void write_pixel(int x, int y, short colour) {
  volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
  *vga_addr=colour;
}
void clear_screen() {
  int x, y;
  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
	  write_pixel(x,y,0);
	}
  }
}
void clear_screenc() {
  int x, y;
  // clear the VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000);
  for (y = 0; y < 60; y++) {
    for (x = 0; x < 80; x++) {
      *(character_buffer + (y << 7) + x) = ' ';
    }
  }

  // clear the VGA pixel buffer
  volatile short *vga_addr=(volatile short*)(0x08000000);
  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
      *(vga_addr + (y << 8) + x) = 0x0000;
    }
  }
}
void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000 + (y<<7) + x);
  *character_buffer = c;
}

/// functions that prints green and black check boxes and board border
void green_checks(){

int x_table[4][4]={{17,69,121,173},{43,95,147,199},{17,69,121,173},{43,95,147,199}};
int y_table[8][4];
int temp=17;

for (int i = 0; i < 8; i++)
{

    for (int j = 0; j < 4; j++)
    {
        y_table[i][j]=temp;
    }
    temp+=26;
}




for (int m = 0; m < 4; m++)
{
    for (int n = 0; n < 4; n++)
    {

        int k=x_table[m][n];
       int l= y_table[m][n];
for (int i = k; i <k+ 26; i++)
{
    for (int j =l; j <l+ 26; j++)
    {
        write_pixel(i,j,0x07e0);
    }
    
}
    }
    
}

for (int m = 0; m < 4; m++)
{
    for (int n = 0; n < 4; n++)
    {

        int k=x_table[m][n];
       int l= y_table[m+4][n];
for (int i = k; i <k+ 26; i++)
{
    for (int j =l; j <l+ 26; j++)
    {
        write_pixel(i,j,0x07e0);
    }
    
}
    }
    
}
}
void black_checks(){

int x_table[4][4]={{43,95,147,199},{17,69,121,173},{43,95,147,199},{17,69,121,173}};
int y_table[8][4];
int temp=17;
for (int i = 0; i < 8; i++)
{

    for (int j = 0; j < 4; j++)
    {
        y_table[i][j]=temp;
    }
    temp+=26;
}




for (int m = 0; m < 4; m++)
{
    for (int n = 0; n < 4; n++)
    {

        int k=x_table[m][n];
       int l= y_table[m][n];
for (int i = k; i <k+ 26; i++)
{
    for (int j =l; j <l+ 26; j++)
    {
        write_pixel(i,j,0x0000);
    }
    
}
    }
    
}

for (int m = 0; m < 4; m++)
{
    for (int n = 0; n < 4; n++)
    {

        int k=x_table[m][n];
       int l= y_table[m+4][n];
for (int i = k; i <k+ 26; i++)
{
    for (int j =l; j <l+ 26; j++)
    {
        write_pixel(i,j,0x0000);
    }
    
}
    }
    
}


}
void board_border(){
       for (int x=17;x<224;x++)
   {

      write_pixel(x, 17, 0x07e0);
      write_pixel(x, 224, 0x07e0);

}
       for (int x=17;x<224;x++)
   {

      write_pixel(17, x, 0x07e0);
      write_pixel(224, x, 0x07e0);

}


}

//positon of pieces array
int position[8][8];
// piece value to be stored for each piece in position array -
// pawn =1
// knight =2
// bishop =3
// rook=4
// queen =5 
// king =6 
// for opposite side pieces
// pawn_white =11
// knight_white =12
// bishop_white =13
// rook_white=14
// queen_white =15 
// king_white =16
// as actual color of pieces is not white or black in display, standard terminology is used here for simplicity

//center point coordinate in pixel buffer of each box
int xarray[8][8];
int yarray[8][8];

//temperary but useful array used for calculation (storing coordinates of position arrary for 2 input boxes)
int position_cods[4];

// storing value of no. of captured piece of each type using display array
int display_piece_array[17];


//winning condition variables
int white_in_game;
int black_in_game;

//functions for storing coordinates of position arrary for 2 input boxes in position_cods array
void position_array_cod_initial_function(int a, int b){
int tempr= a;
a=b;
b= tempr;

a= 8-a;
b=b-1;
position_cods[0]=a;
position_cods[1]=b;

}
void position_array_cod_final_function(int a, int b){
int tempr= a;
a=b;
b= tempr;

a= 8-a;
b=b-1;
position_cods[2]=a;
position_cods[3]=b;

}

//function to paint box when a piece is moved/captured
void paint_black(int x,int y){
        int k=x;
       int l= y;
for (int i = k; i <k+ 26; i++)
{
    for (int j =l; j <l+ 26; j++)
    {
        write_pixel(i,j,0x0000);
    }
    
}
}
void paint_green(int x,int y){
        int k=x;
       int l= y;
for (int i = k; i <k+ 26; i++)
{
    for (int j =l; j <l+ 26; j++)
    {
        write_pixel(i,j,0x07e0);
    }
    
}
}

/// functions used in making pixel art of pieces
void hori(int x,int y,int x1,int x2,int y1){
// horizontal straight line
      for ( int i=x1;i< x2 +1;i++)
   {
      write_pixel(x+i, y+y1, 0xF81F);
   }
}
void ver(int x,int y,int x1,int y1,int y2){
   // vertical straight line
   for (int i = y1; i < y2+1; i++)
   {
       write_pixel(x+x1, y+i, 0xF81F);

   }
}
void hori_or(int x,int y,int x1,int x2,int y1){
// horizontal straight line
      for ( int i=x1;i< x2 +1;i++)
   {
      write_pixel(x+i, y+y1, 0xFD20);
   }
}
void ver_or(int x,int y,int x1,int y1,int y2){
   // vertical straight line
   for (int i = y1; i < y2+1; i++)
   {
       write_pixel(x+x1, y+i, 0xFD20);

   }
}


/// pieces pixel art( for every piece, I have taken its center coordinate in pixel buffer and colored its surrounding pixels to give shape to a piece )
// color of pieces can be changed by replacing existing colors
void pawn(int x,int y){

           // horizontal straight line
      for ( int i=x-2;i<x+3;i++)
   {
      write_pixel(i, y-4, 0xF81F);
   }
   // vertical straight line
   for (int i = 1; i < 4; i++)
   {
       write_pixel(x+3, y-i, 0xF81F);
      write_pixel(x-3, y-i, 0xF81F);

   }


   for ( int i=x-2;i<x+3;i++)
   {
      write_pixel(i, y, 0xF81F);
   }

   for (int i = 1; i < 3; i++)
   {
       write_pixel(x+2, y+i, 0xF81F);
      write_pixel(x-2, y+i, 0xF81F);

   }


// discreate pixel
      write_pixel(x+2, y+3, 0xF81F);
      write_pixel(x-2, y+3, 0xF81F);

      write_pixel(x+3, y+4, 0xF81F);
      write_pixel(x-3, y+4, 0xF81F);

      
      for ( int i=x-4;i<x+5;i++)
   {
      write_pixel(i, y+5, 0xF81F);
   }


      write_pixel(x+4, y+6, 0xF81F);
      write_pixel(x-4, y+6, 0xF81F);

      for ( int i=x-4;i<x+5;i++)
   {
      write_pixel(i, y+7, 0xF81F);
   }


   

}
void king(int x,int y){

write_pixel(x, y-6, 0xF81F);
write_pixel(x-1, y-6, 0xF81F);
write_pixel(x-1, y-3, 0xF81F);
write_pixel(x, y-3, 0xF81F);
write_pixel(x+2, y-3, 0xF81F);
write_pixel(x+3, y-3, 0xF81F);
write_pixel(x+4, y-3, 0xF81F);
write_pixel(x-5, y-3, 0xF81F);
write_pixel(x-4, y-3, 0xF81F);
write_pixel(x-3, y-3, 0xF81F);
write_pixel(x-2, y-2, 0xF81F);
write_pixel(x+1, y-2, 0xF81F);
write_pixel(x+2, y-1, 0xF81F);
write_pixel(x, y-1, 0xF81F);
write_pixel(x-3, y-1, 0xF81F);
write_pixel(x-1, y-1, 0xF81F);
write_pixel(x+1, y, 0xF81F);
write_pixel(x-2, y, 0xF81F);
write_pixel(x-4, y+1, 0xF81F);
write_pixel(x+3, y+1, 0xF81F);
write_pixel(x-3, y+2, 0xF81F);
write_pixel(x-2, y+2, 0xF81F);
write_pixel(x+1, y+2, 0xF81F);
write_pixel(x+2, y+2, 0xF81F);
write_pixel(x+3, y+4, 0xF81F);
write_pixel(x-4, y+4, 0xF81F);
write_pixel(x+4, y+6, 0xF81F);
write_pixel(x-5, y+6, 0xF81F);


ver(x,y,-2,-5,-4);
ver(x,y,1,-5,-4);
ver(x,y,5,-2,1);
ver(x,y,-6,-2,1);
ver(x,y,-5,2,3);
ver(x,y,4,2,3);
hori(x,y,-4,3,5);
hori(x,y,-5,4,7);

}
void rook(int x,int y){
    write_pixel(x-4, y-6, 0xF81F);
write_pixel(x-3, y-6, 0xF81F);
write_pixel(x-1, y-6, 0xF81F);
write_pixel(x+1, y-6, 0xF81F);
write_pixel(x, y-6, 0xF81F);
write_pixel(x+3, y-6, 0xF81F);
write_pixel(x+4, y-6, 0xF81F);
write_pixel(x-3, y-5, 0xF81F);
write_pixel(x-1, y-5, 0xF81F);
write_pixel(x+1, y-5, 0xF81F);
write_pixel(x+3, y-5, 0xF81F);
write_pixel(x-3, y-4, 0xF81F);
write_pixel(x-2, y-4, 0xF81F);
write_pixel(x-1, y-4, 0xF81F);
write_pixel(x+1, y-4, 0xF81F);
write_pixel(x+2, y-4, 0xF81F);
write_pixel(x+3, y-4, 0xF81F);
write_pixel(x+4, y, 0xF81F);
write_pixel(x-4, y, 0xF81F);

write_pixel(x+5, y+6, 0xF81F);
write_pixel(x-5, y+6, 0xF81F);

ver(x,y,5,-6,-2);
ver(x,y,-5,-6,-2);

hori(x,y,-5,5,-1);
hori(x,y,-3,3,1);

ver(x,y,3,2,4);
ver(x,y,-3,2,4);

hori(x,y,-5,5,7);
hori(x,y,-4,4,5);
}
void bishop(int x,int y){
    write_pixel(x, y-6, 0xF81F);
write_pixel(x-1, y-6, 0xF81F);
write_pixel(x-1, y-3, 0xF81F);
write_pixel(x, y-3, 0xF81F);
write_pixel(x+1, y-2, 0xF81F);
write_pixel(x-2, y-2, 0xF81F);
write_pixel(x+2, y-1, 0xF81F);
write_pixel(x-3, y-1, 0xF81F);
write_pixel(x+1, y, 0xF81F);
write_pixel(x, y+1, 0xF81F);
write_pixel(x-3, y+4, 0xF81F);
write_pixel(x+2, y+4, 0xF81F);
write_pixel(x+4, y+6, 0xF81F);
write_pixel(x-5, y+6, 0xF81F);

ver(x,y,-2,-5,-4);
ver(x,y,1,-5,-4);
ver(x,y,3,0,3);
ver(x,y,-4,0,3);
hori(x,y,-4,3,5);
hori(x,y,-5,4,7);
}
void queen(int x,int y){
    write_pixel(x, y-7, 0xF81F);
write_pixel(x+1, y-7, 0xF81F);
write_pixel(x, y-4, 0xF81F);
write_pixel(x+1, y-4, 0xF81F);
write_pixel(x-6, y-2, 0xF81F);
write_pixel(x+7, y-2, 0xF81F);
write_pixel(x+5, y-1, 0xF81F);
write_pixel(x-4, y-1, 0xF81F);
write_pixel(x+1, y-1, 0xF81F);
write_pixel(x, y-1, 0xF81F);
write_pixel(x+5, y-1, 0xF81F);
write_pixel(x+6, y-1, 0xF81F);
write_pixel(x+6, y, 0xF81F);
write_pixel(x+4, y, 0xF81F);
write_pixel(x+2, y, 0xF81F);
write_pixel(x-1, y, 0xF81F);
write_pixel(x-3, y, 0xF81F);
write_pixel(x-5, y, 0xF81F);
write_pixel(x-5, y+1, 0xF81F);
write_pixel(x-2, y+1, 0xF81F);
write_pixel(x+3, y+1, 0xF81F);
write_pixel(x+6, y+1, 0xF81F);
write_pixel(x-3, y+4, 0xF81F);
write_pixel(x+4, y+4, 0xF81F);
write_pixel(x+5, y+6, 0xF81F);
write_pixel(x-4, y+6, 0xF81F);


ver(x,y,-1,-6,-5);
ver(x,y,2,-6,-5);
ver(x,y,-1,-5,-6);
ver(x,y,2,-5,-6);
ver(x,y,-4,2,3);
ver(x,y,5,2,3);

hori(x,y,-3,4,5);
hori(x,y,-4,5,7);
}
void knight(int x,int y){
    hori(x,y,-3,0,-6);
hori(x,y,1,3,-5);
write_pixel(x-3, y-5, 0xF81F);
write_pixel(x-2, y-4, 0xF81F);
write_pixel(x+4, y-4, 0xF81F);
write_pixel(x-1, y-3, 0xF81F);
write_pixel(x-3, y-3, 0xF81F);
write_pixel(x-4, y-2, 0xF81F);
write_pixel(x-5, y-1, 0xF81F);
write_pixel(x-5, y, 0xF81F);
write_pixel(x-2, y, 0xF81F);
write_pixel(x-1, y, 0xF81F);
write_pixel(x-4, y+1, 0xF81F);
write_pixel(x-3, y+1, 0xF81F);
write_pixel(x, y+1, 0xF81F);
write_pixel(x-1, y+2, 0xF81F);
write_pixel(x-2, y+3, 0xF81F);
write_pixel(x+4, y+3, 0xF81F);
write_pixel(x-3, y+4, 0xF81F);
write_pixel(x+4, y+4, 0xF81F);
write_pixel(x+4, y+6, 0xF81F);
write_pixel(x-4, y+6, 0xF81F);


hori(x,y,-3,3,5);
hori(x,y,-4,4,7);
ver(x,y,5,-3,2);
}
void pawn_white(int x,int y){

           // horizontal straight line
      for ( int i=x-2;i<x+3;i++)
   {
      write_pixel(i, y-4, 0xFD20);
   }
   // vertical straight line
   for (int i = 1; i < 4; i++)
   {
       write_pixel(x+3, y-i, 0xFD20);
      write_pixel(x-3, y-i, 0xFD20);

   }


   for ( int i=x-2;i<x+3;i++)
   {
      write_pixel(i, y, 0xFD20);
   }

   for (int i = 1; i < 3; i++)
   {
       write_pixel(x+2, y+i, 0xFD20);
      write_pixel(x-2, y+i, 0xFD20);

   }


// discreate pixel
      write_pixel(x+2, y+3, 0xFD20);
      write_pixel(x-2, y+3, 0xFD20);

      write_pixel(x+3, y+4, 0xFD20);
      write_pixel(x-3, y+4, 0xFD20);

      
      for ( int i=x-4;i<x+5;i++)
   {
      write_pixel(i, y+5, 0xFD20);
   }


      write_pixel(x+4, y+6, 0xFD20);
      write_pixel(x-4, y+6, 0xFD20);

      for ( int i=x-4;i<x+5;i++)
   {
      write_pixel(i, y+7, 0xFD20);
   }


   

}
void king_white(int x,int y){

write_pixel(x, y-6, 0xFD20);
write_pixel(x-1, y-6, 0xFD20);
write_pixel(x-1, y-3, 0xFD20);
write_pixel(x, y-3, 0xFD20);
write_pixel(x+2, y-3, 0xFD20);
write_pixel(x+3, y-3, 0xFD20);
write_pixel(x+4, y-3, 0xFD20);
write_pixel(x-5, y-3, 0xFD20);
write_pixel(x-4, y-3, 0xFD20);
write_pixel(x-3, y-3, 0xFD20);
write_pixel(x-2, y-2, 0xFD20);
write_pixel(x+1, y-2, 0xFD20);
write_pixel(x+2, y-1, 0xFD20);
write_pixel(x, y-1, 0xFD20);
write_pixel(x-3, y-1, 0xFD20);
write_pixel(x-1, y-1, 0xFD20);
write_pixel(x+1, y, 0xFD20);
write_pixel(x-2, y, 0xFD20);
write_pixel(x-4, y+1, 0xFD20);
write_pixel(x+3, y+1, 0xFD20);
write_pixel(x-3, y+2, 0xFD20);
write_pixel(x-2, y+2, 0xFD20);
write_pixel(x+1, y+2, 0xFD20);
write_pixel(x+2, y+2, 0xFD20);
write_pixel(x+3, y+4, 0xFD20);
write_pixel(x-4, y+4, 0xFD20);
write_pixel(x+4, y+6, 0xFD20);
write_pixel(x-5, y+6, 0xFD20);


ver_or(x,y,-2,-5,-4);
ver_or(x,y,1,-5,-4);
ver_or(x,y,5,-2,1);
ver_or(x,y,-6,-2,1);
ver_or(x,y,-5,2,3);
ver_or(x,y,4,2,3);
hori_or(x,y,-4,3,5);
hori_or(x,y,-5,4,7);

}
void rook_white(int x,int y){
    write_pixel(x-4, y-6, 0xFD20);
write_pixel(x-3, y-6, 0xFD20);
write_pixel(x-1, y-6, 0xFD20);
write_pixel(x+1, y-6, 0xFD20);
write_pixel(x, y-6, 0xFD20);
write_pixel(x+3, y-6, 0xFD20);
write_pixel(x+4, y-6, 0xFD20);
write_pixel(x-3, y-5, 0xFD20);
write_pixel(x-1, y-5, 0xFD20);
write_pixel(x+1, y-5, 0xFD20);
write_pixel(x+3, y-5, 0xFD20);
write_pixel(x-3, y-4, 0xFD20);
write_pixel(x-2, y-4, 0xFD20);
write_pixel(x-1, y-4, 0xFD20);
write_pixel(x+1, y-4, 0xFD20);
write_pixel(x+2, y-4, 0xFD20);
write_pixel(x+3, y-4, 0xFD20);
write_pixel(x+4, y, 0xFD20);
write_pixel(x-4, y, 0xFD20);

write_pixel(x+5, y+6, 0xFD20);
write_pixel(x-5, y+6, 0xFD20);

ver_or(x,y,5,-6,-2);
ver_or(x,y,-5,-6,-2);

hori_or(x,y,-5,5,-1);
hori_or(x,y,-3,3,1);

ver_or(x,y,3,2,4);
ver_or(x,y,-3,2,4);

hori_or(x,y,-5,5,7);
hori_or(x,y,-4,4,5);
}
void bishop_white(int x,int y){
    write_pixel(x, y-6, 0xFD20);
write_pixel(x-1, y-6, 0xFD20);
write_pixel(x-1, y-3, 0xFD20);
write_pixel(x, y-3, 0xFD20);
write_pixel(x+1, y-2, 0xFD20);
write_pixel(x-2, y-2, 0xFD20);
write_pixel(x+2, y-1, 0xFD20);
write_pixel(x-3, y-1, 0xFD20);
write_pixel(x+1, y, 0xFD20);
write_pixel(x, y+1, 0xFD20);
write_pixel(x-3, y+4, 0xFD20);
write_pixel(x+2, y+4, 0xFD20);
write_pixel(x+4, y+6, 0xFD20);
write_pixel(x-5, y+6, 0xFD20);

ver_or(x,y,-2,-5,-4);
ver_or(x,y,1,-5,-4);
ver_or(x,y,3,0,3);
ver_or(x,y,-4,0,3);
hori_or(x,y,-4,3,5);
hori_or(x,y,-5,4,7);
}
void queen_white(int x,int y){
    write_pixel(x, y-7, 0xFD20);
write_pixel(x+1, y-7, 0xFD20);
write_pixel(x, y-4, 0xFD20);
write_pixel(x+1, y-4, 0xFD20);
write_pixel(x-6, y-2, 0xFD20);
write_pixel(x+7, y-2, 0xFD20);
write_pixel(x+5, y-1, 0xFD20);
write_pixel(x-4, y-1, 0xFD20);
write_pixel(x+1, y-1, 0xFD20);
write_pixel(x, y-1, 0xFD20);
write_pixel(x+5, y-1, 0xFD20);
write_pixel(x+6, y-1, 0xFD20);
write_pixel(x+6, y, 0xFD20);
write_pixel(x+4, y, 0xFD20);
write_pixel(x+2, y, 0xFD20);
write_pixel(x-1, y, 0xFD20);
write_pixel(x-3, y, 0xFD20);
write_pixel(x-5, y, 0xFD20);
write_pixel(x-5, y+1, 0xFD20);
write_pixel(x-2, y+1, 0xFD20);
write_pixel(x+3, y+1, 0xFD20);
write_pixel(x+6, y+1, 0xFD20);
write_pixel(x-3, y+4, 0xFD20);
write_pixel(x+4, y+4, 0xFD20);
write_pixel(x+5, y+6, 0xFD20);
write_pixel(x-4, y+6, 0xFD20);


ver_or(x,y,-1,-6,-5);
ver_or(x,y,2,-6,-5);
ver_or(x,y,-1,-5,-6);
ver_or(x,y,2,-5,-6);
ver_or(x,y,-4,2,3);
ver_or(x,y,5,2,3);

hori_or(x,y,-3,4,5);
hori_or(x,y,-4,5,7);
}
void knight_white(int x,int y){
    hori_or(x,y,-3,0,-6);
hori_or(x,y,1,3,-5);
write_pixel(x-3, y-5, 0xFD20);
write_pixel(x-2, y-4, 0xFD20);
write_pixel(x+4, y-4, 0xFD20);
write_pixel(x-1, y-3, 0xFD20);
write_pixel(x-3, y-3, 0xFD20);
write_pixel(x-4, y-2, 0xFD20);
write_pixel(x-5, y-1, 0xFD20);
write_pixel(x-5, y, 0xFD20);
write_pixel(x-2, y, 0xFD20);
write_pixel(x-1, y, 0xFD20);
write_pixel(x-4, y+1, 0xFD20);
write_pixel(x-3, y+1, 0xFD20);
write_pixel(x, y+1, 0xFD20);
write_pixel(x-1, y+2, 0xFD20);
write_pixel(x-2, y+3, 0xFD20);
write_pixel(x+4, y+3, 0xFD20);
write_pixel(x-3, y+4, 0xFD20);
write_pixel(x+4, y+4, 0xFD20);
write_pixel(x+4, y+6, 0xFD20);
write_pixel(x-4, y+6, 0xFD20);


hori_or(x,y,-3,3,5);
hori_or(x,y,-4,4,7);
ver_or(x,y,5,-3,2);
}

//function for every new game starting, performs some important display and backend array functions
void game_starting(){
    // placing pieces on board in starting of a new game
rook(30,30);
rook(212,30);
knight(56,30);
knight(186,30);
bishop(82,30);
bishop(160,30);
queen(108,30);
king(134,30);
for (int i = 30; i < 224; i+=26)
{
    pawn(i,56);
}


rook_white(30,212);
rook_white(212,212);
knight_white(56,212);
knight_white(186,212);
bishop_white(82,212);
bishop_white(160,212);
queen_white(108,212);
king_white(134,212);
for (int i = 30; i < 224; i+=26)
{
    pawn_white(i,186);
}

// declaring position array for each new game
for (int i = 0; i < 8; i++)
{
    for (int j = 0; j < 8; j++)
    {
        position[i][j]=0;
    }
    
}
position[0][0]=4;
position[0][7]=4;
position[0][1]=2;
position[0][6]=2;
position[0][2]=3;
position[0][5]=3;
position[0][3]=5;
position[0][4]=6;
for (int i = 0; i < 8; i++)
{
    position[1][i]=1;
}

position[7][0]=14;
position[7][7]=14;
position[7][1]=12;
position[7][6]=12;
position[7][2]=13;
position[7][5]=13;
position[7][3]=15;
position[7][4]=16;
for (int i = 0; i < 8; i++)
{
    position[6][i]=11;
}

//setting value of each  no . of captured piece to 0 (in display array)
for (int i = 0; i < 17; i++)
{
    display_piece_array[i]=0;
}
for (int i = 0; i < 4; i++)
{
    position_cods[i]=0;
}

// placing pieces in side boxes( in right)
queen_white(266,22);
rook_white(266,42);
pawn_white(266,62);
knight_white(302,22);
bishop_white(302,42);

queen(266,142);
rook(266,162);
pawn(266,182);
knight(302,142);
bishop(302,162);
}

/// function that prints names on screen in startin of every new game and after changes
void names(){
    // decalring player names, can be changed via writing them here
       char* name1 = "Hariom";
     int x1 = 62;
      while (*name1) {
        write_char(x1, 1, *name1);
   	 x1++;
   	 name1++;}

            char* name2 = "Abhijeet";
     int x2 = 62;
      while (*name2) {
        write_char(x2, 31, *name2);
   	 x2++;
   	 name2++;
   }

   // printing abcd... and 1234.. on side of board
   char* name3 = "ABCDEFGH";
     int x3 = 7;
     float xsupp = 7;
      while (*name3) {
        write_char(x3, 58, *name3);
   	 xsupp+=6.5;
     int k=(int)xsupp;
     if( k==xsupp){x3= xsupp;}
     else{x3=xsupp+1;}

   	 name3++;
   }


      char* name4 = "87654321";
     int y = 7;
     float ysupp = 7;
      while (*name4) {
        write_char(2, y, *name4);
   	 ysupp+=6.5;
     int k=(int)ysupp;
     if( k==ysupp){y= ysupp;}
     else{y=ysupp+1;}

   	 name4++;
   }
//x
// printing x for x0 on right side symbols
    write_char(67,6,'x');
    write_char(76,6,'x');
    write_char(67,11,'x');
    write_char(67,16,'x');
    write_char(76,11,'x');


        write_char(67,36,'x');
    write_char(76,36,'x');
    write_char(67,41,'x');
    write_char(67,46,'x');
    write_char(76,41,'x');


//no.


////writing value of each captured piece using display array
char queen_value= display_piece_array[5]+'0';
char knight_value= display_piece_array[2]+'0';
char rook_value= display_piece_array[4]+'0';
char bishop_value= display_piece_array[3]+'0';
char pawn_value= display_piece_array[1]+'0';

char queen_white_value= display_piece_array[15]+'0';
char knight_white_value= display_piece_array[12]+'0';
char rook_white_value= display_piece_array[14]+'0';
char bishop_white_value= display_piece_array[13]+'0';
char pawn_white_value= display_piece_array[11]+'0';
      
      
        write_char(68,6,queen_white_value);
    write_char(77,6,knight_white_value);
    write_char(68,11,rook_white_value);
    write_char(68,16,pawn_white_value);
    write_char(77,11,bishop_white_value);

        write_char(68,36,queen_value);
    write_char(77,36,knight_value);
    write_char(68,41,rook_value);
    write_char(68,46,pawn_value);
    write_char(77,41,bishop_value);


//checking for check mate conditions and congratulating winner
    if(white_in_game==1){
               char* name7 = "Congratulations!!";
     int x7 = 61;
      while (*name7) {
        write_char(x7, 25, *name7);
   	 x7++;
   	 name7++;}
     
      char* name10 = "YOU WON!!!";
     int x10 = 61;
      while (*name10) {
        write_char(x10, 27, *name10);
   	 x10++;
   	 name10++;}
     
    }

    if(black_in_game==1){
               char* name8 = "Congratulations!!";
     int x8 = 61;
      while (*name8) {
        write_char(x8, 50, *name8);
   	 x8++;
   	 name8++;}

           char* name11 = "YOU WON!!!";
     int x11 = 61;
      while (*name11) {
        write_char(x11, 52, *name11);
   	 x11++;
   	 name11++;}
    }
      
}


/// main function that puts all functions togather and perform calculation to run the game
int main () {

clear_screen();


// printing lines 
// vertical line 240
for (int i = 0; i < 240; i++)
{
    write_pixel(241,i,0x07e0);
}
//horizontal line 120
for (int i = 241; i < 321; i++)
{
    write_pixel(i,120,0x07e0);
}

// generation of board 
green_checks();
black_checks();
board_border();

// writing names of screen
names();

// placing pieces and other pixel art 
game_starting();

// defining center coordinates of each box in 2 arrays, first box has 30 and subsequently we have to add 26 
xarray[0][0]=30;
yarray[0][0]=30;
int temp=30;

for (int j = 0; j < 8; j++)
{
for (int i = 0; i < 8; i++)
{
    xarray[i][j]=temp;
}
temp+=26;
}
temp=30;

for (int j = 0; j < 8; j++)
{
for (int i = 0; i < 8; i++)
{
    yarray[j][i]=temp;
}
temp+=26;
}



// to print position array in terminal, is representing board that is displayed on screen
for (int i = 0; i < 8; i++)
{
    for (int j = 0; j < 8; j++)
    {
        printf("%4d",position[i][j]);
        printf("  ");
    }
    printf("\n");
}



/// for each turn of players loop iterate
while(1){
    
/////execution of calculations////


// taking 4 characters as input (coordinate of initial and final box) and converting them to make suitable for calculation
char a,b,c,d;

scanf("%c %c %c %c",&a,&b,&c,&d);
printf("%c %c %c %c \n",a,b,c,d);
a=a-64;
c=c-64;
b=b-48;
d=d-48;

int g= (int)a;
int h= (int)b;
int r= (int)c;
int s= (int)d;


// storing positon array coordinate for boxes that are entered by using functions
position_array_cod_initial_function(g,h);
position_array_cod_final_function(r,s);

// retriving centere coordinates of pixel buffer for initial and final boxes
int center_x_initial=xarray[position_cods[0]][position_cods[1]];
int center_y_initial=yarray[position_cods[0]][position_cods[1]];

int starting_of_box_x_initial= center_x_initial-13;
int starting_of_box_y_initial= center_y_initial-13;

int center_x_final=xarray[position_cods[2]][position_cods[3]];
int center_y_final=yarray[position_cods[2]][position_cods[3]];

int starting_of_box_x_final= center_x_final-13;
int starting_of_box_y_final= center_y_final-13;

// using stating pixel coordinates to paint intial and final box after moving to new box and before reaching to final box
if((g+h)%2==0){paint_black(starting_of_box_x_initial,starting_of_box_y_initial);}
else{paint_green(starting_of_box_x_initial,starting_of_box_y_initial);}

if((r+s)%2==0){paint_black(starting_of_box_x_final,starting_of_box_y_final);}
else{paint_green(starting_of_box_x_final,starting_of_box_y_final);}


// instead of using above mathod we can just simply regenrate whole board, but it may give some delay
// green_checks();
// black_checks();

// taking value of piece that is moved and that is captured
int piece_moved= position[position_cods[0]][position_cods[1]];
position[position_cods[0]][position_cods[1]]=0;

int piece_captured= position[position_cods[2]][position_cods[3]];
position[position_cods[2]][position_cods[3]]=piece_moved;

//capturing
if(piece_captured!=0){
display_piece_array[piece_captured]++;
}

//printing new position of pieces( after moving and capturing operations)
for (int i = 0; i < 8; i++)
{
    for (int j = 0; j < 8; j++)
    {
        switch (position[i][j])
{
case 1:
    pawn(xarray[i][j],yarray[i][j]);
    break;
case 2:
    knight(xarray[i][j],yarray[i][j]);
    break;
case 3:
    bishop(xarray[i][j],yarray[i][j]);
    break;
case 4:
    rook(xarray[i][j],yarray[i][j]);
    break;
case 5:
    queen(xarray[i][j],yarray[i][j]);
    break;
case 6:
    king(xarray[i][j],yarray[i][j]);
    break;

    case 11:
    pawn_white(xarray[i][j],yarray[i][j]);
    break;
case 12:
    knight_white(xarray[i][j],yarray[i][j]);
    break;
case 13:
    bishop_white(xarray[i][j],yarray[i][j]);
    break;
case 14:
    rook_white(xarray[i][j],yarray[i][j]);
    break;
case 15:
    queen_white(xarray[i][j],yarray[i][j]);
    break;
case 16:
    king_white(xarray[i][j],yarray[i][j]);
    break;
default:
    break;
}
    }
    
}


// to print position array after  each turn in terminal
for (int i = 0; i < 8; i++)
{
    for (int j = 0; j < 8; j++)
    {
        printf("%4d ",position[i][j]);
        printf("  ");
    }
    printf("\n");
}

// checking for winneing condition after each turn 
white_in_game=1;
black_in_game=1;
for (int i = 0; i < 8; i++)
{
    for (int j = 0; j < 8; j++)
    {
        if(position[i][j]==16){white_in_game=0;}
        if(position[i][j]==6){black_in_game=0;}
    }
    
}

// completing board and updating names
board_border();
names();

}
// turn ends


//function used in green and black checks to paint a box which has starting point k,k
// for (int i = k; i <k+ 43; i++)
// {
//     for (int j =k; j <k+ 43; j++)
//     {
//         write_pixel(i,j,0x07e0);
//     }
    
// }

      return 0;

      //end of main function
}