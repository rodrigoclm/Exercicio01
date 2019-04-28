#include "agenda.hpp"

int main()
{
	int opcao = 10;
	agenda *a = nullptr;
	cout << "Seja bem vindo ao sistema de gerenciamento da agenda virtual!" << endl;
	while (opcao != 0)
	{
		cout << "Insira sua opção:\n1. Abrir agenda\n2. Inserir compromisso\n3. Remove compromisso" << endl;
		cout << "4. Lista compromissos\n5. Verifica compromisso\n6. Fecha agenda\n0. Sair" << endl;
		cout << "Insira sua opção e digite enter:" << endl;
		cin >> opcao;
		if (a == nullptr && opcao != 1)
		{
			cout << "A agenda não foi aberta!" << endl;
			continue;
		}
		if(a != nullptr && opcao == 1)
		{
			cout << "Agenda já foi aberta!" << endl;
			continue;
		}
		switch (opcao)
		{
			case 0:
				cout << "Encerrando..." << endl;
				if(a != nullptr){destroi_agenda(a);}
				break;
			case 1:
				a = abre_agenda();
				break;
			case 2:
				leitura_compromisso(a);
				break;
			case 3:
				remove_compromisso(a);
				break;
			case 4:
				lista_compromissos(a);
				break;
			case 5:
				verifica(a);
				break;
			case 6:
				fecha_agenda(a);
				destroi_agenda(a);
				a = nullptr;
				break;
			default:
				cout << "Opção inválida!" << endl;
				break;
		}
	}
	return 0;
}
