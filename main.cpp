#include<allegro.h>
#include<iostream>
#include<math.h>
#include"araba.cpp"
#include"araba2.cpp"
#include<stdio.h>
#include<cstdlib>
#include<time.h>
using namespace std; 
float km_dondur();  
void Baslat();
void Bitir();
///////////////////////////////////////////
int main() 
{ 
	Baslat(); 
	float toplamkm=0;
	toplamkm=km_dondur();
    BITMAP *ok= load_bitmap("bmp/ok3.bmp", NULL);
    BITMAP *ok1= load_bitmap("bmp/ok4.bmp", NULL);
	BITMAP *ara=create_bitmap(1300,675);
	BITMAP *panel=load_bitmap("bmp/gosterge1.bmp", NULL);
	BITMAP *panel2=load_bitmap("bmp/gosterge2.bmp", NULL);
	BITMAP *yol=load_bitmap("bmp/yoll.bmp", NULL);
    Secenekler *a=new Secenekler(ok,ara,panel,ok1,toplamkm);
	Secenekler2 *a2=new Secenekler2(ok,ara,panel2,ok1,toplamkm);
	time_t bas,son;
	time(&bas);
	 
	

    while(!key[KEY_ESC])
    {
		time(&son);
		rotate_sprite(ara,yol,0,0,0);

		a->sure=difftime(son,bas);
        a->Ciz();

		a2->sure=difftime(son,bas);
		a2->Ciz(a->gunluk_km);

        a->Hareket();

		blit(ara,screen,0,0,0,0,1300,675);

		rest(10); 
                         
    } 

	Bitir();
	return 0;
}

/////////////////////////////////////////////////////////////////////////
END_OF_MAIN()
//////////////////////////////////////////////////////////////////////////////
void Baslat() 
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1300, 675, 0, 0);
	if (res != 0) 
	{
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT, "A");
	
}
///////////////////////////////////////////////////////////////////////////////////
void Bitir() 
{
	clear_keybuf();
} 
////////////////////////////////////////////////////////
float km_dondur()
{
    FILE *dosya;
    float km;
    float tkm=0;
    if((dosya=fopen("data/km.txt","r"))==NULL)
    {

    }
    while(!feof(dosya))
    {
        fscanf(dosya,"%f\n",&km);
        tkm+=km;
    }
    fclose(dosya);
    return tkm;
}
///////////////////////////////////////////////////////////////
