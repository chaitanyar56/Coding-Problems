#include<iostream>
#include<vector>

using namespace std;

class point {
  public:
    int x;
    int y;
    point( int x = 0, int y = 0); // constructor
    point operator-(const point&) const;  // operator+()
};

// define constructor
point::point( int a, int b){
    x = a; y = b;
}

// define overloaded + (plus) operator
point point::operator- (const point& c) const {
    point result;
    result.x = (this->x - c.x);
    result.y = (this->y - c.y);
    return result;
}

//define cross product
int crossProductZ(point a, point b){
  return a.x * b.y - b.x * a.y;
}

//proper intersection when ab and cd intersect at a point e where it is in between a, b and c, d
vector<int> properIntersection(point A, point B, point C, point D){
  point AB, BC, BD, CD, DA, DB;

  AB = B - A;
  BC = C - B;
  BD = D - B;

  CD = D - C;
  DA = A - D;
  DB = B - D;

  //result vector stores all the cross product values for reuse, if r[4] = 1 then proper intersection occured
  vector<int> result(5,0);

  result[0] = crossProductZ(AB,BC);
  result[1] = crossProductZ(AB,BD);
  result[2] = crossProductZ(CD,DA);
  result[3] = crossProductZ(CD,DB);


  if (result[0]*result[1] < 0 && result[2]*result[3] < 0){
    result[4] = 1;
  }
  return result;
}

// only satisfies with crossProduct result
// a point c lies on the line segment ab if x value lies between the range of a,b and viceversa for y following the cross product value is zero
bool onSegment(point a, point b, point c, int crossValue){

  if ( crossValue == 0 && c.x >= min(a.x,b.x) && c.y >= min(a.y,b.x) && c.x <= max(a.x,b.x) && c.y <= max(a.y,b.x) ){
    return true;
  }
  return false;
}



bool checkIntersection(point A, point B, point C, point D){

  //save orientations from properIntersection
  vector<int> orientations = properIntersection(A, B, C, D);

  if (orientations[4] == 1){
    return true;
  }

  // improper intersection when one point lies on the line segment it self

  if (onSegment(A,B,C, orientations[0]) == true){
    return true;
  } else if (onSegment(A,B,D, orientations[1]) == true){
    return true;
  } else if (onSegment(C,D,A, orientations[2]) == true){
    return true;
  } else if (onSegment(C,D,B, orientations[0]) == true){
    return true;
  } else{
    return false; // no intersection
  }
}


//test
int main(){
  // parallel case
  class point p1(1,1);
  class point p2(10,1);
  class point q1(1,2);
  class point q2(10,2);

  checkIntersection(p1, p2, q1, q2)? cout << "Yes\n": cout << "No\n";

  //proper intersection case
  p1 = point(0,10);
  p2 = point(10,0);
  q1 = point(0,0);
  q2 = point(10,10);

  checkIntersection(p1, p2, q1, q2)? cout << "Yes\n": cout << "No\n";

  // no intersection
  p1 = point(-5,-5);
  p2 = point(0,0);
  q1 = point(1,1);
  q2 = point(10,10);

  checkIntersection(p1, p2, q1, q2)? cout << "Yes\n": cout << "No\n";

  // improper intersection
  p1 = point(-5,-5);
  p2 = point(2,2);
  q1 = point(1,1);
  q2 = point(10,10);

  checkIntersection(p1, p2, q1, q2)? cout << "Yes\n": cout << "No\n";


  return 0;
}
