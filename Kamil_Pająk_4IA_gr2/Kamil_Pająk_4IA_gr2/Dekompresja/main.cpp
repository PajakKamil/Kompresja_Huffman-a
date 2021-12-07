#include "Global_header.h"

void Kompresja_huffmana();
int Najmniejsza_para(std::vector<int>tab, int R, std::vector<int>* Link);
void Zamien_na_teskt();
void Drukuj_tablice(std::vector<int> id, std::vector<int> P, std::vector<int> Link, int V, int z, std::vector<char> znaki_wystepujace);

int main()
{
	//Kompresja_huffmana();
	Zamien_na_teskt();
	return 0;
}

//int Najmniejsza_para(std::vector<int>liczba_znakow, int R, std::vector<int>* Link)
//{
//	if (liczba_znakow.size() < 1)
//	{
//		std::cout << "Error! ";
//		return 0;
//	}
//	int min1 = R;
//	int min2 = R;
//	for (int i = 0; i < liczba_znakow.size(); i++)
//	{
//		if (liczba_znakow[i] < min1 && (*Link)[i] == 0)
//		{
//			min2 = min1;
//			min1 = liczba_znakow[i];
//		}
//		else if (liczba_znakow[i] < min2 && (*Link)[i] == 0)
//		{
//			min2 = liczba_znakow[i];
//		}
//	}
//
//
//	return min1 + min2;
//}
void Zamien_na_teskt()
{
	int ilosc_znakow;
	std::cin >> ilosc_znakow;
	std::vector<std::string> znak_i_kod(ilosc_znakow);
	char znak[255]{};
	std::vector<std::string> kod_znaku(ilosc_znakow);
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	for (int i = 0; i < ilosc_znakow; i++)
	{
		std::getline(std::cin, znak_i_kod[i]);
		znak[i] = znak_i_kod[i][0];
		for (int j = 2; j < znak_i_kod[i].size(); j++)
		{
			kod_znaku[i] += znak_i_kod[i][j];
		}
	}
	std::string tekst;
	std::cin >> tekst;
	std::string pomocy{};
	for (int i = 0; i < tekst.length(); i++)
	{
		pomocy += tekst[i];
		for (int j = 0; j < ilosc_znakow; j++)
		{
			if (pomocy == kod_znaku[j])
			{
				std::cout << znak[j];
				pomocy = {};
			}
		}
	}
}

void Kompresja_huffmana()
{
	const int R = 255;
	std::string tekst;
	char ascii[R];
	for (int i = 0; i < R; i++)
	{
		ascii[i] = i;
	}

	std::getline(std::cin, tekst);
	int liczba_wszystkich_znakow = (int)tekst.size();
	int a[R]{};				//Taka chwilówka

	for (int i = 0; i < liczba_wszystkich_znakow; i++)
	{
		for (int j = 0; j < R; j++)
		{
			if (ascii[j] == tekst[i])
			{
				a[j]++;
			}
		}
	}

	std::vector<int> liczba_znakow;
	std::vector<char> znaki_wystepujace;

	for (int i = 0; i < R; i++)
	{
		if (a[i] > 0)
		{
			liczba_znakow.emplace_back(a[i]);
			znaki_wystepujace.emplace_back(ascii[i]);
		}
	}

	//std::cout << liczba_wszystkich_znakow << std::endl;
	/*for (int i = 0; i < znaki_wystepujace.size(); i++)
	{
		std::cout << znaki_wystepujace[i] << " " << liczba_znakow[i] << std::endl;
	}*/

	int z = znaki_wystepujace.size();
	const int V = (2 * z) - 1;
	std::vector<int> P(V);
	std::vector<int> Link(V);
	std::vector<int> id(V);

	for (int i = 0; i < id.size(); i++)
	{
		id[i] = i;
	}

	for (int i = 0; i < z; i++)
	{
		P[i] = liczba_znakow[i];
	}

	//Drukuj_tablice(id, P, Link, V, z, znaki_wystepujace);

	if (liczba_znakow.size() < 1)
	{
		std::cout << "Error! ";
		return;
	}

	int min1 = R;
	int min2 = R;
	int index1 = 0;
	int index2 = 0;
	int licznik_zer{};
	int dodaj_index{};

	for (int i = 0; i < V; i++)
	{
		if (Link[i] == 0)
		{
			licznik_zer++;
		}
	}

	do
	{

		for (int i = 0; i < V; i++)
		{
			if (P[i] < min1 && Link[i] == 0 && P[i] > 0)
			{
				min2 = min1;
				min1 = P[i];
				//std::cout << "id z min1: " << id[i] << std::endl;
				index1 = i;
			}
			else if (P[i] < min2 && Link[i] == 0 && P[i] > 0)
			{
				min2 = P[i];
				//std::cout << "id z min2: " << id[i] << std::endl;
			}
		}

		for (int i = 0; i < V; i++)
		{
			if (min2 == P[i] && i != index1 && Link[i] == 0)
			{
				index2 = i;
				break;
			}
		}
		//std::cout << "Index1: " << index1 << " Index2: " << index2 << std::endl;
		P[index1] = 0;
		P[index2] = 1;

		//int min_id = INT_MAX;

		/*for (int i = z; i < V; i++)
		{
			if (id[i] < min_id && Link[i] == 0)
			{
				min_id = id[i];
				std::cout << "Link przyjmie wartosc: " << min_id << std::endl;
			}
		}*/

		if (Link[index1] == 0 && Link[index2] == 0)
		{
			Link[index1] = z + dodaj_index;
			Link[index2] = z + dodaj_index;
		}
		dodaj_index++;

		for (int i = 0; i < z - 1; i++)
		{
			if (Link[z + i] == 0 && P[z + i] == 0)
			{
				P[z + i] = min1 + min2;
				break;
			}
		}

		min1 = min2 = R;
		//min_id = INT_MAX;
		licznik_zer = 0;

		for (int i = 0; i < V; i++)
		{
			if (Link[i] == 0)
			{
				licznik_zer++;
			}
		}

		//Drukuj_tablice(id, P, Link, V);
	} while (licznik_zer > 2);

	//Drukuj_tablice(id, P, Link, V , z, znaki_wystepujace);

	int max1, max2;
	max1 = max2 = NULL;
	for (int i = 0; i < V; i++)
	{
		if (Link[i] > max1)
		{
			max1 = Link[i];
		}
	}

	std::vector<std::string> kod_binarny(z);
	std::vector<int> chwilowka(V);
	for (int i = 0; i < z; i++)
	{
		chwilowka[i] = Link[id[i]];
		kod_binarny[i] += std::to_string(P[id[i]]);
		for (int j = z; j < V - 1; j++)
		{
			if (chwilowka[i] == id[j])
			{
				chwilowka[i] = Link[id[j]];
				kod_binarny[i] += std::to_string(P[id[j]]);
			}
		}
	}

	std::cout << z << std::endl;
	//std::cout << kod_binarny[0].size() << "\n";
	for (int i = 0; i < z; i++)
	{
		//if (znaki_wystepujace[i] == ' ')
		//{
		//	std::cout << "\\n";
		//}
		//else
		std::cout << znaki_wystepujace[i] << " ";
		for (int j = kod_binarny[i].length(); j >= 0; j--)
		{
			std::cout << kod_binarny[i][j];
			
		}
		std::cout << std::endl;
		//std::cout << " " << kod_binarny[i] << std::endl;
	}


	//std::cout << "Rozmiar calej tablicy: " << kod_binarny.size() << "\nRozmiar pojedynczej komorki: " << kod_binarny[0].length() << std::endl;
	/*for (int i = 0; i < z; i++)
	{
		for (int j = kod_binarny[i].length(); j >= 0; j--)
		{

			std::cout << znaki_wystepujace[i];
			std::cout << " " << kod_binarny[i][j] << std::endl;
		}
	}*/


	for (int i = 0; i < liczba_wszystkich_znakow; i++)
	{
		for (int j = 0; j < z; j++)
		{
			if (znaki_wystepujace[j] == tekst[i])
			{
				//std::cout << znaki_wystepujace[j];
				for (int k = kod_binarny[j].length() - 1; k >= 0; k--)
				{
					std::cerr << kod_binarny[j][k];
				}

			}
		}
	}

	//for (int i = 0; i < V; i++)
	//{
	//	if (P[i] < min1 && Link[i] == 0)
	//	{
	//		min2 = min1;
	//		min1 = P[i];
	//		std::cout << "id z min1: " << id[i] << std::endl;
	//		index1 = i;
	//	}
	//	else if (P[i] < min2 && Link[i] == 0)
	//	{
	//		min2 = P[i];
	//		std::cout << "id z min2: " << id[i] << std::endl;
	//	}
	//}

	//for (int i = 0; i < V; i++)
	//{
	//	if (min2 == P[i])
	//	{
	//		index2 = i;
	//	}
	//}

	////std::cout << "Index min1: " << index1 << " = " << min1 << std::endl << "Index min2: " << index2 << " = " << min2;
	//for (int i = 0; i < z - 1; i++)
	//{
	//	P[z + i] = min1 + min2;
	//	P[index1] = 0;
	//	P[index2] = 1;
	//	if (Link[index1] == 0 && Link[index2] == 0)
	//	{
	//		Link[index1] = z + i;
	//		Link[index2] = z + i;
	//	}
	//}
}

void Drukuj_tablice(std::vector<int> id, std::vector<int> P, std::vector<int> Link, int V, int z, std::vector<char> znaki_wystepujace)
{
	std::cout << std::endl;
	for (int i = 0; i < z; i++)
	{
		std::cout.width(4);
		std::cout << znaki_wystepujace[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < V; i++)
	{
		std::cout.width(4);
		std::cout << id[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < V; i++)
	{
		std::cout.width(4);
		std::cout << P[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < V; i++)
	{
		std::cout.width(4);
		std::cout << Link[i];
	}
	std::cout << std::endl;
}