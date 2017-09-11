//
//  visualizer.cpp
//  Demodulation
//
//  Created by Abhishek Kumar on 8/29/17.
//  Copyright © 2017 Abhishek Kumar. All rights reserved.
//

#include "visualizer.hpp"


using namespace std;

typedef struct{
    int freq0;
    int freq1;
    int dataRate;
    int voltage;
    string bitStream;
}Params;

Params parse(ifstream *f){
    Params P;
    int i=0;
    while (*f){
        string config;
        (*f)>> config;
        size_t pos = config.find("=");
        string value = config.substr(pos+1);
        if (i==0)
            P.freq0 = stoi(value);
        else if (i==1)
            P.freq1 = stoi(value);
        else if (i==2)
            P.dataRate = stoi(value);
        else if (i==3)
            P.voltage = stoi(value);
        else if (i==4)
            P.bitStream = value;
        i++;
    }
    return P;
}
void report(Params P, ofstream *outFile){
    for ( string::iterator it=P.bitStream.begin(); it!=P.bitStream.end(); ++it)
        if (*it == '1'){
            *outFile << P.voltage;
        }
        else
            *outFile << 0;
}

int main(){
    cout << "Hello\n";
    ifstream inFile("Configuration.config");
    if (!inFile){
        cerr<< "File not found"<< endl;
        exit(1);
    }
    Params parameters = parse(&inFile);
    ofstream outFile("Report.out");
    if(!outFile){
        cerr<< "Output file not created"<< endl;
        exit(1);
    }
    report(parameters, &outFile);
    
    outFile.close();
    inFile.close();
    return 0;
}
