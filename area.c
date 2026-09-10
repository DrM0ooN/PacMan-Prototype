#define MODE_WELCOME 1
#define MODE_PLAY 2
#define MODE_START 7
#define MODE_PAUSE 3
#define MODE_EXIT  5
#define MODE_PREPLAY  8
#define MODE_DEATH  9
#define MODE_WIN  10
#define MODE_GAMEOVER 11

struct areaSize getAreaSize (int a[][WIDTH])
{
    int i,j;
    int x;

    struct areaSize s;
    x = 0;
    for(j = HEIGHT - 1; j >= 0; j--) {

        for(i = WIDTH - 1; i >= 0; i--) {
            if(a[j][i] != 0) {
                s.h = j + 1;
                x = 1;
                break;
            }

        }
        if(x == 1)
            break;
    }
    x = 0;
    for(i = WIDTH - 1; i != 0; i--) {
         for(j = HEIGHT - 1; j != 0; j--) {
            if(a[j][i] != 0) {
                s.w = i + 1;
                x = 1;
                break;
            }

         }

         if(x == 1)
            break;
    }
    return s;

};

void printAreaChar(int f, int dot)
{

            if( f == WALL) {
                setColor(LIGHTGREEN);
                setBackgroundColor(GREY);
                printf("X ");
            }
            else if(f == FREE) {
                setBackgroundColor(AREA_BGCOLOR);
                printf("  ");
            }
            else if(f <= GHOSTS_END && f >= GHOSTS_START ) {
               setColor(ghostSkins[ghosts[f - GHOSTS_START].skin].color );
               setBackgroundColor(ghostSkins[ghosts[f - GHOSTS_START].skin].bgcolor);
               printf("%s",ghostSkins[ghosts[f - GHOSTS_START].skin].c);


//               if(i) {                                        // added
//                 printf("%s",ghostSkins[ghosts[0].skin].c);
//                 ghosts[0].skin = 4;
//                 i = 0;
//               }
//               printf("%s",ghostSkins[ghosts[0].skin].c);
//               ghosts[0].skin = 0;
//               i = 1;// added
            }

            else if(f == CROSS) {
              setColor(YELLOW);
              setBackgroundColor(LIGHTBLUE);
              printf(". ");

            }


            else if(f == CORR) {
              setColor(YELLOW);
              setBackgroundColor(AREA_BGCOLOR);
              if(dot == 1) {
                  printf(". ");

              }
              else{
                printf("  ");
              }

            }
            else {
              setColor(YELLOW);
              setBackgroundColor(AREA_BGCOLOR);   //<---------------------------------------------------
              setColor(RED);
              printf("? ");
            }




}



void printAreaChanges(int o[][WIDTH],int n[][WIDTH],struct areaSize s)
{
    int i,j;

    for(i = 0; i < s.h ; i++) {
        for(j = 0; j < s.w; j++) {
            if(o[i][j] != n[i][j]) {
                gotoxy(2 * j + 1, i + 1);
                printAreaChar(n[i][j],dots[i][j]);
                o[i][j] = n[i][j];
            }

        }

    }
}


void printArea(int a[][WIDTH],struct areaSize s)
{
    setBackgroundColor(BLACK);
    cls();
    int h,w,i,z;
    h = s.h;
    w = s.w;
    for(i = 0; i < h ; i++) {
        for(z = 0; z < w ; z++) {
                printAreaChar(a[i][z],dots[i][z]);
        }
        printf("\n");
    }

    setBackgroundColor(CYAN);
    setColor(YELLOW);
    gotoxy(1,s.h + 1);
    printf("SCORE: %4d   LIVES:",game.score);

    for(i = 0; i < game.lives; i++) {
      setColor(RED);
      setBackgroundColor(YELLOW);
      printf("<3");
    }


    setBackgroundColor(CYAN);
    setColor(YELLOW);
    printf("\nLEVEL:    %d  ",game.current_level + 1);

    setBackgroundColor(BLACK);
    setColor(WHITE);
}

void printGhostsPositions(int a[][WIDTH],struct areaSize s)
{
        int h,w,i,z;
    h = s.h;
    w = s.w;

    for(i = 0; i < h ; i++) {
        for(z = 0; z < w ; z++) {
            if( a[i][z] <= GHOSTS_END && a[i][z] >= GHOSTS_START) {
                printf("\n pozice ducha %d je x = %d y = %d", a[i][z] - GHOSTS_START, z, i);
            }
        }



    }
}



void putGhostsToArea (int a_in[][WIDTH],struct areaSize s, struct ghost ghosts[],int ghosts_num, int a_out[][WIDTH])
{
    int h,w,i,z;
    h = s.h;
    w = s.w;
    if(game.skip == 25)
      game.skip = 0;
    else
      game.skip ++;

    for(i = 0; i < h ; i++) {
        for(z = 0; z < w ; z++) {
            a_out[i][z] = a_in[i][z];
        }
    }

    for(i = 0; i < game.ghosts; i++) {

        if(i == 6 && game.skip < 15 ) {
          break;
        }
//        if(i == 6 && game.time % 1000.0 == 0 ) {
//
//        }

          a_out[ghosts[i].y ][ghosts[i].x] = GHOSTS_START + i;


    }
}


void changeScore(int points)
{
    int mezery, i;
    mezery = 4;

    setBackgroundColor(CYAN);
    setColor(YELLOW);

    game.score = game.score + points;


    gotoxy(7,game.height + 1);
//    for(i = 0; i < mezeryy; i++) {   // mezer podle nul
//         mezeryy--;
//        gotoxy(30,30);
//        printf("%d",mezeryy);
//        score = score / 10;
//        if(score > 0)
//            break;
//    }
//



    if(game.score >= 10) {
        mezery = 3;
    }
    if(game.score >= 100) {
        mezery = 2;
    }
    if(game.score >= 1000) {
        mezery = 1;
    }


    for(i = 0; i < mezery; i++) {
       printf(" ");
    }
    printf("%d",game.score);

}





void changeLives(int change)
{
    int i;
    setBackgroundColor(CYAN);
    if(game.lives == 0)
        change = 0;
    game.lives += change;
    if(change < 0) {
        setBackgroundColor(BLACK);
        gotoxy(21 + (game.lives) * 2, game.height + 1);
        for(i = change; i < 0; i ++) {
            printf("  ");
        }
    }

    else {
        gotoxy(21 + (game.lives + 1) * 2, game.height + 1);
        for(i = 0; i < change; i ++) {
            setColor(RED);
            setBackgroundColor(BLACK);
            printf("<3");
        }
    }

}


void printMessage(char message[])
{
    int i,z,message_lenght;
    int x_start, y_start,box_width;

    message_lenght = 0;
    setColor(WHITE);
    setBackgroundColor(RED);
    for(i = 0; message[i] != '\0'; i++) {
        message_lenght++;
    }
    box_width = message_lenght + 6;
    y_start = (game.height - 7) / 2 + 1;
    if(box_width > game.width * 2) {
        x_start = 1;
    }
    else
        x_start = (game.width * 2 - box_width) / 2 + 1;


        gotoxy(x_start, y_start); // vycentrovat
        printf("*");
        for(i = 0; i < message_lenght + 4; i++) { // 1. radek
            printf("=");
        }
        printf("*");

        for(z = 2; z > 0; z--) {
            gotoxy(x_start,y_start - z + 3);
            printf("|");
            for(i = 0; i < message_lenght + 4; i++) { // 2. a 3. radek
                printf(" ");
            }
            printf("|");
        }

        gotoxy(x_start, y_start + 3);
        printf("|  ");
        for(i = 0; i < message_lenght; i++) { // prostredni radek s vypisem
            printf("%c",message[i]);
        }
        printf("  |");

        for(z = 0; z < 2; z++) {
            gotoxy(x_start,y_start + z + 4);
            printf("|");
            for(i = 0; i < message_lenght + 4; i++) { // 5. a 6. radek
                printf(" ");
            }
            printf("|");
        }

        gotoxy(x_start,y_start + 6);
        printf("*");
        for(i = 0; i < message_lenght + 4; i++) { // 7. radek
            printf("=");
        }
        printf("*");

        game.box_height = 7;
        game.box_width = box_width;
        game.box_x = x_start;
        game.box_y = y_start;

}


void clearMessage()
{
    int i,j,w;
    if(game.box_x % 2 == 0) {
        game.box_x --;
        game.box_width ++;
    }
    if(game.box_width % 2 == 0)
        w = game.box_width / 2;
    else
        w = (game.box_width + 1) / 2;


    gotoxy(game.box_x,game.box_y);
    for(j = 0; j < game.box_height ; j++) {
        gotoxy(game.box_x,game.box_y + j);
        for( i = 0; i < w ; i++) {
          printAreaChar(old_screen[game.box_y + j - 1][(game.box_x - 1) / 2 + i  ],dots[game.box_y + j - 1][(game.box_x - 1) / 2 + i  ]); //< -------------
//           printf("xx");
        }
        printf("\n");
    }


}
void changeMode(int newmode)
{
     // 1. pulka jakej je stary mod prev_mode
      if (game.mode == MODE_START || game.mode == MODE_DEATH || game.mode == MODE_WELCOME || game.mode == MODE_PAUSE || game.mode == MODE_EXIT ) {
          clearMessage();
      }
      else if(game.mode == MODE_PREPLAY && newmode == MODE_PLAY) {
          game.start = game.clock;

      }
      else if((game.mode == MODE_PLAY && newmode == MODE_PAUSE) || (game.mode == MODE_PLAY && newmode == MODE_EXIT) ) {
          game.pause_start = game.time;
      }
      else if( (game.mode == MODE_PAUSE && newmode == MODE_PLAY )|| (game.mode == MODE_EXIT && newmode == MODE_PLAY ) ) {
          game.start = game.start + game.time - game.pause_start;
          game.pause_start = 0;
      }
      else if(game.mode == MODE_WIN) {
        game.dots_left = 0;
        game.start = game.clock;     // reset clock
        create_level(++game.current_level);
        gotoxy(0,0);
      }

//-------------------------------------------------------------------------------------------------


    if(newmode == MODE_WELCOME) {
        printMessage("            PACMAN           ");
    }
    else if(newmode == MODE_START) {
        printMessage("press ANY KEY to start playing");

    }
    else if (newmode == MODE_PREPLAY) {
      if(game.lives > 0) {
        int i;
        for(i = 0; i < game.ghosts ; i++) {
          ghosts[i].lastmove = 0;
          ghosts[i].x = levels[game.current_level].ghosts[i].x;
          ghosts[i].y = levels[game.current_level].ghosts[i].y;
        }

        game.p_x = game.start_px;
        game.p_y = game.start_py;
        putGhostsToArea (area, size, ghosts, game.ghosts, screen);
        printAreaChanges(old_screen, screen, size);

      }

    }

    else if(newmode == MODE_PAUSE) {
        printMessage("press SPACE to resume the game");


    }

    else if(newmode == MODE_PLAY) {




    }

    else if(newmode == MODE_EXIT) {
        printMessage("do you really want to exit the game? y/n");
        game.pause_start = game.time;
    }
    else if(newmode == MODE_DEATH) {
      printMessage("YOU DIED TO A GHOST!! PRESS Y to continue");
      changeLives(-1);
      game.death = 0;



    }
    else if(newmode == MODE_WIN) {
      if(game.current_level == LEVELS - 1) {
        printMessage("YOU HAVE COMPLETED ALL THE LEVELS! NOT BAD! PRESS X TO END THE GAME");
      }
      else {
        printMessage("YOU COLLECTED ALL THE POINTS = WIN! PRESS X to continue");

      }
    }
    else if(newmode == MODE_GAMEOVER) {
        printMessage("You have run out of all lives. Try again next time!Press x to end the game");

    }

    if(game.mode != MODE_PAUSE && game.mode != MODE_EXIT) {
        game.prev_mode = game.mode;
    }


      game.mode = newmode;



}


 void printClock()
 {

     setColor(WHITE);
     setBackgroundColor(BLACK);
     gotoxy(1,20);
     printf("%.3f game.clock",game.clock / 1000.0);



     if(game.pause_start) {
        gotoxy(1,21);
        printf("%.3f game.pause",game.pause_start/ 1000.0);

     }
     else {
        gotoxy(1,21);
        printf("%.3f game.time ",game.time/ 1000.0);
        gotoxy(1,22);
        printf("dots left in area = %d ",game.dots_left);

     }






//     gotoxy(1,22);
//     printf("%.3f game.start",game.start/ 1000.0);







 }









void printNavGhost(int x, int y, int p_x, int p_y, int dir, int validdirs[], struct moveOpt o)
{


    gotoxy(1,25);
    setBackgroundColor(BLACK);
    setColor(WHITE);
    printf("x = %d \n y = %d \n p_x = %d \n p_y = %d \n dir = %d \n validdirs = %d %d %d %d \n alg = %d \n rot = %d  ",x, y,p_x, p_y, dir, validdirs[0],validdirs[1],validdirs[2],validdirs[3],o.alg, o.rot );


}


int space(int g_x, int g_y)
{

//    x0 = ;
//    y0 = surroundings[k][l][1] + g_y;
    int surr = 0;

    int k,l;
    for(k = 0; k < 4; k++){
      surr = 0;
      for(l = 0; l < 3; l++){

            if(area[surroundings[k][l][1] + g_y][surroundings[k][l][0] + g_x] != WALL && g_y <= HEIGHT && g_y > 0 && g_x < WIDTH && g_x > 0)     //  area[y][x]
              surr++;
      }

      printf("surr = %d\n",surr);
      if(surr == 3){
        printf("je surroundings %d\n", k);
        return 1;
      }


    }

    printf("neni surroundings\n");
    return 0;



}


void processArea()
{

  int i,j;
  for(i = 0; i < game.height; i++){
    for(j = 0; j < game.width; j++) {
      if(area[i][j] == DOT) {
         dots[i][j] = 1;
         area[i][j] = CORR;

      }
      else {
        dots[i][j] = 0;

      }
    }
  }


}


void movePacman(int a_in[][WIDTH],struct areaSize s, struct ghost ghosts[], int dx, int dy)
{
    int x,y;
    x = ghosts[0].x + dx;
    y = ghosts[0].y + dy;
    if(x >= s.w ||x < 0 ||y >= s.h ||y < 0) {
       return;
    }
    if(a_in[y][x] == WALL) {
       return;
    }
    if(ghosts[0].skin == 0) {
      ghosts[0].skin = 4;
    }
    else
      ghosts[0].skin = 0;

    if(dots[y][x] == 1) {
        dots[y][x] = 0;
        changeScore(10);
        game.dots_left--;

    }

    int i;
     for(i = 1; i < game.ghosts; i++)
     if(x == ghosts[i].x && y == ghosts[i].y) {
        //changeLives(-1);

    }

//    if(a_in[y][x + 1] == DOT) {              // kdyz je pred hracem tecka tak changeScore
//
//    }

    ghosts[0].x = x;
    ghosts[0].y = y;
    int g;
    game.death = 0;
    for(g = 1; g < game.ghosts; g++) {                                        // <--------- added
      if(ghosts[0].x == ghosts[g].x && ghosts[0].y == ghosts[g].y) {
        game.death = 1;

      }
    }



}


int navGhost(int x, int y, int p_x, int p_y, int dir, int validdirs[], struct moveOpt o)
 {
    int i;
    if(o.alg == 1){

        for(i = 0; i < 3; i++) {
            if(validdirs[dir] == 1)
                return dir;
            else {
              dir = dir + o.rot;
              dir = dir % 4;
            }


        }
    return -1;
    }
    //exit(1);

    else if(o.alg == 2) {
        int countValiddirs;
        countValiddirs = 0;
//        if(fakecross(x,y)) {
//
//        }

        if(space(x,y) && area[y][x] != CROSS) {
          for(i = 0; i < 3; i++) {
             if(validdirs[dir] == 1) {
               return dir;
             }
             else {
               dir = dir + o.rot;
               dir = dir % 4;
             }
          }
          return -1;
        }

        for(i = 0; i < 4; i ++) {
            if(validdirs[i] == 1)
               countValiddirs++;
        }
        gotoxy(30,30);
        setColor(RED);
        printf("count of valid directions: %d",countValiddirs);

        if(countValiddirs == 0) {
            return -1;
        }

        if(countValiddirs == 1) {
            i = 0;
            while(validdirs[i] != 1)
                i++;
            return i;
        }

        else if(countValiddirs == 2) {
            validdirs[(dir + 2) % 4] = 0;
            i = 0;
            while(validdirs[i] != 1)
                i++;
            return i;
        }



        else if(countValiddirs > 2) {           //crossroad
            validdirs[(dir + 2) % 4] = 0;
            if(validdirs[i = (dir + o.crossRot) % 4] == 1){
                return i;
            }

            else {
                for(i = 0; i < 4 ;i++) {
                     dir = (dir + o.rot) % 4;
                     if(validdirs[dir] == 1)
                        return dir;

                }
            }
        }

    return -1;
    }
    else if(o.alg == 3) {
      createMaze(x,y,p_x,p_y);
      return searchMaze();

    }

    return -1;
}


void moveGhost (int g)
{
    int movepoint;

    int validdirs[] = {0,0,0,0};



        if (ghosts[g].y > 0 && area[ghosts[g].y - 1][ghosts[g].x] != WALL)// up
            validdirs [0] = 1;


        if(ghosts[g].x < game.width - 1 && area[ghosts[g].y][ghosts[g].x + 1] != WALL) // right
                validdirs [1] = 1;


        if(ghosts[g].y < game.height - 1 && area[ghosts[g].y + 1][ghosts[g].x] != WALL) // down
                validdirs [2] = 1;

        if(ghosts[g].x > 0 && area[ghosts[g].y][ghosts[g].x - 1] != WALL)  // left
            validdirs [3] = 1;



    printNavGhost(ghosts[g].x,ghosts[g].y,ghosts[0].x,ghosts[0].y, ghosts[g].dir, validdirs, moveOpts[ghosts[g].move]);

    movepoint = navGhost(ghosts[g].x,ghosts[g].y,ghosts[0].x,ghosts[0].y, ghosts[g].dir, validdirs, moveOpts[ghosts[g].move]);
    //movepoint = 1;
    gotoxy(20,20);
    setBackgroundColor(BLACK);
    setColor(WHITE);
    printf("direction = %d",movepoint);


    if(movepoint == 0){
        ghosts[g].y --;
    }
    else if(movepoint == 1){
        ghosts[g].x ++;
    }
    else if(movepoint == 2){
        ghosts[g].y ++;
    }
    else if(movepoint == 3){
        ghosts[g].x --;
    }

    ghosts[g].dir = movepoint;
    int j;

    for(j = 1; j < game.ghosts; j++) {
      if(ghosts[0].x == ghosts[j].x && ghosts[0].y == ghosts[j].y) {          // <--------- added
        game.death = 1;

      }
    }

}

void create_level(int levelNum)
{

  int i,j;
  game.ghosts = levels[levelNum].ghosts_num;
  for( i = 0; i < HEIGHT ;i++) {
    for( j = 0; j < WIDTH ;j++) {
      area[i][j] = levels[levelNum].area[i][j];

    }
  }
  size = getAreaSize(area);
  for( i = 0; i < levels[levelNum].ghosts_num; i++) {
      ghosts[i] = levels[levelNum].ghosts[i];


  }

    if(area[ghosts[0].x][ghosts[0].y] == DOT) {
        area[ghosts[0].x][ghosts[0].y] = FREE;
    }


    game.height = size.h;
    game.width = size.w;
    processArea();
    putGhostsToArea (area, size, ghosts, game.ghosts, old_screen);


    printArea(old_screen,size);





}


