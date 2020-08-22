#include <iostream>
#include <iomanip>
#include <vector> //they can store primitives

using namespace std;

class MyPoint{
    //by default is private
    public:
        // Constructor that uses an initializer list
        MyPoint(int x, int y, float z): x_{x}, y_{y}, z_{z} {}
    
        //Destructor frees up memory allocated by the class
        ~MyPoint(){
            cout << "Destructor called." << endl;
        }
    
        //Methods that do not modify member variables should be declared const.
        void print_coords() const {
            cout << "(x,y,z) = (" << x_ << ", " << y_ << ", " << fixed
            << setprecision(2) << z_ << ")" << endl;
        }
        
        //Accessor
        int get_x() const{
            return x_;
        }
        //Mutator.
        void set_x(int x){
            x_ = x;
        }
    private:
        //must intialize in the order that they are declared
        int x_,y_;
        float z_;
}; //need semi colon at the end

void display_points (const vector<MyPoint> &points){
    //only put the const on the outside for a member function
    for(auto it = points.cbegin(); it != points.cend(); ++it){
        //not regular .begin() because it is a const vector
        //whenever we deal with collections class, recommend using a preincrement operator
        //if u did post increment it needs to save the state and call something (requires more steps)
        it -> print_coords(); //because it is a pointer we have to use an arrow
    }
}

int main(){
    MyPoint point1(5,7,1.24);
    MyPoint point2(1,2,3);
    MyPoint point3(4,5,6);
    
    //point1.print_coords();
    
    vector<MyPoint> points;
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
    
    vector<MyPoint> points_above_two;
    /*for (auto point: points) {
        //this makes a copy of everything when we iteratet over
    } */
    for (const auto &point: points) {
        //stays the same for the life of that value it takes on
        if(point.get_x() > 2){
            points_above_two.push_back(point);
        }
    }
    
    display_points(points_above_two);
    
    cout << "Input x: ";
    cin >> x;
    
    cout << "Input y: ";
    cin >> y;
    
    MyPoint *point4 = new MyPoint(x,y,7); //this object exists on the heap
    point4 -> print_coords();
    delete point4; //when you work with stuff in the heap you have to delete it
    
    return 0;
}
