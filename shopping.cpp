/*  Project Name : Shopping Spree
    Date: 4/19/2020
    Programmer: Jacob Mast
    Description: The program to runs the shopping spree problem given in 
                CS 325 HW3 Problem 4.  The program has a knapsack function
                which runs the combinatorial optimization algorithm which
                determines a max price of items one can carry in a knapsack with
                a given weight capacity, and a store of available items to
                carry with given weights and prices.  The main function below
                combines knapsack problem solutions for multiple "family members"
                who are each carrying a knapsack with its own weight capacity
                in the same store.  
                All input is taken through an input file labeled "shopping.txt".
                All output is written to an output file labeled "results.txt".
*/


#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;

// knapsack function declaration, see more below
int knapsackDyn(int[], int[], int, int, vector<int>&);

// max integer function declaration
int max(int, int);

// declare a 2d array/table for use in knapsack function
int K[100][100];

int main(){

    // declare variables

    // number of test cases
    int T;
    // number of items in store
    int N;
    // price of items
    int P[100];
    // weight of items
    int W[100];
    // number of family members
    int F;
    // variable to be used to hold max weight of the current family member
    int M = 0;
    // vector is to be used to store the member items
    vector<vector<int> > vec(100);
    // input file
    ifstream inFile;
    //output file
    ofstream outFile;

    // open input file and verify the file was opened
    inFile.open("shopping.txt");
    if (!inFile.is_open()){
        cout << "Cannot Open file 'shopping.txt'.  Check to make sure it is in this directory" << endl;
        return 1;
    }

    // open the output file
    outFile.open("results.txt");

    // Read T, test cases from input file
    inFile >> T;

    // Run program loop below T times
    for (int k = 0; k < T; k++){
        
        // read N, number of items from input file
        inFile >> N;

        // for i = 0 to less than n
        for (int i = 0; i < N; i++){
            // read and store P[i], price from infile
            inFile >> P[i];
            // read and store W[i], weight from infile
            inFile >> W[i];
        }

        // set max Price to 0
        int maxPrice = 0;

        // read F, number of family members from input file
        inFile >> F;

        // for j = 0 to less than F
        for (int j = 0; j<F; j++){

            // read M, maximum weight by current family member from input file
            inFile >> M;
            
            // call knapsack function to determine max price based on knapsack max weight
            maxPrice = maxPrice + knapsackDyn(W, P, N, M, vec[j]);
        }

        // write maxPrice to output file
        outFile <<"Total Price " << maxPrice << endl;
        
        outFile << "Member Items" << endl;

        // write member number followed by items to output file
        for (int t = 0; t<F; t++){

            // access and sort vector using algorithm lib function
            sort(vec[t].begin(), vec[t].end());
            
            // write family member number to outfile
            outFile << t + 1 << ":";

            // loop for as many values are stored in given vector
            for (int s = 0; s<vec[t].size(); s++){

            // write member item index stored in vector to outfile
            outFile << vec[t][s] << " ";
            }

            outFile<< endl;
        }

    }

    // close the opened files
    inFile.close();
    outFile.close();

    return 0;

}

/* The knapsackDyn function implements the knapsack algorithm using dynamic
programming.  Given two integer arrays (prices and weights) of items in a store/
pantry and given two integers, N is number of items in store and M is max weight
of the knapsack.  The function returns the max price one can carry in a knapsack.
This function has been modified to push/store the member item indexes in a vector, 
to be accessed in the main function. 

source citation: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
*/

int knapsackDyn(int W[], int P[], int N, int M, vector<int> &v){

    // declare counters
    int i, w;

    // build table K in bottom up method
    // find maxPrice using knapsack algorithm
    for(i = 0; i <= N; i++){
        for (w = 0; w <= M; w++){
            if (i == 0 || w == 0){
                K[i][w] = 0;
            }

            else if (W[i - 1] <= w){
                K[i][w] = max(P[i - 1] + K[i - 1][w - W[i - 1]], K[i - 1][w]);
            }

            else{
                K[i][w] = K[i - 1][w];
            }
        }
    }

    // next 18 lines store knapsack result (item indexes)
    // source citation: https://www.geeksforgeeks.org/printing-items-01-knapsack/
    int maxStore = K[N][M];
    int weightStore = M;

    for (int i = N; i > 0 && maxStore > 0; i--){
        if (maxStore == K[i - 1][weightStore])
            // item is not in knapsack
            continue;
        else{

            // item is in knapsack
            v.push_back(i);

            // subtract stored item from counter
            maxStore = maxStore - P[i - 1];
            weightStore = weightStore - W[i - 1];
        }
    }

    // return the maxPrice value for this knapsack
    return K[N][M];

}

/* The function below returns the maximum of the two integer values
which are passed to it */

int max(int a, int b){
    if (a > b)
        return a;
    else
        return b;
}
