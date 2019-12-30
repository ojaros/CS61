/*
 * Image Component Labeling
 * Project 1
 * < Oliver Jaros >
 * < Date >
 *
 * Purpose and usage of this application
 *   . . .
 *   . . .
 *
 */


// . . .
// . . .
// . . .


// global variables

/*
 * pixel should be redesigned as an object, instead of int, with two fields,
 * as described in the Assignment Specification document
 */
#include <iostream>
#include <cstdlib>
#include <random>
#include "make2dArray.h"
#include "position.h"
#include "arrayStack.h"
#include "arrayQueue.h"
#include "pixel.h"

struct pixel **pix;
//struct pixel** bfs;
int size;      // number of rows and columns in the image
float density;
arrayStack<position>* path;

// functions
void welcome()
{
   // Optional code goes here
}


void inputImage()
{// Input the image.
  size = 15;
   cout << "Enter image size in between 5 and 20: " << endl;
   cin >> size;

   // create and input the pixel array
   make2dArray(pix, size + 2, size + 2);
   cout << "Enter a density between 0 and 1: " << endl;
   cin >> density;

   //r = ((double)rand()) / RAND_MAX;


   for (int i = 1; i <= size; i++){
      for (int j = 1; j <= size; j++){
          double r = ((double)rand()/(double)RAND_MAX);
          if (r < density){
            pix[i][j].label = 1;
          }
          else{
            pix[i][j].label = 0;
          }

      }
   }
}


void labelComponents()
{// Label the components.
}

void imageBFS(){
   // initialize offsets


   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up

   // initialize wall of 0 pixels
   for (int i = 0; i <= size + 1; i++){
    pix[0][i].label == pix[size + 1][i].label == 0;
    pix[i][0].label == pix[i][size + 1].label == 0;
   }

   int order = 1;
   arrayQueue<position> q;
   position here, nbr;

   int id = 1;  // component id
   int numOfNbrs = 4; // neighbors of a pix position

   for (int r = 1; r <= size; r++) {     // row r of image
      for (int c = 1; c <= size; c++){   // column c of image
        here.row = r;
        here.col = c;
        if (pix[here.row][here.col].label == 1)
        {
          id++;
          order = 1;
          pix[here.row][here.col].label = id;
          pix[here.row][here.col].order = order;


do {

   for (int i = 0; i < numOfNbrs; i++)
   {// check out neighbors of here
      order++;
      nbr.row = here.row + offset[i].row;
      nbr.col = here.col + offset[i].col;
      if (pix[nbr.row][nbr.col].label == 1)
      {// unided nbr, id it
         pix[nbr.row][nbr.col].label = id;
         pix[nbr.row][nbr.col].order = order;
      }
         if (pix[here.row][here.col].label == 0){
           break; // done
         }
         // put on queue for later expansion
         q.push(nbr);
      }

      if (pix[nbr.row][nbr.col].label == 0){
        break;
      }
      if (q.empty()){
        break;
      } // no path
      else {
      here = q.front();         // get next position
      q.pop();
    }
  } while (!q.empty());
 }
}
}
}






//dfs
void imageDFS(){

  position offset[4];
  offset[0].row = 0; offset[0].col = 1;   // right
  offset[1].row = 1; offset[1].col = 0;   // down
  offset[2].row = 0; offset[2].col = -1;  // left
  offset[3].row = -1; offset[3].col = 0;  // up

  // initialize wall of 0 pixels
  for (int i = 0; i <= size + 1; i++){
   pix[0][i].label == pix[size + 1][i].label == 0;
   pix[i][0].label == pix[i][size + 1].label == 0;
  }

  int option = 0; // next move
  int lastOption = 3;
  int id = 1;
  int order = 1;
path = new arrayStack<position>;
position here;

for (int r = 1; r <= size; r++) {     // row r of image
   for (int c = 1; c <= size; c++){
     id++;
here.row = r;
here.col = c;

if (pix[here.row][here.col].label == 1){
  pix[here.row][here.col].label = id;
  pix[here.row][here.col].order = order;
while (pix[here.row][here.col].label != 0){
  while (option <= lastOption)
  {
     r = here.row + offset[option].row;
     c = here.col + offset[option].col;
     if (pix[r][c].label == 1) break;
     option++; // next option
  }

  if (option <= lastOption)
  {// move to pix[r][c]
     path->push(here);
     here.row = r;
     here.col = c;
     order++;
     pix[r][c].order = order;
     pix[r][c].label = id;
     option = 0;
   }
   else{
     if (path->empty()){
       break;
     }
     position next = path->top();
     path->pop();
     if (next.row == here.row){
       option = 2 + next.col - here.col;
     }
    else {
      option = 3 + next.row - here.row;
    }

    here = next;
     }
   }


}


}
}
}









void outputImage()
{// Output ided image.

   cout << "The labeled image is" << endl;
   for (int i = 1; i <= size; i++)
   {
      for (int j = 1; j <= size; j++){
         cout << pix[i][j].label << "," << pix[i][j].order << "  ";
       }
      cout << endl;
   }
}

int main()
{
   welcome();
   inputImage();
   outputImage();
   imageDFS();
   outputImage();
   inputImage();
   outputImage();
   imageBFS();
   outputImage();
}
