#include <stdio.h>
#include <stdlib.h>
#include "rlutil.h"

#include <time.h>

#include "opts.c"
#include "maze.c"
#include "levels.c"
#include "area.c"




#define MODE_WELCOME 1
#define MODE_PLAY 2
#define MODE_START 7
#define MODE_PAUSE 3
#define MODE_EXIT  5


int main()
{
//        int x0,y0; //<---------------------------------------------------- vypsat 4 lka z surroundings
//   // gotoxy(35,35);
//    int k,l,m;
//    for(k = 0; k < 4; k++){
//        printf("L%d{",k);
//        for(l = 0; l < 3; l++){
//            printf("{");
//            for(m = 0; m < 2; m++) {
//                if(m == 0)
//                  printf("%d",surroundings[k][l][m]);
//                else
//                  printf(", %d",surroundings[k][l][m]);
//
//            }
//            printf("}");
//        }
//        printf("}\n");
//    }



    //int i,z,h,w;

    game.current_level = 0;
    int key;
    hidecursor();
    // fukce levels
    create_level(0);


      game.start_px = 14;               // <----------------------------------------------------added
      game.start_py = 14;













    // printf("%d",game.lives);






//    printGhostsPositions(screen, size);
    setColor(WHITE);
    setBackgroundColor(BLACK);

    game.mode = 0;
    changeMode(MODE_WELCOME);


    while(1) {



        msleep(1);
        game.clock = clock() * 1000 / CLOCKS_PER_SEC;

        if(game.start)
            game.time = game.clock - game.start;

        if(game.mode == MODE_PLAY) {


          int i;
          int move;
          move = 0;
          for(i = 1; i < game.ghosts ; i++) {
               if(ghosts[i].lastmove < game.time / ghosts[i].speed) {


                  moveGhost(i);



                  move = 1;
                  ghosts[i].lastmove = game.time / ghosts[i].speed;


               }

          }

          if(move) {
              putGhostsToArea (area, size, ghosts, game.ghosts, screen);
              printAreaChanges(old_screen, screen, size);

          }
          if(game.death == 1) {
            changeMode(MODE_DEATH);

          }
      }


////
////            for(j = 0; j < game.ghosts; j++) {
////                moveGhost(j);
////            }

        printClock();

        if(kbhit()) {
            key =  getkey();



            if(key == KEY_ESCAPE) {
                changeMode(MODE_EXIT);
            }
            else if(game.mode == MODE_WELCOME) {
                changeMode(MODE_START);
            }
            else if(game.mode == MODE_START) {
                changeMode(MODE_PREPLAY);
            }
            else if(game.mode == MODE_PAUSE) {
                if(key == KEY_SPACE)
                    changeMode(game.prev_mode);

            }
            else if(game.mode == MODE_DEATH) {
               if(key == 'y' || key == 'Y') {
                if(game.lives == 0) {
                  changeMode(MODE_GAMEOVER);
                }
                else {
                  changeMode(MODE_PREPLAY);

                }

               }



            }
            else if(game.mode == MODE_GAMEOVER) {
              if(key == 'x' || key == 'X') {
                    break;
                  }
            }
            else if(game.mode == MODE_WIN) {
              if(key == 'x' || key == 'X') {
                if(game.current_level == LEVELS - 1) {
                  break;
                }
                else {
                  changeMode(MODE_PREPLAY);
                }
              }


            }
            else if(game.mode == MODE_EXIT) {
                    if(key == 'y' || key == 'Y')
                        break;
                    else if(key == 'n' || key == 'N')
                        changeMode(game.prev_mode);

            }

            else if(game.mode == MODE_PLAY || game.mode == MODE_PREPLAY) {
                if(game.mode == MODE_PREPLAY) {
                    //getkey();

                    changeMode(MODE_PLAY);
                }

                if(key == KEY_SPACE) {
                    changeMode(MODE_PAUSE);
                }

                else {


                    int i;
                    for(i = 0; i < sizeof(key_moves)/sizeof(struct key_move); i++) {
                        if(key == key_moves[i].key) {

                            movePacman(area, size, ghosts, key_moves[i].dx, key_moves[i].dy);


                            putGhostsToArea (area, size, ghosts, 6, screen);
                            printAreaChanges(old_screen, screen, size);
                            if(game.dots_left == 0) {
                              changeMode(MODE_WIN);
                            }


                        }
                    }
                }
            }


        }

    }
    setBackgroundColor(BLACK);
    setColor(GREY);
    cls();






//    hidecursor();
//    setColor(RED);
//    setBackgroundColor(GREEN);
//    printf("Hello world!\n");
//
//    setColor(WHITE);
//    gotoxy(7,1);
//    printf("world");
//
//    gotoxy(15,20);
//    printf("ahoj");
//
//    setColor(LIGHTBLUE);
//    setBackgroundColor(GREY);
//    gotoxy(15,4);
//    printf("Hello");
//    printf("\n");
//    resetColor();
    return 0;
}
