/*Emre Can KURAN
Caesar Cipher(Sezar Şifresi) uygulaması
02.10.2019 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include <cstring>
using namespace std;

// map(harita) kullanılarak tablo oluşturulacaktır

map<char, int> tablo;

// kullanıcıya gösterilecek olan mesajlar
string hata1, hata2, sifreMetniGir, cozulecekMetniGir, otelemeSayisiGir, menu, sOnce, sSonra,otelenmis;


//string değişkenlerinin tanımlandığı ve yüklendiği fonksiyon
void mesajlariYukle()
{
	menu = "-Metin sifrelemek için 1 girin\n-Metin cozmek icin 2 girin\n-Cikmak icin 3 girin\n";
	hata1 = "-----Hatali veya cok buyuk bir sayi girdiniz!-----\n";
	hata2 = "-----Hatali bir secim yaptiniz,lutfen tekrar deneyin!-----\n";
	sifreMetniGir = "Sifrelenecek metni girin(Menuye donmek icin 0 girin):\n";
	cozulecekMetniGir = "Cozulecek metni girin(Menuye donmek icin 0 girin):\n";
	otelemeSayisiGir = "Oteleme sayisini girin(Menuye donmek icin 0 girin):\n";
	sOnce = "Sifrelenmeden once metin:";
	sSonra = "\nSifrelendikten sonra metin:";
	otelenmis=" birim kadar kaydırılmış metin:";
}

/*tablo harf ve rakamlara göre oluşturuluyor,belli harf ve rakamlar esas alınmıştır,harflerin ve
rakamların kümesi isteğe
veya ihtiyaca bağlı olarak artırılıp azaltılabilir */

void tabloyuYukle()
{
	tablo['a'] = 0;
	tablo['b'] = 1;
	tablo['c'] = 2;
	tablo['d'] = 3;
	tablo['e'] = 4;
	tablo['f'] = 5;
	tablo['g'] = 6;
	tablo['h'] = 7;
	tablo['i'] = 8;
	tablo['j'] = 9;
	tablo['k'] = 10;
	tablo['l'] = 11;
	tablo['m'] = 12;
	tablo['n'] = 13;
	tablo['o'] = 14;
	tablo['p'] = 15;
	tablo['r'] = 16;
	tablo['s'] = 17;
	tablo['t'] = 18;
	tablo['u'] = 19;
	tablo['v'] = 20;
	tablo['y'] = 21;
	tablo['z'] = 22;
	tablo['q'] = 23;
	tablo['w'] = 24;
	tablo['x'] = 25;
}


//okunabilirliği artırmak için çıktıları biçimlndirmei sağlar

void ayrac(int uzunluk){

for(int i=0;i<uzunluk;i++)
cout<<"-";

cout<<"\n";
}

// Verilen metni şifreler,parametre olacak şifrelenecek metni alır ve her bir karakterin kaç birim
// öteleneceği bilgisini alır

void metniSifrele(const string &sifrelenecekMetin, int otelemeSayisi)
{
	string sifrelenmisMetin = "";	//şifrelenmiş karakterleri tutacak karakter dizisi
	map<char, int>::iterator it;	// tablo sorgulanırken anahtar-değer ikililerinin atanacağı değişken
	int kalan;	// kalanı bulmak için
	int deger;	// karakterin modu alındıktan sonra o anki değerini bulmak için
	int bulunanDeger;	// tabloda arama yaparken bulunan değerlerle asıl değeri kıyaslamak için

	for (int i = 0; i < sifrelenecekMetin.length(); i++)
	{

		// boşlukları atlar
		if (sifrelenecekMetin[i] == ' ')
		{
			sifrelenmisMetin += ' ';
			continue;
		}
		it = tablo.find(tolower(sifrelenecekMetin[i]));	//küçük-büyük harf durumundan dolayı tüm sorgulamalar küçük harfle yapılıyor

		// eğer tabloda olmayan bir karakterse olduğu gibi bırak ve atla
		if (it == tablo.end())
		{
			sifrelenmisMetin += sifrelenecekMetin[i];
			continue;
		}

		deger = it->second;	// burada second map yapısına özgü bir ifadedir, değere işaret
		// eder(it->first ise anahtara);örn karakter '1' ise deger 1'dir(tabloya
		// bakınız)

		if (deger + otelemeSayisi > 0)
			deger = (deger + otelemeSayisi) % tablo.size();	// öteleyip modunu alıyoruz,tablo.size()
		// tablonun boyutudur;yeni deger örn öteleme
		// sayısı 5 ise 1+5=6 olur,tablonun boyutunu
		// 36 kabul edersek 6%36=6 olur;

		else
		{
			deger = (deger + otelemeSayisi);
			while (deger < 0)	//çok büyük negatif sonuçlar için pozitif olana kadar tekrar eder
				deger = deger + tablo.size();
		}

		// tabloyu döngüde tarar, modu alınan yeni karakteri bulup şifrelenmiş metine ekler
		for (map<char, int>::iterator it = tablo.begin(); it != tablo.end(); ++it)
		{
			bulunanDeger = it->second;	// değerleri gezerken ata
			if (bulunanDeger == deger)
			{
				// bulunan değer modu alınan karaktere karşılık geliyorsa harfi kaydır,
                                //harfin durumuna göre eğer büyükse isupper ile kontrol
				//edip toupper ile gerekli dönüşümü yap(cctype kütüphanesi)
				if (isupper(sifrelenecekMetin[i]))
					sifrelenmisMetin += toupper(it->first);
				else
					sifrelenmisMetin += it->first;
				break;
			}
		}
	}

	//çıktıları yazdır
	ayrac(sifrelenecekMetin.length()+sSonra.length());
	cout << sOnce << sifrelenecekMetin <<
		sSonra << sifrelenmisMetin << endl;
	ayrac(sifrelenecekMetin.length()+sSonra.length());
	// okunabilir formda yazdırmak için

}
// Verilen şifrelenmiş metni brute-force(kaba kuvvet) yöntemiyle çözer;maksimum öteleme sayısına
// kadar olan çıktıları verir

void metniCoz(const string &cozulecekMetin, int maxOtelemeSayisi)
{

	string cozulmusMetin = "";	//çözülmüş karakterleri tutacak karakter dizisi
	map<char, int>::iterator it;	// tablo sorgulanırken anahtar-değer ikililerinin atanacağı değişken
	int kalan;	// kalanı bulmak için
	int deger;	// karakterin modu alındıktan sonra o anki değerini bulmak için
	int bulunanDeger;	// tabloda arama yaparken bulunan değerlerle asıl değeri kıyaslamak için

	ayrac(cozulecekMetin.length()+otelenmis.length());
	for (int j = 0; j <= maxOtelemeSayisi; j++)
	{
		cozulmusMetin = "";	// her iterasyonda temizle
		for (int i = 0; i < cozulecekMetin.length(); i++)
		{

			// boşlukları atlar
			if (cozulecekMetin[i] == ' ')
			{
				cozulmusMetin += ' ';
				continue;
			}
			it = tablo.find(tolower(cozulecekMetin[i]));	//küçük-büyük harf durumundan dolayı tüm sorgulamalar küçük harfle yapılıyor

			// eğer tabloda olmayan bir karakterse olduğu gibi bırak ve atla
			if (it == tablo.end())
			{
				cozulmusMetin += cozulecekMetin[i];
				continue;
			}

			deger = it->second;	// burada second map yapısına özgü bir ifadedir, değere işaret
			// eder(it->first ise anahtara);örn karakter '1' ise deger
			// 1'dir(tabloya bakınız)
			if (deger - j > 0)
				deger = deger - j % tablo.size();	// şifreyi çözmek için geriye öteleyip modunu
			// alıyoruz,tablo.size() tablonun boyutudur;yeni
			// deger örn iterasyondaki öteleme sayısı 5 ise
			// 1-5=-4 olur,tablonun boyutunu 36 kabul edersek
			// -4%36=32 olur;
			else
			{
				deger = (deger - j);
				while (deger < 0)	//çok büyük negatif sonuçlar için pozitif olana kadar tekrar eder
					deger = deger + tablo.size();
			}

			// tabloyu döngüde tarar, modu alınan yeni karakteri bulup cozulmus metine ekler
			for (map<char, int>::iterator it = tablo.begin(); it != tablo.end(); ++it)
			{
				bulunanDeger = it->second;	// değerleri gezerken ata
				if (bulunanDeger == deger)
				{
					// bulunan değer modu alınan karaktere karşılık geliyorsa harfi kaydır,harfin durumuna göre eğer büyükse isupper ile kontrol
					//edip toupper ile gerekli dönüşümü yap(cctype kütüphanesi)
					if (isupper(cozulecekMetin[i]))
						cozulmusMetin += toupper(it->first);
					else
						cozulmusMetin += it->first;
					break;
				}
			}
		}

		//çıktıları yazdır
		cout << j << otelenmis << cozulmusMetin << endl;
	}
	ayrac(cozulecekMetin.length()+otelenmis.length());

}

void sifrelenecekMetniAl()
{
	//kullanıcıdan girdileri alacağımız değişkenler

	string sifrelenecekMetin, otelemeSayisi;
	long int os;

	while (true)
	{

		cout << sifreMetniGir;
		getline(cin, sifrelenecekMetin);
		if (sifrelenecekMetin == "0")
			break;

		cout << otelemeSayisiGir;
		getline(cin, otelemeSayisi);

		try
		{
			os = stoi(otelemeSayisi);
		}
		catch (const exception &e)
		{
			cout << hata1;
			break;
		}

		if (os == 0)
			break;

		metniSifrele(sifrelenecekMetin, os);
	}
}
void cozulecekMetniAl()
{
	//kullanıcıdan girdileri alacağımız değişkenler

	string cozulecekMetin, otelemeSayisi;
	long int os;

	while (true)
	{
		cout << cozulecekMetniGir;
		getline(cin, cozulecekMetin);
		if (cozulecekMetin == "0")
			break;

		cout << otelemeSayisiGir;
		getline(cin, otelemeSayisi);

		try
		{
			os = stoi(otelemeSayisi);
		}
		catch (const exception &e)
		{
			cout << hata1;
			break;
		}

		if (os == 0)
			break;

		metniCoz(cozulecekMetin, os);
	}
}

void menuyuGoster()
{
	string secim;	//kullanıcının seçimi

	//menüyü döngü içine alıyoruz(0 menüye dönmek için,3 ise çıkmak için kullanılacaktır)
	while (true)
	{	ayrac(menu.length());
		cout << menu;
		getline(cin, secim);

		if (secim == "1")
		{
			sifrelenecekMetniAl();
		}
		else if (secim == "2")
		{
			cozulecekMetniAl();
		}
		else if (secim == "3")
			break;

		else
			cout << hata2;
	}
}
int main()
{
	mesajlariYukle();	//mesajları oluşturur
	tabloyuYukle();	//tabloyu oluşturur
	menuyuGoster();	//menüyü gösterir

	return 0;
}
