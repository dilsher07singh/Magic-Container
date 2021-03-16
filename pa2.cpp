//
//  main.cpp
/*
 * main.cpp
 *
 *  Created on: Sep 19, 2019
 *      Author: kevinw
 */

#include <iostream>
#include <cstring>
using namespace std;

const int ARRAY_SIZE = 12;
const char POTION = 'o';
const char RIM = 'T';
const char WALL = '*';
const char EMPTY = ' ';

enum TASK {CLEANUP, WARMUP_FILL, SIMPLE_FILL, ADVANCED_FILL};
void print_array(const char array[][ARRAY_SIZE+1]) {
    cout << "  ";
    for (int j = 0; j < ARRAY_SIZE; j++)
        cout << j % 10;
    cout << endl;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << i % 10 << " ";
        cout << array[i] << endl;
    }
}

int cleanup(char array[ARRAY_SIZE][ARRAY_SIZE+1], int row = 0, int col = 0) {
// check base case
    if(row<0 || col>ARRAY_SIZE+1 || row>ARRAY_SIZE || col<0)
        return 0;
// potion call with sum to check potion
    if(array[row][col]==POTION){
        array[row][col]=' ';
        return 1+cleanup(array,row+1,col)+cleanup(array,row,col+1);;
    }
    return 0+cleanup(array,row+1,col)+cleanup(array,row,col+1);


}


void warmup_fill(char array[][ARRAY_SIZE+1], int row, int col, int level) {
 
    
   // check all the cases everytime recursively
    //FOR WALL
    // FOR NULL
    // FOR POTION
   
        if(array[row][col]==WALL)
            //check wall carefully
            return;
        else if(array[row][col]==POTION)
            //check potion as well
            return;
        else if(array[row][col]=='\0')
            //check null character as well
            return;
    
    if(row>=level){
        
    if (array[row][col]==EMPTY){
        //potion check
        array[row][col]=POTION;
        
        warmup_fill(array,row-1,col,level);
        
        warmup_fill(array,row+1,col,level);
        // Row to col switch change
        warmup_fill(array,row,col-1,level);
        
        warmup_fill(array,row,col+1,level);
        
    }
    }
    else if(row<level){
        
        if(array[row][col]==RIM ||array[row][col]==WALL)
                return;
        
        else{
            // TO MOVE TO THE NEXT RECURSION UNTIL ROW STOPS
                warmup_fill(array,row+1,col,level);
                
            }
        }
   
    }

    

void simple_fill(char array[][ARRAY_SIZE+1], int row, int col) {
   //use other recursive functions for call
    if((array[row][col+1]=='T' && (array[row+1][col]=='*'||array[row+1][col-1]=='*'||array[row+1][col+1]=='*'))){
        warmup_fill(array,row,col,row);
    }
    else
        simple_fill(array,row+1,col);
    
    
    
}

int find_left_rim (char array[][ARRAY_SIZE+1], int row=0, int col=0){
    
    if ((col>=ARRAY_SIZE+1)||(row>=ARRAY_SIZE)){
        return 0;}
    
    {
        if (array[row][col]=='\0'){
        return find_left_rim(array,row+1,0);
        
    }
    else if (array[row][col]==RIM) {
        return col;
        
    }
    else{
        return find_left_rim(array,row,col+1);
        
    }
        
        
    }
}


int find_right_rim (char array[][ARRAY_SIZE+1], int row=0, int col=0){
    
    if ((col>=ARRAY_SIZE+1)||(row>=ARRAY_SIZE)){
        return 0;
        
    }
    
    {
        if (col==-1){
            return find_right_rim(array,row+1,ARRAY_SIZE);
            
            
        }
    else if (array[row][col]==RIM) {
        
        return col;
        
    }
    else{
        return find_right_rim(array,row,col-1);
        
    }
        
        
    }
}



int advanced_correction(char[][ARRAY_SIZE+1],int,int,int);
// function prototype to check

int error_detection(char array[][ARRAY_SIZE+1], int row, int col, int level){
    if(col==0){
        
        if (array[row][col]==POTION)
            
            return -1;
        
        // check cases for cleanup
        
        
    }
    
    if(col==ARRAY_SIZE-1){
        //limitation of array
        if (array[row][col]==POTION){
            return -1;
        }
        //check cases for cleanup
        //all conditions
    }
    
    if(array[ARRAY_SIZE-1][col]==POTION){
        //clean this particular case
        return -1;
        
        
    }
    //check cases for cleanup
    
    
   
    
    
// different cases
    
    else if (row>=level){
        //row>=level will change the cases
        
        if (array[row][col]==EMPTY){
            array[row][col]=POTION;
            // fill empty with potions in order to find row and col
            //RETURN ALL CONDITIONS
            return advanced_correction(array,row+1,col,level)+
            advanced_correction(array,row,col+1,level)+
            advanced_correction(array,row,col-1,level)+
            advanced_correction(array,row-1,col,level);
            // call all various cases of row and col to ensure efficiency
        }
        
    }
    return 0;
}


// ALL CASES CONFIRMED
//CEHCK FURTHERMORE

    



    

int advanced_correction(char array[][ARRAY_SIZE+1], int row, int col,int level){
    
    if((row>=0)&&(row<ARRAY_SIZE)&&(col>=0)&&(col<ARRAY_SIZE+1)){
        
    if(array[row][col]==WALL)
        //wall check
        return 0;
    else if(array[row][col]=='\0')
        // null check
        return 0;
    else if(array[row][col]==POTION)
        return 0;
        // safe potion check
    // call other function which detects and corrects the errors
    error_detection(array, row, col, level);
    
    }
    //protect the returns
    else return 0;


    return 0;
}


int advanced_fill(char array[][ARRAY_SIZE+1], int row, int col) {
//ensure col in the middle of both otherwise cleanup
    if(find_left_rim(array)<col && find_right_rim(array)>col)
    {
        
        if(array[row][find_left_rim(array)]==RIM){
            //as mentioned in cases
            int z= advanced_correction(array, row, col, row);
            //int is efficient
            
            
            //different cases will change the course
            //-1 is a checkup for the cleanup
            if (z<-1)
            cleanup(array);
            //ALL CASES
            else if (array[row][0]==POTION)
            cleanup(array);

            else if (array[row][ARRAY_SIZE-1]==POTION)
            cleanup(array);
            //potion check
            else if (array[row][0]==POTION)
                cleanup(array);
            
            else if (array[ARRAY_SIZE-1][col]==POTION)
                cleanup(array);
            
            return 0;
            
        }
        
        else{

            return advanced_fill(array, row+1, col);
            
           // repeat and recurse in order to check all cases
            
        }
        
        
    }
    //prevent non void function
    
    //prevention
    return 0;
}
    
            
   




void fill(int algorithm, char array[][ARRAY_SIZE+1], int row, int col) {
    cout << "Before Water is filled" << endl;
    print_array(array);
    int level;
    switch (algorithm) {
        case CLEANUP:
            cleanup(array);
            break;
        case WARMUP_FILL:
            cout << "Please help me mark the level:" << endl;
            cin >> level;
            warmup_fill(array, row, col, level);
            cout << "Warmup Fill" << endl;
            break;
        case SIMPLE_FILL:
            simple_fill(array, row, col);
            cout << "Simple Fill" << endl;
            break;
        case ADVANCED_FILL:
            advanced_fill(array,row,col);
            cout << "Advanced Fill" << endl;
            break;
    }
    print_array(array);
}


int main() {
    char test_tube[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     ***    ",
        "            ",
        "            "
    };
    
    
    char two_tubes[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "     T T    ",
        "     ***    ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     ***    ",
        "            ",
        "            "
    };
    
    
    char conical_flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "    *   *   ",
        "   *     *  ",
        "  ********* ",
        "            ",
        "            "
    };
    
    
    char broken_tube[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "     * *    ",
        "            ",
        "            ",
        "            "
    };
    
    char broken_flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "     T T    ",
        "     * *    ",
        "     * *    ",
        "    *   *   ",
        "         *  ",
        "  ********* ",
        "            ",
        "            "
    };
    char beaker[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "  T    T    ",
        "  *    *    ",
        "  *    *    ",
        "  *    *    ",
        "  *    *    ",
        "  ******    ",
        "            ",
        "            "
    };
    
    
    
    char flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "    T T     ",
        "    * *     ",
        "    * *     ",
        "  **   **   ",
        " *       *  ",
        " *       *  ",
        " *       *  ",
        "  *     *   ",
        "   *****    ",
        "            ",
        "            "
    };
    
    
    char up_and_down[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        " T T        ",
        " * * *******",
        " * * *   * *",
        " * *** * * *",
        " *     *   *",
        " ********* *",
        " *         *",
        " ***********"
    };
    
    char broken_u_flask[ARRAY_SIZE][ARRAY_SIZE+1] = {
        "            ",
        "            ",
        "            ",
        "            ",
        "    T T     ",
        "    * * *  *",
        "    * ***  *",
        "   *      * ",
        "  *     **  ",
        " *********  ",
        "            ",
        "            "
    };
    
    
    int opt;
    while (true) {
        cout << "Enter 0 (cleanup), 1 (warmup), 2 (simple), 3 (advanced) to select your algorithm, or other value to quit the program:" << endl;
        cin >> opt;
        if (opt < 0 || opt > 3)
            return 0;
        
        fill(opt, test_tube, 0, 6);
        fill(opt, conical_flask, 0, 6);
        fill(opt, flask,0,5);
        fill(opt, up_and_down, 0, 2);
        if (opt != ADVANCED_FILL)
            fill(opt, two_tubes, 0, 6);
        else
            cout << "Not for advanced_fill" << endl;
        if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
            fill(opt, broken_flask, 0, 6);
        else
            cout << "Not for warmup_fill and simple_fill" << endl;
        if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
            fill(opt, broken_tube, 0, 6);
        else
            cout << "Not for warmup_fill and simple_fill" << endl;
        if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
            fill(opt, beaker, 0, 4);
        else
            cout << "Not for warmup_fill and simple_fill" << endl;
        if (opt != SIMPLE_FILL && opt != WARMUP_FILL)
            fill(opt, broken_u_flask,0,5);
        else
            cout << "Not for warmup_fill and simple_fill" << endl;
    }
    return 0;
    
    
}
