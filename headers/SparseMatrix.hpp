#ifndef SPARSE_MATRIX_CLASS

#define SPARSE_MATRIX_CLASS

#include "Avl_headers\AvlTree.hpp"
#include "Avl_headers\Node.hpp"
#include "Element.hpp"

#include "stdio.h"
using std::string;


template <class T>
class SparseMatrix {
  private:
    AvlTree<Element<AvlTree<Element<T>>>>* elements;
    T defaultValue;
    int rowLength;
    int colLength;

  public:
    SparseMatrix()
    {
      this->elements = new AvlTree<Element<AvlTree<Element<T>>>>(nullptr);
      this->rowLength = 0;
      this->colLength = 0;
    };

    SparseMatrix(T def)
    {
      this->elements = new AvlTree<Element<AvlTree<Element<T>>>>(nullptr);
      this->defaultValue = def;
      this->rowLength = 0;
      this->colLength = 0;
    };

    void setDefaultValue(T def)
    {
      this->defaultValue = def;
    };

    int getRowLength() const
    {
      return this->rowLength;
    }

    int getColLength() const
    {
      return this->colLength;
    }

    T getDefaultValue() const
    {
      return this->defaultValue;
    };

    void addElement(T value, int rowNumber, int colNumber)
    {
      if(rowNumber > this->rowLength)
        this->rowLength = rowNumber;
      if(colNumber > this->colLength)
        this->colLength = colNumber;


      T valueInPos = this->getInfo(rowNumber, colNumber);

      if(valueInPos == this->defaultValue)
      {
        if(value == this->defaultValue)
          return;
        
        // findInfo retorna um element q tenha a key igual a linha desejada para a insercao
        Element<AvlTree<Element<T>>>* row = this->elements->findInfo(*new Element<AvlTree<Element<T>>>(*new AvlTree<Element<T>>(nullptr), rowNumber));
        if(row == nullptr)
        {
          // significa q a linha 'rowNumber' nao foi criada ainda em elements
          AvlTree<Element<T>>* cell = new AvlTree<Element<T>>(nullptr);
          cell->addInfo(*new Element<T>(value, colNumber));

          // apos criar uma arvore com as colunas daquela linha, insere um novo element em elements contendo o numero da linha e essa arvore
          this->elements->addInfo(*new Element<AvlTree<Element<T>>>(*cell, rowNumber));
        }
        else
        {
          AvlTree<Element<T>> colTree = row->getValue();
          // se a linha ja estiver criada, adiciona um elemente a ela representando a coluna do valor
          colTree.addInfo(*new Element<T>(value, colNumber));
          row = new Element<AvlTree<Element<T>>>(*new AvlTree<Element<T>>(colTree.getRoot()), rowNumber);
          this->elements->deleteInfo(*row);
          this->elements->addInfo(*row);
        }
      }
      else
      {
        if (valueInPos == value) 
          return;
        else
        {
          AvlTree<Element<T>> colTree = this->elements->findInfo(*new Element<AvlTree<Element<T>>>(*new AvlTree<Element<T>>(nullptr), rowNumber))->getValue();
          colTree.deleteInfo(*new Element<T>(valueInPos, colNumber));
          if(value != this->defaultValue)
            colTree.addInfo(*new Element<T>(value, colNumber));

          this->elements->deleteInfo(*new Element<AvlTree<Element<T>>>(colTree.getRoot(), rowNumber));
          this->elements->addInfo(*new Element<AvlTree<Element<T>>>(colTree.getRoot(), rowNumber));
        }
      }
    };


    T getInfo(int row, int col) const
    {
      Element<AvlTree<Element<T>>>* rowElementPtr = this->elements->findInfo(*new Element<AvlTree<Element<T>>>(*new AvlTree<Element<T>>(nullptr), row));
      if(rowElementPtr == nullptr)
        return this->defaultValue;

      Element<AvlTree<Element<T>>> rowElement = *rowElementPtr;

      Element<T>* colElement = rowElement.getValue().findInfo(*new Element<T>(*new T(), col));
      if(colElement == nullptr)
        return this->defaultValue;

      return colElement->getValue();
    };

    friend std::ostream &operator<<(std::ostream &stream, const SparseMatrix &matrix)
    {
      for(int i=0; i<=matrix.getRowLength(); i++)
      {
        for(int j=0; j<=matrix.getColLength(); j++)
        {
          stream << " " << matrix.getInfo(i, j);
        }
        stream << " \n";
      }
      return stream;
    };
};

#endif
