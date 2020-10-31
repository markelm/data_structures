/**
 * @author      : Guilherme Wachs Lopes (gwachs@fei.edu.br)
 * @file        : main
 * @created     : quinta out 22, 2020 21:11:06 -03
 */

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


public:
  T getValue () {
    return value;
  }
  Node () : father (nullptr), left (nullptr), right (nullptr) {
    value = T{};
  }
  Node (T value) : father (nullptr), left (nullptr), right (nullptr), value (value) {
  }

  friend class Tree<T>;
};

template <typename T>
class Tree {
private:
  Node<T>* root;
  int n;

  void deleteSubTree (Node<T>* r) {
    if (!r)
      return;

    deleteSubTree (r->left);
    deleteSubTree (r->right);
    delete r;
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
    //IMPLEMENTAR ESSA FUNÇÃO SEM UTILIZAR RECURSÃO. 
    //A IMPRESSÃO DEVERÁ SER FEITA EM ORDEM CRESCENTE
    //
    	vector<Node<T>*> v;
	Node<T>* current = new Node<T>;
	current = root;
	while(current){
		v.push_back(current);
		current = current->left;
	}
	while(v.size() > 0){
		current = v[v.size()-1];
		v.pop_back();
		cout << current->value << endl;
		if(current->right){
			Node<T>* tmp = current->right;
			while(tmp){
				v.push_back(tmp);
				tmp = tmp->left;
			}
		}

	}
  }

  ~Tree () {
    deleteSubTree (root);
  }
};

int main () {
  Tree<int> v;
  v.insert (315);
  v.insert (25);
  v.insert (325);
  v.insert (962);
  v.insert (687);
  v.insert (778);
  v.insert (695);
  v.insert (245);
  v.insert (299);
  v.insert (135);
  v.insert (50);
  v.insert (307);
  v.insert (640);
  v.insert (564);
  v.insert (222);
  v.insert (913);
  v.insert (105);
  v.insert (279);
  v.insert (45);
  v.insert (826);
  v.insert (75);
  v.insert (495);
  v.insert (962);
  v.insert (913);

  v.print ();

  return 0;
}


