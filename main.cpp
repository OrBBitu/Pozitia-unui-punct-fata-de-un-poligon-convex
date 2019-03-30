#include <iostream>
#include <fstream>

using namespace std;

struct Punct
{
    float x , y ;
};

ifstream in ( "date.in");
ofstream out ("date.out");

bool TestOrientare (Punct p , Punct q , Punct r)  ///returneaza 1 daca r e la stanga, si 0 altfel
{
    int rezultat =( ( q.x - p.x ) * ( r.y - p.y ) - ( q.y - p.y ) * ( r.x - p.x ) );
    if( rezultat > 0 ) ///r este in stanga
        return 1;
    else
        return 0;
}

bool verificaColiniaritate ( Punct p , Punct q , Punct r ) ///returneaza 1 daca sunt si 0 daca nu sunt
{
    int rez = p.x * ( q.y - r.y ) + q.x * ( r.y - p.y ) + r.x * ( p.y - q.y );
    if( rez == 0)
        return 1; ///sunt coliniare
    else
        return 0;
}

int main()
{
    int numarPuncte , i , rezultat1 , rezultat2 , rezultat3 , coliniare1 , coliniare2 ;
    int verifica = 0; /// 0 daca punctul e in afara, 1 daca e in interior si 2 daca e pe latura
    Punct P;

    in >> P.x >> P.y;
    in >> numarPuncte;

    Punct *vectorPuncte = new Punct [ numarPuncte + 1 ];

    for(i = 0 ; i < numarPuncte ; i ++)
    {
        in >> vectorPuncte[i].x >> vectorPuncte[i].y;
    }

    if( (P.x == vectorPuncte[0].x && P.y == vectorPuncte[0].y ) || (P.x == vectorPuncte[numarPuncte-1].x && P.y == vectorPuncte[numarPuncte-1].y ) )
    {
        verifica = 2;
    }
	
    else
    {
        for( i = 1 ; i < numarPuncte-1 ; i++ )
        {
            rezultat1 = TestOrientare( vectorPuncte[0] , vectorPuncte[i] , P );
            rezultat2 = TestOrientare( vectorPuncte[0] , vectorPuncte[i+1] , P );

            if( (rezultat1 == 0 && rezultat2 == 1)  ) ///este la dreapta si la stanga unei dreapta
            {
                rezultat3 = TestOrientare( vectorPuncte[i] , vectorPuncte[i+1] , P );

                if(rezultat3 == 0) ///se afla in poligon, de verificat daca e pe latura unui poligon sau nu, daca e 0 e in triunghi
                {///daca a intrat pe if inseamna ca punctul e in poligon
                    if( i == 1 )  ///trebuie sa verificam pentru 2 laturi ale primului triunghi
                    {
                        coliniare1 = verificaColiniaritate( vectorPuncte[0], vectorPuncte[i] , P );  ///A0A1P
                        coliniare2 = verificaColiniaritate( vectorPuncte[i], vectorPuncte[i+1] , P ); ///A1A2P

                        if(coliniare1==1) ///se afla pe latura A0A1
                        {
                            verifica = 2;
                        }
                        else if(coliniare2 == 1) ///e pe A1A2
                        {
                            verifica = 2;
                        }
                        else
                        {
                            verifica = 1; ///e inauntru poligonului
                        }

                    }
                    else if ( i == numarPuncte - 2 ) ///ultimul triunghi
                    {
                        coliniare1 = verificaColiniaritate( vectorPuncte[i+1] , vectorPuncte[0] , P ); ///A5A0P
                        coliniare2 = verificaColiniaritate( vectorPuncte[i] , vectorPuncte[i+1] , P ); ///A4A5P

                        if( coliniare1 == 1)
                        {
                            verifica = 2; /// e pe A5A0
                        }
                        else if( coliniare2 == 1)
                        {
                            verifica = 2; /// e pe A4A5
                        }
                        else
                        {
                            verifica = 1; ///e inauntru poligonului;
                        }

                    }
                    else ///verificam doar pentru o latura a poligonului
                    {
                        coliniare1 = verificaColiniaritate( vectorPuncte[i], vectorPuncte[i+1], P );

                        if( coliniare1 == 1)
                        {
                            verifica = 2; ///e pe latura AiAi+1
                        }
                        else
                        {
                            verifica = 1; ///e inauntru poligonului
                        }

                    }

                    i = numarPuncte;
                }

                else ///e in afara
                {
                    verifica = 0;
                    i = numarPuncte;
                }
            }
        }
    }

    if( verifica == 0 )
        out << "Punctul P se afla inafara poligonului";
    else if( verifica == 1 )
        out << "Punctul P se afla inauntru poligonului";
    else
        out << "Punctul P se afla pe o latura a poligonului";


    return 0;
}

