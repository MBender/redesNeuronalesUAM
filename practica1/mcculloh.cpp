/* 
 * File:   mcculloh.cpp
 * Author: HollyBuster
 *
 * Created on 2 de marzo de 2014, 3:34
 */

#include <cstdlib>
#include <vector>

using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {
    //procesa las entradas
    
    //crea la red
    
    //introduce entradas a la red
        
    
    return 0;
}

class mp_eyes{
public:
    mp_eyes(){
        //construye la red
        for(int i = 0; i < 3; i++)
            in.push_back(new Neuron());
        for(int i = 0; i < 3; i++)
            z1.push_back(new Neuron());
        for(int i = 0; i < 6; i++)
            z2.push_back(new Neuron());
        for(int i = 0; i < 2; i++)
            out.push_back(new Neuron());
        
        //construye los links
        //capa o:
                //a z1
        Link l = new Link();
        l.from = &in[0];
        l.to = &z1[0];
        l.weight = 1;
        from_in.push_back(l);
        
        l = new Link();
        l.from = &in[1];
        l.to = &z1[1];
        l.weight = 1;
        from_in.push_back(l);
        
        l = new Link();
        l.from = &in[2];
        l.to = &z1[2];
        l.weight = 1;
        from_in.push_back(l);
                //a z2
        l = new Link();
        l.from = &in[0];
        l.to = &z2[2];
        l.weight = 2;
        from_in.push_back(l);
        
        l = new Link();
        l.from = &in[0];
        l.to = &z2[5];
        l.weight = 2;
        from_in.push_back(l);
        
        l = new Link();
        l.from = &in[1];
        l.to = &z2[1];
        l.weight = 2;
        from_in.push_back(l);
        
        l = new Link();
        l.from = &in[1];
        l.to = &z2[4];
        l.weight = 2;
        from_in.push_back(l);
        
        l = new Link();
        l.from = &in[2];
        l.to = &z2[0];
        l.weight = 2;
        from_in.push_back(l);
        
        l = new Link();
        l.from = &in[2];
        l.to = &z2[3];
        l.weight = 2;
        from_in.push_back(l);
        
        //from z1
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 2; j++){
                l = new Link();
                l.from = &z1[i];
                l.to = &z2[i*2 + j];
                l.weight = 1;
                from_z1.push_back(l);
            }
        }
        
        //from z2
        for(int i = 0; i < 6; i++){
            l = new Link();
            l.from = &z2[i];
            l.to = &out[i%2];
            l.weight = 1;
            from_z2.push_back(l);
        }
        
        
    }
    
    void eval(vector<vector> data){
        
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

