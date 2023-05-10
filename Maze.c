#include <stdio.h>
#define KEY_BASE 0xFF200050


// colours 
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define GREY 0xC618
#define PINK 0xFC18
#define ORANGE 0xFC00


//maze is generated from this 2d array 
int data [12][16];


// this contain the data of maze of diffent levels ( at present 4 ) ,
// we will load the required level data in the   "data" 2d array 
int datast[4][12][16] ={ {
{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
{1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,1 },
{1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 },
{1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,1 ,1 ,1 },
{1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,0 ,0 ,1 },
{1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,1 },
{1 ,0 ,0 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 },
{1 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,1 },
{1 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 },
{1 ,0 ,1 ,1 ,1 ,1 ,0 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,0 ,1 },
{1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 },
{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
},


{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
},


{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
},


{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}

};


// these are the delay functions 

void delay()
{

    volatile int *pixel_ctrl_ptr = (int *)0xff203020;
    int status;
    *pixel_ctrl_ptr = 1;
    status = *(pixel_ctrl_ptr + 3);

    while ((status & 0x01) != 0)
    {

        status = *(pixel_ctrl_ptr + 3);
    }
}

void delayb() {
    for (int i = 0; i < 64 ; i++) {
        volatile int *pixel_ctrl_ptr = (int *)0xff203020;
        int status;
        *pixel_ctrl_ptr = 1;
        status = *(pixel_ctrl_ptr + 3);

        while ((status & 0x01) != 0) {
            status = *(pixel_ctrl_ptr + 3);
        }
    }
}


// making the required pixel of given colour 
void write_pixel(int x, int y, short colour)
{
    volatile short *abhi = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    *abhi = colour;
}

// writing a character on the screen 
void write_char(int x, int y, char c)
{    
    volatile char *cha = (char *)(0x09000000 + (y << 7) + x);
    *cha = c;
}

// make all 320 * 240 pixels black ie 0 
void clear_screen()
{
    int x, y;
    for (x = 0; x < 320; x++)
    {
        for (y = 0; y < 240; y++)
        {
            write_pixel(x, y, 0);
        }
    }
}

// make all 80 * 60  characters to null 
void clear_screen_char ( ){
    int x, y;
    for (x = 0; x < 80; x++)
    {
        for (y = 0; y < 60; y++)
        {
            write_char(x, y, 0);
        }
    }
}


// this function draws the yellow cloured pointer 
void draw_img(int x, int y, int color)
{
    int xx = x - 2, yy = y - 2;
    for (int i = xx; i < xx + 6; i++)
    {
        for (int j = yy; j < yy + 6; j++)
        {
            write_pixel(i, j, color);
        }
    }
}

// this function draws the maze on the screen 
void draw_maze()
{
    //data size 16 * 12 
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            // if  data [i][j] is 1 we have to color 20 * 20 pixels with red 
            if (data[i][j] == 1)
            {
                for (int k = 20 * i; k < 20 * i + 20; k++)
                {
                    for (int l = 20 * j; l < 20 * j + 20; l++)
                    {
                        write_pixel(l, k, RED);
                    }
                }
            }
        }
    }
}


// drawing the finish area 
void draw_finish()
{
    for (int k = 280; k < 300; k++)
    {
        for (int l = 200; l < 220; l++)
        {
            write_pixel(k, l, GREEN);
        }
    }
}

int checker ( int a ,int b ){
    // as we have reduced 320 * 240 into 16 * 12 
    // so checking wether a given point lies on the red area or not 
    if ( data [ b / 20][a/20] ==1  ){
        printf("returning 1 \n");
        return 1 ;
    }
    
    return 0 ;
}

// this function checks green area is touched or not 
int checkb ( int a , int b ){
    
    // as we have reduced 320 * 240 into 16 * 12 
    // and green area is in ( 14 , 10 )    zero indexed 
    // so checking wether a given point in in this area or not 
    if ( a / 20 == 14 && b / 20 == 10 ){
        return 1 ;
    }
    return 0 ; 
}


// this function will load the given level of maze from datast to data 
void load_maze ( int ind ) {
    // just normal nested loop to load data 
    for ( int  i = 0; i < 12; i++)
    {
        for ( int  j = 0; j < 16; j++)
        {
            data[i][j] = datast [ind][i][j];
        }        
    }    
}

int main(void)
{        
        
    clear_screen();  // make all pixels black 

    // few welcome messages 
    char * wela = "MAZE GAME";
    char * welb = "you have to reach destination without touching maze";
    char * welc = "ARE YOU READY.......";
    int x = 35  , y = 30 ; 
    while ( *wela)
    {
        write_char (x , 28  , *wela  );
        wela ++ ; 
        x ++ ; 
    }
    delayb(); 
    x = 15 ; 
    while ( *welb)
    {
        write_char (x , 30  , *welb  );
        welb ++ ; 
        x ++ ; 
    }
    delayb();
    delayb();
    clear_screen_char(); // this clears all the character on the screen 
    x = 30 ; 
    while ( *welc)
    {
        write_char (x , 30  , *welc  );
        welc ++ ; 
        x ++ ; 
    }
    delayb() ; delayb();

    // time to load maze so clear all character and pixels 
    clear_screen_char ( );
    clear_screen();

    int mazenum = 0  ;  // start lavel = 0 

    while (1 )
    {   int loopbr = 0 ; 
        clear_screen();
        clear_screen_char();
        load_maze ( mazenum);        // loading from datast to data 
        
        draw_maze();
        draw_finish();            // drawing the finish green area 
        x = 30 , y = 30 ; 

        volatile int *kp = (int *)KEY_BASE;
        unsigned int kv;    
        draw_img(x, y, YELLOW);          // this is out yellow pointer 
        while (1)
        {
            delay();
            kv = *kp;
            // applying the cases for movement of yellow pointer 
            switch (kv)
            {
            case 1:
                draw_img(x, y, 0);  // clearing the previous image 
                x++;
                break; 
            case 2:
                draw_img(x, y, 0);
                y++;
                break; 
            case 4:
                draw_img(x, y, 0);
                y--;
                break; 
            case 8:
                draw_img(x, y, 0);
                x--;
                break; 
            default:
                break;
            }
            printf("x and y are %d %d \n ", x, y);  // just printing in terminal 
            int chec = 0 ; 

            // checking if the yellow pointer is touching the red line or not 

            // for this we didn't need to check each pixel just 4 corner point is sufficient 
            chec |= checker ( x-4 , y-4 );
            chec |= checker ( x+4 , y-4 );
            chec |= checker ( x-4 , y+4 );
            chec |= checker ( x+4 , y+4 );

            if ( chec == 1 ){ // If touched red line 

                // printing and clearing message 
                char * disp  = "Failed!";
                int x = 37 ; 
                while ( *disp)
                {
                    write_char (x , 28  , *disp  );
                    disp ++ ; 
                    x ++ ; 
                }
                delayb ();
                x = 37 ;
                while ( x < 240)
                {
                    write_char (x , 28  , 0  );                
                    x ++ ; 
                }
                // two options given either to leave or to retry the same level 
                char * msga = "Make push button 0 to Retry Else leave";
                x = 20 ; 
                while ( *msga)
                {
                    write_char (x , 32  , *msga  );
                    msga ++ ; 
                    x ++ ; 
                }
                delayb ();
                delayb();
                x = 0 ;
                while ( x < 240)
                {
                    write_char (x , 28  , 0  );                
                    x ++ ; 
                }

                // checking the user input  
                // if 0  loopbr will remain as it is 0 
                // else make it 1 
                kv = * kp ; 
                if ( kv != 0 ){
                    loopbr = 1 ;
                } 
                break; 
            }
            int ch2 = 0 ; 
            // checking if the green area is touched or not 
            ch2 |= checkb ( x-4 , y-4 );
            ch2 |= checkb ( x+4 , y-4 );
            ch2 |= checkb ( x-4 , y+4 );
            ch2 |= checkb ( x+4 , y+4 );
            if ( ch2 ){
                char * disp  = "Congratulations! you won";
                int x = 30 ; 
                // displaying and clearing message 
                while ( *disp)
                {
                    write_char (x , 28  , *disp  );
                    disp ++ ; 
                    x ++ ; 
                }
                delayb ();
                delayb ();
                delayb();
                x = 30;
                while ( x < 240)
                {
                    write_char (x , 28  , 0  );                
                    x ++ ; 
                }
                mazenum = ( mazenum + 1 ) % 4 ; 
                break; 
            }        
            
            draw_img(x, y, YELLOW);
        }

        // if loopbr = 1 that means user wants to exit so leave the game 
        if ( loopbr == 1 )        
        {
            clear_screen();
            clear_screen_char();
            break; 
        }

    }
    return 0;
}