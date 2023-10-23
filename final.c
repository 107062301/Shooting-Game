#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
/*+
    TODO: Declare display variable.
*/
#define up 0
#define down 1
#define left 2
#define right 3
#define gameterminate 666
int use1=0;
int use2=0;
float damage=0;
float c;
float X;
float proof;
float proof1;
float proof2;
int chan=0;
int change=0;
int count;
int difficulty=1;
int mute=0;
int end=0;
float health=15;
int kill=0;
int now=1;
int flagx,flagy;
typedef struct enemy1_{
int is_use;
float x;
float y;
float vx;
float vy;
float w;
float h;
float health;

}enemy1;
enemy1 enemy[9];
int n;
int t;
int j;
int i;

typedef struct bullet_{

float posx;
float posy;
float w;
float h;
float v;
int is_use;
}bullet;

bullet bullets[10];
bullet bullets2[10];

ALLEGRO_DISPLAY *display = NULL;
const ALLEGRO_EVENT_QUEUE *event_queue = NULL;
const ALLEGRO_EVENT event;
const ALLEGRO_FONT *font=NULL;
const ALLEGRO_FONT *font2=NULL;
const ALLEGRO_FONT *font3=NULL;
const ALLEGRO_BITMAP *img = NULL;
const ALLEGRO_BITMAP *ope = NULL;
const ALLEGRO_BITMAP *evil = NULL;
const ALLEGRO_BITMAP *angel = NULL;
const ALLEGRO_BITMAP *vic = NULL;
const ALLEGRO_BITMAP *clos = NULL;
const ALLEGRO_BITMAP *img2 = NULL;
const ALLEGRO_BITMAP *flower = NULL;
const ALLEGRO_BITMAP *sky = NULL;
//const ALLEGRO_BITMAP *blast1 = NULL;
//const ALLEGRO_BITMAP *blast2 = NULL;
const ALLEGRO_BITMAP *character = NULL;
const ALLEGRO_BITMAP *character2 = NULL;
const ALLEGRO_BITMAP *bu = NULL;
const ALLEGRO_BITMAP *fire = NULL;
const ALLEGRO_BITMAP *ho = NULL;
const ALLEGRO_BITMAP *character3 = NULL;
ALLEGRO_SAMPLE *music = NULL;
ALLEGRO_SAMPLE_INSTANCE *music1 = NULL;
ALLEGRO_SAMPLE *hor = NULL;
ALLEGRO_SAMPLE_INSTANCE *hor1 = NULL;
ALLEGRO_SAMPLE *sad = NULL;
ALLEGRO_SAMPLE_INSTANCE *sad1 = NULL;
ALLEGRO_SAMPLE *victor = NULL;
ALLEGRO_SAMPLE_INSTANCE *victor1 = NULL;
ALLEGRO_SAMPLE *halo = NULL;
ALLEGRO_SAMPLE_INSTANCE *halo1 = NULL;
ALLEGRO_SAMPLE *bl = NULL;
ALLEGRO_SAMPLE_INSTANCE *bl1 = NULL;
ALLEGRO_SAMPLE *light = NULL;
ALLEGRO_SAMPLE_INSTANCE *light1 = NULL;
ALLEGRO_SAMPLE *magic = NULL;
ALLEGRO_SAMPLE_INSTANCE *magic1 = NULL;
ALLEGRO_SAMPLE *pon = NULL;
ALLEGRO_SAMPLE_INSTANCE *pon1 = NULL;
ALLEGRO_SAMPLE *bang = NULL;
ALLEGRO_SAMPLE_INSTANCE *bang1 = NULL;


const int width = 800;
const int height = 600;
void game_vlog(const char* format, va_list arg);
void show_err_msg(int msg);
void game_init();
void game_begin_page1();
void game_begin_page2();
void game_begin_page3();
void game_begin_page4();
void game_begin_page5();
void game_begin_page6();
void game_begin_page7();
void game_destroy();
int msg = 0;
int prosses_event();
int game_run();
int process_event2();
int process_event3();
int process_event4();
int process_event5();
int process_event6();
int process_event7();
int judgex(bullet*,enemy1*);
int judgeb(bullet*,enemy1*);
int judgey(float,float,enemy1*);
int px,py;
bool *key;
bool draw;

int main(int argc, char *argv[]) {
    al_init();
    /*if (!al_init()) {
            show_err_msg(-1);
        }
   /*

    ALLEGRO_DISPLAY*al_create_display(width,heigth);

    ALLEGRO_DISPLAY*display=NULL;

    ALLEGRO_FONT*font=NULL;

*/
    printf("Hello world!!!\n");

   // al_rest(5);

    game_init();

   // game_begin_page1();

    while(msg!=gameterminate){

         msg = game_run();

        if(msg==gameterminate){
             printf("See you, world!!\n");
        }
    }

    game_destroy();
    return 0;
}


void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if(!al_init()){
        show_err_msg(-1);
    }

    px=350;
    py=450;

    display = al_create_display(width , height);
    if(display==NULL){


        show_err_msg(-1);
    }
    al_init_primitives_addon();

    al_install_keyboard();

    key=(bool*)malloc(4*sizeof(bool));

    memset(key,false,4*sizeof(bool));



    draw=true;

    al_init_image_addon();

    al_init_font_addon();

    al_init_ttf_addon();

    al_init_acodec_addon();

    al_install_audio();

    al_reserve_samples(20);

    font2=al_load_ttf_font("pirulen.ttf",25,0);
    font3=al_load_ttf_font("pirulen.ttf",15,0);
    font=al_load_ttf_font("pirulen.ttf",60,0);
    flower=al_load_bitmap("flower.png");
    if(font==NULL){
        printf("noooooo");

        show_err_msg(-1);
    }
   // blast1=al_load_bitmap("blast1.jpg");
 //   blast2=al_load_bitmap("blast2.jpg");
    ope = al_load_bitmap("open.jpg");
    clos = al_load_bitmap("close.jpg");
    evil = al_load_bitmap("evil.jpg");
    angel = al_load_bitmap("angel.jpg");

    character = al_load_bitmap("sans1.png");
    character2 = al_load_bitmap("sans.png");
    character3 = al_load_bitmap("sans2.png");

    bu = al_load_bitmap("bullet1.png");
    img = al_load_bitmap("boom1.png");
    img2 = al_load_bitmap("pa.jpg");
    music = al_load_sample("mega.wav");
    music1 = al_create_sample_instance(music);
    hor = al_load_sample("rrr.wav");
    hor1 = al_create_sample_instance(hor);
    sad = al_load_sample("sad.wav");
    sad1 = al_create_sample_instance(sad);
    victor = al_load_sample("victory.wav");
    victor1 = al_create_sample_instance(victor);
    halo = al_load_sample("halo.wav");
    halo1 = al_create_sample_instance(halo);
    bl = al_load_sample("bl.wav");
    bl1 = al_create_sample_instance(bl);
    light = al_load_sample("light.wav");
    light1 = al_create_sample_instance(light);
    magic = al_load_sample("magic.wav");
    magic1 = al_create_sample_instance(magic);
    pon = al_load_sample("pon.wav");
    pon1 = al_create_sample_instance(pon);
    bang = al_load_sample("bang.wav");
    bang1 = al_create_sample_instance(bang);
    vic = al_load_bitmap("vic.jpg");
    sky = al_load_bitmap("sky.jpg");
    fire = al_load_bitmap("fire2.png");
    ho = al_load_bitmap("ho.png");
    if(img==NULL){
        printf("naaaaaa");

        show_err_msg(-1);
    }
      al_install_mouse();
    event_queue= al_create_event_queue();

    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_sample_instance_playmode(music1,ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(music1,1.0);
    al_attach_sample_instance_to_mixer(music1,al_get_default_mixer());
    al_set_sample_instance_playmode(hor1,ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(hor1,1.0);
    al_attach_sample_instance_to_mixer(hor1,al_get_default_mixer());
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_set_sample_instance_playmode(sad1,ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(sad1,1.0);
    al_attach_sample_instance_to_mixer(sad1,al_get_default_mixer());
    al_set_sample_instance_playmode(victor1,ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(victor1,1.0);
    al_attach_sample_instance_to_mixer(victor1,al_get_default_mixer());
    al_set_sample_instance_playmode(halo1,ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(halo1,1.0);
    al_attach_sample_instance_to_mixer(halo1,al_get_default_mixer());
    al_set_sample_instance_playmode(bl1,ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(bl1,1.0);
    al_attach_sample_instance_to_mixer(bl1,al_get_default_mixer());
    al_set_sample_instance_playmode(light1,ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(light1,1.0);
    al_attach_sample_instance_to_mixer(light1,al_get_default_mixer());
    al_set_sample_instance_playmode(magic1,ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(magic1,1.0);
    al_attach_sample_instance_to_mixer(magic1,al_get_default_mixer());
    al_set_sample_instance_playmode(pon1,ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(pon1,1.0);
    al_attach_sample_instance_to_mixer(pon1,al_get_default_mixer());
    al_set_sample_instance_playmode(bang1,ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(bang1,1.0);
    al_attach_sample_instance_to_mixer(bang1,al_get_default_mixer());
    al_register_event_source(event_queue,al_get_keyboard_event_source());


}

void game_begin_page1() {

    al_clear_to_color(al_map_rgb(50,10,70));
    if(mute==0){al_play_sample_instance(halo1);}
    al_draw_bitmap(sky,0,0,0);
    al_draw_text(font,al_map_rgb(255,255,255),400,10,1,"Go GO Fighter!!!");

    al_draw_filled_rectangle(200,230,600,290,al_map_rgb(0,187,0));
    al_draw_filled_rectangle(200,310,600,370,al_map_rgb(225,225,51));
    al_draw_filled_rectangle(200,470,600,530,al_map_rgb(255,45,45));
    al_draw_filled_rectangle(200,390,600,450,al_map_rgb(166,166,210));

    al_draw_rectangle(201.1,231.5,599,289,al_map_rgb(255,255,0),0);
    al_draw_rectangle(201.1,311.5,599,369,al_map_rgb(255,255,0),0);
    al_draw_rectangle(201.1,471.5,599,529,al_map_rgb(255,255,0),0);
    al_draw_rectangle(201.1,391.5,599,449,al_map_rgb(255,255,0),0);

    al_draw_text(font2,al_map_rgb(255,255,255),400,243,1,"About");
    al_draw_text(font2,al_map_rgb(255,255,255),400,325,1,"Start");
    al_draw_text(font2,al_map_rgb(255,255,255),400,488,1,"Exit");
    al_draw_text(font2,al_map_rgb(255,255,255),400,405,1,"Settings");
    al_draw_text(font3,al_map_rgb(255,255,255),400,570,1,"press Esc to leave");




    if(img==NULL){
        printf("neeeee");
        show_err_msg(-1);
    }

    now=1;

    al_draw_bitmap(img2,324,95,0);


    al_flip_display();


}
void game_destroy() {
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(img);

}

int prosses_event(){
    al_wait_for_event(event_queue,&event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){

        switch(event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
            key[up]=true;
            break;

        case ALLEGRO_KEY_DOWN:
            key[down]=true;
            break;

        case ALLEGRO_KEY_LEFT:
            key[left]=true;
            break;

        case ALLEGRO_KEY_RIGHT:
            key[right]=true;
            break;
        case ALLEGRO_KEY_D:
            now=2;
            break;

        case ALLEGRO_KEY_E:
            now=3;
            break;
        }

    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_UP:
            key[up]=false;
            break;

            case ALLEGRO_KEY_DOWN:
            key[down]=false;
            break;

            case ALLEGRO_KEY_LEFT:
            key[left]=false;
            break;

            case ALLEGRO_KEY_RIGHT:
            key[right]=false;
            break;

            case ALLEGRO_KEY_D:
            now=2;
            break;

            case ALLEGRO_KEY_E:
            now=3;
            break;

            case ALLEGRO_KEY_ESCAPE:
                return gameterminate;
                break;
        }

    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button == 1){
            if(event.mouse.x>200&&event.mouse.x<600&&event.mouse.y<370&&event.mouse.y>315){
                al_stop_sample_instance(halo1);
                now = 2;
            }
            else if(event.mouse.x>200&&event.mouse.x<600&&event.mouse.y>450&&event.mouse.y<505){
                al_stop_sample_instance(halo1);
                now = 3;
            }
            else if(event.mouse.x>200&&event.mouse.x<600&&event.mouse.y>385&&event.mouse.y<440){
                al_stop_sample_instance(halo1);
                now = 4;
            }
            else if(event.mouse.x>200&&event.mouse.x<600&&event.mouse.y>245&&event.mouse.y<300){
                al_stop_sample_instance(halo1);
                now = 5;
            }

    }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

        return gameterminate;

    }
    if(now==2){
        game_begin_page2();
    }
    else if(now==3){
        game_begin_page3();
    }
    else if(now==4){
        game_begin_page4();
    }

    py-= key[up]*10;
    py+= key[down]*10;
    px-= key[left]*10;
    px+= key[right]*10;


     // al_draw_filled_rectangle(px+100,py-300,px+200,py-200,al_map_rgb(0,255,0));


    al_flip_display();

    al_clear_to_color(al_map_rgb(0,0,0));

    return 0;

}
int game_run(){

    int error=0;

    if(now==2)
    {
        game_begin_page2();
    }
    else if(now==3)
    {
        game_begin_page3();
    }
    else if(now==4)
    {
        game_begin_page4();
    }
    else if(now==5)
    {
        game_begin_page5();
    }
    else if(now==6)
    {
        game_begin_page6();
    }
    else if(now==7)
    {
        game_begin_page7();
    }


    if(!al_is_event_queue_empty(event_queue)){
            if(now==1){
                 game_begin_page1();
                 error=prosses_event();
            }
            else if(now==2){

                error=process_event2();
            }
            else if(now==3)
            {
                error=process_event3();

            }
            else if(now==4)
            {
                error=process_event4();

            }
            else if(now==5)
            {
                error=process_event5();

            }
            else if(now==6)
            {
                error=process_event6();

            }
            else if(now==7)
            {
                error=process_event7();

            }

    }

    return error;

}

int process_event2() {
    al_wait_for_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return gameterminate;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button == 1)
            draw = !draw;
        /*else if (event.mouse.button == 2)
            return gameterminate;*/
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        px = event.mouse.x;
        py = event.mouse.y;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
         switch(event.keyboard.keycode){
             case ALLEGRO_KEY_UP:
            key[up]=true;
            break;

        case ALLEGRO_KEY_DOWN:
            key[down]=true;
            break;

        case ALLEGRO_KEY_LEFT:
            key[left]=true;
            break;

        case ALLEGRO_KEY_RIGHT:
            key[right]=true;
            break;
        case ALLEGRO_KEY_C:
            now=1;
            break;
        case ALLEGRO_KEY_R:
            if(change==0){
                change=1;
            }
            else if(change==1){
                change=0;
            }

            break;

    }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_C:
            al_stop_sample_instance(music1);
            now=1;
            break;
            case ALLEGRO_KEY_UP:
            key[up]=false;
            break;

            case ALLEGRO_KEY_DOWN:
            key[down]=false;
            break;

            case ALLEGRO_KEY_LEFT:
            key[left]=false;
            break;

            case ALLEGRO_KEY_RIGHT:
            key[right]=false;
            break;
            case ALLEGRO_KEY_Q:
            al_play_sample_instance(magic1);
            for(i=0;i<10;i++){
             if(bullets2[i].is_use==0){
                bullets2[i].posx=px-60;
                bullets2[i].posy=py-40;
                bullets2[i].is_use=1;
                bullets2[i].v=0.001;
             }
            }
            break;

            case ALLEGRO_KEY_W:
            al_play_sample_instance(light1);
            for(i=0;i<10;i++){
             if(bullets[i].is_use==0){
                bullets[i].posx=px+30;
                bullets[i].posy=py;
                bullets[i].is_use=1;
                bullets[i].v=0.001;
             }
            }
            break;

            case ALLEGRO_KEY_R:
            if(change<2){
                if(change==0){
                    if(use1==0){
                    al_play_sample_instance(pon1);
                    health=15;
                    change=1;
                    use1=1;
                    }
                }
                else if(change==1){
                    if(use2==0){
                    al_play_sample_instance(bang1);
                    health=15;
                    change=2;
                    use2=1;
                    }
                }
            }
            else if(change==2){
                health=15;
                change=0;
            }


            break;



            case ALLEGRO_KEY_ESCAPE:
                return gameterminate;
                break;
        }
    }

    if(now==1){
        game_begin_page1();
    }
    py-= key[up]*25;
    py+= key[down]*25;
    px-= key[left]*25;
    px+= key[right]*25;

    //if(draw)
    //al_draw_filled_rectangle(px+50, py-50, px - 50, py+50 , al_map_rgb(255, 0, 255));
    //al_draw_filled_rectangle(px+50,py-50,px-50,py+50,al_map_rgb(0,255,0));
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));

    return 0;
}
void game_begin_page2(){
    al_clear_to_color(al_map_rgb(0,0,0));
    if(mute==0){al_play_sample_instance(music1);}
    al_draw_text(font2,al_map_rgb(255,26,25),400,10,1,"h e l l o");
    al_draw_text(font2,al_map_rgb(255,26,25),400,40,1,"r e a d y   t o   d i e e e e e   ? ? ?");
    al_draw_text(font2,al_map_rgb(255,255,255),400,550,1,"press C to return to menu");
    /*al_draw_filled_rectangle(px+50, py-50, px - 50, py+50 ,al_map_rgb(2,255,25));
    al_draw_filled_rectangle(px+50, py-50, px - 50, py+50 ,al_map_rgb(255,0,255));*/
    if(change==0){
        al_draw_bitmap(character2,px-60,py-70,0);
        chan=0;
    }
    else if(change==1){
        al_draw_bitmap(character,px-60,py-70,0);
        al_draw_bitmap(fire,(rand()%2)*10+(px-120),(rand()%2)*10+(py-140),0);
        chan=1;
    }
    else if(change==2){
        al_draw_bitmap(character3,px-60,py-70,0);
        al_draw_bitmap(ho,(rand()%2)*10+(px-120),(rand()%2)*10+(py-140),0);
        chan=0;
    }
    al_draw_rectangle(px-27,py+50,px+33,py+55,al_map_rgb(255,255,255),0);
    float now1=al_get_time();
    for(t=1;t<count+1;t++){
        // printf("%f\n",33*(health/15.0));
        // printf("%f\n",(33*health/15.0));
        if(33*(health/15.0)<=0){
            end=1;
        }
        if((judgey(px-60,py-70,&enemy[t]))==1&&now1-proof>=0.4){
            health-=(1+damage);
            if(change==1||change==2){
                health+=0.3*(1+damage);
            }
            proof=now1;
        }
    }
     //printf("%f\n",33*(health/15.0));
    X=px-27;
    al_draw_filled_rectangle(X,py+50,X+(60*health/15.0),py+55,al_map_rgb(0,255,0));
    for(j=0;j<10;j++){
        if(bullets2[j].is_use==1){
            al_draw_bitmap(bu,bullets2[j].posx,bullets2[j].posy,0);
            //al_draw_rectangle(bullets2[j].posx,bullets2[j].posy,bullets2[j].posx+30,bullets2[j].posy+80,al_map_rgb(255,255,0),0);
            bullets2[j].posy-=1.0+chan*0.7;
        }
        if(bullets2[j].posx<0||bullets2[j].posx>850||bullets2[j].posy<0){
            bullets2[j].is_use=0;
        }
    }
    for(n=0;n<10;n++){
        if(bullets[n].is_use==1){
            al_draw_bitmap(img,bullets[n].posx,bullets[n].posy,0);
            bullets[n].posy-=0.3+chan*0.7;
        }
        if(bullets[n].posx<0||bullets[n].posx>850||bullets[n].posy<0){
            bullets[n].is_use=0;
        }
    }
    if(difficulty==1){
        damage=0;
        c=1.3;
        count=8;

    }
    if(difficulty==2){
        damage=0.77;
        c=1.6;
        count=5;
    }
    if(difficulty==3){
        damage=1.33;
        c=1.8;
        count=6;
    }
    for(t=1;t<count+1;t++){
        if(enemy[t].is_use==0){
        enemy[t].is_use=1;
        enemy[t].x=rand()%700;
        enemy[t].y=rand()%300;

        if(rand()%2==0){
            flagx=1;
        }
        else flagx=-1;

        if(rand()%2==0){
            flagy=1;
        }
        else flagy=-1;

        enemy[t].vx=0.23*c*flagx;
        enemy[t].vy=0.23*c*flagy;
        enemy[t].health=10;
        }

    }
    for(t=1;t<count+1;t++){
        if(69*(enemy[t].health/10.0)<=1.4 && enemy[t].is_use!=2){
            kill++;
            enemy[t].x=900;
            enemy[t].y=700;
            enemy[t].is_use=2;
        }
        if(enemy[t].is_use==1){
            al_draw_bitmap(flower,enemy[t].x,enemy[t].y,0);
            if(change==1||change==2){
                if(rand()%2==1)
                al_draw_rectangle(enemy[t].x,enemy[t].y,enemy[t].x+80,enemy[t].y+80,al_map_rgb(255,0,0),0);
                if(rand()%2==0)
                al_draw_rectangle(enemy[t].x,enemy[t].y,enemy[t].x+80,enemy[t].y+80,al_map_rgb(255,255,0),0);
            }
            enemy[t].x-=enemy[t].vx;
            enemy[t].y-=enemy[t].vy;
            /*al_draw_rectangle(enemy[t].x+9,enemy[t].y+100,enemy[t].x+69,enemy[t].y+105,al_map_rgb(255,255,255),0);

            al_draw_filled_rectangle(enemy[t].x+9.1,enemy[t].y+100.1,enemy[t].x+68.9,enemy[t].y+104.9,al_map_rgb(255,0,0));*/

            al_draw_rectangle(enemy[t].x+9,enemy[t].y+100,enemy[t].x+69,enemy[t].y+105,al_map_rgb(255,255,255),0);

            for(i=0;i<10;i++){
                if(bullets2[i].is_use==1){
                    if((judgex(&bullets2[i],&enemy[t]))==1&&now1-proof1>=0.3){
                        proof1=now1;
                        enemy[t].health-=1+chan*0.7;
                        if(change==2){
                            health+=0.6;
                        }
                    }
                }
            }
            for(i=0;i<10;i++){
                if(bullets[i].is_use==1){
                    if((judgeb(&bullets[i],&enemy[t]))==1&&now1-proof2>=0.1){
                        proof2=now1;
                        enemy[t].health-=2.5+chan*1;
                        if(change==2){
                            health+=0.6;
                        }
                    }
                }
            }
            if(change==2){
                if((judgey(px-60,py-70,&enemy[t]))==1&&now1-proof>=0.4){
                    proof=now1;
                    enemy[t].health-=1.0;
                }

            }


           al_draw_filled_rectangle(enemy[t].x+9,enemy[t].y+100,enemy[t].x+(69*(enemy[t].health/10.0)),enemy[t].y+105,al_map_rgb(255,0,0));

            if(enemy[t].y<20 || enemy[t].y>520){
                enemy[t].vy=enemy[t].vy*(-1);
            }
            if(enemy[t].x>750 || enemy[t].x<10){
                enemy[t].vx=enemy[t].vx*(-1);
            }
        }

    }

    now=2;
    if(kill==count){
        now=6;
    }
    if(end==1){
        now=7;
    }

    al_flip_display();


}
void game_begin_page3(){

    al_clear_to_color(al_map_rgb(0,0,0));
    if(mute==0){al_play_sample_instance(hor1);}
    al_draw_text(font,al_map_rgb(255,225,215),400,50,1,"YOU CAN'T");
    al_draw_text(font,al_map_rgb(255,55,55),400,150,1,"RUN AWAY");
    al_draw_text(font,al_map_rgb(255,25,125),400,250,1,"@!#$$&^*(&^))");
    al_draw_text(font2,al_map_rgb(255,0,0),400,550,1,"press C to return");
    al_draw_bitmap(character,px-60,py-70,0);
     for(n=0;n<8;n++){
        enemy[n].x=rand()%800;
        enemy[n].y=rand()%300;
    }

    for(n=0;n<8;n++){
        al_draw_bitmap(flower,enemy[n].x,enemy[n].y,0);
    }


   // al_draw_bitmap(blast1,0,500,0);

   // al_draw_bitmap(blast2,500,500,0);


    now=3;

    al_flip_display();


}
int process_event3(){

al_wait_for_event(event_queue,&event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){

        switch(event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
            key[up]=true;
            break;

        case ALLEGRO_KEY_DOWN:
            key[down]=true;
            break;

        case ALLEGRO_KEY_LEFT:
            key[left]=true;
            break;

        case ALLEGRO_KEY_RIGHT:
            key[right]=true;
            break;
       // case ALLEGRO_KEY_D:
          //  now=2;
         //   break;

        case ALLEGRO_KEY_C:
            now=1;
            break;
        }

    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_UP:
            key[up]=false;
            break;

            case ALLEGRO_KEY_DOWN:
            key[down]=false;
            break;

            case ALLEGRO_KEY_LEFT:
            key[left]=false;
            break;

            case ALLEGRO_KEY_RIGHT:
            key[right]=false;
            break;

            case ALLEGRO_KEY_C:
            al_stop_sample_instance(hor1);
            now=1;
            break;

          //  case ALLEGRO_KEY_D:
          //  now=2;
          //  break;

            case ALLEGRO_KEY_ESCAPE:
                return gameterminate;
                break;
        }

    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

        return gameterminate;

    }

    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button == 1)
            draw = !draw;
        else if (event.mouse.button == 2)
            return gameterminate;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        px = event.mouse.x;
        py = event.mouse.y;
    }
    if(now==2){
        game_begin_page2();
    }
    else if(now==1){
        game_begin_page1();
    }
    al_draw_bitmap(character,px-60,py-70,0);

    //al_draw_bitmap(blast1,0,500,0);

    //al_draw_bitmap(blast2,500,500,0);


    al_flip_display();

    al_clear_to_color(al_map_rgb(0,0,0));

    return 0;


}
void game_begin_page4(){
    al_clear_to_color(al_map_rgb(50,10,70));
    if(mute==0){al_play_sample_instance(bl1);}
    al_draw_text(font2,al_map_rgb(255,255,255),400,550,1,"press C to return");
    al_draw_text(font2,al_map_rgb(255,255,255),270,50,0,"background music open");
    al_draw_text(font2,al_map_rgb(255,255,255),270,200,0,"background music mute");
    al_draw_text(font2,al_map_rgb(255,255,255),270,320,0,"difficulty adjust A");
    al_draw_text(font2,al_map_rgb(255,255,255),270,450,0,"difficulty adjust V");
    al_draw_bitmap(ope,100,10,0);
    al_draw_bitmap(clos,100,150,0);
    al_draw_bitmap(evil,100,280,0);
    al_draw_bitmap(angel,100,410,0);
    now=4;

    al_flip_display();
}
int process_event4(){
    al_wait_for_event(event_queue,&event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){

        switch(event.keyboard.keycode){

        case ALLEGRO_KEY_C:
            al_stop_sample_instance(bl1);
            now=1;
            break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){

            case ALLEGRO_KEY_C:
            al_stop_sample_instance(bl1);
            now=1;
            break;

            case ALLEGRO_KEY_ESCAPE:
                return gameterminate;
                break;
        }

    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button == 1){
            if(event.mouse.x>100&&event.mouse.x<220&&event.mouse.y<130&&event.mouse.y>10&&mute==1){
                mute=0;
            }
            else if(event.mouse.x>100&&event.mouse.x<220&&event.mouse.y<280&&event.mouse.y>160&&mute==0){
               mute=1;
            }
            if(event.mouse.x>100&&event.mouse.x<220&&event.mouse.y<400&&event.mouse.y>280&&difficulty<3){
                health=15;
                kill=0;
                for(t=0;t<8;t++){
                enemy[t].is_use=0;
                }
                use1=0;
                use2=0;
                difficulty++;
            }
            else if(event.mouse.x>100&&event.mouse.x<220&&event.mouse.y<530&&event.mouse.y>410&&difficulty>1){
                health=15;
                kill=0;
                for(t=0;t<8;t++){
                enemy[t].is_use=0;
                }
                use1=0;
                use2=0;
                difficulty--;
            }

        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

        return gameterminate;
    }
    if(now==1){
        game_begin_page1();
    }

    al_flip_display();

    al_clear_to_color(al_map_rgb(0,0,0));

    return 0;
}
void game_begin_page5(){
    al_clear_to_color(al_map_rgb(50,10,70));
    if(mute==0){al_play_sample_instance(bl1);}
    al_draw_text(font2,al_map_rgb(255,255,255),400,40,1,"this game is made by Jeff_Lee");
    al_draw_text(font2,al_map_rgb(255,255,255),400,90,1,"how to play:");
    al_draw_text(font2,al_map_rgb(255,255,51),400,160,1,"press 'Q' to shoot");
    al_draw_text(font2,al_map_rgb(255,255,51),400,210,1,"press 'W' to shoot special bullet");
    al_draw_text(font2,al_map_rgb(255,255,255),90,260,0,"press 'R' to ");
    al_draw_text(font2,al_map_rgb(255,0,0),325,260,0,"BECOME ULTIMATE!!!");
    al_draw_text(font2,al_map_rgb(255,255,255),80,310,0,"you'll get");
    al_draw_text(font2,al_map_rgb(255,0,0),300,310,0,"30% damage discount");
    al_draw_text(font2,al_map_rgb(187,255,255),80,370,0,"and also ");
    al_draw_text(font2,al_map_rgb(255,0,0),300,370,0,"enhance your bullet!!!");
    al_draw_text(font2,al_map_rgb(187,255,255),400,430,1," hope you enjoy the game!!!");
    al_draw_text(font,al_map_rgb(255,117,117),400,465,1,"Have fun!!!!");
    al_draw_text(font2,al_map_rgb(255,255,255),400,550,1,"press C to return");
    now=5;
    al_flip_display();
}
int process_event5(){
    al_wait_for_event(event_queue,&event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){

        switch(event.keyboard.keycode){

        case ALLEGRO_KEY_C:
            al_stop_sample_instance(bl1);
            now=1;
            break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){

            case ALLEGRO_KEY_C:
            al_stop_sample_instance(bl1);
            now=1;
            break;

            case ALLEGRO_KEY_ESCAPE:
                return gameterminate;
                break;
        }

    }
    if(now==1){
        game_begin_page1();
    }
    al_flip_display();

    al_clear_to_color(al_map_rgb(0,0,0));

    return 0;
}
int judgex(bullet *a,enemy1 *b){

    float apx = a->posx;
    float bpx = b->x;
    float apy = a->posy;
    float bpy = b->y;


    if((apx+30<bpx)||(apx>bpx+60) || (apy>bpy+60)||(apy+80<bpy))
    {
            return 0;
    }

    else if(((apx+30>=bpx)&&(apx<=bpx+60))||((apx<=bpx+60)&&(apx+30>=bpx)) || ((apy<=bpy+60)&&(apy+80<=bpy))||((apy+80>bpy)&&(apy<=bpy+60))){
        a->is_use=0;
        return 1;
    }

}
int judgey(float apx,float apy,enemy1 *b){

    float bpx = b->x;

    float bpy = b->y;

    if((apx+80<bpx)||(apx>bpx+55) || (apy>bpy+55)||(apy+80<bpy))
    {
            return 0;
    }

    else if(((apx+80>=bpx)&&(apx<=bpx+55))||((apx<=bpx+55)&&(apx+80>=bpx)) || ((apy<=bpy+55)&&(apy+80<=bpy))||((apy+80>bpy)&&(apy<=bpy+55))){
        return 1;
    }


}
void game_begin_page6(){
    al_clear_to_color(al_map_rgb(50,10,70));
    al_stop_sample_instance(music1);
    if(mute==0){al_play_sample_instance(victor1);}
    al_draw_bitmap(vic,0,0,0);
    al_draw_filled_rectangle(355,343,445,363,al_map_rgb(255,0,0));
    al_draw_text(font3,al_map_rgb(255,255,255),363,343,0,"again!");
    al_draw_text(font2,al_map_rgb(255,255,255),400,550,1,"press C to return to menu");
    now=6;
    al_flip_display();
}
int process_event6(){
    al_wait_for_event(event_queue,&event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){

        switch(event.keyboard.keycode){

        case ALLEGRO_KEY_C:
            al_stop_sample_instance(victor1);
            now=1;
            break;

        case ALLEGRO_KEY_A:
            now=2;
            break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){

            case ALLEGRO_KEY_C:
            al_stop_sample_instance(victor1);
            now=1;
            break;

            case ALLEGRO_KEY_A:
            now=2;
            break;

            case ALLEGRO_KEY_ESCAPE:
                return gameterminate;
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button == 1){
            if(event.mouse.x>355&&event.mouse.x<445&&event.mouse.y<363&&event.mouse.y>343){
                al_stop_sample_instance(victor1);
                use1=0;
                use2=0;
                now = 2;
            }

        }
    }

    if(now==1){
        health=15;
        kill=0;
        for(t=0;t<8;t++){
            enemy[t].is_use=0;
        }
        game_begin_page1();
    }
    else if(now==2){
        health=15;
        kill=0;
        for(t=0;t<8;t++){
            enemy[t].is_use=0;
        }
        game_begin_page2();
    }
    al_flip_display();

    al_clear_to_color(al_map_rgb(0,0,0));

    return 0;








}
void game_begin_page7(){
    al_clear_to_color(al_map_rgb(50,10,70));
    al_stop_sample_instance(music1);
    if(mute==0){al_play_sample_instance(sad1);}
    al_draw_text(font,al_map_rgb(255,255,255),380,200,1,"you lose!");
    al_draw_filled_rectangle(165,280,595,360,al_map_rgb(255,0,0));
    al_draw_text(font,al_map_rgb(255,255,255),380,275,1,"restart!");
    al_draw_text(font2,al_map_rgb(255,255,255),400,550,1,"press C to return to menu");
    now=7;
    al_flip_display();
}
int process_event7(){

    al_wait_for_event(event_queue,&event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){

        switch(event.keyboard.keycode){

        case ALLEGRO_KEY_C:
            health=15;
            end=0;
            now=1;
            break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){

            case ALLEGRO_KEY_C:
            al_stop_sample_instance(sad1);
            health=15;
            end=0;
            now=1;
            break;

            case ALLEGRO_KEY_ESCAPE:
                return gameterminate;
                break;
        }
    }

    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if(event.mouse.button == 1){
            if(event.mouse.x>165&&event.mouse.x<595&&event.mouse.y<360&&event.mouse.y>280){
                al_stop_sample_instance(sad1);
                health=15;
                end=0;
                use1=0;
                use2=0;
                now = 2;
            }

        }
    }

    if(now==1){
        game_begin_page1();
    }
    else if(now==2){
        end=0;
        kill=0;
        for(t=0;t<8;t++){
            enemy[t].is_use=0;
        }
        game_begin_page2();
    }
    al_flip_display();

    al_clear_to_color(al_map_rgb(0,0,0));

    return 0;

}
int judgeb(bullet*a,enemy1*b){
    float apx = a->posx;
    float bpx = b->x;
    float apy = a->posy;
    float bpy = b->y;


    if((apx+60<bpx)||(apx>bpx+60) || (apy>bpy+60)||(apy+60<bpy))
    {
            return 0;
    }

    else if(((apx+60>=bpx)&&(apx<=bpx+60))||((apx<=bpx+60)&&(apx+60>=bpx)) || ((apy<=bpy+60)&&(apy+60<=bpy))||((apy+60>bpy)&&(apy<=bpy+60))){
        a->is_use=0;
        return 1;
    }
}
