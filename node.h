#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {
  public:
    T data;
    int x, y;
    Node* next;
    Node* down;
    Node(): next(NULL), down(NULL),x(0),y(0),data(0){};
    Node(T data,Node* next = NULL, Node* down = NULL):
		data(data),next(next),down(down) {};

    Node(int x,int y,T data = 0,Node* next = NULL, Node* down = NULL):
		x(x),y(y),data(data),next(next),down(down) {};

    void set(int x, int y, T data){
        this->x=x;
        this->y=y;
        this->data=data;
    };

    T get(){
      return data;
    };
};

#endif
