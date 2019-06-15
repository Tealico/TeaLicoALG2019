#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//percaktimi i struktures se pemes binare
typedef struct peme{
       string fjala;
       struct peme *majtas;
       struct peme *djathtas;
       struct peme *prind;
} peme;

//funksioni i meposhtem krijon nje kulm per nje fjale te dhene
peme * krijoKulm(string fjala){
	peme * p = new peme;
	p->fjala = fjala;
	p->majtas = NULL;
	p->djathtas = NULL;
	p->prind = NULL;
	return p;
}

//funksioni ben kthimin ne numer te plote te fjales
//duke perdorur nje algoritem qe kthen cdo karakter ne numer 
//te plote dhe ben shumen pas cdo iteracioni e shumezon me 10
int ktheInteger(string fjala){
	int s = 0;
	for(int i=0;i<fjala.length();i++){
		s = s*10 + fjala.at(i);
	}
	return s;
}

//funksioni shton kulme ne nje peme binar, 
//p - rrenja e pemes, z - kulmi qe do te shtohet
peme * shtoNePeme(peme *p, peme *z){
	//perdorim 2 shenjuesa ndihmes njeri shenjon NULL dhe tjetri ne rrenjen e pemes p
	peme * y = NULL;
	peme * x = p;
	int fjalaRe = ktheInteger(z->fjala); //bejme kthimin e fjales ne numer te plote
	
	//per sa kohe qe nuk jemi ne fund te pemes 
	while(x != NULL){
		y = x; //y shenjon tek kulmi x qe fillimisht eshte rrenja e pemes
		
		//bejme kthimin e fjales qe ndodhtet tek kulmi x ne numer te plote
		int xFjala = ktheInteger(x->fjala);		
		
        //nqs vlera e fjales qe duam te shtojme eshte me e vogel se vlera e fjales se gjetur
        //levizim shenjuesin majtas, nqs eshte me e madhe e levizim shenjuesin djathtas
        //nqs eshte e barabarte dmth kemi gjetur te njejten fjale dhe nuk e shtojme ne peme
        //por kthejme pemen pa ndryshuar asgje, kjo shmang perseritjen e fjaleve
        if(fjalaRe < xFjala)
			x = x->majtas;
 	 	else if(fjalaRe > xFjala)
			x = x->djathtas;
 		else 
			return p;
 	}
 	
	//nqs nuk eshte gjetur fjala atehere prindi i fjales qe duam te shtojme behet sa kulmi i fundit qe 
	//kemi pasi kemi bredhur pemen
	z->prind = y;
	
	//y eshte NULL nqs pema ka qen bosh dhe rrenja e pemes behet sa z
	if(y==NULL){
		p = z;
	}
	
	//nqs y nuk ka qen NULL atehere
	else{
		//kthejme vleren e fjales ne kulmin e fundit ne numer te plote
		int yFjala = ktheInteger(y->fjala);
		
 		// nqs vlera e fjales qe duam te shtojme eshte me e vogel se vlera e kulmit ku duam  ta
 		//shtojme, fjalen e shtojme majtas dhe nqs eshte me e madhe se vlera e kulmit ku duam ta  	
		//shtojme, fjalen e shtojme djathtas 
 		if (fjalaRe < yFjala)
			y->majtas = z;
 		else if(fjalaRe > yFjala)
 	 		y->djathtas = z;
	}
	
	//kthejme pemen me kulmin e shtuar
	return p;
}

//funksioni kthen numrin e kulmeve te pemes
int nrKulme(peme * p){
 	if(p == NULL) 
		return 0;
 	else if(p->majtas == NULL && p->djathtas == NULL) 
		return 1;
 	else  
		return 1 + nrKulme(p->majtas) + nrKulme(p->djathtas);
}

//funksioni afishon pemen sipas bredhjes pararendore
//ku trajtohet rrenja, me pas nenpema e majte 
//dhe nenpema e djathte
void afishoPeme(peme *p) { 
	if(p != NULL) { 
		cout << p->fjala << endl; 
		afishoPeme(p->majtas); 
		afishoPeme(p->djathtas); 
	} 
} 

int main(){
	//deklarojm nje objekt te klases ifstream dhe bejme lidhjen me skedarin
 	ifstream in;
 	in.open("100Fjale.txt");
 	//deklarojme nje strukture te tipit peme dhe e inicializojme ate me NULL
 	peme * p = NULL;
 	if(in.is_open()){
 		while (!in.eof()) {
 			//bejme leximin per cdo fjale
 			string fjale;
 			in>>fjale;
 			//shtojme ne pemen p, nje kulm te krijuar nga funksioni krijoKulm()
 			//duke vendosur si parameter fjalen e lexuar
 			p = shtoNePeme(p,krijoKulm(fjale));
 		}
 		//afishojme pemen dhe numrin e fjaleve te fjalorit
 		afishoPeme(p);
 		cout<<endl<<"Numri i fjaleve te fjalorit eshte: "<<nrKulme(p)<<endl;
 	}
 	else{
 		cout<<"Gabim ne hapjen e skedarit";
 	}
 	return 0;
}

