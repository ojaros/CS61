#ifndef pixel_
#define pixel_

struct pixel
{
   int label;
   double order;

   operator int() const {return label;}
   operator double() const {return order;}
};

#endif
