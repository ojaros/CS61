/*
Priority Queue ADT
gives operations for the priority queue to insert, return min element, etc
*/
#ifndef PQ_H
#define PQ_H

#include <iostream>



template<class Item, class Compare = std::less<Item> >
class MinPQ{
  //std::vector<Item> pq;
  Item *pq; //pointer to array of elements in heap ITEM MUST BE ARRAY
  int n; // number of elements in heap

//exchange function
  /*void exch(int i, int j){
    Item t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
  }
  */

  void exch(Item *x, Item *y){
    Item temp = *x;
    *x = *y;
    *y = temp;
  }

  // parent and children of a node
  int parent(int i){
    return (i-1)/2;
  }
  int left(int i){
    return (2*i+1);
  }
  int right(int i){
    return (2*i+2);
  }

  void swim(int k){
    while (k > 1 && pq[k/2] > pq[k]){
      exch(&pq[k/2], &pq[k]);
      k = k/2;
    }
  }

  void sink(int k, int n){
    while(2*k <= n){
      int j = 2*k;
      if (j < n && pq[j] > pq[j+1]){
        j++;
      }
      if (pq[k] < pq[j]){
        break;
      }
      exch(&pq[k], &pq[j]);
      k = j;
    }
  }

public:
  MinPQ(){
    int n = 0;
    pq = new Item[0];
  }

  MinPQ(int capacity){
    n = 0;
    pq = new Item[capacity];
  }

/*
  void insert(Item v){
    //pq[++n] = v;
    n++;
    int i = n-1;
    pq[i] = v;


    while (i != 0 && pq[parent(i)] > pq[i]){
      //exch(i, parent(i));
      exch(&pq[i], &pq[parent(i)]);
      i = parent(i);
    }
  }
  */


//deletes min and returns
  Item delMin(){
    if (n <= 0){
      //return;
    }
    if (n == 1){
      n--;
      return pq[0];
    }
    //store root, remove
    Item root = pq[0];
    pq[0] = pq[n-1];
    n--;
    minHeapify(0);
    return root;
  }



  void insert(Item v){
    n++;
    int i = n-1;
    pq[i] = v;
    swim(i);
  }

/*
  Item delMin(){
    Item max = pq[0];
    exch(&pq[0], &pq[n-1]);
    sink(0, n);
    n--;
    return max;
  }
  */


  bool empty(){
    return n == 0;
  }

  Item peak(){
    //minHeapify(0);
    return pq[0];
  }


  unsigned int size(){
    return n;
  }

//used if the heap is out of order, restores to minheap
    void minHeapify(int i){
      int l = left(i);
      int r = right(i);
      int small = i;
      if (l < n && pq[l] < pq[i]){
        small = l;
      }
      if (r < n && pq[r] < pq[small]){
        small = r;
      }
      if (small != i){
        //exch(i, small);
        exch(&pq[i], &pq[small]);
        minHeapify(small);
      }
    }
 };

 #endif
