#include <iostream>
#include <string>

using namespace std;

//compromisso com determinada hora e descriçao em forma de lista
typedef struct Compromisso
{
	string s;
	int h, min;
	struct Compromisso *p;
}compromisso;

//estrutura que guarda a lista de compromissos
typedef struct Dia
{
	compromisso *inicial;
	compromisso *fim;
}dia;

//guarda os dias do mes
typedef struct Mes
{
	int d, t;
	dia *tabela;
	struct Mes *p;
}mes;

//guarda os meses
typedef struct Agenda
{
	mes *inicial;
	mes *fim;
}agenda;

agenda *abre_agenda();
void verifica(agenda *a);
void lista_compromissos(agenda *a);
void remove_compromisso(agenda *a);
void leitura_compromisso(agenda *a);
void fecha_agenda(agenda *a);
void destroi_agenda(agenda *a);