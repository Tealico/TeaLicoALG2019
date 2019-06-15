#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//percaktimi i struktures se listes 1-Drejtimore
typedef struct nyje {
	string vlera;
	struct nyje *pas;
}nyje;

//funksioni i meposhtem shton nje element te ri ne fillim te nje liste
nyje *shtoElement (nyje *koka,string fjala){
	nyje *elementRi = new nyje; //krijohet nje element i ri
	elementRi->vlera = fjala; //vlera e elementit te ri behet sa fjala
	elementRi->pas = koka; // pasardhesi i elementit te ri behet sa koka e listes
	koka = elementRi; // elementi shtohet ne fillim te listes, d.m.th. ai behet koka e listes	
 	return koka; //kthejme koken e listes
}

//funksioni i meposhtem kontrollon nese nje fjal e dhene ndodhet ne liste duke bredhur
//te gjithe listen, nese e gjen kthen true, ne rast te kundert
//jemi ne fund te listes dhe do te kthehet false
bool ndodhetNeList(nyje * l,string fjala){
	nyje * tmp = l;
	while(tmp!=NULL){
		if(tmp->vlera==fjala){
			return true;
		}
		tmp=tmp->pas;
	}
	return false;
}

//funksioni llogarit vleren e funksionit hash per nje fjale te dhene,
// duke perdorur funksionin h(k)=k mod N
//konvertimi i fjales ne numer na sherben per te llogaritur vleren hash
int llogaritVlerenHash(string fjala,int N){
	int s=0;
	for(int i=0;i<fjala.length();i++){
		s = s + fjala.at(i);
	}
	return s%N;
}

//funksioni afishon listat e tabeles hash duke bredhur
//secilen prej tyre deri ne fund
void afishoListat (nyje * T[],int nrEl){
	for(int i=0;i<nrEl;i++){
		nyje *tmp = T[i];
		cout<<"Elementet ne pozicionin "<<i<<" jane: "<<endl;
		while(tmp!=NULL){
			cout<<tmp->vlera<<endl;
			tmp=tmp->pas;
		}
		cout<<endl;
	}
}

int main(){ 
	ifstream in; //deklarojm nje objekt te klases ifstream
	in.open("100Fjale.txt"); // dhe bejme lidhjen me skedarin
	const int nrEl=10; 
	nyje *tabelaHash[nrEl]; //deklarojme nje tabele te tipit nyje
	//inicializojme secilen nyje te tabeles me vleren NULL
 	for(int i=0;i<nrEl;i++){
 		tabelaHash[i]=NULL;	
 	}
 	if(in.is_open()){
 		int nrFjaleshNeFjalor = 0; //deklarojme nje variabel per te numeruar numrin e fjaleve 
 		while(!in.eof()){
 			string fjala;
 			in>>fjala; //bejme leximin per cdo fjale
 			int hash = llogaritVlerenHash(fjala,nrEl); //llogarisim vleren hash per fjalen e lexuar
 			//kontrollojme nese fjala ndodhet ne listen me koke te vendosur
 			//ne indeksin hash te tabeles
 			if(ndodhetNeList(tabelaHash[hash],fjala)==false){
 				//shtojme fjalen ne listen me indeks hash te tabeles 
 				//dhe rrisim me 1 numrin e fjaleve te gjetura
 				tabelaHash[hash]=shtoElement(tabelaHash[hash],fjala);
 				nrFjaleshNeFjalor++;
 			}
 		}
 		//afishojme listat per cdo element te tabeles dhe numrin e fjaleve te fjalorit
 		afishoListat(tabelaHash,nrEl);
 		cout<<endl<<"Numri i fjaleve te fjalorit eshte: "<<nrFjaleshNeFjalor<<endl;
 	}
 	else{
 		cout<<"Gabim ne hapjen e skedarit";
 	} return 0;
}

