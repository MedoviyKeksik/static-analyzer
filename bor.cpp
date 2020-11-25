//
// Created by Slonik on 13.11.2020.
//

#include "bor.h"

Bor::Bor() {
    root = new Vertex();
}

Bor::~Bor() {
    delete root;
}

Bor::Vertex *Bor::get_root() {
    return root;
}

void Bor::add_string(const std::string &query) {
    Vertex* now = root;
    for (auto c : query) {
        if (now->next[c] == nullptr) {
            now->next[c] = new Vertex();
        }
        now->num++;
        now = now->next[c];
    }
    now->leaf = true;
}

bool Bor::find(const std::string &query) {
    Vertex* tmp = find_vertex(query);
    return tmp != nullptr && tmp->leaf;
}

Bor::Vertex *Bor::find_vertex(const std::string &query) {
    Vertex* now = root;
    for (auto c : query) {
        if (now->next[c] == nullptr)
            return nullptr;
        now = now->next[c];
    }
    return now;
}

Bor::Bor(const std::vector<std::string> &str) {
    root = new Vertex();
    for (const std::string &now: str) {
        add_string(now);
    }
}

Bor::Vertex::Vertex() {
    num = 0;
    leaf = false;
    for (auto & now : next)
        now = nullptr;
}

Bor::Vertex::~Vertex() {
    for (auto & now : next)
        delete now;

}
