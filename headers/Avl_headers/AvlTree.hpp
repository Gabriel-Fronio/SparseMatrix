#ifndef AvlTreeClass

#define AvlTreeClass

#include "Node.hpp"
#include <stdio.h>
#include <string>
using std::string;

template <class T>
class AvlTree
{
  
    private:
    Node<T> *root;

    public:
    AvlTree() {};

    AvlTree(Node<T> *newRoot)
    {
      this->root = newRoot;
    };

    Node<T>* getRoot() const
    {
      return this->root;
    };

    void addInfo(T info)
    {
      
      if (findInfo(info) != nullptr)
        return;

      Node<T> *curr = this->root;
      while (curr != nullptr)
      {
        if (info > curr->getInfo())
        {
          if (curr->getRight() != nullptr)
            curr = curr->getRight();
          else
          {
            curr->setRight(new Node<T>(info));
            break;
          }
        }
        else
        {
          if (curr->getLeft() != nullptr)
            curr = curr->getLeft();
          else
          {
            curr->setLeft(new Node<T>(info));
            break;
          }
        }
      }

      if (this->root == nullptr)
        this->root = new Node<T>(info);
      else{
        Node<T>* balancedTree = this->balanceTree(this->root);
        if(balancedTree != nullptr)
          this->root = balancedTree;
      }
    };

    void deleteInfo(T info)
    {
      if (findInfo(info) == nullptr)
        return;

      if(info == this->root->getInfo())
      {
        if(this->root->isLeaf())
        {
          //quer dizer que so ha a raiz na arvore, remove a raiz e continua
          this->root = nullptr;
          return;
        }
        else
        {
          if(this->root->getLeft() != nullptr)
          {
            if(this->root->getRight() == nullptr)
            {
              this->root = this->root->getLeft();
              return;
            }

            if(this->root->getLeft()->isLeaf() || this->root->getLeft()->getRight() == nullptr)
            {
              this->root->getLeft()->setRight(this->root->getRight());
              this->root = this->root->getLeft();
              return;
            }
            
            Node<T>* toReplace = this->biggerNodeOnSubtree(this->root->getLeft());// no a ser excluido para q esse entre no lugar do no
            // acha o pai de toReplace
            Node<T>* parent = this->root;
            while(parent != nullptr)
            {
              if(parent->getInfo() < toReplace->getInfo())
              {
                if(parent->getRight()->getInfo() == toReplace->getInfo())
                  break;
                parent = parent->getRight();
              }
              else
              {
                if(parent->getLeft()->getInfo() == toReplace->getInfo())
                  break;
                parent = parent->getLeft();
              }
            }
            // como toReplace eh a maior info, nao tem filho a direita e parent so pode apontar para ele a direita
            parent->setRight(toReplace->getLeft()); // conserva o filho esquerdo de toReplace

            toReplace->setRight(this->root->getRight());
            toReplace->setLeft(this->root->getLeft());
            this->root = toReplace;
            return;
          }
          else
          {
            this->root = this->root->getRight();
            return;
          }
        }
      }

      Node<T> *curr = this->root;
      Node<T> *currParent = curr;
      while (curr->getInfo() != info)
      {
        if (curr->getInfo() < info)
        {
          if (curr->getRight()->isLeaf())
          {
            curr->setRight(nullptr);
            return;
          }
          currParent = curr;
          curr = curr->getRight();
        }
        else
        {
          if (curr->getLeft()->isLeaf())
          {
            curr->setLeft(nullptr);
            return;
          }
          currParent = curr;
          curr = curr->getLeft();
        }
      }

      if (curr->getLeft() != nullptr)
      {
        // se a esquerda de curr for uma folha ou n tiver o no a sua direita, so troca curr pela sua esquerda
        if(curr->getLeft()->isLeaf() || curr->getLeft()->getRight() == nullptr)
        {
          if (currParent->getLeft() == curr)
          {
            currParent->getLeft()->getLeft()->setRight(curr->getRight());
            currParent->setLeft(curr->getLeft());
            return;
          }
          else
          {
            currParent->getRight()->getLeft()->setRight(curr->getRight());
            currParent->setRight(curr->getLeft());
            return;
          }
        }

        // acha o maior no na subarvore iniciada a esquerda do no desejado
        Node<T>* toReplace = this->biggerNodeOnSubtree(curr->getLeft());// no a ser excluido para q esse entre no lugar do no
        Node<T>* parent = this->root; // no auxiliar para achar pai do 'toReplace'
        // acha o pai de toReplace
        while(parent != nullptr)
        {
          if(parent->getInfo() < toReplace->getInfo())
          {
            if(parent->getRight()->getInfo() == toReplace->getInfo())
              break;
            parent = parent->getRight();
          }
          else
          {
            if(parent->getLeft()->getInfo() == toReplace->getInfo())
              break;
            parent = parent->getLeft();
          }
        }
        //toReplace vai estar com certeza a direita de parent (por ser o maior no da subarvore)
        parent->setRight(toReplace->getLeft()); // seta o filho de toReplace no lugar dele, tirando as refs a ele

        //conserva os filhos do no a ser excluido
        toReplace->setLeft(curr->getLeft());
        toReplace->setRight(curr->getRight());
        if (currParent->getLeft() == curr)
          currParent->setLeft(toReplace);
        else
          currParent->setRight(toReplace);
      }
      else // curr so tem um filho (da direita), fazendo com que nao se perca nenhuma info
      {
        if (currParent->getLeft() == curr)
          currParent->setLeft(curr->getRight());
        else
          currParent->setRight(curr->getRight());
      }

      Node<T>* balancedTree = this->balanceTree(this->root);
      if(balancedTree != nullptr)
        this->root = balancedTree;
    };

    T* findInfo(T info) const
    {
      Node<T> *curr = this->root;
      while (curr != nullptr)
      {
        if (curr->getInfo() == info) {
          T ret = curr->getInfo();
          T* retPointer = &ret;
          return retPointer;
        }
        if (curr->getInfo() > info)
          curr = curr->getLeft();
        else
          curr = curr->getRight();
      }
      return nullptr;
    };

    Node<T>* balanceTree(Node<T> *root)
    {
      Node<T>* aux = root;
      if(root->getLeft() != nullptr)
      {
        aux = this->balanceTree(root->getLeft());
        if(aux != nullptr)
          root->setLeft(aux);
      }
      if(root->getRight() != nullptr)
      {
        aux = this->balanceTree(root->getRight());
        if(aux != nullptr)
          root->setRight(aux);
      }
      return root->balance();
    };

    Node<T>* biggerNodeOnSubtree(Node<T>* subtree)
    {
      while(subtree->getRight() != nullptr)
        subtree = subtree->getRight();
      return subtree;
    };

    friend std::ostream &operator<<(std::ostream &stream, const AvlTree &tree)
    {
      AvlTree *subtree = nullptr;

      if(tree.getRoot() == nullptr)
      {
        stream << "()";
        return stream;
      }

      stream << "(";
      if (tree.getRoot()->getLeft() != nullptr)
      {
        subtree = new AvlTree(tree.getRoot()->getLeft());
        stream << *subtree;
      }

      stream << tree.getRoot()->getInfo();

      if (tree.getRoot()->getRight() != nullptr)
      {
        subtree = new AvlTree(tree.getRoot()->getRight());
        stream << *subtree;
      }
      stream << ")";
      return stream;
    };

    bool operator==(const AvlTree& other)
    {
      return (this->compareSubTrees(this->root, other.root) == 0);
    };

    bool operator != (const AvlTree& other)
    {
      return (this->compareSubTrees(this->root, other.root) != 0);
    };

    // compara info por info das subarvores com raizes em curr e em other
    // retorna 0 se as subarvores forem iguais, -1 se diferentes
    int compareSubTrees(Node<T>* curr, Node<T>* other)
    {
      if(curr == nullptr && other == nullptr)
        return 0;
      
      // se curr for nulo e other nao (ou vice-versa), sao diferentes
      if( (curr == nullptr && other != nullptr) || (curr != nullptr && other == nullptr) )
        return -1;
      
      if(compareSubTrees(curr->getLeft(), other->getLeft()) != 0)
        return -1;
      
      if(curr->getInfo() != other->getInfo())
        return -1;

      if(compareSubTrees(curr->getRight(), other->getRight()) != 0)
        return -1;
      
      // se as subarvores filhas e a info sao iguais, as subarvores iniciadas em curr e other sao iguais 
      return 0;
    }
};

#endif
