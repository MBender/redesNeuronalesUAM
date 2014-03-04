/* 
 * File:   mcculloh.cpp
 * Author: HollyBuster
 *
 * Created on 2 de marzo de 2014, 3:34
 */
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <fstream>
#include "neuron.h"
#include "cargar.h"
using namespace std;

/*
 * 
 */




class mp_eyes{
public:
    mp_eyes(){
        //construye la red
        for(int i = 0; i < 3; i++){
            Neuron ne;
            ne.in_value = 0;
            in.push_back(ne);
        }
        for(int i = 0; i < 3; i++){
                        Neuron ne;
            ne.in_value = 0;
            z1.push_back(ne);
        }
        for(int i = 0; i < 6; i++){
                        Neuron ne;
            ne.in_value = 0;
            z2.push_back(ne);
        }
        for(int i = 0; i < 2; i++){
                        Neuron ne;
            ne.in_value = 0;
            out.push_back(ne);
        }
        
        //construye los links
        //capa o:
                //a z1
        Link l;
        l.from = &in[0];
        l.to = &z1[0];
        l.weight = 2;
        from_in.push_back(l);
        
        l = *(new Link);
        l.from = &in[1];
        l.to = &z1[1];
        l.weight = 2;
        from_in.push_back(l);
        
        l = *(new Link);
        l.from = &in[2];
        l.to = &z1[2];
        l.weight = 2;
        from_in.push_back(l);
                //a z2
        l = *(new Link);
        l.from = &in[0];
        l.to = &z2[2];
        l.weight = 1;
        from_in.push_back(l);
        
        l = *(new Link);
        l.from = &in[0];
        l.to = &z2[5];
        l.weight = 1;
        from_in.push_back(l);
        
        l = *(new Link);
        l.from = &in[1];
        l.to = &z2[1];
        l.weight = 1;
        from_in.push_back(l);
        
        l = *(new Link);
        l.from = &in[1];
        l.to = &z2[4];
        l.weight = 1;
        from_in.push_back(l);
        
        l = *(new Link);
        l.from = &in[2];
        l.to = &z2[0];
        l.weight = 1;
        from_in.push_back(l);
        
        l = *(new Link);
        l.from = &in[2];
        l.to = &z2[3];
        l.weight = 1;
        from_in.push_back(l);
        
        //from z1
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 2; j++){
                l = *(new Link);
                l.from = &z1[i];
                l.to = &z2[i*2 + j];
                l.weight = 1;
                from_z1.push_back(l);
            }
        }
        
        //from z2
        for(int i = 0; i < 6; i++){
            l = *(new Link);
            l.from = &z2[i];
            l.to = &out[i%2];
            l.weight = 1;
            from_z2.push_back(l);
        }
        
        
    }
    
    void eval(vector<vector<int> > data){
        //por cada elem de data
        ofstream of;
        of.open("mcculloh_salida.txt");
        for (std::vector<vector<int> >::iterator elem = data.begin(); elem != data.end(); ++elem){
            int i = 0;
            
            for (std::vector<int>::iterator n = elem[0].begin(); n != elem[0].end(); ++n)
            {
                in[i].out_value = (float)n[0];
                i++;
            }


            for (std::vector<Neuron>::iterator n = out.begin(); n != out.end(); ++n){
                if(n->in_value >= 2) n->out_value = 1;
                else n->out_value = 0;
                n->in_value = 0;
            }

            for (std::vector<Neuron>::iterator n = z1.begin(); n != z1.end(); ++n){
                if(n->in_value >= 2) n->out_value = 1;
                else n->out_value = 0;
                n->in_value = 0;
            }

            for (std::vector<Neuron>::iterator n = z2.begin(); n != z2.end(); ++n){
                if(n->in_value >= 2) n->out_value = 1;
                else n->out_value = 0;
                n->in_value = 0;
            }

            for (std::vector<Link>::iterator l = from_in.begin(); l != from_in.end(); ++l){
                if(l->from->out_value >= 1) 
                {
                    l->to->in_value+= l->weight;
                    l->from->in_value = 0;
                }
            }

            for (std::vector<Link>::iterator l = from_z1.begin(); l != from_z1.end(); ++l){
                if(l->from->out_value >= 1) {
                    l->to->in_value+= l->weight;
                    l->from->in_value = 0;
                }
            }


            for (std::vector<Link>::iterator l = from_z2.begin(); l != from_z2.end(); ++l){
                if(l->from->in_value >= 1) {
                    l->to->in_value+= l->weight;
                    l->from->in_value = 0;
                }
            }
            
            


            of << out[0].out_value << "\t" << out[1].out_value << endl;


            
        }
    }
    
private:
    //neurons
    //capa O
    std::vector<Neuron> out;
    //capa Z
    std::vector<Neuron> z1;
    std::vector<Neuron> z2;
    //capa I
    std::vector<Neuron> in;
    
    //links
    //o
    std::vector<Link> from_in;
    //z1
    std::vector<Link> from_z1;
    //z2
    std::vector<Link> from_z2;
    
    
};

int main(int argc, char** argv) {
    //procesa las entradas
    ifstream leer;
    leer.open(argv[1]);
    vector<vector<int> > dataArray;
    while(!leer.eof()){
        vector<int> data;
        for(int i = 0; i < 3; i++){
            int num;
            leer >> num;
            data.push_back(num);
        }
        dataArray.push_back(data);
    }
    leer.close();
    //crea la red
    mp_eyes mp;
    //introduce entradas a la red
    mp.eval(dataArray);
    
    return 0;
}

