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

int crossProductZ(point a, point b){
  return a.x * b.y - b.x * a.y;
}

vector<int> properIntersection(point A, point B, point C, point D){
  point AB, BC, BD, CD, DA, DB;

  AB = B - A;
  BC = C - B;
  BD = D - B;

  CD = D - C;
  DA = A - D;
  DB = B - D;

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

  // improper intersection

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

/*

    // Improper intersection
    if  onSegment(A, C, B)  or
        onSegment(A, D, B)  or
        onSegment(C, A, D)  or
        onSegment(C, B, D):
        return True

    // No intersection
    return False

function onSegment(A, C, B):
    // Whether C lies on AB  [3]
    return |AC| + |CB| = |AB|
*/


//test
int main(){
  class point p1(1,1);
  class point p2(4,4);
  class point q1(3,1);
  class point q2(1,3);

  checkIntersection(p1, p2, q1, q2)? cout << "Yes\n": cout << "No\n";

  p1 = point(1,2);
  p2 = point(1,10);
  q1 = point(2,2);
  q2 = point(2,10);

  checkIntersection(p1, p2, q1, q2)? cout << "Yes\n": cout << "No\n";

  p1 = point(1,2);
  p2 = point(10,2);
  q1 = point(1,1);
  q2 = point(1,10);

  checkIntersection(p1, p2, q1, q2)? cout << "Yes\n": cout << "No\n";


  return 0;
}
