#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
      Matrix():hRows(NULL),hColumns(NULL),columns(0),rows(0){};

     Matrix(int sizeX, int sizeY):rows(sizeX),columns(sizeY)
     {
         Node<T>* row = new Node<T>(0,0,sizeX-1,NULL,NULL);
         Node<T>* column = new Node<T>(0,0,sizeY-1,NULL,NULL);

         for(int i = 0; i < rows-1;i++)
         {
             Node<T>* temp1 = row;
             row = new Node<T>(rows,columns,rows-2-i,NULL,temp1);
         }
         hRows = row;

         for(int i = 0; i < columns-1;i++)
         {
             Node<T>* temp1 = column;
             column = new Node<T>(rows,columns,columns-2-i,temp1,NULL);
         }
         hColumns = column;
     }

     void set(int x, int y, T data)
     {
         Node<T>* row = hRows;
         Node<T>* column = hColumns;

         if(x<0 || x > rows || y<0 || y > columns)
             throw "out of range";

         while(row->data != x)
             row = row->down;

         while(column->data != y)
             column = column->next;

         Node<T>* tmp = column;
         Node<T>* tmp2;
         if(!row->next)
         {
             if(data == 0) return;

             else if(!(column->down))
             {
                 Node<T>* temp1 = new Node<T>(x,y,data,NULL,NULL);
                 row->next = temp1;
                 column->down = temp1;
             }
             else
             {
                 while(tmp->down)
                 {
                     tmp2 = tmp;
                     tmp = tmp->down;

                     if(tmp->x > x)
                     {
                         Node<T>* nNode = new Node<T>(x,y,data,NULL,tmp);
                         tmp2->down = nNode;
                         row->next = nNode;
                         return;
                     }
                 }
                 Node<T>* nNode = new Node<T>(x,y,data,NULL,NULL);
                 tmp->down = nNode;
                 row->next = nNode;
             }

         }
         else
         {
             Node<T>* tmp1 = row;
             Node<T>* tmp3;
             while(tmp1->next != NULL)
             {
                 tmp3 = tmp1;
                 tmp1 = tmp1->next;
                 if(tmp1->y == y)
                 {
                     if(data == 0)
                     {
                         while(tmp->down)
                         {
                             tmp2 = tmp;
                             tmp = tmp->down;
                             if(tmp->x == x) break;
                         }
                         tmp2->down = tmp->down;
                         tmp3->next = tmp1->next;
                         delete tmp1;
                     }
                     else{
                         tmp1->data = data;
                     }
                     return;
                 }
                 if(tmp1->y > y)
                 {
                     if(data == 0) return;

                     Node<T>* nNode = new Node<T>(x,y,data,tmp1,NULL);
                     tmp3->next = nNode;

                     if(!(column->down)) column->down = nNode;

                     while(tmp->down)
                     {
                         tmp2 = tmp;
                         tmp = tmp->down;

                         if(tmp->x > x)
                         {
                             tmp2->down = nNode;
                             nNode->down = tmp;
                             return;
                         }
                     }
                     tmp->down = nNode;
                     return;
                 }
             }

             if(data == 0) return;

             Node<T>* nNode = new Node<T>(x,y,data,NULL,NULL);
             tmp1->next = nNode;
             if(!(column->down))
             {
                 column->down = nNode;
                 return;
             }

             while(tmp->down)
             {
                 tmp2 = tmp;
                 tmp = tmp->down;

                 if(tmp->x > x)
                 {
                     tmp2->down = nNode;
                     nNode->down = tmp;
                     return;
                 }
             }
             tmp->down = nNode;
         }
     }

     T operator()(int x, int y)
     {
       if(x<0 || x > rows || y<0 || y > columns)
           throw "out of range";

         Node<T>* row = hRows;

         while(row->data != x)
             row = row->down;

         Node<T>* temp = row;
         while(temp->next)
         {
             temp = temp->next;
             if(temp->y == y)
                 return temp->data;
             else if(temp->y > y)
                 return 0;
         }
         return 0;
     }

     Matrix<T> operator*(Matrix<T> other){
         if(columns != other.rows)
             throw "size error";

         Matrix result(rows,other.columns);
         int sum;
         for (int i = 0; i < rows; ++i)
         {
             for (int j = 0; j < other.columns; ++j)
             {
                 sum = 0;
                 for (int k = 0; k < columns ; ++k)
                 {
                     sum += (*this)(i,k)*other(k,j);
                 }
                 result.set(i,j,sum);
             }
         }
         return result;
     }

     Matrix<T> operator*(T scalar){
         Matrix result(rows, columns);
         Node<T>* row = hRows;
         Node<T>* temp;
         for (int i = 0; i < rows; ++i)
         {
             temp = row->next;
             while(temp != NULL)
             {
                 result.set(temp->x,temp->y,temp->data*scalar);
                 temp = temp->next;
             }
             row = row->down;
         }
         return result;
     }

     Matrix<T> operator+(Matrix<T> other){
         if(rows != other.rows || columns != other.columns)
             throw "size error";

         Matrix result(rows,columns);
         result = other;

         Node<T>* row = hRows;
         Node<T>* temp;
         for(int i = 0; i < rows;i++)
         {
             temp = row->next;
             while(temp)
             {
                 result.set(temp->x,temp->y,temp->data + result(temp->x,temp->y));
                 temp = temp->next;
             }
             row = row->down;
         }
         return result;
     }

     Matrix<T> operator-(Matrix<T> other){
         if (rows != other.rows || columns != other.columns)
             throw "size error";

         Matrix result(rows,columns);
         result = *this;

         Node<T>* row = other.hRows;
         Node<T>* temp;
         for (int i = 0; i < rows; ++i)
         {
             temp = row->next;
             while(temp)
             {
                 result.set(temp->x,temp->y,result(temp->x,temp->y)-temp->data);
                 temp = temp->next;
             }
             row = row->down;
         }
         return result;
     }

     Matrix<T> transposed(){
         Matrix a(columns, rows);
         Node<T>* row = hRows;
         Node<T>* temp;
         for (int i = 0; i < rows; ++i)
         {
             temp = row->next;
             while(temp)
             {
                 a.set(temp->y,temp->x,temp->data);
                 temp = temp->next;
             }
             row = row->down;
         }
         return a;

     }

     Matrix<T> operator=(Matrix<T> other)
     {
         Node<T>* row = hRows;
         Node<T>* temp;
         Node<T>* temp1;

         if(rows != other.rows || columns != other.columns)
             throw "size error";

         for(int i = 0; i < rows;i++)
         {
             temp = row->next;
             while(temp)
             {
                 temp1 = temp;
                 temp = temp->next;
                 delete temp1;
             }
             row = row->down;
         }

         row = other.hRows;
         for(int i = 0; i < other.rows;i++)
         {
             temp = row->next;
             while(temp)
             {
                 set(temp->x,temp->y,temp->data);
                 temp = temp->next;
             }
             row = row->down;
         }
         return *this;
     }
     void print(){
           for(int i=0;i<rows;i++){
               for(int j=0;j<columns;j++){
                   cout <<(*this)(i,j)<<" ";
               }
               cout<<endl;
           }
       }
     ~Matrix(){
       // delete hRows;
       // delete hColumns;
     }
};

#endif
