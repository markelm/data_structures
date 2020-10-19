/**
 * @author      : Guilherme Wachs Lopes (gwachs@fei.edu.br)
 * @file        : les
 * @created     : quarta ago 26, 2020 21:44:01 -03
 */

#include <iostream>
using std::cout;
using std::endl;


// Tipo abstrato de dados
class AbstractOrderedList {
public:
  AbstractOrderedList () {
  }

  virtual bool insert (int value) = 0;
  virtual bool remove (int value) = 0;
  virtual bool search (int value) = 0;
  virtual int getAtIndex (int index) = 0;
  virtual unsigned int getSize () = 0;

  virtual void print () {
    for (int i = 0; i < getSize (); i++) {
      cout << getAtIndex (i) << " ";
    }
    cout << endl;
  }


  virtual ~AbstractOrderedList () {
  }
};

#define MAX 200

class LES : public AbstractOrderedList {
private:
  unsigned int n;
  int v[MAX];

public:
  LES () {
    n = 0;
  }

  bool insert (int value) {
    if (n == MAX)
      return false;

    int i;
    for (i = 0; i < n && v[i] <= value; i++)
      ;

    for (int j = n; j > i; j--) {
      v[j] = v[j - 1];
    }

    v[i] = value;
    n++;
    return true;
  }
  bool remove (int value) {
    //IMPLEMENTAR
    if(n == 0){
        return false;
    }
    else{
        while(v[n - 1] == value && n >= 0){
            n--;
        }
        bool check = this->search(value);
        while(check == true){
            int i;
            for(i = 0; v[i] != value; i++);
            for(int j = i; j < n-1; j++){
                v[j] = v[j + 1];
                }
            n--;
            check = this->search(value);
            }
        }
    return true;
  }
  bool search (int value) {
    //IMPLEMENTAR
    // Binária
    
    int l = 0;
    int h = n-1;
    int mid;
    while(l <= h){
        mid = (l + h)/2;
        if(value == v[mid]){
            return true;
        }
        if(value < v[mid]){
            h = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return false;
  }
  int getAtIndex (int index) {
    if (index < n && index >= 0)
      return v[index];

    return 0;
  }
  unsigned int getSize () {
    return n;
  }

  virtual ~LES () {
  }
};


int main () {
    //NÃO ALTERE O MAIN
  AbstractOrderedList* l = new LES ();

  cout << (l->remove (0) ? "removi 0" : "nao removi") << endl;
  l->insert (5);
  l->insert (85);
  l->insert (69);
  l->remove (5);
  l->insert (84);
  l->insert (83);
  cout << (l->remove (84) ? "removi 84" : "nao removi") << endl;
  l->print ();
  cout << (l->remove (83) ? "removi 83" : "nao removi") << endl;
  l->print ();
  l->insert (38);
  cout << l->search (85) << endl;
  cout << l->search (86) << endl;
  l->insert (856);
  l->insert (846);
  l->print ();
  cout << (l->remove (856) ? "removi 856" : "nao removi") << endl;
  l->print ();
  l->insert (390);
  l->print ();
  cout << (l->remove (390) ? "removi 390" : "nao removi") << endl;
  l->print ();
  cout << l->search (9000) << endl;

  delete l;

  return 0;
}

