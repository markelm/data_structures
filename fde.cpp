/**
 * @author      : Guilherme Wachs Lopes (gwachs@fei.edu.br)
 * @file        : LDE
 * @created     : quinta ago 27, 2020 22:58:52 -03
 */

// _________________________
/// Alterar apenas a Classe \
//\ LinkedQueue             /
// -------------------------
//        \   ^__^
//         \  (oo)\_______
//            (__)\       )\/\
//                ||----w |
//                ||     ||
//
//
#include <cstdlib>
#include <iostream>
#include <new>
#include <set>


using std::cout;
using std::endl;

template <typename T>
class AbstractQueue {
public:
  virtual bool enqueue (T value) = 0;
  virtual bool dequeue (T* outElement = nullptr) = 0;
  virtual void clear () = 0;
  virtual ~AbstractQueue () {
  }
};

template <typename T>
class LinkedQueue;

template <typename T>
class QueueNode {
private:
  int value;
  QueueNode* next;
  friend class LinkedQueue<T>;

public:
  static std::set<void*> allocs;
  ~QueueNode () {
  }
  void* operator new (size_t n) {
    void* x = malloc (n);
    allocs.insert (x);
    return x;
  }

  void operator delete (void* p) {
    if (allocs.erase (p) == 0) {
      cout << "ERRO DE DESALOCACAO" << endl;
    };
    free (p);
  }
};

template <typename T>
std::set<void*> QueueNode<T>::allocs;

template <typename T>
class LinkedQueue : public AbstractQueue<T> {
private:
  QueueNode<T>* first;
  QueueNode<T>* last;
  int n;

public:
  LinkedQueue () {
    first = nullptr;
    last = nullptr;
    n = 0;
  }


  // Construtor por cópia (l chega como other)
  LinkedQueue (const LinkedQueue& other) {
    // IMPLEMENTAR
    copy(other);
  }

  void copy (const LinkedQueue& other) {
    // IMPLEMENTAR
    QueueNode<T>* novo;
    first = nullptr;
    last = nullptr;
    QueueNode<T>* ptrAtualOther = other.first;
    while (ptrAtualOther) {
      QueueNode<T>* novo = new QueueNode<T>;
      novo->value = ptrAtualOther->value;
      novo->next = nullptr;
      if (!first) {
        first = novo;
        last = novo;
      } else {
        last->next = novo;
        last = novo;
      }
      ptrAtualOther = ptrAtualOther->next;
    }
    n = other.n;
  }

  LinkedQueue& operator= (const LinkedQueue& other) {
    // IMPLEMENTAR
    clear();
    copy(other);
    return *this;
  }

  bool enqueue (T value) {
    // IMPLEMENTAR
    QueueNode<T>* novo = new QueueNode<T>;
    novo->value = value;
    novo->next = nullptr;
    if(last){
    	last->next = novo;
	last = novo;
    }
    else{
	first = novo;
	last = novo;
	
    }
    n++;
    return true;

  }

  bool dequeue (T* outElement = nullptr) {
    // IMPLEMENTAR
    if(first == nullptr){
    	return false;
    }
    if(first == last){
	*outElement = first->value;
	delete first;
	first = last = nullptr;
	n--;
	return true;
    }
    else{
	QueueNode<T>* tmp = first;
	*outElement = first->value;
	first = first->next;
	delete tmp;
	n--;
    	return true;
    }
    
  }

  virtual void print () const {
    QueueNode<T>* tmp = first;
    while (tmp) {
      cout << tmp->value << " ";
      tmp = tmp->next;
    }
    cout << endl;
  }

  unsigned int getSize () {
    return n;
  }

  void clear () {
    // IMPLEMENTAR
    QueueNode<T>* tmp = first;
    QueueNode<T>* tmpNext;
    while (tmp) {
      tmpNext = tmp->next;
      delete tmp;
      n--;
      tmp = tmpNext;
    }
    first = nullptr;
    last = nullptr;
  }

  ~LinkedQueue () {
    cout << "destrutor invocado" << endl;
    clear ();
  }
};


int main () {
  // NÃO ALTERAR O MAIN
  {
    LinkedQueue<int> l;
    int temp;
    cout << "==========TESTE 1==========" << endl;

    l.enqueue (5);
    l.enqueue (6);
    cout << "Tamanho: " << l.getSize () << endl;

    {
      cout << "==========TESTE 2==========" << endl;
      cout << "Construtor por copia sera invocado" << endl;
      LinkedQueue<int> l2 = l;
      l2.enqueue (10);
      l2.enqueue (11);
      l2.enqueue (15);
      int temp;
      while (l2.dequeue (&temp)) {
        cout << "Removido de l2 " << temp << endl;
      }
      l2.enqueue (13);
      l2.enqueue (19);
      cout << "imprimindo l2:" << endl;
      l2.print ();
      l2.clear ();
      cout << "imprimindo l2:" << endl;
      l2.print ();
    }
    cout << "==========TESTE 2 acabou===" << endl;

    {
      cout << "==========TESTE 3==========" << endl;
      LinkedQueue<int> l3;
      cout << "Atribuicao por copia sera invocado" << endl;
      l3 = l;
      l3.enqueue (50);
      l3.enqueue (51);
      l3.enqueue (55);
      int temp;
      while (l3.dequeue (&temp)) {
        cout << "Removido de l3 " << temp << endl;
      }
      l3.enqueue (53);
      l3.enqueue (59);
      cout << "imprimindo l3:" << endl;
      l3.print ();
      l3.clear ();
      cout << "imprimindo l3:" << endl;
      l3.print ();
      cout << "==========TESTE 3 acabou===" << endl;
    }

    cout << "imprimindo l:" << endl;
    l.print ();

    l.enqueue (4);
    l.dequeue (&temp);
    cout << temp << endl;
    l.enqueue (8);

    l.print ();
  }

  if (QueueNode<int>::allocs.size ())
    cout << "Existem nos alocados" << endl;
  cout << "==========TESTE 1 acabou===" << endl;

  return 0;
}
