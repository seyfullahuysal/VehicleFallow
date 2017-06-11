#include <allegro.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>     
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Araba2
{
private:

	struct durulamakey{
		float deger;
		char karakter;
	};


public:
		float hiz,toplam_km,gunluk_km,devir,yakit,toplamhiz,hararet,sayac,islem,sonuc,ar1_gunluk_km;
		int vites,sure;
		int bolge;
		float koordinat;
		BITMAP *ok,*ok1,*ara,*panel,*ar2;
		FONT *myfont,*myfontb;
		PALETTE palette;
   
		Araba2(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float tkm)
		{

		   ar2=load_bitmap("bmp/ar2.bmp", NULL);
		   devir=0.0;
           hiz=0.0;
           gunluk_km=0.0;
           toplam_km=tkm;
		   vites=1;
		   ok=o;
		   ara=index;
		   bolge=1;
		   koordinat=0;
		   panel=p;
		   ok1=o1;
		   yakit=140;
		   toplamhiz=0;
		   hararet=0;
		   sayac=0;
		   islem=0;
		   sonuc=0;
		}
      	
		void Ciz()
		{

          
           char x[]="km/h";
           myfont=load_font("font/7.pcx",palette,NULL);
           myfontb=load_font("font/13.pcx",palette,NULL);
		   BITMAP *fren=load_bitmap("bmp/abs.bmp",NULL);
		   rotate_sprite(ara,panel,950,320,0);
				

		   /////////////////Bulanikkkk////////////////////////
		   float MVk[] = { -5, 40, 85, 125, 165 }, MDx[] = {0, 20, 40, 60, 80 }, Mak[] = { -40, -30, -20, -10, 0, 10, 20, 30, 40 };
		   char MVkc[] = { 'V', 'A', 'S', 'F', 'G' }, MDxc[] = { 'V', 'A', 'S', 'F', 'G' }, Makc[] = { 'Z', 'X', 'V', 'A', 'S', 'F', 'G', 'H', 'I' };
		   /////////////////////////////////////////
		   durulamakey *hizkey, *mesafekey, *sonuc;
		   float sonucDurula;
		   float uzaklik = ar1_gunluk_km - gunluk_km;
		   //////////////////////////////////////////
		   hizkey = GenlikDondur(MVk, MVkc, hiz, 5);
		   mesafekey = GenlikDondur(MDx, MDxc, uzaklik-2, 5);
		   sonuc = Fisislem(hizkey, mesafekey);
		   sonucDurula = Durula(sonuc, Mak, Makc, 9);
		   
		   hiz = hiz + sonucDurula;
		   textprintf_ex(ara, myfontb, 450, 475, makecol(255, 0, 0), makecol(0, 0, 0), "Dx = %.3f",uzaklik );
		   textprintf_ex(ara, myfontb, 700, 475, makecol(255, 0, 0), makecol(0, 0, 0), "V = %.3f", hiz);

		   gunluk_km += hiz*0.01;

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
			      rotate_sprite(ara,ar2,1265,610-koordinat*25,0);

		   }

		   if(bolge==2)
		   {
			      rotate_sprite(ara,ar2,1255-koordinat*25,-7,ftofix(-64));

		   }

		    if(bolge==3)
		   {
			      rotate_sprite(ara,ar2,10,0+koordinat*25,ftofix(-128));

		   }

			if(bolge==4)
		   {
			      rotate_sprite(ara,ar2,10+koordinat*25,623,ftofix(64));

		   }
          
           rotate_sprite(ara,ok,985,445,ftofix((hiz*1.16)*160/255-30));
		   if(sonucDurula<0)
		   {
			   blit(fren,ara,0,0,1065,515,1000,357);

		   }
		   textprintf_ex(ara,myfontb,150,475,makecol(255,0,0),makecol(0,0,0),"A: %.3f",sonucDurula); 

         }
	
        
public:
		//////////////////////////////////////////////////////
	float Durula(durulamakey *giris, float M[], char Mc[], int uzunluk)
	{
		float sonuc = 0, toplam = 0;
		int i_index = -1;
		durulamakey *index;
		for (int i = 0; giris[i].karakter != 'N'; i++)
		{
			for (int j = i + 1; giris[j].karakter != 'N'; j++)
			{
				if (giris[i].karakter == giris[j].karakter)
				{
					if (giris[i].deger > giris[j].deger)
					{
						giris[j].karakter = 'M';
					}
					else
					{
						giris[i].karakter = 'M';
					}
				}
			}
		}

		for (int i = 0; giris[i].karakter != 'N'; i++)
		{
			if (giris[i].karakter != 'M')
			{
				toplam = toplam + giris[i].deger;
				sonuc = sonuc + (giris[i].deger*FamToMerkez(giris[i].karakter, M, Mc, uzunluk));
			}
		}

		sonuc = sonuc / toplam;
		return sonuc;
	}
	float FamToMerkez(char giris, float M[], char Mc[], int uzunluk)
	{
		float cikis = 0;
		for (int i = 0; i<uzunluk; i++)
		{
			if (giris == Mc[i])
			{
				cikis = M[i];
				break;
			}
		}
		return cikis;
	}
	float MinBul(float a, float b)
	{
		float sonuc = 0;
		if (a <= b)
		{
			sonuc = a;
		}
		else
		{
			sonuc = b;
		}
		return sonuc;
	}
	float MaxBul(float a, float b)
	{
		float sonuc = 0;
		if (a >= b)
		{
			sonuc = a;
		}
		else
		{
			sonuc = b;
		}
		return sonuc;
	}
	durulamakey* Fisislem(durulamakey *ilk, durulamakey *son)
	{
		durulamakey *sonuc;
		sonuc = (durulamakey *)malloc(5 * sizeof(durulamakey));
		int say = 0;
		for (int i = 0; ilk[i].karakter != 'N'; i++)
		{
			for (int j = 0; son[j].karakter != 'N'; j++)
			{
				sonuc[say].karakter = FamDondur(ilk[i].karakter, son[j].karakter);
				sonuc[say].deger = MinBul(ilk[i].deger, son[j].deger);
				say++;
			}
		}

		sonuc[say].karakter = 'N';
		sonuc[say].deger = -1;

		return sonuc;
	}
	char KarakterDondur(int uzunluk, int giris, float M[], char Mc[])
	{
		char cikis;

		for (int i = 0; i<uzunluk; i++)
		{
			if (giris == M[i])
			{
				cikis = Mc[i];
			}
		}

		return cikis;
	}
	char FamDondur(char hiz, char mesafe)
	{
		char dondur = 'N';
		//////-----------V-------------////////
		if (hiz == 'V' && mesafe == 'V')
		{
			dondur = 'S';
		}
		else if (hiz == 'V' && mesafe == 'A')
		{
			dondur = 'F';
		}
		else if (hiz == 'V' && mesafe == 'S')
		{
			dondur = 'G';
		}
		else if (hiz == 'V' && mesafe == 'F')
		{
			dondur = 'H';
		}
		else if (hiz == 'V' && mesafe == 'G')
		{
			dondur = 'I';
		}
		//////////////------A----//////////////////
		else if (hiz == 'A' && mesafe == 'V')
		{
			dondur = 'A';
		}
		else if (hiz == 'A' && mesafe == 'A')
		{
			dondur = 'S';
		}
		else if (hiz == 'A' && mesafe == 'S')
		{
			dondur = 'F';
		}
		else if (hiz == 'A' && mesafe == 'F')
		{
			dondur = 'G';
		}
		else if (hiz == 'A' && mesafe == 'G')
		{
			dondur = 'H';
		}
		//////////////---------S-----------//////////////
		else if (hiz == 'S' && mesafe == 'V')
		{
			dondur = 'V';
		}
		else if (hiz == 'S' && mesafe == 'A')
		{
			dondur = 'A';
		}
		else if (hiz == 'S' && mesafe == 'S')
		{
			dondur = 'S';
		}
		else if (hiz == 'S' && mesafe == 'F')
		{
			dondur = 'F';
		}
		else if (hiz == 'S' && mesafe == 'G')
		{
			dondur = 'G';
		}
		////////////////-------F------------/////////////
		else if (hiz == 'F' && mesafe == 'V')
		{
			dondur = 'X';
		}
		else if (hiz == 'F' && mesafe == 'A')
		{
			dondur = 'V';
		}
		else if (hiz == 'F' && mesafe == 'S')
		{
			dondur = 'A';
		}
		else if (hiz == 'F' && mesafe == 'F')
		{
			dondur = 'S';
		}
		else if (hiz == 'F' && mesafe == 'G')
		{
			dondur = 'F';
		}
		//////////////////////////////-----G--------////////////
		else if (hiz == 'G' && mesafe == 'V')
		{
			dondur = 'Z';
		}
		else if (hiz == 'G' && mesafe == 'A')
		{
			dondur = 'X';
		}
		else if (hiz == 'G' && mesafe == 'S')
		{
			dondur = 'V';
		}
		else if (hiz == 'G' && mesafe == 'F')
		{
			dondur = 'A';
		}
		else if (hiz == 'G' && mesafe == 'G')
		{
			dondur = 'S';
		}

		return dondur;
	}
	durulamakey* GenlikDondur(float M[], char Mc[], int ara, int uzunluk)
	{
		int i_index;
		int oldu = 0;
		durulamakey *dondur;
		dondur = (durulamakey *)malloc(3 * sizeof(durulamakey));
		float egim = 1 / (M[2] - M[1]);
		float ilk = 0, son = 0, yilk = 0, yson = 0;

		if (ara > M[uzunluk - 1])
		{
			dondur[0].deger = 1;
			dondur[0].karakter = 'V';
			/////////////kontrol amacli////////////////
			dondur[1].deger = -1;
			dondur[1].karakter = 'N';
		}
		else if (ara < M[0])
		{
			dondur[0].deger = 1;
			dondur[0].karakter = 'G';
			/////////////kontrol amacli////////////////
			dondur[1].deger = -1;
			dondur[1].karakter = 'N';
		}
		else
		{
			for (int i = 0; i<uzunluk; i++)
			{
				if (ara == M[i])
				{
					dondur[0].deger = 0;
					dondur[0].karakter = KarakterDondur(uzunluk, ara, M, Mc);
					dondur[1].deger = 1;
					dondur[1].karakter = KarakterDondur(uzunluk, ara, M, Mc);
					dondur[2].deger = -1;
					dondur[2].karakter = 'N';
					oldu = 1;
					break;
				}
				else if (M[i] > ara)
				{
					ilk = M[i - 1];
					son = M[i];
					i_index = i;
					break;
				}
			}
			if (oldu == 0)
			{
				yilk = egim*(ara - ilk);
				yson = -1 * egim*(ara - son);

				dondur[0].deger = yilk;
				dondur[0].karakter = KarakterDondur(uzunluk, M[i_index], M, Mc);
				dondur[1].deger = yson;
				dondur[1].karakter = KarakterDondur(uzunluk, M[i_index - 1], M, Mc);
				dondur[2].deger = -1;
				dondur[2].karakter = 'N';
			}


		}

		return dondur;

	}
		//////////////////////////////////////////////////////////

		
		
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Kontroller2: public Araba2
{
	private:
			BITMAP *benzin,*uzun_acik,*kisa_acik,*uzun_kapali,*kisa_kapali,*sol,*sag;
		    int far_durum,sinyal_durum;
        
	public:
		    Kontroller2(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float t_km):Araba2(o,index,p,o1,t_km)
			{
			    
			}


/////////////////////////////////////////////////////////////////////
        void Ciz()
        {
            Araba2::Ciz();
			////////////////////////////////////////////////////////
			benzin=load_bitmap("bmp/benzin_bitti.bmp",NULL);
			//////////////////////////////////////////////////////////

            if(yakit<50)
            {
                       yakit=49;
                       blit(benzin,ara,0,0,414,611,1000,357);
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
class Secenekler2: public Kontroller2
{
	private:

		BITMAP *elfren,*korna,*dortlu,*hararet_s,*park,*sison,*sisarka;
        SAMPLE *ses;

    public:
		 Secenekler2(BITMAP *o,BITMAP *index,BITMAP *p,BITMAP *o1,float t_km):Kontroller2(o,index,p,o1,t_km)
        {
            
        }
		 void Ciz(float gunluk)
		 {
			 ar1_gunluk_km=gunluk;
			Kontroller2::Ciz();
			
		 }

};