/*
 * Tema 2 EGC - Rubik
 * Necula Roxana - Valentina 332CA
 */

#include "WorldDrawer3d.h"
bool WorldDrawer3d::animation=true;
bool rot = false;
int dr = 0, sus = 0, lateral_dr = 0;
CoordinateSystem3d *cs1, *cs2, *cs3;
Object3d* vector[27], *rez, *minicub;
std::vector<Object3d*> cub_scor;

int mat[3][3][3], matx[3][3][3], vprim[27], nr, count, diferit[24], it = 100, scor = 0;

//24 vectori ce reprezinta stari finale, de castig ale cubului
int initial[27] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
int ur2lr[27] = {0,3,6,9,12,15,18,21,24,1,4,7,10,13,16,19,22,25,2,5,8,11,14,17,20,23,26};
int u2r3lr3[27] = {0,9,18,1,10,19,2,11,20,3,12,21,4,13,22,5,14,23,6,15,24,7,16,25,8,17,26};

int u1[27] = {6, 3, 0, 7, 4, 1, 8, 5, 2, 15, 12, 9, 16, 13, 10, 17, 14, 11, 24, 21, 18, 25, 22, 19, 26, 23, 20};
int lr3[27] = {6, 7, 8, 15, 16, 17, 24, 25, 26, 3, 4, 5, 12, 13, 14, 21, 22, 23, 0, 1, 2, 9, 10, 11, 18, 19, 20};
int u2r3[27] = {6,15,24,3,12,21,0,9,18,7,16,25,4,13,22,1,10,19,8,17,26,5,14,23,2,11,20};

int u2[27] = {8, 7, 6, 5, 4, 3, 2, 1, 0, 17, 16, 15, 14, 13, 12, 11, 10, 9, 26, 25, 24, 23, 22, 21, 20, 19, 18};   
int r3u[27] = {8,5,2,17,14,11,26,23,20,7,4,1,16,13,10,25,22,19,6,3,0,15,12,9,24,21,18};
int dl[27] = {8,17,26,7,16,25,6,15,24,5,14,23,4,13,22,3,12,21,2,11,20,1,10,19,0,9,18};

int r2[27] = {20, 19, 18, 23, 22, 21, 26, 25, 24, 11, 10, 9, 14, 13, 12, 17, 16, 15, 2, 1, 0, 5, 4, 3, 8, 7, 6};
int rlr[27] = {20,11,2,19,10,1,18,9,0,23,14,5,22,13,4,21,12,3,26,17,8,25,16,7,24,15,6};
int r3u3[27] = {20,23,26,11,14,17,2,5,8,19,22,25,10,13,16,1,4,7,18,21,24,9,12,15,0,3,6};

int r3[27] = {2, 11, 20, 5, 14, 23, 8, 17, 26, 1, 10, 19, 4, 13, 22, 7, 16, 25, 0, 9, 18, 3, 12, 21, 6, 15, 24};
int r2lr[27] = {2,1,0,11,10,9,20,19,18,5,4,3,14,13,12,23,22,21,8,7,6,17,16,15,26,25,24};
int u3[27] = {2, 5, 8, 1, 4, 7, 0, 3, 6, 11, 14, 17, 10, 13, 16, 9, 12, 15, 20, 23, 26, 19, 22, 25, 18, 21, 24};

int lr1[27] = {18, 19, 20, 9, 10, 11, 0, 1, 2, 21, 22, 23, 12, 13, 14, 3, 4, 5, 24, 25, 26, 15, 16, 17, 6, 7, 8};
int ur2[27] = {18,21,24,19,22,25,20,23,26,9,12,15,10,13,16,11,14,17,0,3,6,1,4,7,2,5,8};
int r1[27] = {18, 9, 0, 21, 12, 3, 24, 15, 6, 19, 10, 1, 22, 13, 4, 25, 16, 7, 20, 11, 2, 23, 14, 5, 26, 17, 8};

int lr2[27] = {24, 25, 26, 21, 22, 23, 18, 19, 20, 15, 16, 17, 12, 13, 14, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};
int ur[27] = {24, 21, 18, 15, 12, 9, 6, 3, 0, 25, 22, 19, 16, 13, 10, 7, 4, 1, 26, 23, 20, 17, 14, 11, 8, 5, 2};
int u2rlr[27] = {24,15,6,25,16,7,26,17,8,21,12,3,22,13,4,23,14,5,18,9,0,19,10,1,20,11,2};

int rlr2[27] = {26,17,8,23,14,5,20,11,2,25,16,7,22,13,4,19,10,1,24,15,6,21,12,3,18,9,0};
int ulr2[27] = {26,23,20,25,22,19,24,21,18,17,14,11,16,13,10,15,12,9,8,5,2,7,4,1,6,3,0};
int u2lr[27] = {26,25,24,17,16,15,8,7,6,23,22,21,14,13,12,5,4,3,20,19,18,11,10,9,2,1,0};


bool rx = false, ry = false, rz = false;
bool mx = false, my = false, mz = false;
bool px = false, py = false, pz = false;
bool stop = false, start = false;
float unghi = 0.0f;
int cnt = 0;

std::vector<Point3d> points;
std::vector<int> topology;
std::vector<Point3d> points_rez;
std::vector<Point3d> points_scor;

void WorldDrawer3d::init(){
	//creeaza 3 sisteme de coordonate client
	cs1 = new CoordinateSystem3d();
	cs2 = new CoordinateSystem3d();
	cs3 = new CoordinateSystem3d();
	cs_used.push_back(cs3);
	cs_used.push_back(cs2);
	cs_used.push_back(cs1);
	
	points.push_back(Point3d(3,3,3));
	points.push_back(Point3d(3,3,-3));
	points.push_back(Point3d(-3,3,-3));
	points.push_back(Point3d(-3,3,3));
	points.push_back(Point3d(3,-3,3));
	points.push_back(Point3d(3,-3,-3));
	points.push_back(Point3d(-3,-3,-3));
	points.push_back(Point3d(-3,-3,3));
	
	topology.push_back(0);topology.push_back(1);topology.push_back(2);	//top
	topology.push_back(2);topology.push_back(3);topology.push_back(0);

	topology.push_back(6);topology.push_back(5);topology.push_back(4);	//bottom
	topology.push_back(7);topology.push_back(4);topology.push_back(6);

	topology.push_back(2);topology.push_back(3);topology.push_back(6);	//left
	topology.push_back(7);topology.push_back(3);topology.push_back(6);

	topology.push_back(0);topology.push_back(1);topology.push_back(5);	//right
	topology.push_back(0);topology.push_back(5);topology.push_back(4);

	topology.push_back(0);topology.push_back(3);topology.push_back(4);	//front
	topology.push_back(7);topology.push_back(3);topology.push_back(4);

	topology.push_back(5);topology.push_back(1);topology.push_back(2);	//back
	topology.push_back(6);topology.push_back(2);topology.push_back(5);

	//crearea cubului mare, format din 27 de cuburi mai mici
	nr = 0;
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for(int z = 0; z < 3; z++)
			{
				vector[nr]= new Object3d(points,topology);
				vector[nr]->translate((float)6*(x - 1), (float)6*(y - 1), (float)6*(z - 1));
				nr++;
			}

	for (int i = 0; i < 27; i++)
		cs1->objectAdd(vector[i]);

	nr = 0;
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for(int z = 0; z < 3; z++)
				mat[x][y][z] = nr++;

	//rez = obiect care va fi afisat doar in modul rezolvare, la apasarea tastei 'r'
	std::vector<Point3d> points_rez;
	points_rez.push_back(Point3d(15,15,-20));
	points_rez.push_back(Point3d(15,15,-20.5f));
	points_rez.push_back(Point3d(10,15,-20.5f));
	points_rez.push_back(Point3d(10,15,-20));
	points_rez.push_back(Point3d(15,5,-20));
	points_rez.push_back(Point3d(15,5,-20.5f));
	points_rez.push_back(Point3d(10,5,-20.5f));
	points_rez.push_back(Point3d(10,5,-20));

	rez = new Object3d(points_rez, topology);

	for (int i = 0; i < 24; i++)
		diferit[i] = 0;

	points_scor.push_back(Point3d(1,1,1));
	points_scor.push_back(Point3d(1,1,-1));
	points_scor.push_back(Point3d(-1,1,-1));
	points_scor.push_back(Point3d(-1,1,1));
	points_scor.push_back(Point3d(1,-1,1));
	points_scor.push_back(Point3d(1,-1,-1));
	points_scor.push_back(Point3d(-1,-1,-1));
	points_scor.push_back(Point3d(-1,-1,1));

}
//functie folosita pentru definirea unui minicub ce reprezinta 1 pct la scor
Object3d *createCube()
{
	Object3d* o;
	o = new Object3d(points_scor, topology);
	return o;
}
void WorldDrawer3d::onIdle(){	//per frame
	static int iteration=1;
	if(animation){
		iteration++;
	}
	
	//vectorul vprim[i] reprezinta pozitia cuburilor din alcatuirea cubului Rubik
	//exemplu vprim = {0, 1, 2, ..., 24, 25} reprezinta pozitia initiala a cubului Rubik
	nr = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				vprim[nr++] = mat[i][j][k];

	//rotirea cubului in functie de axa(rx, ry, rz), sau de semnul unghiului cu care se roteste(mx, my, mz sau px, py, pz)
	//rotirea se face pana in momentul in care cubul s-a rotit cu 90 grade apoi se opreste
	if (rx == true && mx == true)
	{
		if (unghi > -1.5707963267948966192313216916398f)
		{
			unghi = unghi - 0.005f;
			for (int i = 0; i < 27; i++)
				vector[vprim[i]]->rotateXRelativeToPoint(Point3d(0,0,0), -0.005f);
		}
		else {
			rx = false;
			mx = false;
		}
	}

	if (rx == true && px == true)
	{
		if (unghi < 1.5707963267948966192313216916398f)
		{
			unghi = unghi + 0.005f;
			for (int i = 0; i < 27; i++)
				vector[vprim[i]]->rotateXRelativeToPoint(Point3d(0,0,0), 0.005f);
		}
		else {
			rx = false;
			px = false;
		}
	} 

	if (ry == true && px == true)
	{
		if (unghi < 1.5707963267948966192313216916398f)
		{
			unghi = unghi + 0.005f;
			for (int i = 0; i < 27; i++)
				vector[vprim[i]]->rotateYRelativeToPoint(Point3d(0,0,0), 0.005f);
		}
		else {
			ry = false;
			px = false;
		}
	}

	if (ry == true && mx == true)
	{
		if (unghi > -1.5707963267948966192313216916398f)
		{
			unghi = unghi - 0.005f;
			for (int i = 0; i < 27; i++)
				vector[vprim[i]]->rotateYRelativeToPoint(Point3d(0,0,0), -0.005f);
		}
		else {
			ry = false;
			mx = false;
		}
	}

	if (rz == true && mx == true)
	{
		if (unghi > -1.5707963267948966192313216916398f)
		{
			unghi = unghi - 0.005f;
			for (int i = 0; i < 27; i++)
				vector[vprim[i]]->rotateZRelativeToPoint(Point3d(0,0,0), -0.005f);
		}
		else {
			rz = false;
			mx = false;
		}
	}

	if (rz == true && px == true)
	{
		if (unghi < 1.5707963267948966192313216916398f)
		{
			unghi = unghi + 0.005f;
			for (int i = 0; i < 27; i++)
				vector[vprim[i]]->rotateZRelativeToPoint(Point3d(0,0,0), 0.005f);
		}
		else {
			rz = false;
			px = false;
		}
	}

	//verificarea daca avem cubul Rubik intr-o pozitie castigatoare
	//toti cei 24 de vectori reprezinta pozitii castigatoare
	//vectorul diferit[i] este egal cu 0, daca se afla intr-o pozitie castigatoare, 1 altfel
	for (int i = 0; i < 27; i++)
	{
		if (vprim[i] != initial[i])
			diferit[0] = 1;
		if (vprim[i] != u1[i])
			diferit[1] = 1;
		if (vprim[i] != u2[i])
			diferit[2] = 1;
		if (vprim[i] != u3[i])
			diferit[3] = 1;
		if (vprim[i] != r1[i])
			diferit[4] = 1;
		if (vprim[i] != r2[i])
			diferit[5] = 1;
		if (vprim[i] != r3[i])
			diferit[6] = 1;
		if (vprim[i] != lr1[i])
			diferit[7] = 1;
		if (vprim[i] != lr2[i])
			diferit[8] = 1;
		if (vprim[i] != lr3[i])
			diferit[9] = 1;
		if (vprim[i] != ur2lr[i])
			diferit[10] = 1;
		if (vprim[i] != r3u[i])
			diferit[11] = 1;
		if (vprim[i] != rlr[i])
			diferit[12] = 1;
		if (vprim[i] != r2lr[i])
			diferit[13] = 1;
		if (vprim[i] != ur2[i])
			diferit[14] = 1;
		if (vprim[i] != ur[i])
			diferit[15] = 1;
		if (vprim[i] != u2rlr[i])
			diferit[16] = 1;
		if (vprim[i] != rlr2[i])
			diferit[17] = 1;
		if (vprim[i] != ulr2[i])
			diferit[18] = 1;
		if (vprim[i] != u2lr[i])
			diferit[19] = 1;
		if (vprim[i] != r3u3[i])
			diferit[20] = 1;
		if (vprim[i] != u2r3[i])
			diferit[21] = 1;
		if (vprim[i] != u2r3lr3[i])
			diferit[22] = 1;
		if (vprim[i] != dl[i])
			diferit[23] = 1;
	}

	//start desemneaza trecerea din modul de shuffle al cubului, in modul de rezolvare
	if (start == true)
		for (int i = 0; i < 24; i++)
			if (diferit[i] == 0)
			{
				stop = true;
				start = false;
				scor++;
			}
	
	//verificarea daca este pozitie castigatoare, atunci se afiseaza scorul pe ecran
	//astfel ca numarul de minicuburi afisate este egal cu scorul
	if (stop == true)
	{
		cs2->objectRemove(rez);
		cs1->objects.clear();
		if (scor % 8 == 0)
		{
			cnt++;
			scor-=7;
		}

		for (int i = 0; i < scor; i++)
			cub_scor.push_back(createCube());
		
		for (int i = 0; i < scor; i++)
		{			
			cub_scor.at(i)->translate(0, cnt * 4, (i - 1)*4);
			cs3->objectAdd(cub_scor.at(i));
		}
		stop = false;
	}
}

void WorldDrawer3d::onKey(unsigned char key){
	switch(key){
		case KEY_UP:
			unghi = 0.0f;
			rx = true;
			mx = true;

			//la apasarea tastei UP se va roti cubul pe axa X in sus
			//si se reactualizeaza pozitia cuburilor din cubul Rubik
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						int tz;
						if (k == 0)
						{
							tz = 2;
							mat[i][j][k] = matx[i][tz][j];
						} else
							if (k == 2)
							{
								tz = 0;
								mat[i][j][k] = matx[i][tz][j];
							}
							else
								mat[i][j][k] = matx[i][k][j];
					}
			break;
		case KEY_DOWN:
			//la apasarea tastei DOWN se va roti cubul pe axa X in jos
			//si se reactualizeaza pozitia cuburilor din cubul Rubik
			unghi = 0.0f;
			rx = true;
			px = true;
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						int tz;
						if (j == 0)
						{
							tz = 2;
							mat[i][j][k] = matx[i][k][tz];
						} else
							if (j == 2)
							{
								tz = 0;
								mat[i][j][k] = matx[i][k][tz];
							}
							else
								mat[i][j][k] = matx[i][k][j];
					}
			break;
		case KEY_LEFT:
			//la apasarea tastei LEFT se va roti cubul pe axa Y in stanga
			//si se reactualizeaza pozitia cuburilor din cubul Rubik
			unghi = 0.0f;
			ry = true;
			px = true;
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						int tz;
						if (i == 2)
						{
							tz = 0;
							mat[i][j][k] = matx[k][j][tz];
						} else 
							if (i == 0)
							{
								tz = 2;
								mat[i][j][k] = matx[k][j][tz];
							} else 
								mat[i][j][k] = matx[k][j][i];
					}
			break;
		case KEY_RIGHT:
			//la apasarea tastei RIGHT se va roti cubul pe axa Y in dreapta
			//si se reactualizeaza pozitia cuburilor din cubul Rubik
			unghi = 0.0f;
			ry = true;
			mx = true;
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						int tz;
						if (k == 2)
						{
							tz = 0;
							mat[i][j][k] = matx[tz][j][i];
						} else 
							if (k == 0)
							{
								tz = 2;
								mat[i][j][k] = matx[tz][j][i];
							} else 
								mat[i][j][k] = matx[k][j][i];
					}
			break;
		case 'k':
			//la apasarea tastei "k" se va roti cubul pe axa Z in "fata"
			//si se reactualizeaza pozitia cuburilor din cubul Rubik
			unghi = 0.0f;
			rz = true;
			mx = true;
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						int tz;
						if (j == 2)
						{
							tz = 0;
							mat[i][j][k] = matx[tz][i][k];
						} else 
							if (j == 0)
							{
								tz = 2;
								mat[i][j][k] = matx[tz][i][k];
							} else 
								mat[i][j][k] = matx[j][i][k];
					}
			break;
		case 'j':
			//la apasarea tastei "j" se va roti cubul pe axa Z in "spate"
			//si se reactualizeaza pozitia cuburilor din cubul Rubik
			unghi = 0.0f;
			rz = true;
			px = true;
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];
			
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						int tz;
						if (i == 2)
						{
							tz = 0;
							mat[i][j][k] = matx[j][tz][k];
						} else 
							if (i == 0)
							{
								tz = 2;
								mat[i][j][k] = matx[j][tz][k];
							} else 
								mat[i][j][k] = matx[j][i][k];
					}
			break;
		case 't':
			//tasta pentru a roti felia din spate vertical pe axa X
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			for (int i = 0; i < 27; i++)
			{
				if (i >= 0 && i < 9)
					vector[vprim[i]]->rotateXRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
			}

			//reactualizarea poztiei cuburilor din cubul Rubik
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						if (i == 0)
						{
							int tz;
							if (k == 0)
							{
								tz = 2;
								mat[i][j][k] = matx[i][tz][j];
							} else
								if (k == 2)
								{
									tz = 0;
									mat[i][j][k] = matx[i][tz][j];
								}
								else
									mat[i][j][k] = matx[i][k][j];
						}
					}

			break;

		case 'h':
			//tasta pentru a roti felia din mijloc vertical pe axa X
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			for (int i = 0; i < 27; i++)
			{
				if (i >= 9 && i < 18)
					vector[vprim[i]]->rotateXRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
			}

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						if (i == 1)
						{
							int tz;
							if (k == 0)
							{
								tz = 2;
								mat[i][j][k] = matx[i][tz][j];
							} else
								if (k == 2)
								{
									tz = 0;
									mat[i][j][k] = matx[i][tz][j];
								}
								else
									mat[i][j][k] = matx[i][k][j];
						}
					}

			break;
		case 'b':
			//tasta pentru rotirea feliei din fata vertical pe axa X
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			for (int i = 0; i < 27; i++)
			{
				if (i >= 18 && i < 27)
					vector[vprim[i]]->rotateXRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
			}

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						if (i == 2)
						{
							int tz;
							if (k == 0)
							{
								tz = 2;
								mat[i][j][k] = matx[i][tz][j];
							} else
								if (k == 2)
								{
									tz = 0;
									mat[i][j][k] = matx[i][tz][j];
								}
								else
									mat[i][j][k] = matx[i][k][j];
						}
					}

			break;
		case 'p':
			//tasta pentru rotirea feliei de jos orizontal pe axa Y
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			for (int i = 0; i < 27; i++)
			{
				if (i >= 0 && i < 3)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
				if (i >= 9 && i < 12)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
				if (i >= 18 && i < 21)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
			}
			//reactualizarea pozitiei cubului Rubik
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						if (j == 0)
						{
							int tz;
							if (k == 2)
							{
								tz = 0;
								mat[i][j][k] = matx[tz][j][i];
							} else 
								if (k == 0)
								{
									tz = 2;
									mat[i][j][k] = matx[tz][j][i];
								} else 
									mat[i][j][k] = matx[k][j][i];
						}
					}
			break;
		case 'o':
			//tasta pentru rotirea feliei din mijloc orizontal pe axa Y
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			for (int i = 0; i < 27; i++)
			{
				if (i >= 3 && i < 6)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
				if (i >= 12 && i < 15)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
				if (i >= 21 && i < 24)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
			}
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						if (j == 1)
						{
							int tz;
							if (k == 2)
							{
								tz = 0;
								mat[i][j][k] = matx[tz][j][i];
							} else 
								if (k == 0)
								{
									tz = 2;
									mat[i][j][k] = matx[tz][j][i];
								} else 
									mat[i][j][k] = matx[k][j][i];
						}
					}
			break;
		case 'i':
			//rotirea feliei de sus orizontal pe axa Y
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			for (int i = 0; i < 27; i++)
			{
				if (i >= 6 && i < 9)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
				if (i >= 15 && i < 18)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
				if (i >= 24 && i < 27)
					vector[vprim[i]]->rotateYRelativeToPoint(vector[13]->axiscenter, -1.5707963267948966192313216916398f);
			}
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
						matx[i][j][k] = mat[i][j][k];

			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					for (int k = 0; k < 3; k++)
					{
						if (j == 2)
						{
							int tz;
							if (k == 2)
							{
								tz = 0;
								mat[i][j][k] = matx[tz][j][i];
							} else 
								if (k == 0)
								{
									tz = 2;
									mat[i][j][k] = matx[tz][j][i];
								} else 
									mat[i][j][k] = matx[k][j][i];
						}
					}
			break;
		case 'r':
			//tasta pentru a intra in modul de rezolvare
			//de aici se contorizeaza scorul
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			cs2->objectAdd(rez);
			start = true;
			cub_scor.clear();
			break;
		case 'R':
			//restart
			//readucerea cubului in pozitia initiala
			cs1->objects.clear();
			nr = 0;
			for (int x = 0; x < 3; x++)
				for (int y = 0; y < 3; y++)
					for(int z = 0; z < 3; z++)
					{
						vector[nr]= new Object3d(points,topology);
						vector[nr]->translate((float)6*(x - 1), (float)6*(y - 1), (float)6*(z - 1));
						nr++;
					}

			for (int i = 0; i < 27; i++)
				cs1->objectAdd(vector[i]);
			nr = 0;
			for (int x = 0; x < 3; x++)
				for (int y = 0; y < 3; y++)
					for(int z = 0; z < 3; z++)
						mat[x][y][z] = nr++;
			for (int i = 0; i < 24; i++)
				diferit[i] = 0;
			cs2->objects.clear();
			start = false;
			stop = false;
			cs3->objects.clear();
			it = 100;
			break;
		case KEY_SPACE:
			animation=!animation;
			break;
		default:
			break;
				}
}


int main(int argc, char** argv){
	WorldDrawer3d wd3d(argc,argv,600,600,200,100,std::string("Tema 2 EGC"));
	wd3d.init();
	wd3d.run();
	return 0;
}