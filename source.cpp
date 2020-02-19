/****************************************************************************
**					SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**				    BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				          PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...: PROJE ODEVI
**				ÖÐRENCÝ ADI...............: KUTAY
**				ÖÐRENCÝ NUMARASI.: B171210074
**				DERS GRUBU…………: D
****************************************************************************/

#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;
int y = 0; // olusturulan ucagin tusa basarken y koordinatini kontrol etmek icin olusturdum
const int genislik = 80;
const int yukseklik = 20;
const int maxMermiSayisi = 10000;
const int maxDusmanSayisi = 10000;
int aktifMermi = 0;
int aktifDusman = 0;
char sahne[genislik][yukseklik];
char		tuslar[256];
struct DusmanHucre
{
	int xxx;
	int yyy;
};
DusmanHucre dusmanKonumu[maxDusmanSayisi];
struct MermiHucre
{
	int xx;
	int yy;
};
MermiHucre mermiKonumu[maxMermiSayisi];

void gotoxy(int x, int y)

{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}


void sahneyiCiz()
{
	for (int y = 0; y < yukseklik; y++)  //2 tane ic ice forla 2 boyutlu sahnenin guncel halini ekrana bastirmak icin
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << sahne[x][y];
		}
		cout << endl;
	}
}
void sahneyiTemizle()
{
	for (int y = 0; y < yukseklik; y++) //2 tane ic ice forla 2 boyutlu sahneyi temizlemek icin
	{
		for (int x = 0; x < genislik; x++)
		{
			sahne[x][y] = ' ';
		}
	}
}
void sinirlariOlustur()
{
	for (int x = 0; x < genislik; x++) // sahnenin en ustunun ve en altinin sinirlarini olusturmak icin
	{
		sahne[x][0] = 219;
		sahne[x][yukseklik - 1] = 219;
	}

	for (int y = 0; y < yukseklik; y++) //sahnenin en sol ve en sag tarafinin sinirlarini olusturmak icin
	{
		sahne[0][y] = 219;
		sahne[genislik - 1][y] = 219;
	}
}
void ucakOlustur()
{
	sahne[1][12 + y] = 219;
	sahne[2][11 + y] = 219;
	sahne[3][10 + y] = 219;
	sahne[2][9 + y] = 219;
	sahne[1][8 + y] = 219;
}



void klavyeOku(char tuslar[])
{
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
}

void dusmaniSahneyeYerlestir()
{
	for (int i = 0; i < aktifDusman; i++) //olusturulan dusmanlari sahneye yerlestirmek icin
	{
		int xxx = dusmanKonumu[i].xxx;
		int yyy = dusmanKonumu[i].yyy;
		sahne[xxx][yyy] = 178;
		sahne[xxx + 1][yyy] = 178;
		sahne[xxx + 1][yyy + 1] = 178;
		sahne[xxx][yyy + 1] = 178;
		sahne[xxx + 2][yyy] = 178;
		sahne[xxx + 2][yyy + 1] = 178;
	}
}
void dusmaniHareketEttir()
{
	for (int i = 0; i < aktifDusman; i++) //aktif haldeki dusmanlarin 2 boyutlu dizideki hareketini saglamak icin
	{
		if (dusmanKonumu[i].xxx == 0)  //eger dusmanlar artik sahnenin en sol kosesine geldiyse x koordinati 1 arttirilacak ve bu sekilde dusmanlarin sahne disina cikmasini onleyerek programin hata vermesini onlemis olucaz.
			dusmanKonumu[i].xxx++;
		dusmanKonumu[i].xxx--;
	}
}
void dusmanEkle()
{

	int t = rand();
	if (t % 23 == 0)  //dusmanlari rastgele olarak farkli zaman araliklarinda bastirmak icin eger random olarak atanan t degeri 17nin katiysa dusmani ekleyecek
	{

		dusmanKonumu[aktifDusman].xxx = 78;
		dusmanKonumu[aktifDusman].yyy = 1 + rand() % 17;  // y ekseni uzerindeki konumunu random olarak belirliyor ve sahne sinirlarinin ustunde dusman olusmasin diye 1 ekledim ve 17 ile modunu aldim.
		aktifDusman++;                                   //eger 1 eklemeseydim ust sinirda olusurdu, 17'ye gore mod almasaydimda alt taraftaki sinirin ustunde dusman olusabilirdi.
	}


}


void mermiyiSahneyeYerlestir()
{
	for (int i = 0; i < aktifMermi; i++) //olusturulan mermileri 2 boyutlu dizide yani sahnede yerlerine yerlestirmek icin
	{
		int xx = mermiKonumu[i].xx;
		int yy = mermiKonumu[i].yy;
		sahne[xx][yy] = 254;
	}
}
void mermiyiHareketEttir()
{
	for (int i = 0; i < aktifMermi; i++) //olusturulan mermilerin 2 boyutlu dizide yani sahnede hareketini saglamak icin
	{
		if (mermiKonumu[i].xx == genislik) //eger mermi sahnenin en sag kosesine geldiyse bunun x koordinatini 1 azaltacak yani sahnenin disina cikip programin hata vermesini onleyecek.
			mermiKonumu[i].xx--;

		mermiKonumu[i].xx++;
	}
}
void mermiEkle()
{


	mermiKonumu[aktifMermi].xx = 4;
	mermiKonumu[aktifMermi].yy = 10 + y;
	aktifMermi++;

}

void dusmanYokEt()
{
	for (int k = 0; k < aktifMermi; k++) //distaki for aktif mermileri teker teker dolasacak
	{
		for (int l = 0; l < aktifDusman; l++) //icteki for aktif dusmanlari teker teker dolasacak
			if ((mermiKonumu[k].xx == dusmanKonumu[l].xxx && mermiKonumu[k].yy == dusmanKonumu[l].yyy) || (mermiKonumu[k].xx == (dusmanKonumu[l].xxx) + 1 && mermiKonumu[k].yy == dusmanKonumu[l].yyy) || (mermiKonumu[k].xx == dusmanKonumu[l].xxx && mermiKonumu[k].yy == (dusmanKonumu[l].yyy) + 1) || (mermiKonumu[k].xx == (dusmanKonumu[l].xxx) + 1 && mermiKonumu[k].yy == (dusmanKonumu[l].yyy) + 1) || (mermiKonumu[k].xx == (dusmanKonumu[l].xxx) + 2 && mermiKonumu[k].yy == dusmanKonumu[l].yyy) || (mermiKonumu[k].xx == (dusmanKonumu[l].xxx) + 2 && mermiKonumu[k].yy == (dusmanKonumu[l].yyy) + 1)) //if kosulu ile bunlarin sahnede ayni yerde olup olmadiklari kontrol edilecek eger ayni yerdelerse bu mermiyi sahnenin en sag kosesine tasiyacak, dusmani ise sahnenin en sag kosesinin 3 ilerisine tasiyacak
			{
				{
					mermiKonumu[k].xx = genislik;
					dusmanKonumu[l].xxx = genislik + 3;
				}
			}
	}
	for (int l = 0; l < aktifDusman; l++) //aktif dusmanlarin hepsini dolasmak icin
	{
		if (dusmanKonumu[l].xxx == 0)//eger dusmanlar olmeden sahnenin en sol kosesine geldiyse onlarý sahhenin en sag kosesinin 3 ilerisine atmak icin 
			dusmanKonumu[l].xxx = genislik + 3;
	}
}


void klavyeKontrol()
{
	//buradaki ifler ile tusa basilip basilmadigi kontrol ediliyor
	klavyeOku(tuslar);
	if (tuslar['S'] != 0 && 12 + y != yukseklik)
		y++;
	if (tuslar['W'] != 0 && 8 + y - 1 != -2)
		y--;
	if (tuslar['P'] != 0)
	{

		mermiEkle();
	}
}
int main()
{
	kursoruGizle();



	while (true)
	{
		sahneyiTemizle();
		sinirlariOlustur();
		ucakOlustur();
		klavyeKontrol();
		mermiyiHareketEttir();
		mermiyiSahneyeYerlestir();
		dusmanEkle();
		dusmaniHareketEttir();
		dusmaniSahneyeYerlestir();
		dusmanYokEt();
		gotoxy(0, 0);
		sahneyiCiz();
		Sleep(2);

	}




}