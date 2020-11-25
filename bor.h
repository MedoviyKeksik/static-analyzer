//
// Created by Slonik on 13.11.2020.
//

#ifndef STATIC_ANALYZER_BOR_H
#define STATIC_ANALYZER_BOR_H
#include <string>
#include <vector>

class Bor {
public:
    struct Vertex {
        bool leaf;
        int num;
        Vertex* next[sizeof(char)]{};
        Vertex();
        ~Vertex();
    };
private:
    Vertex* root;
public:
    Bor();
    Bor(const std::vector<std::string> &str);
    ~Bor();
    Vertex* get_root();
    void add_string(const std::string &query);
    bool find(const std::string &query);
    Vertex* find_vertex(const std::string &query);
};


#endif //STATIC_ANALYZER_BOR_H
