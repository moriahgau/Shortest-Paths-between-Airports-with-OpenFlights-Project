#include "dsets.h"

void DisjointSets::addelements(int num){

    for(int i = 0; i < num; i++) nodes.push_back(-1);
}

int DisjointSets::find(int elem){
    
    //if node is already root
    if(nodes[elem] < 0) return elem;
    //if node is a child 
    return nodes[elem];
}

void DisjointSets::setunion(int a, int b){

    //size 
    int elemASize = size(a);
    int elemBSize = size(b);

    //rep elems
    int repElemA = find(a);
    int repElemB = find(b);

    //if first tree is larger
    if(elemASize >= elemBSize){
        //set nodes with rep elem to correct one
        for(unsigned int i = 0; i < nodes.size(); i++) if(nodes[i] == repElemB) nodes[i] = repElemA;

        //manually set repElemB 
        nodes[repElemB] = repElemA;

        //set root node value to negative of new size
        nodes[repElemA] = (-1)*(elemASize + elemBSize);
    } 

    //if second tree is larger
    else {
        for(unsigned int i = 0; i < nodes.size(); i++) if(nodes[i] == repElemA) nodes[i] = repElemB;
        nodes[repElemA] = repElemB;
        nodes[repElemB] = (-1)*(elemASize + elemBSize);
    }
}

int DisjointSets::size(int elem){
    
    //if node is already a root
    if(nodes[elem] < 0) return (-1)*nodes[elem];
    //negative of value stored at root node is size
    return ((-1)*nodes[nodes[elem]]);
}