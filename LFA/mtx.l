/*
 * Necula Roxana - Valentina 332CA
 * Tema LFA - Parsarea si executia unei masini Turing
 */

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <list>
	#include <string>
	#include <iostream>
	char* alphabet;
	int nraloc = 0;
	int pozitie = 0, incr = 0;
	std::string inp;
	std::string output;
	using namespace std;
	list<pair<string, list<pair<string, list<string> > > > > lista_masini;
	list<string> mas_elem;
	pair<string, list<string> > nume_el;
	list<pair<string, list<string> > > elem;
	pair<string, list<pair<string, list<string> > > > nume_mas;
	string ind, tagg, tag;
	list<pair<string, list<string> > >mas_executat;
	list<pair<string, list<pair<string, list<string> > > > >::iterator ii;
%}

cuvant [A-Za-z_0-9\#\$\@\*]+
delimm [@\[]
delim [\[\]\(\)]
nume_temp {cuvant}{delimm}
masina_elem {delim}*{cuvant}*{delim}*
space [ \t\n]
%s expect
%x comment
%x masina
%x indicator
%x parsare
%x lista_element

%%
"alphabet :: " {BEGIN(expect);}
<expect>.  {if (nraloc == 0) {
	alphabet = (char*)malloc(200*sizeof(char));
	nraloc++;
	}
	if (strcmp(yytext, ";") != 0 && strcmp(yytext, " ") != 0)
		strcat(alphabet, yytext);}
<expect>\n {BEGIN(INITIAL);}
";"         {BEGIN(comment);}
<comment>.+ {}
<comment>\n {BEGIN(INITIAL);}
{space} {}
{cuvant} { 
	nume_mas.first.clear();
	nume_mas.second.clear();
	elem.clear();
	nume_mas.first = yytext;
	BEGIN(masina);}
<masina>" ::= " {
	ind.clear();
	BEGIN(indicator);}
<indicator>. {
	ind.append(yytext);}
<indicator>" (\n" {
	BEGIN(parsare);}
<parsare>"{"{cuvant}+"}" {
	mas_elem.clear();
	nume_el.first.clear();
	nume_el.second = mas_elem;
	nume_el.first = yytext;
	BEGIN(lista_element);}
<parsare>"\n" {}
<parsare>{space} {}
<lista_element>"-> " {}
<lista_element>{space} {}
<lista_element>{masina_elem}+ {
	mas_elem.push_back(yytext);}
<lista_element>"&"{cuvant}+ {
	mas_elem.push_back(yytext);}
<lista_element>" (" {BEGIN(parsare);}
<parsare>") ;" {}
<lista_element>";" {
	nume_el.second = mas_elem;
	elem.push_back(nume_el);
	nume_mas.second = elem;
	BEGIN(parsare);}
<parsare>") ;;" {
	pair<string, list<string> >aux;
	aux.first = ind;
	aux.second.clear();
	elem.push_back(aux);
	nume_mas.second = elem;
	lista_masini.push_back(nume_mas);
	nume_el.first.clear();
	BEGIN(INITIAL);}
<indicator>"(\n" {BEGIN(masina);}
<<EOF>> {return 0;}
%%

//functie pentru definirea masinilor elementare
void functie_masini_elementare(char* alphabet, string element, string tag)
{
	int i, j;

	for (i = 0; i < strlen(alphabet); i++)
	{
		//masina elementara "L"
		if (element.compare("[L]") == 0)
		{
			//merg la stanga o pozitie
			if (pozitie > 0)
				pozitie--;
			return;
		}

		if (element.compare("[R]") == 0)
		{
			//merg la dreapta o pozitie
			pozitie++;
			return;
		}

		std::string ss; ss.append("]"); ss.insert(ss.begin(), alphabet[i]); ss.insert(ss.begin(), '[');  
		
		if (element.compare(ss) == 0)
		{
			//masina elementara cu un element din alfabet
			inp.erase(pozitie, 1);
			inp.insert(pozitie, 1, alphabet[i]);
			return;
		}
		
		string ml; string mr; string mnl; string mnr;

		ml.append("[L("); ml.insert(ml.begin()+3, alphabet[i]); ml.append(")]");
		mr.append("[R("); mr.insert(mr.begin()+3, alphabet[i]); mr.append(")]"); 
		mnl.append("[L(!"); mnl.insert(mnl.begin()+4, alphabet[i]); mnl.append(")]"); 
		mnr.append("[R(!"); mnr.insert(mnr.begin()+4, alphabet[i]); mnr.append(")]"); 

		if (element.compare(ml) == 0)
		{
			//masina L(element)
			if (pozitie > 0)
				for (j = pozitie - 1; j > 0; j--)
				{
					if (inp.at(j) != alphabet[i])
						pozitie--;
					else {pozitie--; return;}
				}
		}

		if (element.compare(mr) == 0)
		{
			//masina R(element)
			for (j = pozitie + 1; j < inp.length(); j++)
			{
				if (inp.at(j) != alphabet[i])
					pozitie++;
				else {pozitie++; return;}
			}
		}

		if (element.compare(mnl) == 0)
		{
			//masina L(!element)
			if (pozitie > 0)
				for (j = pozitie - 1; j > 0; j--)
				{
					if (inp.at(j) == alphabet[i])
						pozitie--;
					else {pozitie--; return;}
				}
		}

		if (element.compare(mnr) == 0)
		{
			//masina R(!element)
			for (j = pozitie; j < inp.length(); j++)
			{
				if (inp.at(j) == alphabet[i])
					pozitie++;
				else {pozitie++; return;}
			}
		}

	}
}

//functie pentru executia &loop / &start
void functie_loop()
{
	int ij;
	for (ij = 0; ij < tag.size() - 1; ij++)
		{
			if (tag.at(ij) == '@' && tag.at(ij + 1) == '[')
			{
				string send;
				send.insert(0, tag, ij + 1, ij + 3);
				//cout<<"TAG poz i: "<<pozitie<<" input: "<<inp<<" ";
				functie_masini_elementare(alphabet, send, tag);
				//cout<<"poz dupa: "<<pozitie<<" input: "<<inp<<endl;
			}
		}

			list<pair<string, list<string> > >::iterator j;
			for (j = (*ii).second.begin(); j != (*ii).second.end(); ++j)
			{
				string tt;
				tt.insert(tt.begin(), '}');
				tt.insert(tt.begin(), inp.at(pozitie));
				tt.insert(tt.begin(), '{');
				if (tt.compare((*j).first) == 0)
				{
					list<string>::iterator k;
					for (k = (*j).second.begin(); k != (*j).second.end(); ++k)
					{
						//cout<<(*k)<<"\t"<<"poz i: "<<pozitie<<" input: "<<inp<<" ";
						functie_masini_elementare(alphabet, (*k), tag);
						//cout<<"poz dupa: "<<pozitie<<" input: "<<inp<<endl;

						if (tagg.compare((*k)) == 0)
						{
							functie_loop();
						}

					}
				}
				
			}
}

main(int argc, char** argv)
{
	yyin = fopen(argv[1], "r");
	yylex();
	list<pair<string, list<pair<string, list<string> > > > >::iterator i;
	
	inp.append(argv[3]);
	inp.append("######");
	inp.insert(inp.begin(),'#');inp.insert(inp.begin(),'#');inp.insert(inp.begin(),'#');

	pozitie = inp.find(">");
	inp.erase(pozitie, 1);

	for (i = lista_masini.begin(); i != lista_masini.end(); ++i)
	{
		if ((*i).first.compare(argv[2]) == 0)
		{
			tag.append((*i).second.back().first);
			ii = i;
			list<pair<string, list<string> > >::iterator j;
			
			for (j = (*i).second.begin(); j != (*i).second.end(); ++j)
			{
				list<string>::iterator k;
				for (k = (*j).second.begin(); k != (*j).second.end(); ++k)
				{
					//cout<<(*k)<<" ";
				}
			}
		}
	}

	int found = tag.find("@"), found2, found3, ij;
	
	for (ij = 0; ij < tag.size(); ij++)
	{
		if (tag.at(ij) != '@')
		{
			tagg.insert(tagg.begin()+ij, tag.at(ij));
		} else break;
	}
	tagg.insert(tagg.begin(), '&');

	if (found != string::npos)
	{
		//daca avem label @
		for (ij = 0; ij < tag.size() - 1; ij++)
		{
			if (tag.at(ij) == '@' && tag.at(ij + 1) == '[')
			{
				string send;
				send.insert(0, tag, ij + 1, ij + 3);
				//cout<<"TAG poz i: "<<pozitie<<" input: "<<inp<<" ";
				functie_masini_elementare(alphabet, send, tag);
				//cout<<"poz dupa: "<<pozitie<<" input: "<<inp<<endl;
			}
		}

			list<pair<string, list<string> > >::iterator j;
			for (j = (*ii).second.begin(); j != (*ii).second.end(); ++j)
			{
				string tt;
				tt.insert(tt.begin(), '}');
				tt.insert(tt.begin(), inp.at(pozitie));
				tt.insert(tt.begin(), '{');
				if (tt.compare((*j).first) == 0)
				{
					list<string>::iterator k;
					for (k = (*j).second.begin(); k != (*j).second.end(); ++k)
					{
						//cout<<(*k)<<"\t"<<"poz i: "<<pozitie<<" input: "<<inp<<" ";
						functie_masini_elementare(alphabet, (*k), tag);
						//cout<<"poz dupa: "<<pozitie<<" input: "<<inp<<endl;

						if (tagg.compare((*k)) == 0)
						{
							functie_loop();
						}
					}
				}
			}

	} else {
		//daca nu avem label @
		found2 = tag.find_first_of("[");
		found3 = tag.find_first_of("]");
		string send; send.insert(0, tag, found2, found2 + found3 + 1);
		functie_masini_elementare(alphabet, send, tag);
		if (found2 != string::npos)
		{
			found2 = tag.find_first_of("[", found2 + 1);
			found3 = tag.find_first_of("]", found3 + 1);
			send.clear();
			send.insert(0, tag, found2, found2 + found3 + 1);
			functie_masini_elementare(alphabet, send, tag);
		}		
		
			list<pair<string, list<string> > >::iterator j;
			for (j = (*ii).second.begin(); j != (*ii).second.end(); ++j)
			{
				int inc = 0;
				while (inc != strlen(alphabet))
				{
					string tt;
					tt.insert(tt.begin(), '}');
					tt.insert(tt.begin(), alphabet[inc++]);
					tt.insert(tt.begin(), '{');
					if (tt.compare((*j).first) == 0)
					{
						list<string>::iterator k;
						for (k = (*j).second.begin(); k != (*j).second.end(); ++k)
						{
							//cout<<(*k)<<"\t"<<"poz i: "<<pozitie<<" input: "<<inp;
							functie_masini_elementare(alphabet, (*k), tag);
							//cout<<"poz dupa: "<<pozitie<<" input: "<<inp<<endl;
						}
					}
				}
			}

	}

	for (i = lista_masini.begin(); i != lista_masini.end(); ++i)
	{
		if ((*i).first.compare(argv[2]) == 0)
		{
			list<pair<string, list<string> > >::iterator j;
			//fiecare element din alfabet
			for (j = (*i).second.begin(); j != (*i).second.end(); ++j)
			{
				//luam fiecare char din input si verificam cu fiecare element din masina copy pentru executie
				list<string>::iterator k;
				//fiecare masina elementara
				for (k = (*j).second.begin(); k != (*j).second.end(); ++k)
				{
					//cout<<"\t"<<(*k)<<endl;
					//functie_masini_elementare(alphabet, (*k), tag);
				}
			}
		}
	}
	if (strcmp(argv[3], "#>#") == 0)
	{
		int ji; int incc = 0;
		for (ji = 0; ji < inp.size(); ji++)
		{
			if (inp.at(ji) == '#')
				incc++;
		}

		while (incc-- > 0)
		{
			for (ji = 0; ji < inp.size() - incc; ji++)
				if (inp.at(ji) == '#')
					inp.erase(ji, 1);
		}
		
		inp.insert(inp.begin(), '#');
		inp.insert(inp.begin(), '>');
		inp.insert(inp.begin(), '#');
		
		for (ji = 0; ji < inp.size(); ji++)
			if (inp.at(ji) != '#' && inp.at(ji) != '>')
				{
					inp.append("#");
					break;
				}
		
	} else {

		int fd1, fd2, fd3, fd4;
		fd1 = inp.find_first_of("#");
		fd2 = inp.find_first_not_of("#");
		inp.erase(fd1, fd2 - 1);
		fd3 = inp.find_last_of("#");
		fd4 = inp.find_last_not_of("#");
		inp.erase(fd4 + 1, fd3 - fd4 - 1);
		inp.insert(inp.begin(), '>'); inp.insert(inp.begin(), '#');
	}
	cout<<inp<<endl;

	if (alphabet != NULL)
		free(alphabet);
}