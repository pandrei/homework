/*
 * Tema 1 EGC - Fotbal static
 * Necula Roxana - Valentina 332CA
 */

#include "WorldDrawer2d.h"
#include <stdlib.h>
#include <time.h>
bool WorldDrawer2d::animation=true;

//used global vars
CoordinateSystem2d *cs1, *cs2,*cs3, *cs4, *cs5;
Object2d *teren_w, *teren_n, *teren_e, *teren_s, *poarta_sus, *poarta_jos;
Object2d *minge, *schimbare;
Object2d *om10, *om11, *om12, *om13, *om14, *om15;
Object2d *om20, *om21, *om22, *om23, *om24, *om25;
Object2d *sc1_1, *sc2_1, *sc3_1;
Object2d *sc1_2, *sc2_2, *sc3_2;
Object2d *poarta1, *poarta2, *linie;
int jucator_random, scor1 = 0, scor2 = 0, e[12], it = 150;
float axa_x[12], axa_y[12], a, b, ai, bi, trX, trY;
bool start = true, flag_scor1 = false, flag_scor2 = false;
bool flag_minge = false;

void WorldDrawer2d::init(){
	//creeaza 4 sistem de coordonate client
	cs1 = new CoordinateSystem2d();
	cs2 = new CoordinateSystem2d();
	cs3 = new CoordinateSystem2d();
	cs4 = new CoordinateSystem2d();
	cs5 = new CoordinateSystem2d();
	
	cs_used.push_back(cs4);
	cs_used.push_back(cs3);
	cs_used.push_back(cs5);
	cs_used.push_back(cs2);
	cs_used.push_back(cs1);	
	
	//poarta de sus
	std::vector<Point2d> points_poarta_sus;
	std::vector<int> topology_poarta;
	points_poarta_sus.push_back(Point2d(-5, 15));
	points_poarta_sus.push_back(Point2d(5, 15));
	points_poarta_sus.push_back(Point2d(-5, 19.5));
	points_poarta_sus.push_back(Point2d(5, 19.5));
	topology_poarta.push_back(0);
	topology_poarta.push_back(1);
	topology_poarta.push_back(2);
	topology_poarta.push_back(2);
	topology_poarta.push_back(1);
	topology_poarta.push_back(3);
	poarta_sus = new Object2d(points_poarta_sus, topology_poarta);
	poarta_sus->setcolor(0.75f, 0.75f, 0.75f);
	cs1->objectAdd(poarta_sus);
	
	//poarta de jos
	std::vector<Point2d> points_poarta_jos;
	points_poarta_jos.push_back(Point2d(-5, -19.5));
	points_poarta_jos.push_back(Point2d(5, -19.5));
	points_poarta_jos.push_back(Point2d(-5, -15));
	points_poarta_jos.push_back(Point2d(5, -15));
	poarta_jos = new Object2d(points_poarta_jos, topology_poarta);
	poarta_jos->setcolor(0.75f, 0.75f, 0.75f);
	cs1->objectAdd(poarta_jos);

	//margine poarta sus
	std::vector<Point2d> points_poarta1;
	points_poarta1.push_back(Point2d(-5.3f, 15));
	points_poarta1.push_back(Point2d(-5.3f, 19.8f));
	points_poarta1.push_back(Point2d(5.3f, 15));
	points_poarta1.push_back(Point2d(5.3f, 19.8f));
	std::vector<int> topology_teren;
	topology_teren.push_back(0);
	topology_teren.push_back(1);
	topology_teren.push_back(2);
	topology_teren.push_back(2);
	topology_teren.push_back(1);
	topology_teren.push_back(3);
	poarta1 = new Object2d(points_poarta1, topology_teren);
	poarta1->setcolor(1, 1, 1);
	cs1->objectAdd(poarta1);

	//margine poarta jos
	std::vector<Point2d> points_poarta2;
	points_poarta2.push_back(Point2d(-5.3f, -19.8f));
	points_poarta2.push_back(Point2d(-5.3f, -15));
	points_poarta2.push_back(Point2d(5.3f, -19.8f));
	points_poarta2.push_back(Point2d(5.3f, -15));
	poarta2 = new Object2d(points_poarta2, topology_teren);
	poarta2->setcolor(1, 1, 1);
	cs1->objectAdd(poarta2);

	/*
	 * Fiecare margine a terenului este compusa din dreptunghiuri, iar acestea
	 * se compun fiecare din 2 triunghiuri.
	 */
	//teren west (marginea stanga)
	std::vector<Point2d> points_teren_w;
	points_teren_w.push_back(Point2d(-15, -15));
	points_teren_w.push_back(Point2d(-15, 15));
	points_teren_w.push_back(Point2d(-14.5f, -15));
	points_teren_w.push_back(Point2d(-14.5f, 15));

	teren_w = new Object2d(points_teren_w, topology_teren);
	teren_w->setcolor(0.59f, 0.41f, 0.31f);
	cs1->objectAdd(teren_w);

	//teren north (marginea sus)
	std::vector<Point2d> points_teren_n;
	points_teren_n.push_back(Point2d(15, 15));
	points_teren_n.push_back(Point2d(-15, 15));
	points_teren_n.push_back(Point2d(15, 15.5f));
	points_teren_n.push_back(Point2d(-15, 15.5f));
	teren_n = new Object2d(points_teren_n, topology_teren);
	teren_n->setcolor(0.59f, 0.41f, 0.31f);
	cs1->objectAdd(teren_n);

	//teren east (margine dreapta)
	std::vector<Point2d> points_teren_e;
	points_teren_e.push_back(Point2d(15, -15));
	points_teren_e.push_back(Point2d(15, 15));
	points_teren_e.push_back(Point2d(14.5f, -15));
	points_teren_e.push_back(Point2d(14.5f, 15));
	teren_e = new Object2d(points_teren_e, topology_teren);
	teren_e->setcolor(0.59f, 0.41f, 0.31f);
	cs1->objectAdd(teren_e);

	//teren south (margine jos)
	std::vector<Point2d> points_teren_s;
	points_teren_s.push_back(Point2d(-15, -15.5f));
	points_teren_s.push_back(Point2d(15, -15.5f));
	points_teren_s.push_back(Point2d(-15, -15));
	points_teren_s.push_back(Point2d(15, -15));
	teren_s = new Object2d(points_teren_s, topology_teren);
	teren_s->setcolor(0.59f, 0.41f, 0.31f);
	cs1->objectAdd(teren_s);

	//linie mijloc
	std::vector<Point2d> points_linie;
	points_linie.push_back(Point2d(-14.5f, -0.1f));
	points_linie.push_back(Point2d(-14.5f, 0.1f));
	points_linie.push_back(Point2d(14.5f, -0.1f));
	points_linie.push_back(Point2d(14.5f, 0.1f));
	linie = new Object2d(points_linie, topology_teren);
	linie->setcolor(1, 1, 1);
	cs1->objectAdd(linie);

	//mingea
	/*
	 * Am intuit coordonatele triunghiurilor din care este alcatuit cercul
	 * (cerc construit asemanator celui din cerinta).
	 */
	std::vector<Point2d> points_minge1;
	std::vector<int> topology_minge1;
	points_minge1.push_back(Point2d(0, 0));
	points_minge1.push_back(Point2d(0, 0.48f));
	points_minge1.push_back(Point2d(0.15f, 0.43f));
	points_minge1.push_back(Point2d(0.38f, 0.24f));
	points_minge1.push_back(Point2d(0.48f, 0));
	points_minge1.push_back(Point2d(0.38f, -0.24f));
	points_minge1.push_back(Point2d(0.15f, -0.43f));
	points_minge1.push_back(Point2d(0, -0.48f));
	points_minge1.push_back(Point2d(-0.15f, -0.43f));
	points_minge1.push_back(Point2d(-0.38f, -0.24f));
	points_minge1.push_back(Point2d(-0.48f, 0));
	points_minge1.push_back(Point2d(-0.38f, 0.24f));
	points_minge1.push_back(Point2d(-0.15f, 0.43f));
	topology_minge1.push_back(0);
	topology_minge1.push_back(1);
	topology_minge1.push_back(2);
	topology_minge1.push_back(2);
	topology_minge1.push_back(0);
	topology_minge1.push_back(3);
	topology_minge1.push_back(3);
	topology_minge1.push_back(0);
	topology_minge1.push_back(4);
	topology_minge1.push_back(4);
	topology_minge1.push_back(0);
	topology_minge1.push_back(5);
	topology_minge1.push_back(5);
	topology_minge1.push_back(0);
	topology_minge1.push_back(6);
	topology_minge1.push_back(6);
	topology_minge1.push_back(0);
	topology_minge1.push_back(7);
	topology_minge1.push_back(7);
	topology_minge1.push_back(0);
	topology_minge1.push_back(8);
	topology_minge1.push_back(8);
	topology_minge1.push_back(0);
	topology_minge1.push_back(9);
	topology_minge1.push_back(9);
	topology_minge1.push_back(0);
	topology_minge1.push_back(10);
	topology_minge1.push_back(10);
	topology_minge1.push_back(0);
	topology_minge1.push_back(11);
	topology_minge1.push_back(11);
	topology_minge1.push_back(0);
	topology_minge1.push_back(12);
	topology_minge1.push_back(12);
	topology_minge1.push_back(0);
	topology_minge1.push_back(1);
	minge = new Object2d(points_minge1, topology_minge1);
	minge->setcolor(0, 0, 0);
	cs5->objectAdd(minge);

	/* topologie oameni
	 * Jucatorii i-am obtinut in acelasi mod cu mingea,
	 * dar cu alte puncte, pentru a mari dimensiunea cercului corespunzator jucatorilor.
	 */
	std::vector<Point2d> points_players;
	std::vector<int> topology_players;
	points_players.push_back(Point2d(0, 0));
	points_players.push_back(Point2d(0, 0.8f));
	points_players.push_back(Point2d(0.26f, 0.72f));
	points_players.push_back(Point2d(0.64f, 0.42f));
	points_players.push_back(Point2d(0.8f, 0));
	points_players.push_back(Point2d(0.64f, -0.42f));
	points_players.push_back(Point2d(0.26f, -0.72f));
	points_players.push_back(Point2d(0, -0.8f));
	points_players.push_back(Point2d(-0.26f, -0.72f));
	points_players.push_back(Point2d(-0.64f, -0.42f));
	points_players.push_back(Point2d(-0.8f, 0));
	points_players.push_back(Point2d(-0.64f, 0.42f));
	points_players.push_back(Point2d(-0.26f, 0.72f));
	topology_players.push_back(0);
	topology_players.push_back(1);
	topology_players.push_back(2);
	topology_players.push_back(2);
	topology_players.push_back(0);
	topology_players.push_back(3);
	topology_players.push_back(3);
	topology_players.push_back(0);
	topology_players.push_back(4);
	topology_players.push_back(4);
	topology_players.push_back(0);
	topology_players.push_back(5);
	topology_players.push_back(5);
	topology_players.push_back(0);
	topology_players.push_back(6);
	topology_players.push_back(6);
	topology_players.push_back(0);
	topology_players.push_back(7);
	topology_players.push_back(7);
	topology_players.push_back(0);
	topology_players.push_back(8);
	topology_players.push_back(8);
	topology_players.push_back(0);
	topology_players.push_back(9);
	topology_players.push_back(9);
	topology_players.push_back(0);
	topology_players.push_back(10);
	topology_players.push_back(10);
	topology_players.push_back(0);
	topology_players.push_back(11);
	topology_players.push_back(11);
	topology_players.push_back(0);
	topology_players.push_back(12);
	topology_players.push_back(12);
	topology_players.push_back(0);
	topology_players.push_back(1);

	//pozitionarea jucatorilor
	//echipa1 albastra cu cei 6 jucatori
	om10 = new Object2d(points_players, topology_players);
	om10->setcolor(0, 0, 1);
	om10->translate(3, 4);
	cs2->objectAdd(om10);

	om11 = new Object2d(points_players, topology_players);
	om11->setcolor(0, 0, 1);
	om11->translate(-7, 5);
	cs2->objectAdd(om11);

	om12 = new Object2d(points_players, topology_players);
	om12->setcolor(0, 0, 1);
	om12->translate(11, 12);
	cs2->objectAdd(om12);
	
	om13 = new Object2d(points_players, topology_players);
	om13->setcolor(0, 0, 1);
	om13->translate(10, -6);
	cs2->objectAdd(om13);

	om14 = new Object2d(points_players, topology_players);
	om14->setcolor(0, 0, 1);
	om14->translate(0, 14);
	cs2->objectAdd(om14);

	om15 = new Object2d(points_players, topology_players);
	om15->setcolor(0, 0, 1);
	om15->translate(-6, -10);
	cs2->objectAdd(om15);

	//echipa2 galbena cu cei 6 jucatori
	om20 = new Object2d(points_players, topology_players);
	om20->setcolor(1, 1, 0);
	om20->translate(-13, -6);
	cs2->objectAdd(om20);

	om21 = new Object2d(points_players, topology_players);
	om21->setcolor(1, 1, 0);
	om21->translate(7, 8);
	cs2->objectAdd(om21);

	om22 = new Object2d(points_players, topology_players);
	om22->setcolor(1, 1, 0);
	om22->translate(9, -12);
	cs2->objectAdd(om22);

	om23 = new Object2d(points_players, topology_players);
	om23->setcolor(1, 1, 0);
	om23->translate(-3, -4);
	cs2->objectAdd(om23);

	om24 = new Object2d(points_players, topology_players);
	om24->setcolor(1, 1, 0);
	om24->translate(0, -14);
	cs2->objectAdd(om24);

	om25 = new Object2d(points_players, topology_players);
	om25->setcolor(1, 1, 0);
	om25->translate(-12, 7);
	cs2->objectAdd(om25);

	//scor
	std::vector<Point2d> points_scor1_1;
	std::vector<int> topology_scor;
	points_scor1_1.push_back(Point2d(16, 3));
	points_scor1_1.push_back(Point2d(16, 9));
	points_scor1_1.push_back(Point2d(16.5f, 9));
	points_scor1_1.push_back(Point2d(16.5f, 3));
	topology_scor.push_back(0);
	topology_scor.push_back(1);
	topology_scor.push_back(2);
	topology_scor.push_back(0);
	topology_scor.push_back(2);
	topology_scor.push_back(3);
	sc1_1 = new Object2d(points_scor1_1, topology_scor);
	sc1_1->setcolor(0, 0, 1);

	std::vector<Point2d> points_scor2_1;
	points_scor2_1.push_back(Point2d(16.7f, 3));
	points_scor2_1.push_back(Point2d(16.7f, 9));
	points_scor2_1.push_back(Point2d(17.2f, 9));
	points_scor2_1.push_back(Point2d(17.2f, 3));
	sc2_1 = new Object2d(points_scor2_1, topology_scor);
	sc2_1->setcolor(0, 0, 1);

	std::vector<Point2d> points_scor3_1;
	points_scor3_1.push_back(Point2d(17.4f, 3));
	points_scor3_1.push_back(Point2d(17.4f, 9));
	points_scor3_1.push_back(Point2d(17.9f, 9));
	points_scor3_1.push_back(Point2d(17.9f, 3));
	sc3_1 = new Object2d(points_scor3_1, topology_scor);
	sc3_1->setcolor(0, 0, 1);

	std::vector<Point2d> points_scor1_2;
	points_scor1_2.push_back(Point2d(16, -3));
	points_scor1_2.push_back(Point2d(16, -9));
	points_scor1_2.push_back(Point2d(16.5f, -9));
	points_scor1_2.push_back(Point2d(16.5f, -3));
	sc1_2 = new Object2d(points_scor1_2, topology_scor);
	sc1_2->setcolor(1, 1, 0);

	std::vector<Point2d> points_scor2_2;
	points_scor2_2.push_back(Point2d(16.7f, -3));
	points_scor2_2.push_back(Point2d(16.7f, -9));
	points_scor2_2.push_back(Point2d(17.2f, -9));
	points_scor2_2.push_back(Point2d(17.2f, -3));
	sc2_2 = new Object2d(points_scor2_2, topology_scor);
	sc2_2->setcolor(1, 1, 0);

	std::vector<Point2d> points_scor3_2;
	points_scor3_2.push_back(Point2d(17.4f, -3));
	points_scor3_2.push_back(Point2d(17.4f, -9));
	points_scor3_2.push_back(Point2d(17.9f, -9));
	points_scor3_2.push_back(Point2d(17.9f, -3));
	sc3_2 = new Object2d(points_scor3_2, topology_scor);
	sc3_2->setcolor(1, 1, 0);

	//schimbare culoare ecran
	std::vector<Point2d> points_schimbare;
	points_schimbare.push_back(Point2d(-50, -20));
	points_schimbare.push_back(Point2d(-50, 20));
	points_schimbare.push_back(Point2d(50, 20));
	points_schimbare.push_back(Point2d(50, -20));
	schimbare = new Object2d(points_schimbare, topology_scor);
	schimbare->setcolor(0.3f, 0.7f, 0.6f);

	/*
	 * axa_x = vectorul cu pozitiile jucatorilor pe axa x, iar axa_y = pe axa y
	 * axa_x[0...5] apartine echipei 1 iar axa_x[6...11] apartine echipei 2
	 */
	axa_x[0] = 3;	axa_y[0] = 4;
	axa_x[1] = -7;	axa_y[1] = 5;
	axa_x[2] = 11;	axa_y[2] = 12;
	axa_x[3] = 10;	axa_y[3] = -6;
	axa_x[4] = 0;	axa_y[4] = 14;
	axa_x[5] = -6;	axa_y[5] = -10;
	//
	axa_x[6] = -13;	axa_y[6] = -6;
	axa_x[7] = 7;	axa_y[7] = 8;
	axa_x[8] = 9;	axa_y[8] = -12;
	axa_x[9] = -3;	axa_y[9] = -4;
	axa_x[10] = 0;	axa_y[10] = -14;
	axa_x[11] = -12;axa_y[11] = 7;

	/*
	 * e[i] este vectorul care tine evidenta jucatorilor ce detin mingea
	 * e[i] = 1 daca jucatorul i are mingea si 0 altfel
	 */
	for (int i = 0; i < 12; i++)
		e[i] = 0;
 
	trX = 0.1f;
	trY = 0.1f;

}
void WorldDrawer2d::onIdle(){	//per frame
	static int iteration=1;
	static bool o1dir=true;
	static bool o2dir=true;
	static bool o3dir=true;
	static bool o3dir2=true;

	if(animation){
		iteration++;
	}
	
	if (start == true)
	{
		minge->translate(-minge->axiscenter.x, -minge->axiscenter.y);
		start = false;
		//dau mingea unui jucator aleator din oricare echipa
		srand(time(NULL));
		jucator_random = rand() % 12;
		
		if (jucator_random == 4)
			jucator_random = 5;
		if (jucator_random == 10)
			jucator_random = 11;
		
		/*
		 * Marchez jucatorul care detine mingea din vectorul e[i]
		 * Vectorii sunt alcatuiti din 12 elemente corespunzatoare fiecarui jucator
		 * Primii 6 reprezinta prima echipa, ultimii 6 reprezinta a doua echipa
		 */
		for (int i = 0; i < 12; i++)
			e[i] = 0;
		e[jucator_random] = 1;
		minge->translate(axa_x[jucator_random] + 0.7f, axa_y[jucator_random] + 0.7f);
	}

	//coordonatele mingii
	minge->aflapctx();
	a = minge->aflax;
	b = minge->aflay;

	if ((a <= -14.5 || a >= 14.5) && !(a >= -5 && a <= 5 && b >= 14.5 && b <= 19.5) 
		&& !(a >= -5 && a <= 5 && b <= -14.5 && b >= -19.5))
			trX = -trX;

	if ((b <= -14.5 || b >= 14.5) && !(a >= -5 && a <= 5 && b >= 14.5 && b <= 19.5) 
		&& !(a >= -5 && a <= 5 && b <= -14.5 && b >= -19.5))
		trY = -trY;

	if (flag_minge == true)
		minge->translate(trX, trY);
	/*
	 * Oprirea mingii daca se afla in raza unui jucator si marcarea jucatorului
	 * care detine mingea in vectorul e[i]
	 */
	for (int i = 0; i < 12; i++)
		if ((e[i] != 1) && (sqrt((a - axa_x[i]) * (a - axa_x[i]) + (b - axa_y[i]) * (b - axa_y[i])) <= 1.5))
		{
			e[i] = 1;
			for (int j = 0; j < 12; j++)
				if (i != j)
					e[j] = 0;
				
			flag_minge = false;
		}

	//gol in poarta echipei albastre
	if (a >= -5 && a <= 5 && b >= 14.5 && b <= 19.5)
		flag_scor2 = true;

	//gol in poarta echipei galbene
	if (a >= -5 && a <= 5 && b <= -14.5 && b >= -19.5)
		flag_scor1 = true;

	//daca echipa 1 da gol
	if (flag_scor1 == true && scor1 < 2)
	{
		flag_scor1 = false;
		flag_minge = false;
		scor1++;
		for (int i = 0; i < 12; i++)
			e[i] = 0;
		//dau mingea echipei adverse
		srand(time(NULL));
		jucator_random = rand() % 12;

		if (jucator_random < 6)
			jucator_random += 6;

		if (jucator_random == 10)
			jucator_random = 11;
			
		minge->translate(axa_x[jucator_random] - a - 0.7f, axa_y[jucator_random] - b - 0.7f);

		e[jucator_random] = 1;

		//afisez scorul pe ecran
		if (scor1 == 1)
			cs3->objectAdd(sc1_1);
		else
			if (scor1 == 2)
				cs3->objectAdd(sc2_1);
			else
				if (scor1 == 3)
					cs3->objectAdd(sc3_1);
	} else {
		if (scor1 == 2 && flag_scor1 == true)
		{
			scor1++;
			flag_scor1 = false;
			flag_minge = false;
		}
	}

	//daca echipa 2 da gol
	if (flag_scor2 == true && scor2 < 2)
	{
		flag_scor2 = false;
		flag_minge = false;
		scor2++;
		for (int i = 0; i < 12; i++)
			e[i] = 0;
		//dau mingea echipei adverse
		srand(time(NULL));
		jucator_random = rand() % 12;

		if (jucator_random > 5)
			jucator_random -= 6;
			
		if (jucator_random == 4)
			jucator_random = 5;
			
		minge->translate(axa_x[jucator_random] - a - 0.7f, axa_y[jucator_random] - b - 0.7f);
			
		e[jucator_random] = 1;

		//afisez scorul pe ecran
		if (scor2 == 1)
			cs3->objectAdd(sc1_2);
		else
			if (scor2 == 2)
				cs3->objectAdd(sc2_2);
			else
				if (scor2 == 3)
					cs3->objectAdd(sc3_2);
			
	} else {
		if (scor2 == 2 && flag_scor2 == true)
		{
			scor2++;
			flag_scor2 = false;
			flag_minge = false;
		}
	}

	//terminarea jocului
	if (scor1 == 3 || scor2 == 3)
	{
		if (it > 0)
		{
			cs4->objectAdd(schimbare);
			it--;
		} else {
				flag_minge = false;
				cs4->objects.clear();
				//resetare flaguri
				flag_scor1 = false, flag_scor2 = false;
				scor1 = 0, scor2 = 0;
				for (int i = 0; i < 12; i++)
					e[i] = 0;
				jucator_random = 1;

				it = 150;

				cs3->objects.clear();
				start = true;
		}
	}
}

void WorldDrawer2d::onKey(unsigned char key){
	switch(key){
		case KEY_UP:
			flag_minge = true;
			for (int i = 0; i < 12; i++)
				if (e[i] == 1)
				{
					trX = a - axa_x[i];
					trY = b - axa_y[i];
				}
			if (abs(trX) > 0.1 || abs(trY) > 0.1)
			{
				trX = trX / 30;
				trY = trY / 30;
			}
			break;
		case KEY_DOWN:
			flag_minge = true;
			for (int i = 0; i < 12; i++)
				if (e[i] == 1)
				{
					trX = a - axa_x[i];
					trY = b - axa_y[i];
				}
			if (abs(trX) > 0.1 || abs(trY) > 0.1)
			{
				trX = trX / 30;
				trY = trY / 30;
			}
			break;
		case KEY_LEFT:
			for (int i = 0; i < 12; i++)
				if (e[i] == 1)
					minge->rotateRelativeToPoint(Point2d(axa_x[i], axa_y[i]), 0.1f);
			break;
		case KEY_RIGHT:
			for (int i = 0; i < 12; i++)
				if (e[i] == 1)
				{
					minge->rotateRelativeToPoint(Point2d(axa_x[i], axa_y[i]), -0.1f);
				}
			break;
		case KEY_SPACE:
				animation=!animation;
			break;
		default:
			break;
	}
}

int main(int argc, char** argv){
	WorldDrawer2d wd2d(argc,argv,600,600,200,100,std::string("Tema 1 EGC"));
	wd2d.init();
	wd2d.run();
	return 0;
}