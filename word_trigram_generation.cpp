#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>

//Word Probability Distribution generator

char sample(std::vector<int>& sv){
    int total = sv[27];
    int r = (rand() % total) + 1;
    int sum = 0;
    for(int i = 0; i < 27; i++){
        sum += sv[i];
        if(r <= sum){
            return ((char)(i)) + 'a';
        }
    }
    return '{';
}

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cout << "Please specify 1 input file" << std::endl;
    }
    srand(time(NULL));
    std::ifstream inf; inf.open(std::string(argv[1]));
    std::unordered_map<std::string, std::vector<int>> dist;
    for(int i = 0; i < 300000; i++){
        std::string a, b; inf >> a >> b;
        std::string current= "..";
        int j = 0;
        for(; j < a.size(); j++){
            std::string map_key = current + std::to_string(j);
            if(dist.count(map_key) == 0){
                dist[map_key] = std::vector<int>(28, 0);
            }
            dist[map_key][a[j] - 'a']++;
            dist[map_key][27]++;
            current[0] = current[1];
            current[1] = a[j];
        }
        std::string map_key = current + std::to_string(j);
        if(dist.count(map_key) == 0){
            dist[map_key] = std::vector<int>(28, 0);
        }
        dist[map_key][26]++; dist[map_key][27]++;
    }

    int N = 200;
    for(int i = 0; i < N; i++){
        std::string current= "..";
        int j = 0;
        char cc = sample(dist[(current + std::to_string(j))]);
        std::string output;
        while(cc != '{'){
            output.push_back(cc);
            j++;
            current[0] = current[1];
            current[1] = cc;
            cc = sample(dist[(current + std::to_string(j))]);
        }
        std::cout << output << std::endl;
    }
    return 0;
}