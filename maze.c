#define MAZE_WALL -1
#define MAZE_FREE -2
#define MAZE_TARGET 0     // nesmi se menit
#define MAZE_START -3
#define MAZE_PATH 10000


int maze[HEIGHT][WIDTH];
// start x,y = pozice ducha
//target x,y = pozice pacmana
void createMaze(int start_x, int start_y, int target_x, int target_y) // predelat aby tam byli fake walls kolem
{
  int i,j;
  //creating fake walls
  for(i = 0; i <= game.height + 1; i++) // vlevo
    maze[i][0] = MAZE_WALL ;

  for(i = 0; i <= game.width + 1; i++) // nahore
    maze[0][i] = MAZE_WALL;

  for(i = 0; i <= game.width + 1; i++) // dole
    maze[game.height + 1][i] = MAZE_WALL;

  for(i = 0; i <= game.height + 1; i++) //vpravo
    maze[i][game.width  + 1] = MAZE_WALL;
// ------------------------------

  for(i = 1; i <= game.height ; i++) {
    for(j = 1; j <= game.width ; j++) {

      if(area[i - 1][j - 1] == WALL) {
        maze[i][j] = MAZE_WALL;
      }
      else {
        maze[i][j] = MAZE_FREE;
      }
    }

  }
  maze[start_y + 1][start_x + 1] = MAZE_START;
  maze[target_y + 1][target_x + 1] = MAZE_TARGET;
}


void printMaze()
{
  int i,j;

  for(i = 0; i <= game.height  + 1; i++) {
    for(j = 0; j <= game.width + 1; j++) {

        if(maze[i][j] == MAZE_WALL) {
          setBackgroundColor(GREEN);
          setColor(BLUE);
          printf("X ");

        }
        else if(maze[i][j] == MAZE_FREE) {
          setBackgroundColor(BROWN);
          printf("  ");
        }
        else if(maze[i][j] == MAZE_START) {
          setBackgroundColor(YELLOW);
          setColor(BLUE);
          printf("S ");
        }
        else if(maze[i][j] == MAZE_TARGET) {
          setBackgroundColor(RED);
          setColor(YELLOW);
          printf("T ");
        }
        else{
          setBackgroundColor(BLUE);
          setColor(WHITE);
          if(maze[i][j] % 2 == 0) {
            setBackgroundColor(LIGHTBLUE);
            setColor(WHITE);
          }
          else {
            setBackgroundColor(BLUE);
            setColor(WHITE);
          }
          if(maze[i][j] < MAZE_PATH){
            if(maze[i][j] < 10)
              printf("%d ",maze[i][j]);
            else if(maze[i][j] >= 10) {
              printf("%d",maze[i][j]);
            }
          }

          else{
            setBackgroundColor(LIGHTMAGENTA);
            setColor(WHITE);
            if(maze[i][j] < 10 + MAZE_PATH)
              printf("%d ",maze[i][j] - MAZE_PATH);
            else{
              printf("%d",maze[i][j] - MAZE_PATH);
            }
          }
        }



    }
    printf("\n");
  }

}



void pathMaze(int target_x,int target_y,int steps)
{
  int i,once,road;
  int x,y;
  road = steps;
  once = 1;
  y = target_y;
  x = target_x;
  for(i = 0; i < road; i++) {
    if(maze[y - 1][x] == steps  && once) {      //up
      maze[y - 1][x] += MAZE_PATH;
      y--;
      once = 0;
    }
    if(maze[y][x + 1] == steps  && once) {      //right
      maze[y][x + 1] += MAZE_PATH;
      x++;
      once = 0;
    }
    if(maze[y + 1][x] == steps  && once) {      //down
      maze[y + 1][x] += MAZE_PATH;
      y++;
      once = 0;
    }
    if(maze[y][x - 1] == steps && once) {      //left
      maze[y][x - 1] += MAZE_PATH;
      x--;
      once = 0;
    }
    once = 1;
    steps--;

  }


}
int dirMaze(int start_x,int start_y,int steps)
{

  int x,y;
  x = start_x;
  y = start_y;

  printf("x = %d y = %d, steps = %d   ",x,y,steps);
    if(maze[y - 1][x] == steps || maze[y - 1][x] == steps + MAZE_PATH) {             //up

      printf("first");
      return  0;
    }
    if(maze[y][x + 1] == steps || maze[y][x + 1] == steps + MAZE_PATH) {      //right

      printf("sec");
      return 1;
    }
    if(maze[y + 1][x] == steps || maze[y + 1][x] == steps + MAZE_PATH) {      //down
      printf("third");
      return 2;
    }
    if(maze[y][x - 1] == steps || maze[y][x- 1] == steps + MAZE_PATH) {      //left
      printf("fourth");
      return 3;
    }
    else {
      printf("error");
      return -1;
    }


}


int searchMaze()
{

  int i,j,steps,start_x,start_y,start;
  steps = 0;
 start = 0;
  for(i = 1; i <= game.height  ; i++) {     //finding target and start
    for(j = 1; j <= game.width ; j++) {


        if(maze[i][j] == MAZE_START){     // pacman
          start_x = j;
          start_y = i;
          start = 1;

        }

        if(maze[i][j] == MAZE_TARGET){     //ghost


        }


    }
  }
        if(!start)
          return -1;



  while(1) {
    for(i = 1; i <= game.height  ; i++) {
      for(j = 1; j <= game.width ; j++) {
        if(maze[i][j] == steps) {
          if(maze[i - 1][j] == MAZE_START || maze[i][j + 1] == MAZE_START || maze[i + 1][j] == MAZE_START || maze[i][j - 1] == MAZE_START) {
            pathMaze(start_x,start_y,steps);
            return dirMaze(start_x,start_y,steps);

          }

          if(maze[i - 1][j] == MAZE_FREE)  {    // up
              maze[i - 1][j] = steps + 1;
          }
          if(maze[i][j + 1] == MAZE_FREE) {      //right
              maze[i][j + 1] = steps + 1 ;
          }
          if(maze[i + 1][j] == MAZE_FREE) {     //down
              maze[i + 1][j] = steps + 1;
          }
          if(maze[i][j - 1] == MAZE_FREE){      //left
              maze[i][j - 1] = steps + 1;

          }
        }
      }
    }
    steps++;

  }
}

