#include <allegro.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>     
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Araba
{

public:

		float hiz,toplam_km,gunluk_km,devir,yakit,toplamhiz,hararet,sayac,islem,sonuc;
		int vites,sure;
		int bolge;
		float koordinat;
		BITMAP *ok,*ok1,*ara,*panel,*ar1;
		FONT *myfont,*myfontb;
		PALETTE palette;
   
		Araba(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float tkm)
		{
			ar1=load_bitmap("bmp/ar1.bmp", NULL);
			devir=0.0;
           hiz=0.0;
		   gunluk_km=5;    
           toplam_km=tkm;
		   vites=1;
		   ok=o;
		   bolge=1;
		  koordinat=0;
		   ara=index;
		   panel=p;
		   ok1=o1;
		   yakit=140;
		   toplamhiz=0;
		   hararet=0;
		   sayac=0;
		   islem=0;
		   sonuc=0;
		}
      	
private:

		float hiz_dondur(float d,int v)
		{
			return (d/3.647/disli_dondur(v)/1000)*60; //*1.74
		}

        
public:

		void Ciz()
		{
          
           char x[]="km/h";
           myfont=load_font("font/7.pcx",palette,NULL);
           myfontb=load_font("font/13.pcx",palette,NULL);
		   BITMAP *fren=load_bitmap("bmp/abs.bmp",NULL);
		   
		   gunluk_km += hiz*0.01;
           islem=(toplamhiz+sayac)/10000;
		   rotate_sprite(ara,panel,60,80,0);
		   if(key[KEY_DOWN])
		   {
			   blit(fren,ara,0,0,515,360,1000,357);
		   }

		   float alinan_yol=fmod(gunluk_km,149);
		 
		   if(alinan_yol>=0 && alinan_yol<=25)
		   {
			  
				koordinat=fmod(alinan_yol,25);
				bolge=1;

		   }

		   if(alinan_yol>25 && alinan_yol<=74)
		   {

				koordinat=fmod(alinan_yol-25,49);
				bolge=2;

		   }

		   if(alinan_yol>74 && alinan_yol<=99)
		   {
			 
				koordinat=fmod(alinan_yol-74,25);
				bolge=3;

		   }

		   if(alinan_yol>99 && alinan_yol<=152)
		   {
			   
				koordinat=fmod(alinan_yol-99,51);
				bolge=4;

		   }


		  if(bolge==1)
		   {
			      rotate_sprite(ara,ar1,1265,610-koordinat*25,0);

		   }

		   if(bolge==2)
		   {
			      rotate_sprite(ara,ar1,1255-koordinat*25,-7,ftofix(-64));

		   }

		    if(bolge==3)
		   {
			      rotate_sprite(ara,ar1,10,0+koordinat*25,ftofix(-128));

		   }

			if(bolge==4)
		   {
			      rotate_sprite(ara,ar1,10+koordinat*25,623,ftofix(64));

		   }


           rotate_sprite(ara,ok,620,240,ftofix((hiz*1.16)*178/255-30));
           rotate_sprite(ara,ok,250,240,ftofix((devir*4)/100*178/255-35));
           rotate_sprite(ara,ok1,470,200,ftofix(yakit*178/256));
           rotate_sprite(ara,ok1,850,340,ftofix(((hararet*sayac)/5000)*178/256+30));

         }


///////////////////////////////////////////////////////////////////////////////////////////////////////////
		void Hareket()
		{
            
            if(yakit>50 && !key[KEY_SPACE] && hararet<128)
             {
				if(key[KEY_UP])
			    {

                    toplamhiz=toplamhiz+hiz;
                    sayac+=1;
                    hararet=hararet+0.02;
					if(devir<7000 && hiz<300)
					{
                            hararet=hararet+0.02;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
							devir+=10;
							if(devir<6000)
							{
                                sayac+=1;
								devir+=10;
								hiz=hiz_dondur(devir,vites);
								toplamhiz=toplamhiz+hiz;
								hararet=hararet+0.02;
							}
							if(devir>6100 && devir<6500 && vites<5)
							{
                                sayac+=1.2;
								vites++;
								

								devir=devir-2000;
								hiz=hiz_dondur(devir,vites);
								toplamhiz=toplamhiz+hiz;
								hararet=hararet+0.05;
							}
							if(devir>6550 && vites==5)
							{
                                sayac+=1.6;
								devir++;
								hiz=hiz_dondur(devir,vites);
								toplamhiz=toplamhiz+hiz;
								hararet=hararet+0.1;
							}
					}
				}

				else if(key[KEY_DOWN] && devir>900 && hiz>0 && vites>0)
				{
                    sayac+=0.3;
					devir=devir-100;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					hararet=hararet-0.01;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+3000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}

					
					}
				
				
				}
				else if(!key[KEY_UP] && !key[KEY_DOWN] && devir>900 && hiz>0 && vites>0)
				{	
                    hararet=hararet-0.01;
                    sayac+=0.3;
					devir=devir-10;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+2000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}
					}
				}	
       }
     else if((yakit<=50 || hararet>128) && devir>0 && hiz>0 && vites>0)
     {
     
                    hararet=hararet-0.01;
                    sayac+=0.3;
					devir=devir-10;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+2000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}
					}
    }
    else if(key[KEY_SPACE] && devir>100 && hiz>0 && vites>0)
    {
                    hararet=hararet-0.01;
                    sayac+=0.3;
					devir=devir-100;
					hiz=hiz_dondur(devir,vites);
					toplamhiz=toplamhiz+hiz;
					if(vites>1)
					{

						if(devir>3000 && devir<3500)
						{
							vites--;
							devir=devir+2000;
							hiz=hiz_dondur(devir,vites);
							toplamhiz=toplamhiz+hiz;
						}
					}



    }

   }

private:

	float disli_dondur(int a)
	{

			switch(a)
			{
			  case 1:
				  return 3.94182;
			  case 2:
				  return 2.6701;
			  case 3:
				  return 1.8087;
			  case 4:
				  return 1.2252;
			  case 5:
				  return 0.830;

			}
			
	}
		
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Kontroller: public Araba
{
	private:
			BITMAP *benzin,*uzun_acik,*kisa_acik,*uzun_kapali,*kisa_kapali,*sol,*sag;
		    int far_durum,sinyal_durum;
        
	public:
		    Kontroller(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float t_km):Araba(o,index,p,o1,t_km)
			{
			    
			}


/////////////////////////////////////////////////////////////////////
        void Ciz()
        {
            Araba::Ciz();
			////////////////////////////////////////////////////////
			benzin=load_bitmap("bmp/benzin_bitti.bmp",NULL);
			//////////////////////////////////////////////////////////

            if(yakit<50)
            {
                       yakit=49;
                       blit(benzin,ara,0,0,414,251,1000,357);
            }
            else
            {
               yakit=140-(islem*1.2);
            }
            
            
        }
///////////////////////////////////////////////////////////////////////
        float km_cevir()
        {
            return sonuc;
        }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Secenekler: public Kontroller
{
	private:

		BITMAP *elfren,*korna,*dortlu,*hararet_s,*park,*sison,*sisarka;
        SAMPLE *ses;

    public:
		 Secenekler(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float t_km):Kontroller(o,index,p,o1,t_km)
        {
            
        }
		 void Ciz()
		 {
			Kontroller::Ciz();
			
		 }

};