#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//percaktimi i struktures se listes 1-Drejtimore
typedef struct nyje {
	string vlera;
	struct nyje *pas;
}nyje;

//funksioni i meposhtem shton nje element te ri ne liste
nyje *shtoElementFillim (nyje *koka,string fjala){
	nyje *elementRi = new nyje; //krijohet nje element i ri
	elementRi->vlera = fjala; //vlera e elementit te ri behet sa fjala
	elementRi->pas = koka; // pasardhesi i elementit te ri behet sa koka e listes
	koka = elementRi; // elementi shtohet ne fillim te listes, dmth ai behet koka e listes
	return koka; //kthejme koken e listes
}

//funksioni i meposhtem afishon listen duke mar si parameter koken e listes
//afishohet vlera per cdo nyje deri sa te kete mbaruar bredhja
void afishoListe (nyje *koka){
	nyje *tmp = koka;
	while (tmp!=NULL){
		cout<<tmp->vlera<<endl;
		tmp=tmp->pas;
	}
}

//funksioni i meposhtem kontrollon nese nje fjal e dhene ndodhet ne liste duke bredhur
//te gjithe listen, nese e gjen kthen vleren booleane true, ne rast te kundert
//shkon deri ne fund te listes dhe kthen false
bool *ndodhetNeList(nyje *koka,string fjala){
	nyje *tmp = koka;
	while(tmp!=NULL){
		if(fjala.compare(tmp->vlera) == 0){
			return true;
		}
		tmp=tmp->pas;
	}
	return false;
}

int main() {
	//deklarojm nje objekt te klases ifstream dhe bejme lidhjen me skedarin
	ifstream in;
	in.open("100Fjale.txt");
	//deklarojm nje strukture te tipit nyje dhe e inicializojme ate me NULL
	nyje *lista = NULL;
	if(in.is_open()){
		//deklarojme nje variabel per te numeruar numrin e fjaleve ne fjalor
		int nrFjaleshNeFjalor = 0;
		while(!in.eof()){
			//bejme leximin per cdo fjale
			string fjala;
			in>>fjala;
			//kontrollojme nese fjala ndodhet ne liste
			//nese nuk ndodhet e shtojme ne liste nese jo vazhdojme me fjalen tjeter
			if(ndodhetNeList(lista,fjala) == false){
				//shtojme fjalen ne liste dhe risim me 1 numrin e fjaleve te gjetura
				lista = shtoElementFillim(lista,fjala);
				nrFjaleshNeFjalor++; 
			}
		}
		//afishojme listen dhe numrin e fjaleve te saj
		afishoListe(lista);
		cout<<endl<<"Numri i fjaleve te ndryshme te fjalorit eshte: "<<nrFjaleshNeFjalor<<endl;
	}
	else{  
        cout<<"Gabim ne hapjen e skedarit";   
 	}
	return 0;
}

