#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using std::queue;
using std::stack;
using std::string;
using std::vector;
using std::ostream;

namespace ariel{
    class Node{
        string description="";
        uint level=0;
        vector<Node *> next=vector<Node *>();
        Node* prev=nullptr;
    public:
        Node()=default;

        Node(const string &description): description(description), level(0){}

        Node(const string &description, uint level): description(description), level(level){}

        Node(Node &other_node);

        Node(Node && node)=default;

        Node& operator=(Node const &other)=default;

        friend ostream& operator<<(ostream &out, Node &node);

        static void DestroyRecursive(Node* node){
            if(node!=nullptr){
                for(unsigned int i=0;i<node->next.size();i++){
                    delete node->next[i];
                    node->next[i] = nullptr;
                }
            }
        }

        ~Node();

        Node& operator=(Node && other)=default;

        uint length(){
            return description.length();
        }

        string getDescription() const{
            return this->description;
        }

        void setDescription(const string &desc){
            this->description = desc;
        }

        uint getLevel() const{
            return this->level;
        }

        uint size(){
            return next.size();
        }

        vector<Node *> getNextLevel() const{
            return next;
        }

        Node* getNewestSon(){
            return next.back();
        }

        void addToNextLevel(const string &next_description);

        bool doesSonExist(string &name){
            bool flag = false;
            for(unsigned int i = 0; i<next.size(); i++){
                if(next[i]->getDescription() == name) {
                    flag = true;
                    break;
                }
            }
            return flag;
        }

        Node getPrev();

        void setPrev(Node &previous_node);

        static vector<string> preOrderQueue(Node &root){
            vector<string> output_queue;
            std::stack<Node*> node_stack;
            node_stack.push(&root);
            Node temp;
            while(!node_stack.empty()){
                if(node_stack.top()== nullptr){
                    break;
                }
                temp = *node_stack.top();
                output_queue.push_back( node_stack.top()->getDescription());
                node_stack.pop();
                vector<Node *> next_level = temp.getNextLevel();
                if(!next_level.empty()){
                    uint i=next_level.size()-1;
                    for(;i>=0 && i<next_level.size();i--){
                        node_stack.push({next_level[i]});
                    }
                }
            }
            return output_queue;
        }

        static vector<string> levelOrderedQueue(Node &root){
            vector<string> output_queue;
            queue<Node*> node_queue;
            node_queue.push(&root);
            Node temp;
            output_queue.push_back(root.getDescription());
            while(!node_queue.empty()){
                if(node_queue.front()== nullptr){
                    break;
                }
                temp = *node_queue.front();
//                output_queue.push(node_queue.front());
                node_queue.pop();
                vector<Node *> next_level =temp.getNextLevel();
                if(!next_level.empty()) {
                    for (unsigned int i = 0; i < next_level.size(); i++) {
                        output_queue.push_back(next_level.at(i)->getDescription());
                        node_queue.push(next_level.at(i));
                    }
                }
            }
            return output_queue;
        }

        static vector<string> ReversedLevelOrderedStack(Node &root){
            vector<string> output_queue;
            queue<Node*> node_queue;
            node_queue.push(&root);
            Node temp;
            while(!node_queue.empty()){
                if(node_queue.front()== nullptr){
                    break;
                }
                temp = *node_queue.front();
                output_queue.push_back(node_queue.front()->getDescription());
                node_queue.pop();
                vector<Node *> next_level =temp.getNextLevel();
                if(!next_level.empty()) {
                    for (unsigned int i = next_level.size()-1; i >= 0 && i<next_level.size(); i--) {
                        node_queue.push(next_level.at(i));
                    }
                }
            }
            std::reverse(output_queue.begin(), output_queue.end());
            return output_queue;
        }
    };

};