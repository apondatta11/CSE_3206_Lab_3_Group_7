#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
// ----- Element stored in the collection -----
class Post {
public:
    string author;
    string content;
    Post(string a, string c) : author(a), content(c) {}
};
 
// ----- Iterator Interface -----
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual Post next() = 0;
    virtual ~Iterator() {}
};
 
class Feed;
 
// ----- Concrete Iterator -----
class FeedIterator : public Iterator {
private:
    vector<Post>* posts;
    int position;
public:
    FeedIterator(vector<Post>* p) {
        posts = p;
        position = 0;
    }
    bool hasNext() override {
        return position < (int)posts->size();
    }
    Post next() override {
        return posts->at(position++);
    }
};
 
// ----- Aggregate Interface + Concrete Aggregate -----
class Feed {
private:
    vector<Post> posts;
public:
    void addPost(const Post& p) {
        posts.push_back(p);
    }
    Iterator* createIterator() {
        return new FeedIterator(&posts);
    }
};
 
int main() {
    Feed feed;
    feed.addPost(Post("Apon", "Just finished the Lab 3 report!"));
    feed.addPost(Post("Emon", "Studying Mediator pattern today."));
    feed.addPost(Post("Sanjida", "UML diagrams ready for the demo."));
 
    Iterator* it = feed.createIterator();
    while (it->hasNext()) {
        Post post = it->next();
        cout << post.author << ": " << post.content << "\n";
    }
 
    delete it;
    return 0;
}
