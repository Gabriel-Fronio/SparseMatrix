#ifndef NodeClass

#define NodeClass

template <class T>
class Node{
    private:
        T info;
        Node<T>* left;
        Node<T>* right;

        Node<T>* rotateLeft() {
            Node<T>* auxNode = this->right->left;
            Node<T>* ret = this->right;
            ret->left = this;
            ret->left->right = auxNode;
            return ret;
        };

        Node<T>* rotateRight() {
            Node<T>* auxNode = this->left->right;
            Node<T>* ret = this->left;
            ret->right = this;
            ret->right->left = auxNode;
            return ret;
        }

        Node<T>* rotateRightLeft() { // rotacao dupla a esquerda
            Node<T>* ret = this;
            ret->setRight(ret->getRight()->rotateRight());
            ret = ret->rotateLeft();
            return ret;
        }

        Node<T>* rotateLeftRight() { // rotacao dupla a direita
            Node<T>* ret = this;
            ret->setLeft(ret->getLeft()->rotateLeft());
            ret = ret->rotateRight();
            return ret;
        }

    public:
        T getInfo() { return this->info; };
        Node<T>* getLeft() { return this->left; };
        Node<T>* getRight() { return this->right; };
        void setRight(Node<T>* newNode) { this->right = newNode; };
        void setLeft(Node<T>* newNode) { this->left = newNode; };

        Node(T info) {
            this->info = info;
            this->left = nullptr;
            this->right = nullptr;
        };

        bool isLeaf() {
            if(this->left == nullptr && this->right == nullptr)
                return true;
            return false;
        }

        int getBalance() {
            if(this->right == nullptr && this->left == nullptr)
                return 0;

            if(this->right == nullptr)
                return 0 - this->left->getHeight();
            if(this->left == nullptr)
                return this->right->getHeight();

            return this->right->getHeight() - this->left->getHeight();
        };

        int getHeight(){
            if(this->left == nullptr && this->right == nullptr)
                return 1;

            int leftHeight = 0;
            int rightHeight = 0;
            if(this->left != nullptr)
                leftHeight = this->left->getHeight() + 1;
            if(this->right != nullptr)
                rightHeight = this->right->getHeight() + 1;

            if(leftHeight > rightHeight)
                return leftHeight;
            return rightHeight;
        };

        Node<T>* balance() {
            if(this->getBalance() > 1)
            {
                if(this->right->getBalance() < 0)
                    return this->rotateRightLeft();
                else
                    return this->rotateLeft();
            }
            else if(this->getBalance() < -1)
            {
                if(this->left->getBalance() > 0)
                    return this->rotateLeftRight();
                else
                    return this->rotateRight();
            }
            else
                return nullptr;
        };
};

#endif
