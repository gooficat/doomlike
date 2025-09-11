//i wrote these 2 libraries myself, hehe
#define SHORTTYPE
#include "shorttype.h"
#define EASYRENDER
#include "easyrender.h"


//object oriented programming minus inheritance in c? yes please!
typedef struct {
    u8 a, b;
    bool portal;
} wall_t;
//btw you compile with gcc main.c -lSDL2 (and I add -Wall -Wpedantic)
typedef struct {
    u8 idx, siz;
    i16 flr, cei;
} sector_t;
//IT FIXED IT AAAAGH MAKING IT ALL INTS FIXED IT I DONT KNOW WHY AND I CANT BE BOTHERED TO FIND OUT WHY BUT WHYYYYYYYYYYYYYYY
//i have no idea when and when not to use static but i just use it when someone else used it im the material i took it -- i mean inspired by
static struct player {
    v3 p, v;
    f32 a, l;
} player = { {50, 250, 20}, {0, 0, 0}, 0, 0 };
f32 sa, ca;//how github feels after hiding THE KEYS IN DEVELOPER SETTINGS WHAT IS WRONG WITH THEM WHY AM I STILL USING GITHUB
// i would use gitlab but it feels too professional and team-y...
//you can be a float dont worry


//time to "optimize"
v2i verts[] = {
    {30, 30}, {60, 30}, {90, 60}, {90, 90},
    {60, 120}, {30, 120}, {0, 90}, {0, 60},
    {90, 0}, {120, 30}
};
//YOURE ALL INTEGERS NOW
wall_t walls[] = {
    {0, 1},
    {1, 2, true},
    {2, 3},
    {3, 4},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 0},
    {1, 8},
    {8, 9},
    {9, 2},
    {2, 1, true}
};

sector_t sectors[] = {
    {0, 8, 0, 20},
    {8, 4, 0, 30}//sorry you guys gotta be shorter nw
};
u8 sector_ct = 2;
//double cream, strawberries, milk
void init(int argc, char** argv) {
    
}

void setup() {
    CLEAR_COLOR = rgb(25, 25, 25);
}

#define P_SPD 0.06
void update(double dt) {
    //sleep(16);
    player.v.x = 0;
    player.v.y = 0;
    player.v.z = 0;
    if (keys[SDL_SCANCODE_W])
        player.v.y++;
    if (keys[SDL_SCANCODE_S])
        player.v.y--;
    if (keys[SDL_SCANCODE_A])
        player.v.x--;
    if (keys[SDL_SCANCODE_D])
        player.v.x++;   

    if (keys[SDL_SCANCODE_Q])
        player.a += dt * 0.001;
    if (keys[SDL_SCANCODE_E])
        player.a -= dt * 0.001;

        
    if (keys[SDL_SCANCODE_SPACE])
        player.p.z -= dt * P_SPD;
    if (keys[SDL_SCANCODE_LSHIFT])
        player.p.z += dt * P_SPD;   

    if (player.v.x && player.v.y) {
        player.v.x /= sqrt(2);
        player.v.y /= sqrt(2);//neat lil solution instead of normalizing the vector. instead, i just normalize the vector! (kidding, but it gives the same result. idk if this is actually more optimla but it looks like it should be so whatever)
    }

    player.v = v3_rotz(player.v, player.a);

    player.p.x += player.v.x * dt * P_SPD;
    player.p.y += player.v.y * dt * P_SPD;

    sa = sin(player.a);
    ca = cos(player.a);
}//these commnets for the clip behind arent all mine. thanks to 3Dsage!
//while im at it, ill thank bisqwit and jdh aka jdah (hes called jdh on yt and jdah on github so idk)
void clipBehind(v2i* a, i16* l, i16* h, v2i b) {
 f32 da=a->y;                                 //distance plane -> point a
 f32 db= b.y;                                 //distance plane -> point b
 f32 d=da-db; if (d == 0) d = 1;
 f32 s = da/(da-db);                         //intersection factor (between 0 and 1)
 a->x = a->x + s*(b.x-(a->x));
 a->y = a->y + s*(b.y-(a->y)); if (/*some people shouldnt be allowed to write code. i mean look at this abysmal spacing. and this is after i cleaned part of it up*/ a->y==0){ a->y=1;} //prevent divide by zero 
// l = l + s*(l-(l));//yeah that does literally nothing because i actually just dont even change these things. by which i mean i dont turn thecam for y shearing i just lock the axisby not using it or whatever
}
//i wonder when i'll fix the glitch where stuff goes off to rly far away (not infinity)
void drawWall(v2i a, v2i b, i16 l, i16 h, u32 c) {
    line(100 + a.x, 100 + a.y, 100 + b.x, 100 + b.y, c);
    //*yes im modifying arguments what are you gonna do about it
    a.x -= player.p.x;
    a.y -= player.p.y;
//boutta make it all ints here we gooooooo
    b.x -= player.p.x;
    b.y -= player.p.y;

    l -= player.p.z;
    h -= player.p.z;
    
    a = v2i_rot(a, player.a);
    b = v2i_rot(b, player.a);
//yeah i made this function just for this abomination of a rework. now its all integers ewww
    //for some reason the verts that should clip run away to some far corner. i dont get it
    //it just occured to me that my old wall drawing thingy was possibly so ... nvm
    if (a.y <= 0 && b.y <= 0) return;
    if (a.x > b.x) {
        v2i swp = a;
        a = b;
        b = swp;
    }//i just fixed so many problems with this, by which i mean like 1
    if (a.y <= 0) {
        clipBehind(&a, &l, &h, b);//might be losing it rn
    }
    else if (b.y <= 0) {
        clipBehind(&b, &l, &h, a);//yeah its glitching so bad brb
    }

    i16 az = a.y;
    i16 bz = b.y;

    i16 ax = a.x * 200 / a.y + WIDTH/2;//well now i have *Different* issues. not solved, but new!
    /*i accidentall made these u16 when i was changing them from f32 to i16 aghh*/i16 ah = h * 200 / a.y + HEIGHT/2;
    i16 al = l * 200 / a.y + HEIGHT/2;

    i16 bx = b.x * 200 / b.y + WIDTH/2;
    i16 bh = h * 200 / b.y + HEIGHT/2;
    i16 bl = l * 200 / b.y + HEIGHT/2;


    i16 dx = bx - ax; if (dx == 0) dx = 1;
    i16 dl = bl - al;
    i16 dh = bh - ah;
    i16 xs = ax;
    {
    if (ax < 1) ax = 1;
    if (bx < 1) bx = 1;
    if (ax > WIDTH - 2) ax = WIDTH-2;
    if (bx > WIDTH - 2) bx = WIDTH-2;
    }
	for (i16 x = ax; x < bx; x+=1) {
        i16 y1 = dl * (x - xs + 0.5f) / dx + al;
        i16 y2 = dh * (x - xs + 0.5f) / dx + ah;//flipping didnt work
        {
        if (y1 < 1) y1 = 1;
        if (y2 < 1) y2 = 1;
        if (y1 > HEIGHT - 2) y1 = HEIGHT-2;
        if (y2 > HEIGHT - 2) y2 = HEIGHT-2;
        }  
        i16 z = 1;
        //pix(floor(x), floor(y1), c / z);
        /*//ad thiss*/ for (i16 y = y1; y < y2; y+=1) {
    		/*//lemme just comment this out for now */pix(floor(x), floor(y), c / z);
        /*////////}*/} //i just commented out comments, cry me a river so that i may bathe the contents of my soup
	}
}
//absurd block of code ahead (if youre movin backwards)
void draw() {
    clear();
    for (i8 i = 0; i != sector_ct; i+=1) {
        sector_t s = sectors[i];
        for (i8 j = 0; j != s.siz; j+=1) {//
            //you cant escape me but someone else did
            v2i a = verts[walls[s.idx + j].a], b = verts[walls[s.idx + j].b];
            if (walls[s.idx+j].portal)
                drawWall(a, b, s.flr, s.cei, rgb(255, 0, 52));
            else
                drawWall(a, b, s.flr, s.cei, rgb(150, 0, 152));//chaning colors
        }
    }
    pix(100 + player.p.x, 100 + player.p.y, rgb(0, 255, 255));
}