/**
 * @author      : Guilherme Wachs Lopes (gwachs@fei.edu.br)
 * @file        : main
 * @created     : quinta out 22, 2020 21:11:06 -03
 */

#include <iomanip>
#include <iostream>
#include <vector>


using namespace std;

template <typename T>
class Tree;

template <typename T>
class Node {
private:
  Node<T>* father;
  Node<T>* left;
  Node<T>* right;
  T value;
  int height;


public:
  T getValue () {
    return value;
  }
  Node () : father (nullptr), left (nullptr), right (nullptr), height (0) {
    value = T{};
  }
  Node (T value) : father (nullptr), left (nullptr), right (nullptr), value (value), height(0) {
  }

  friend class Tree<T>;
};

template <typename T>
class Tree {
private:
  Node<T>* root;
  int n;

  void print (Node<T>* x) {
    if (!x)
      return;

    print (x->left);
    cout << x->value << "\n";
    print (x->right);
  }

  void deleteSubTree (Node<T>* r) {
    if (!r)
      return;

    deleteSubTree (r->left);
    deleteSubTree (r->right);
    delete r;
  }


  int child (Node<T>* n) {
    return (n->left != nullptr) + (n->right != nullptr);
  }

  Node<T>** fromParent (Node<T>* child) {
    if (child && child->father) {
      if (child->father->left == child)
        return &(child->father->left);
      else
        return &(child->father->right);
    }
    return nullptr;
  }

  Node<T>* sucessor (Node<T>* node) {
    node = node->right;
    while (node && node->left) {
      node = node->left;
    }
    return node;
  }

  bool remove (Node<T>* node) {
    if (!node)
      return false;

    Node<T>* father = node->father;

    if (child (node) == 0) {
      if (fromParent (node))
        *fromParent (node) = nullptr;
      else
        root = nullptr;

      delete node;
      n--;

      return true;
    } else if (child (node) == 1) {
      Node<T>* son = node->left;
      if (!son)
        son = node->right;

      son->father = node->father;
      if (fromParent (node)) {
        *fromParent (node) = son;
      } else {
        root = son;
      }
      delete node;
      n--;

      return true;
    } else {
      Node<T>* s = sucessor (node);
      node->value = s->value;
      return remove (s);
    }

    //NÃO PRECISA ADAPTAR PARA O BALANCEAMENTO (SERÁ O PRÓXIMO LAB)
  }


  void printDeitada (Node<T>* n, int nivel = 0) {
    //NÃO ALTERAR!
    if (!n)
      return;

    printDeitada (n->right, nivel + 1);

    for (int i = 0; i < nivel; i++) {
      cout << "     ";
    }
    cout << "    /" << endl;
    for (int i = 0; i < nivel; i++) {
      cout << "     ";
    }
    cout << setw (4) << n->getValue () << "(" << n->height << ")[" << BalanceFactor(n) << "]" << setw (0) << endl;
    for (int i = 0; i < nivel; i++) {
      cout << "     ";
    }
    cout << "    \\" << endl;

    printDeitada (n->left, nivel + 1);
  }

  void updateHeight(Node<T>* n){
    while(n){
      int e = -1;
      if(n->left)
        e = n->left->height;
      
      int d = -1;
      if(n->right)
        d = n->right->height;

      n->height = ((e > d) ? e : d) + 1;

      n = n->father;
    }
  }

public:
  Tree () : root (nullptr), n (0) {
  }

  bool insert (T value) {
    Node<T>* novo = new Node<T> (value);
    if (!novo)
      return false;

    if (!root) {
      root = novo;
      n++;
      return true;
    }

    Node<T>* atual = root;
    Node<T>* anterior = nullptr;

    while (atual) {
      anterior = atual;

      if (value <= atual->value)
        atual = atual->left;
      else
        atual = atual->right;
    }

    novo->father = anterior;
    if (value <= anterior->value)
      anterior->left = novo;
    else
      anterior->right = novo;

    n++;


    //ATUALIZAR PARA CHAMAR O BALANCEAMENTO
    updateHeight(novo->father);
    novo=novo->father;
    while(novo){
      Balance(novo);
      novo = novo->father;
    }

    return true;
  }

  Node<T>* search (T value) {
    Node<T>* atual = root;
    while (atual) {
      if (value < atual->value)
        atual = atual->left;
      else if (value > atual->value)
        atual = atual->right;
      else
        return atual;
    }
    return nullptr;
  }

  void print () {
    print (root);
  }

  void printDeitada () {
    //NÃO ALTERAR!
    cout << "=====================================================" << endl;
    printDeitada (root);
    cout << "=====================================================" << endl;
  }

  bool remove (T value) {
    return remove (search (value));
  }

  void LeftRotate (Node<T>* X) {
    // IMPLEMENTAR
    Node<T>* Y = X->right;
    Node<T>* tmp = X->right->left;
    Node<T>* Father = X->father;

    X->right = tmp;
    if(tmp)
	    tmp->father = X;
    Y->left = X;
    X->father = Y;
    Y->father = Father;
    if(Father){
    	if(Y->value > Father->value)
		Father->right = Y;
	else
		Father->left = Y;
    }
    else
	    root = Y;
    updateHeight(X);

    
  }

  void RightRotate (Node<T>* X) {
    // IMPLEMENTAR
   
    Node<T>* Y = X->left;
    Node<T>* tmp = X->left->right;
    Node<T>* Father = X->father;

    X->left = tmp;
    if(tmp)
	    tmp->father = X;
    Y->right = X;
    X->father = Y;
    Y->father = Father;
    if(Father){
    	if(Y->value > Father->value)
		Father->right = Y;
	else
		Father->left = Y;
    }
    else
	    root = Y;
    updateHeight(X);
    
  }

  int BalanceFactor (Node<T>* node) {
    int r = node->right ? node->right->height : -1;
    int l = node->left ? node->left->height : -1;
    return r - l;
  }

  void Balance(Node<T>* node){
    //IMPLEMENTAR

    while(node){

    	int b = BalanceFactor(node);
	if(b <= -2){
	    	if(BalanceFactor(node->left) > 0)
	    		LeftRotate(node->left);
		RightRotate(node);
	}
	else if(b >= 2){
		if(BalanceFactor(node->right) < 0)
			RightRotate(node->right);
		LeftRotate(node);
	}
	node = node->father;
    }

  }

  ~Tree () {
    deleteSubTree (root);
  }

};

int main () {
  Tree<int> v;
  v.insert (50);
  v.insert (70);
  v.insert (80);
  v.insert (40);
  v.insert (55);
  v.insert (52);
  v.printDeitada ();
  cout << endl;
  v.insert (75);
  v.insert (59);
  v.insert (82);
  v.insert (99);
  v.insert (22);
  v.insert (77);
  v.insert (86);
  v.insert (91);
  v.insert (29);
  v.printDeitada ();
  cout << endl;
  v.insert (37);
  v.insert (96);
  v.insert (52);
  v.insert (2);
  v.insert (69);
  v.insert (23);
  v.insert (27);
  v.insert (13);
  v.insert (43);
  v.insert (21);
  v.insert (31);
  v.insert (53);


  v.printDeitada ();
  cout << endl;

  return 0;
}
