
#define AREA_BGCOLOR BLUE



#define WALL 1
#define FREE 2
#define DOT 0
#define X WALL
#define F FREE
#define CORR 3
#define WIDTH 80
#define HEIGHT 25
#define MAX_GHOSTS 15
#define CROSS 4
#define Z CROSS

// Ghosts
#define GHOSTS_START 100
#define GHOSTS_END   199
#define A 101
#define B 102
#define C 103
#define D 104
#define E 105

//PLAYER
#define PLAYER GHOSTS_START
#define P PLAYER

#define DIR_STR 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3
int area[HEIGHT][WIDTH] ;/*= {
    {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X},     // predelat abych mohl otestovat algoritmus 2
    {X,Z,0,0,X,X,0,0,0,0,0,X,0,0,0,0,0,X,0,0,0,0,X,0,0,0,X,0,0,0,0,X},
    {X,0,0,X,X,0,Z,0,0,X,0,X,0,X,X,X,0,0,0,X,X,0,0,0,X,0,X,0,X,0,0,X},
    {X,0,0,X,0,0,X,0,0,X,0,0,0,0,0,0,0,X,X,X,X,0,X,X,X,0,X,0,X,X,0,X},
    {X,0,0,0,0,0,X,X,X,X,X,X,X,X,X,0,0,0,0,0,0,0,0,0,0,0,X,0,0,0,Z,X},
    {0,0,0,0,0,0,X,0,Z,0,0,0,0,Z,X,0,X,0,0,X,0,0,X,0,X,X,X,X,X,0,0,X},
    {X,X,0,0,X,0,0,0,0,X,0,0,0,0,0,0,X,0,0,X,0,0,X,0,0,0,X,X,0,0,Z,X},
    {X,0,0,0,X,0,X,X,X,X,X,0,0,X,0,0,X,0,0,X,X,X,X,Z,0,0,0,0,0,X,0,X},
    {X,0,0,0,X,0,Z,0,0,0,0,0,X,X,0,0,X,0,0,0,0,0,X,X,0,0,0,0,0,X,Z,X},
    {X,0,0,0,X,X,0,0,0,X,0,0,0,X,0,0,X,0,0,0,0,0,X,X,X,X,X,0,0,X,0,X},
    {X,0,0,0,X,X,0,0,X,X,X,Z,0,X,0,0,X,X,X,X,0,0,0,0,0,0,X,0,0,X,0,X},
    {0,0,Z,0,0,0,0,0,Z,0,X,0,X,X,0,0,0,X,X,X,0,0,X,X,0,0,X,0,0,X,0,X},
    {0,X,0,X,X,X,X,X,0,0,X,0,X,X,0,0,0,0,0,0,0,0,X,0,0,X,X,Z,0,0,0,X},
    {0,X,0,0,0,0,0,X,X,X,X,0,X,X,X,X,X,0,0,X,0,0,0,0,0,0,0,0,X,X,0,X},
    {0,X,X,X,X,0,0,X,Z,0,0,0,0,0,0,0,X,X,X,X,0,0,X,0,0,X,0,X,X,X,0,0},
    {0,0,0,0,0,0,0,0,0,0,X,0,0,X,X,0,0,0,0,0,0,0,X,0,0,X,0,0,0,0,0,X},
    {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X},
};*/


int old_screen[HEIGHT][WIDTH];

int dots[HEIGHT][WIDTH];

int screen[HEIGHT][WIDTH];

struct areaSize {
    int w,h;
};

struct areaSize size;

struct ghostSkin  {
    char c[4];   // 3 znaky a 0
    int color,bgcolor;
};

struct moveOpt {
   unsigned int alg;
   unsigned int rot;
   unsigned int crossRot;


};

int surroundings[4][3][2] = {
    {{0,-1},{1,-1},{1,0}},  // prava horni
    {{1,0},{1,1},{0,1}},    // prava dolni
    {{0,1},{-1,1},{-1,0}},   // leva dolni
    {{-1,0},{-1,-1},{-1,0}}  // leva horni

};



struct ghost {
    int x,y;
    int skin;
    int dir;
    int move;      // index do moveOpt
    int speed;     // pocet ms po kterych se duch hne
    int lastmove;  // cas posledniho pohybu

};
#define NU 0 // not used
#define MOVE0 0
#define MOVE1 1
#define MOVE2 2
#define MOVE3 3
#define MOVE4 4
#define MOVE5 5
#define MOVE6 6
#define MOVE7 7
#define MOVE8 8
struct moveOpt moveOpts[] = {
     {0,NU,NU}, //0   // pro pacmana
     {1,1,NU}, //1     // pri narazu se otoci doPRAVA
     {1,2,NU}, //2      // pri narazu se otoci CELEM VZAD
     {1,3,NU}, //3       //  pri narazu se otoci doLEVA
     {2,DIR_LEFT,DIR_RIGHT}, //4        //pri narazu se otoci doLEVA - crossroad - doPRAVA
     {2,DIR_LEFT,DIR_STR}, //5        //pri narazu se otoci doLEVA - crossroad - ROVNE
     {2,DIR_LEFT,DIR_LEFT},  //6        //pri narazu se otoci doLEVA - crossroad - doLEVA
     {2,DIR_RIGHT,DIR_LEFT},  //7        //pri narazu se otoci doPRAVA - crossroad - doLEVA
     {3,DIR_LEFT,DIR_LEFT},  //8

} ;
#define SKIN0 0
#define SKIN1 1
#define SKIN2 2
#define SKIN3 3
#define SKIN4 4
#define SKIN5 5
#define SKIN6 6
struct ghostSkin ghostSkins [] = {
    {":<", MAGENTA,YELLOW}, // 0
    {";;",BLUE, WHITE},    // 1
    {"''",BLACK, LIGHTGREEN },   // 2
    {"**",BLUE, RED },         // 3
    {":-", MAGENTA, YELLOW }, // 4
    {"oo", YELLOW,BROWN}, // 5
    {"PP", GREEN,WHITE} // 6
};

struct ghost ghosts[MAX_GHOSTS];


struct key_move {
    int key;
    int dx, dy;
};

struct key_move key_moves[] = {
    {KEY_UP,0,-1},
    {KEY_DOWN,0,1},
    {KEY_RIGHT,1,0},
    {KEY_LEFT,-1,0},
    {'w',0,-1},
    {'a',-1,0},
    {'s',0,1},
    {'d',1,0},
};


struct {
    int score;
    int level;
    int lives;
    int ghosts;
    int height;
    int width;
    int box_width;
    int box_height;
    int box_x;
    int box_y;
    int mode;
    int prev_mode;
    int time;
    int start;
    int clock;
    int pause_start;
    int p_x;
    int p_y;
    int dots_left;
    int levels;
    int skip;
    int start_px;
    int start_py;
    int death;
    int current_level;


} game = {0,1,3,6};
