#include <cstdlib>
#include <iostream>
#include <cmath>
#include <new>
using namespace std;

int n = 35;          // nombre de sommets
int **adj;           //[n][n];  // matrice d'adjacence du graphe
int *couleur1;       //[n];  // couleurs des sommets pour l'agorithme exact
int *couleur2;       //[n]; // couleurs pour DSATUR
int *DSAT;           //[n]; // degrés de saturation
int *Degre;          //[n]; // degrés des sommets
bool trouve = false; // permet de stopper l'algorithme exact
                     // quand une coloration  a ete trouvee

void genere(int p) // genere un graphe non orienté de n sommets et probabilité p d'arête entre toute paire de sommets
{
  srand(time(NULL));
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
      if (rand() % 101 <= p)
        adj[i][j] = adj[j][i] = 1;
      else
        adj[i][j] = adj[j][i] = 0;
  }
}

bool convient(int x, int c, int k) // teste si la couleur c peut être donnee au sommet x (elle n'est pas utilisee par un de ses voisins)
{
  int nb = 0;
  for (int i = 0; i < n; i++)
    if (adj[x][i] && (couleur1[i] == c))
      nb++;
  return (nb <= k);
}

bool convientDSAT(int x, int c, int k) // teste si la couleur c peut �tre donnee au sommet x - version pour DSATUR
{
  int nb = 0;
  for (int i = 0; i < n; i++)
    if (adj[x][i] && (couleur2[i] == c))
      nb++;
  return (nb <= k);
}

void colorRR(int x, int k, int imp) // fonction recursive pour tester toutes les couleurs possible pour le sommet x
{
  if (x == n)
  {
    cout << "Coloration en " << k << " couleurs trouvee" << endl;
    /*
    for (int i = 0; i < n; i++)
      cout << "couleur de " << i << " : " << couleur1[i] << endl; // int z;cin >> z;
      //*/
    trouve = true;
  }
  else
    for (int c = 1; c <= k; c++)
      if (convient(x, c, imp))
      {
        couleur1[x] = c; // cout << "=>couleur de " << x << " : " << couleur[x] << endl;
        colorRR(x + 1, k, imp);
        if (trouve)
          return;
      }
  // return false;
}

void colorexact(int k, int imp) // teste si le graphe possede une coloration en k couleurs en essayant toutes les combinaisons
{
  for (int i = 0; i < n; i++)
    couleur1[i] = 0;
  colorRR(0, k, imp);
  // if(!trouve) cout << "Pas de coloration en " << k <<" couleurs" << endl;
}

int nbChromatique(int d, int imp) // calcule le nombre chromatique en testant à partir de d couleurs et diminuant k tant que c'est possible
{
  int k = d + 1;
  do
  {
    k--;
    trouve = false;
    colorexact(k, imp);
  } while (trouve);
  return k + 1;
}

int dsatMax()
{
  int maxDeg = -1, maxDSAT = -1, smax = 0;
  for (int i = 0; i < n; i++)
    if (couleur2[i] == 0 && (DSAT[i] > maxDSAT || (DSAT[i] == maxDSAT && Degre[i] > maxDeg)))
    {
      maxDSAT = DSAT[i];
      maxDeg = Degre[i];
      smax = i;
    }
  // cout << "sommet " << smax << " choisi" << endl;
  return smax;
}

int DSATUR(int k)
{
  int nb = 0, c, x, cmax = 0;
  for (int i = 0; i < n; i++)
  {
    couleur2[i] = 0;
    DSAT[i] = 0;
    Degre[i] = 0;
    for (int j = 0; j < n; j++)
      if (adj[i][j])
        Degre[i]++;
    DSAT[i] = Degre[i];
  }

  while (nb < n) // tant qu'on a pas colorié tous les sommets
  {
    c = 1;
    x = dsatMax(); // on choisit le sommet de DSAT max non encore colorié
    while (!convientDSAT(x, c, k))
      c++;                      // on cherche la plus petite couleur disponible pour ce sommet
    for (int j = 0; j < n; j++) // mise à jour des DSAT
    {
      if (adj[x][j] && convientDSAT(j, c, k))
        DSAT[j]++; // j n'avait aucun voisin colorié c,on incrémente donc son DSAT
    }
    couleur2[x] = c;
    if (cmax < c)
      cmax = c;
    nb++;
  }

  return cmax;
}

float degmoy()
{
  float deg = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      deg += adj[i][j];
  return deg / n;
}

int main()
{
  int p, k, nbc, imp = 0;
  cout << "nombre de sommets" << endl;
  cin >> n;
  cout << "proba d'arête: " << endl;
  cin >> p;
  adj = new int *[n];
  for (int i = 0; i < n; i++)
    adj[i] = new int[n];
  couleur1 = new int[n];
  couleur2 = new int[n];
  DSAT = new int[n];
  Degre = new int[n];

  genere(p);

  for (int i = 0; i < n; i++)
  {
    cout << "sommet " << i << " : ";
    for (int j = 0; j < n; j++)
      if (adj[i][j])
        cout << j << " ";
    cout << endl;
  }
  float dm = degmoy();
  cout << "degre moyen: " << dm << endl;
  while (imp < dm + 1) {
    cout << "-----------------------------------------" << endl;
    cout << "degre d'improprete: " << imp << endl;
    // cin >> imp;

    k = DSATUR(imp);
    cout << "DSAT: coloration en " << k << " couleurs : " << endl;
    /*for (int i = 0; i < n; i++)
      cout << "couleur de " << i << " : " << couleur2[i] << endl;
    */
    cout << "ColorExact :" << endl;
    nbc = nbChromatique(dm, imp);
    cout << "Nombre chromatique : " << nbc << endl;
    imp++;
  }


  return 0;
}
