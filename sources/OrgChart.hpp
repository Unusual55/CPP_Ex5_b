#include "Node.hpp"
#include <iostream>
#include <unordered_map>
#include <stack>
#include <queue>
#include <iterator>
using std::string;

using std::queue, std::stack, std::string, std::endl, std::ostream;

namespace ariel {
    class OrgChart {

    public:
        void setRoot(const string &root_name) {
            root->setDescription(root_name);
        }

        OrgChart() : root(new Node()) {}

        OrgChart(OrgChart &&org) = delete;

        OrgChart(OrgChart &other_org);

        ~OrgChart(){
            delete root;
        }

        Node &getRoot();

        Node &getRootCopy();

        OrgChart &add_root(const string &root_name);

        OrgChart &operator=(OrgChart && other) noexcept {
            return *this;
        }

        Node *getNode(const string &name);

        OrgChart &add_sub(const string &parent, const string &node);

        bool check_isExist(const string &name);

        friend ostream &operator<<(ostream &out, OrgChart &org);

        OrgChart &operator=(const OrgChart &org) = default;

        class preOrderIterator {
        private:
            vector<string> *q=nullptr;
        public:
            preOrderIterator(Node *ptr=nullptr) {
                if (ptr != nullptr) {
                    q = new vector<string>(Node::preOrderQueue(*ptr));
                    q->shrink_to_fit();
                }
            }

            ~preOrderIterator(){
                delete q;
            }

            preOrderIterator(preOrderIterator &other)=default;

            preOrderIterator(preOrderIterator &&other)=default;

            preOrderIterator operator=(preOrderIterator &other)=delete;

            preOrderIterator operator=(preOrderIterator &&other)=delete;

            string operator*() const {
                return q->front();
            }

            string* operator->() const {
                return &(q->at(0));
            }

            preOrderIterator &operator++() {
                q->erase(q->begin());
                return *this;
            }

//            const preOrderIterator operator++(int) {
//                preOrderIterator tmp = *this;
//                pointer_to_current_node = q.front();
//                q.pop();
//                return tmp;
//            }

            bool operator==(const preOrderIterator &rhs) const {
                return this->q == rhs.q;
            }

            bool operator!=(const preOrderIterator &rhs) const {
                return !this->q->empty() && rhs.q==nullptr;
            }
        };

        class levelOrderIterator {
        private:
            vector<string> *q=nullptr;
        public:
            levelOrderIterator(Node *ptr=nullptr) {
                if (ptr != nullptr) {
                    q = new vector<string>();
                    *q = Node::levelOrderedQueue(*ptr);
                    q->shrink_to_fit();
//                    pointer_to_current_node = q.front();
//                    q.pop();
                }
            }

            ~levelOrderIterator(){
                delete q;
            };

            levelOrderIterator(levelOrderIterator &other)=default;

            levelOrderIterator(levelOrderIterator &&other)=default;

            levelOrderIterator operator=(levelOrderIterator &other)=delete;

            levelOrderIterator operator=(levelOrderIterator &&other)=delete;


            string operator*() const {
                return q->front();
            }

            string* operator->() const {
                return &(q->at(0));
            }

            levelOrderIterator &operator++() {
                q->erase(q->begin());
                return *this;
            }

//            const levelOrderIterator operator++(int temp) {
//                levelOrderIterator tmp = *this;
//                pointer_to_current_node = q.front();
//                q.pop();
//                return tmp;
//            }

            bool operator==(const levelOrderIterator &rhs) const {
                return this->q == rhs.q;
            }

            bool operator!=(const levelOrderIterator &rhs) const {
                return !this->q->empty() && rhs.q==nullptr;
            }

        };


        class ReversedlevelOrderIterator {
        private:
            vector<string> *s=nullptr;
        public:
            ReversedlevelOrderIterator(Node *ptr=nullptr) {
                if (ptr != nullptr) {
                    s = new vector<string>(Node::ReversedLevelOrderedStack(*ptr));
                    s->shrink_to_fit();
//                    pointer_to_current_node = s.top();
//                    s.pop();
                }
            }

            ~ReversedlevelOrderIterator(){
                delete s;
            };

            ReversedlevelOrderIterator(ReversedlevelOrderIterator &other)=default;

            ReversedlevelOrderIterator(ReversedlevelOrderIterator &&other)=default;

            ReversedlevelOrderIterator operator=(ReversedlevelOrderIterator &other)=delete;

            ReversedlevelOrderIterator operator=(ReversedlevelOrderIterator &&other)=delete;


            string operator*() const {
                return s->front();
            }

            string* operator->() const {
                return &(s->at(0));
            }

            ReversedlevelOrderIterator &operator++() {
                if (s->empty()) {
                    s = nullptr;
                } else {
                    s->erase(s->begin());
                }
                return *this;
            }

//            const ReversedlevelOrderIterator operator++(int temp) {
//                ReversedlevelOrderIterator tmp = *this;
//                pointer_to_current_node = s.top();
//                s.pop();
//                return tmp;
//            }

            bool operator==(const ReversedlevelOrderIterator &rhs) const {
                return this->s == rhs.s;
            }

            bool operator!=(const ReversedlevelOrderIterator &rhs) const {
                return !this->s->empty() && rhs.s==nullptr;
            }

        };


    private:
        Node *root;
        std::unordered_map<string, Node *> inserted;


    public:
        preOrderIterator begin_preorder() const {
            if((this->root->getDescription().empty())){
                throw std::invalid_argument("The organization chart is empty");
            }
            return preOrderIterator(this->root);
        }

        preOrderIterator end_preorder() {
            if((this->root->getDescription().empty())){
                throw std::invalid_argument("The organization chart is empty");
            }
            return preOrderIterator(nullptr);
        }

        levelOrderIterator begin_level_order() const {
            if((this->root->getDescription().empty())){
                throw std::invalid_argument("The organization chart is empty");
            }
            return levelOrderIterator(this->root);
        }

        levelOrderIterator end_level_order() {
            if((this->root->getDescription().empty())){
                throw std::invalid_argument("The organization chart is empty");
            }
            return levelOrderIterator(nullptr);
        }

        ReversedlevelOrderIterator begin_reverse_order() const {
            if((this->root->getDescription().empty())){
                throw std::invalid_argument("The organization chart is empty");
            }
            return ReversedlevelOrderIterator(this->root);
        }

        ReversedlevelOrderIterator reverse_order() {
            if((this->root->getDescription().empty())){
                throw std::invalid_argument("The organization chart is empty");
            }
            return ReversedlevelOrderIterator(nullptr);
        }

        levelOrderIterator begin() const {
            return begin_level_order();
        }

        levelOrderIterator end() {
            return end_level_order();
        }

    };
}