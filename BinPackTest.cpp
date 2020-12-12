/*
Programmer: Claire Meany
Assignment 5
IT 279
Description:
  This application runs 10 tests on 5 different bin packing methods
*/
#include "Bin.h"
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

const int SIZE = 100;

//sort an array in bins using next fit
int nextFit(vector<Bin> &bins, int arrRand[SIZE], ofstream &rawData){
  //keeps track of bins
  int count=0;
  //create first bin
  Bin temp;
  bins.push_back(temp);
  for(int i=0;i<SIZE;i++){
    //check if there is room in current bin
    if(bins.at(count).isSpace(arrRand[i])){
      bins.at(count).add(arrRand[i]);
    }
    //else create new bin and add it there
    else{
      Bin temp;
      bins.push_back(temp);
      count++;
      bins.at(count).add(arrRand[i]);
    }
  }

  //raw data info
  for(int i=0;i<=count;i++){
    rawData <<"Bin "<< i+1 <<":";
    bins.at(i).printList(rawData);
  }
  //clear out bins for next tests
  bins.clear();

  return count+1;
}

//sort an array into bins using first fit
int firstFit(vector<Bin> &bins, int arrRand[SIZE], ofstream &rawData){
  //keeps track of bins
  int count=0;
  bool added=false;
  //create first bin
  Bin temp;
  bins.push_back(temp);
  for(int i=0;i<SIZE;i++){
    //check if there is room in any existing bin
    for(int k=0;k<count;k++){
      if(bins.at(k).isSpace(arrRand[i])){
        bins.at(k).add(arrRand[i]);
        added =true;
        break;
      }
    }
    if(count==0&&bins.at(count).isSpace(arrRand[i])){
      bins.at(count).add(arrRand[i]);
      added =true;
    }
    if(!added){
      Bin temp;
      bins.push_back(temp);
      count++;
      bins.at(count).add(arrRand[i]);
    }
    added=false;
  }

  //raw data info
  for(int i=0;i<=count;i++){
    rawData <<"Bin "<< i+1 <<":";
    bins.at(i).printList(rawData);
  }
  //clear out bins for next tests
  bins.clear();

  return count+1;
}

//sort an array into bins using best fit
int bestFit(vector<Bin> &bins, int arrRand[SIZE],ofstream &rawData){
  //keeps track of bins
  int count=1;
  int tempSmall=0;
  int smallestSpace=SIZE+1;
  int bestIndex=0;
  //create first bin
  Bin temp;
  bins.push_back(temp);
  for(int i=0;i<SIZE;i++){
    smallestSpace=SIZE+1;
    bestIndex=0;
    for(int k=0;k<count;k++){
      //find how much space would be left after adding current num to current bin
      tempSmall=bins.at(k).spaceAfterAdd(arrRand[i]);
      //check if smallestSpace and best index should be updated
      if(tempSmall>=0){
        if(tempSmall<smallestSpace){
          smallestSpace=tempSmall;
          bestIndex=k;
        }
      }
    }
    //insert num into bin
    if(smallestSpace<SIZE+1){
      bins.at(bestIndex).add(arrRand[i]);
    }
    //create new bin
    else{
      Bin temp;
      bins.push_back(temp);
      count++;
      bins.at(count-1).add(arrRand[i]);
    }
  }

  //raw data info
  for(int i=0;i<count;i++){
    rawData <<"Bin "<< i+1 <<":";
    bins.at(i).printList(rawData);
  }
  //clear out bins for next tests
  bins.clear();

  return count;
}

//finds average of an array
double findAverage(int arr[10]){
  double average=0;
  double total=0;
  for(int i=0;i<10;i++){
    total=total+arr[i];
  }
  average=total/10.0;
  return average;
}

//prints average number of bins for each strategy
void printAverages(int arrNFBins[10], int arrFFOnBins[10], int arrBFOnBins[10],int arrFFOffBins[10], int arrBFOffBins[10], ofstream &results){
  double nfAv=0;
  double ffOnAv=0;
  double bfOnAv=0;
  double ffOffAv=0;
  double bfOffAv=0;

  double lowestBins=SIZE+1;

  //averages
  results<<"Bin Averages:" <<endl;
  cout<<"Bin Averages:" <<endl;

  nfAv=findAverage(arrNFBins);
  results<<"Next Fit had a bin average of " << nfAv << " bins."<<endl;
  cout<<"Next Fit had a bin average of " << nfAv << " bins."<<endl;

  ffOnAv=findAverage(arrFFOnBins);
  results<<"First Fit Online had a bin average of " << ffOnAv << " bins."<<endl;
  cout<<"First Fit Online had a bin average of " << ffOnAv << " bins."<<endl;

  bfOnAv=findAverage(arrBFOnBins);
  results<<"Best Fit Online had a bin average of " << bfOnAv << " bins."<<endl;
  cout<<"Best Fit Online had a bin average of " << bfOnAv << " bins."<<endl;

  ffOffAv=findAverage(arrFFOffBins);
  results<<"First Fit Offline had a bin average of " << ffOffAv << " bins."<<endl;
  cout<<"First Fit Offline had a bin average of " << ffOffAv << " bins."<<endl;

  bfOffAv=findAverage(arrBFOffBins);
  results<<"Best Fit Offline had a bin average of " << bfOffAv << " bins."<<endl;
  cout<<"Best Fit Offline had a bin average of " << bfOffAv << " bins."<<endl;

  //find smallest bin average(s)
  if(nfAv<lowestBins){
    lowestBins=nfAv;
  }
  if(ffOnAv<lowestBins){
    lowestBins=ffOnAv;
  }
  if(bfOnAv<lowestBins){
    lowestBins=bfOnAv;
  }
  if(ffOffAv<lowestBins){
    lowestBins=ffOffAv;
  }
  if(bfOffAv<lowestBins){
    lowestBins=bfOffAv;
  }

  //report smallest bin average
  results<<"\nBest Bin Average:"<<endl;
  cout<<"\nBest Bin Average:"<<endl;
  if(nfAv==lowestBins){
    results<<"Next Fit had the lowest bin average of " << lowestBins << " bins"<<endl;
    cout<<"Next Fit had the lowest bin average of " << lowestBins << " bins"<<endl;
  }
  if(ffOnAv==lowestBins){
    results<<"First Fit Online had the lowest bin average of " << lowestBins << " bins"<<endl;
    cout<<"First Fit Online had the lowest bin average of " << lowestBins << " bins"<<endl;
  }
  if(bfOnAv==lowestBins){
    results<<"Best Fit Online had the lowest bin average of " << lowestBins << " bins"<<endl;
    cout<<"Best Fit Online had the lowest bin average of " << lowestBins << " bins"<<endl;
  }
  if(ffOffAv==lowestBins){
    results<<"First Fit Offline had the lowest bin average of " << lowestBins << " bins"<<endl;
    cout<<"First Fit Offline had the lowest bin average of " << lowestBins << " bins"<<endl;
  }
  if(bfOffAv==lowestBins){
    results<<"Best Fit Offline had the lowest bin average of " << lowestBins << " bins"<<endl;
    cout<<"Best Fit Offline had the lowest bin average of " << lowestBins << " bins"<<endl;
  }
}

//prints home many times each strategy preformed best and the best over all tests
void bestStrat(int arrNFBins[10], int arrFFOnBins[10], int arrBFOnBins[10],int arrFFOffBins[10], int arrBFOffBins[10], ofstream &results){
  int lowestBinCnt=SIZE+1;
  int nfBest=0;
  int ffOnBest=0;
  int bfOnBest=0;
  int ffOffBest=0;
  int bfOffBest=0;

  //for each index find which strategy was best(lowest amount of bins)
  for(int i=0;i<10;i++){
    lowestBinCnt=SIZE+1;
    if(arrNFBins[i]<lowestBinCnt){
      lowestBinCnt=arrNFBins[i];
    }
    if(arrFFOnBins[i]<lowestBinCnt){
      lowestBinCnt=arrFFOnBins[i];
    }
    if(arrBFOnBins[i]<lowestBinCnt){
      lowestBinCnt=arrBFOnBins[i];
    }
    if(arrFFOffBins[i]<lowestBinCnt){
      lowestBinCnt=arrFFOffBins[i];
    }
    if(arrBFOffBins[i]<lowestBinCnt){
      lowestBinCnt=arrBFOffBins[i];
    }

    //report which method(s) had lowest bin count for each test
    if(arrNFBins[i]==lowestBinCnt){
      nfBest++;
    }
    if(arrFFOnBins[i]==lowestBinCnt){
      ffOnBest++;
    }
    if(arrBFOnBins[i]==lowestBinCnt){
      bfOnBest++;
    }
    if(arrFFOffBins[i]==lowestBinCnt){
      ffOffBest++;
    }
    if(arrBFOffBins[i]==lowestBinCnt){
      bfOffBest++;
    }
  }
  results<<"Bin Counts for each strategy: "<<endl;
  results<< "Next Fit had the lowest bin count "<< nfBest <<" times."<<endl;
  results<< "First Fit Online had the lowest bin count "<< ffOnBest <<" times."<<endl;
  results<< "Best Fit Online had the lowest bin count "<< bfOnBest <<" times."<<endl;
  results<< "First Fit Offline had the lowest bin count "<< ffOffBest <<" times."<<endl;
  results<< "Best Fit Offline had the lowest bin count "<< bfOffBest <<" times."<<endl;
  cout<<"Bin Counts for each strategy: "<<endl;
  cout<< "Next Fit had the lowest bin count "<< nfBest <<" times."<<endl;
  cout<< "First Fit Online had the lowest bin count "<< ffOnBest <<" times."<<endl;
  cout<< "Best Fit Online had the lowest bin count "<< bfOnBest <<" times."<<endl;
  cout<< "First Fit Offline had the lowest bin count "<< ffOffBest <<" times."<<endl;
  cout<< "Best Fit Offline had the lowest bin count "<< bfOffBest <<" times."<<endl;

}

int main(){
  int numOfTests=10;
  int arrRandNum[SIZE];

  //create filestream for raw data
  ofstream rawData;
  rawData.open("rawdata.txt");

  //arrays for hold number of bins used in each test
  int arrNFBins[numOfTests];
  int arrFFOnBins[numOfTests];
  int arrFFOffBins[numOfTests];
  int arrBFOnBins[numOfTests];
  int arrBFOffBins[numOfTests];

  vector<Bin> bins;

  //do 10 tests
  for(int i=0; i<numOfTests;i++){
    rawData <<"Test " << i+1 << ":" <<endl;
    //gen 100 random nums and fill array
    rawData <<"Random Array: ";
    for(int k=0;k<SIZE;k++){
      arrRandNum[k]=rand() %SIZE+1;
      rawData <<arrRandNum[k]<<" ";
    }
    rawData << endl;
    //next fit
    rawData <<"\nNEXT FIT"<<endl;
    arrNFBins[i]=nextFit(bins, arrRandNum, rawData);
    //first fit online
    rawData <<"\nFIRST FIT ONLINE"<<endl;
    arrFFOnBins[i]=firstFit(bins, arrRandNum, rawData);
    //best fit online
    rawData <<"\nBEST FIT ONLINE"<<endl;
    arrBFOnBins[i]=bestFit(bins, arrRandNum, rawData);
    //sort array before doing offline testing
    sort(arrRandNum,arrRandNum+SIZE,greater<int>());

    //first fit offline
    rawData <<"\nFIRST FIT OFFLINE"<<endl;
    arrFFOffBins[i]=firstFit(bins, arrRandNum, rawData);
    //best fit offline
    rawData <<"\nBEST FIT OFFLINE"<<endl;
    arrBFOffBins[i]=bestFit(bins, arrRandNum, rawData);
    rawData<<"\n\n";
  }

  //calculate summary info
  
  //create filestream for results
  ofstream results;
  results.open("results.txt");

  //print num of times each test did the best
  bestStrat(arrNFBins,arrFFOnBins,arrBFOnBins,arrFFOffBins,arrBFOffBins, results);
  results<<endl;
  cout <<endl;
  printAverages(arrNFBins,arrFFOnBins,arrBFOnBins,arrFFOffBins,arrBFOffBins, results);

  rawData.close();
  results.close();
  return 0;

}
