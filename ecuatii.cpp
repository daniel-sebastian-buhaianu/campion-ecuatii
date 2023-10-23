#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#define LGMAX 256
#define MAXCIF 5
using namespace std;
ifstream fin("ecuatii.in");
ofstream fout("ecuatii.out");
struct expresie
{
	char sir[LGMAX];
	int sumaCoef, sumaNr;
};
struct ecuatie
{
	char sir[LGMAX];
	expresie st, dr;
};
void citesteEcuatie(ecuatie &);
void calculeazaExpresie(expresie &);
void actualizeazaExpresie(expresie &, char, char*, int=0);
void calculeazaEcuatie(ecuatie &);
bool esteCifra(char);
int main()
{
	int n, i;
	ecuatie ec;
	fin >> n;
	fin.get();
	for (i = 0; i < n; i++)
	{
		citesteEcuatie(ec);
		calculeazaEcuatie(ec);
	}
	fin.close();
	fout.close();
	return 0;
}
void calculeazaEcuatie(ecuatie & ec)
{
	calculeazaExpresie(ec.st);
	calculeazaExpresie(ec.dr);
	if (ec.st.sumaCoef == ec.dr.sumaCoef)
	{
		if (ec.st.sumaNr == ec.dr.sumaNr)
		{
			fout << "infinit";
		}
		else
		{
			fout << "imposibil";
		}
	}
	else
	{
		// ax + b = 0 <=> x = -b/a
		int a = ec.st.sumaCoef - ec.dr.sumaCoef;
		int b = ec.st.sumaNr - ec.dr.sumaNr;
		float x = (float)-b/a;
		fout << fixed << setprecision(4) << x; 
	}
	fout <<'\n';
}
void actualizeazaExpresie(expresie & ex, char semn, char* nr, int tip)
{
	if (tip == 1)
	{
		if (semn == '+')
		{
			ex.sumaCoef += atoi(nr);
		}
		else
		{
			ex.sumaCoef -= atoi(nr);
		}
	}
	else
	{
		if (semn == '+')
		{
			ex.sumaNr += atoi(nr);
		}
		else
		{
			ex.sumaNr -= atoi(nr);
		}
	}
}
bool esteCifra(char c)
{
	return c >= '0' && c <= '9';
}
void calculeazaExpresie(expresie & ex)
{
	int lg, i, st, dr;
	char s[LGMAX], nr[MAXCIF], semn;
	strcpy(s, ex.sir);
	lg = strlen(s);
	semn = '+';
	for (st = i = 0; i <= lg; i++)
	{
		if (s[i] == '+'|| s[i] == '-' || !s[i])
		{
			dr = s[i-1] == 'x' ? i-2 : i-1;
			if (!esteCifra(s[dr]))
			{
				nr[0] = '1';
				nr[1] = 0;
			}
			else
			{
				strncpy(nr, s+st, dr-st+1);				
				nr[dr-st+1] = 0;
			}
			if (s[i-1] == 'x')
			{
				actualizeazaExpresie(ex, semn, nr, 1);
			}
			else
			{
				actualizeazaExpresie(ex, semn, nr);
			}
			st = i+1;
			semn = s[i];
		}
	}
}
void citesteEcuatie(ecuatie & ec)
{
	char s[LGMAX], *p;
	fin.getline(s, LGMAX);
	strcpy(ec.sir, s);
	p = strchr(s, '=');
	strcpy(ec.dr.sir, p+1);
	*p = 0;
	strcpy(ec.st.sir, s);
	ec.st.sumaCoef = ec.st.sumaNr = 0;
	ec.dr.sumaCoef = ec.dr.sumaNr = 0;
}
// scor 100
