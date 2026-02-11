
#include <iostream>
#include <vector>


void generate(int pos, int sizen, vector<int>& arr){
    //base case: ful llength reached
    if (pos == sizen){
        for(int x : arr)
            std::cout << x;
        
        std::cout <<"\n";
        return;
    }
    
    //try all possible choices (0 and 1)
    for(int choice = 0; choice <=1; choice++){
        arr[pos] = choice; //make choice
        generation(pos+1, n ,arr); //recurse
        // no explicit undo needed (value gets overwritten)

    }
}


int main(){
    
    int n = 3;
    std::vector<int> arr(n);
    generate(0, n, arr); //generate all binary strings of length N;
    
    
    return EXIT_SUCCESS;
}





