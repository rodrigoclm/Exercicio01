#include "agenda.hpp"
#include <fstream>

//cria a tabela dos dias, onde cada mes tem um número especifico de dias
void cria_tabela_dias(mes *m)
{
	if(m->d == 2)
	{
		m->tabela = new dia[28];
		m->t = 28;
	}
	else if(m->d == 1 || m->d == 3 || m->d == 5 || m->d == 7 || m->d == 8 || m->d == 10 || m->d == 12)
	{
		m->tabela = new dia[31];
		m->t = 31;
	}
	else
	{
		m->tabela = new dia[30];
		m->t = 30;
	}
	for (int i = 0; i < m->t; i++)
	{
		m->tabela[i].fim = nullptr;
		m->tabela[i].inicial = nullptr;
	}
	
}

//cria a lista dos meses
void cria_lista_meses(agenda *a)
{
	mes *aux = new mes();
	aux->d = 1;
	cria_tabela_dias(aux);
	a->inicial = aux;
	a->fim = aux;
	a->fim->p = nullptr;
	for (int i = 2; i < 13; i++)
	{
		aux = new mes();
		aux->d = i;
		cria_tabela_dias(aux);
		a->fim->p = aux;
		a->fim = a->fim->p;
		a->fim->p = nullptr;
	}
}

//cria a agenda
agenda *abre_agenda()
{
	agenda *a = new agenda();
	cria_lista_meses(a);
	return a;
}

//insere um novo compromisso ao final da lista do dia determinado
void insere_compromisso(int h, int min, int d, string s, mes* m)
{
	if (m->tabela[d].inicial == nullptr)
	{
		m->tabela[d].inicial = new compromisso();
		m->tabela[d].fim = m->tabela[d].inicial;
		m->tabela[d].fim->h = h;
		m->tabela[d].fim->s = s;
		m->tabela[d].fim->min = min;
		m->tabela[d].fim->p = nullptr;
	}
	else
	{
		m->tabela[d].fim->p = new compromisso();
		m->tabela[d].fim->p->h = h;
		m->tabela[d].fim->s = s;
		m->tabela[d].fim->min = min;
		m->tabela[d].fim = m->tabela[d].fim->p;
		m->tabela[d].fim->p = nullptr;
	}
	
}

//verifica se um compromisso com horario especifico existe
bool verifica_compromisso(agenda *a, int h, int min, int d, int m)
{
	compromisso *aux1;
	mes *aux = a->inicial;
	while (aux->d != m)
	{
		aux = aux->p;
	}
	aux1 = aux->tabela[d].inicial;
	while (aux1 != nullptr && aux1->h != h && aux1->min != min)
	{
		aux1 = aux1->p;
	}
	if (aux1 == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//verifica se um compromisso existe e então o remove da lista
void remove_compromisso(agenda *a)
{
	bool r;
	int m, d, h, min;
	mes *aux = a->inicial;
	compromisso *c, *c1;
	cout << "Insira o mês:" << endl;
	cin >> m;
	while(m < 1 || m > 12)
	{
		cout << "Mês inválido!\nInsira o mês:" << endl;
		cin >> m;
	}
	while (aux->d != m && aux != nullptr)
	{
		aux = aux->p;
	}
	cout << "Insira o dia:" << endl;
	cin >> d;
	while(d < 1 || d > aux->t)
	{
		cout << "Dia inválido!\nInsira o dia:" << endl;
		cin >> d;
	}
	cout << "Insira a hora do compromisso:" << endl;
	cin >> h;
	cout << "Insira o minuto do compromisso:" << endl;
	cin >> min;
	while ( h < 0 || h > 23 || min < 0 || min > 59)
	{
		cout << "Horário errado!" << endl;
		cout << "Insira a hora do compromisso:" << endl;
		cin >> h;
		cout << "Insira o minuto do compromisso:" << endl;
		cin >> min;
	}
	r = verifica_compromisso(a, h, min, d - 1, m);
	if(r)
	{
		c = aux->tabela[d - 1].inicial;
		c1 = aux->tabela[d - 1].inicial;
		if (aux->tabela[d - 1].inicial != nullptr && aux->tabela[d - 1].inicial->h == h && aux->tabela[d - 1].inicial->min == min)
		{
			aux->tabela[d - 1].inicial = aux->tabela[d - 1].inicial->p;
			delete c;
			cout << "Compromisso removido!" << endl;
			return;
		}
		c = c->p;
		while(c != nullptr && c1 != nullptr)
		{
			if (c->h == h && c->min == min)
			{
				c1->p = c->p;
				delete c;
			}
			c = c->p;
			c1 = c1->p;
		}
	}
	else
	{
		cout << "Compromisso inexistente!" << endl;
	}
	
}

//faz a listagem de todos os compromissos do mês
void lista_compromissos(agenda *a)
{
	int n;
	mes *m = a->inicial;
	compromisso *aux;
	cout << "Insira o mês:" << endl;
	cin >> n;
	while (n < 1 && n > 12)
	{
		cout << "Mês inválido!\nInsira o mês:" << endl;
		cin >> n;
	}
	while (m->d != n && m != nullptr)
	{
		m = m->p;
	}
	cout << "Compromissos do mês:" << endl;
	for (int i = 0; i < m->t; i++)
	{
		aux = m->tabela[i].inicial;
		cout << "Dia " << i + 1 << endl;
		while (aux != nullptr)
		{
			cout << aux->h << ":" << aux->min << endl;
			cout << aux->s << endl;
			aux = aux->p;
		}
	}
}

void verifica(agenda *a)
{
	bool r;
	int h, min, d, m;
	mes *aux;
	cout << "Insira o mês:" << endl;
	cin >> m;
	while(m < 1 || m > 12)
	{
		cout << "Mês inválido!\nInsira o mês:" << endl;
		cin >> m;
	}
	aux = a->inicial;
	while (aux->d != m)
	{
		aux = aux->p;
	}
	cout << "Insira o dia:" << endl;
	cin >> d;
	while(d < 1 || d > aux->t)
	{
		cout << "Dia inválido!\nInsira o dia:" << endl;
		cin >> d;
	}
	cout << "Insira a hora e o minuto, em sequência:" << endl;
	cin >> h;
	cin >> min;
	while(h > 23 || h < 0 || min > 59 || min < 0)
	{
		cout << "Horário inválido!\nInsira a hora e o minuto, em sequência:" << endl;
		cin >> h;
		cin >> min;
	}
	r = verifica_compromisso(a, h, min, d - 1, m);
	if (r)
	{
		cout << "Compromisso já existente!" << endl;
	}
	else
	{
		cout << "Horário vago!" << endl;
	}
}

void leitura_compromisso(agenda *a)
{
	string s;
	int h, min, m, d;
	mes *aux = a->inicial;
	cout << "Insira o mês:" << endl;
	cin >> m;
	while (m > 12 || m < 1)
	{
		cout << "Mês inválido!\nInsira o mês:" << endl;
		cin >> m;
	}
	while (aux->d != m)
	{
		aux = aux->p;
	}
	cout << "Insira o dia:" << endl;
	cin >> d;
	while(d < 1 || d > aux->t)
	{
		cout << "Dia inválido!\nInsira o dia:" << endl;
		cin >> d;
	}
	cout << "Insira a hora do compromisso:" << endl;
	cin >> h;
	cout << "Insira o minuto do compromisso:" << endl;
	cin >> min;
	while ( h < 0 || h > 23 || min < 0 || min > 59)
	{
		cout << "Horário errado!" << endl;
		cout << "Insira a hora do compromisso:" << endl;
		cin >> h;
		cout << "Insira o minuto do compromisso:" << endl;
		cin >> min;
	}
	cout << "Insira o compromisso:" << endl;
	cin >> s;
	insere_compromisso(h, min, d - 1, s, aux);
}

void fecha_agenda(agenda *a)
{
	ofstream arquivo;
	arquivo.open("agenda");
	mes *aux = a->inicial;
	compromisso *aux1;
	while (aux != nullptr)
	{
		arquivo << aux->d << endl;
		for (int j = 0; j < aux->t; j++)
		{
			aux1 = aux->tabela[j].inicial;
			while (aux1 != nullptr)
			{
				arquivo << aux1->h << " " << aux1->min << endl;
				arquivo << aux1->s << endl;
				aux1 = aux1->p;
			}
		}
		aux = aux->p;
	}
	arquivo.close();
}

void destroi_compromissos(dia *d)
{
	compromisso *aux = d->inicial;
	while (aux != nullptr)
	{
		d->inicial = d->inicial->p;
		delete aux;
		aux = d->inicial;
	}
}

void destroi_agenda(agenda *a)
{
	mes *aux = a->inicial;
	while (aux != nullptr)
	{
		a->inicial = a->inicial->p;
		for (int i = 0; i < aux->t; i++)
		{
			destroi_compromissos(&aux->tabela[i]);
		}
		delete[] aux->tabela;
		delete aux;
		aux = a->inicial;
	}
	delete a;
}