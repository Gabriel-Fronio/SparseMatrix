#include <iostream>
#include <stdlib.h>

#include "..\headers\SparseMatrix.hpp"

using namespace std;

int main()
{
  cout << "Digite o valor padrao da matriz:";

  int defaultValue;
  cin >> defaultValue;

  SparseMatrix<int>* matrix = new SparseMatrix<int>(defaultValue);

  while (true) {

    system("cls");
    cout << "Digite o numero de uma opcao:" << endl;

    cout << "1) Inserir" << endl;
    cout << "2) Consultar" << endl;
    cout << "3) Ver a matriz" <<endl;
    cout << "4) Sair" << endl << endl;

    int option;
    cin >> option;

    switch (option) {
      case 1:
      {
        cout << "Digite o valor que deseja inserir: ";
        int insertedValue;
        cin >> insertedValue;
        cout << endl << endl;

        cout << "Digite a linha em que deseja inserir o valor: ";
        int row;
        cin >> row;
        cout << endl;

        cout << "Digite a coluna em que deseja inserir o valor: ";
        int col;
        cin >> col;
        cout << endl;

        if(col < 0 || row < 0)
        {
          cout << "Coluna e linha devem ser maiores ou iguais a 0";
          break;
        }

        matrix->addElement(insertedValue, row, col);
        cout << "Valor inserido com sucesso" << endl << endl;
        cout << *matrix;
        break;
      }

      case 2:
      {
        cout << "Digite a linha que deseja consultar: ";
        int row;
        cin >> row;
        cout << endl;

        cout << "Digite a coluna que deseja consultar: ";
        int col;
        cin >> col;
        cout << endl;

        if(col < 0 || row < 0)
        {
          cout << "Coluna e linha devem ser maiores ou iguais a 0";
          break;
        }
        int foundValue = matrix->getInfo(row, col);

        cout << endl << endl;
        cout << foundValue;

        break;
      }

      case 3:
        cout << endl << endl;
        cout << *matrix;
        break;
      case 4:
        exit(0);
        break;
      default:
        cout << "Digite uma opcao valida";
    }
    cout << endl << endl;
    cout << "Pressione [enter] para continuar...";
    cin.sync();
    cin.ignore();
  }
}
