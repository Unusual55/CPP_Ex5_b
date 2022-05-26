#include "OrgChart.hpp"

using namespace ariel;

OrgChart::OrgChart(OrgChart &other_org) {
    root = &other_org.getRootCopy();
    for (auto const &element: other_org.inserted) {
        inserted[element.first] = element.second;
    }
}

Node &OrgChart::getRootCopy() {
    Node *ret{root};
    return *ret;
}


Node &OrgChart::getRoot() {
    return *root;
}

OrgChart &OrgChart::add_root(const string &root_name) {
    if (root == nullptr) {
        root = new Node{root_name};
        this->inserted[root_name] = root;
    } else if(this->root->getDescription() != root_name && !this->inserted.contains(root_name)){
        this->inserted.erase(root->getDescription());
        setRoot(root_name);
        this->inserted[root_name] = root;
    }
    else if(this->root->getDescription() != root_name && this->inserted.contains(root_name)){

    }
    return *this;
}

Node *OrgChart::getNode(const string &name) {
    if (!inserted.contains(name)) {
        throw std::invalid_argument("Error: cannot add under someone who does not exist!");
    }
    return inserted.at(name);
}

bool OrgChart::check_isExist(const string &name) {
    return (inserted.at(name)!=nullptr);
}

OrgChart &OrgChart::add_sub(const string &parent, const string &node) {
    bool flag = false;
    string node_non = node;
    if(inserted.contains(parent) && (inserted.at(parent)->doesSonExist(node_non) || parent == node)){
        flag = true;
    }
    else if(inserted.contains(node) && parent != node){
        inserted.at(node)->setPrev(*inserted.at(parent));
        inserted.at(parent)->addToNextLevel(node);
        Node *n = this->inserted.at(parent)->getNewestSon();
        inserted[node] = n;
        flag = true;
    }
    else if(inserted.contains(parent) && parent != node && !inserted.contains(node)){
        inserted.at(parent)->addToNextLevel(node);
        Node *n = this->inserted.at(parent)->getNewestSon();
        inserted[node] = n;
        flag = true;
    }
    else if(!inserted.contains(parent)){
        throw std::invalid_argument("Parent does not exist");
    }
    if(!flag){
        throw std::logic_error("An error occured in add_Sub");
    }
    return *this;
}

ostream &ariel::operator<<(ostream &out, OrgChart &org) {
    string t_push = "\t";
    for (auto it = org.begin_preorder(); it != org.end_preorder(); ++it) {
            Node *n = org.inserted.at(*it);
            uint level = n->getLevel();
            for (int i = 0; i < level; i++) {
                out << t_push;
            }
            out << (*it) << endl;
    }
    return out;
}

ostream &ariel::operator<<(ostream& out, Node& node){
    string push_t;
    for(int i = 0; i < node.level; i++){
        push_t+="\t";
    }
    out<<push_t<<node.getDescription()<<std::endl;
    return out;
}
