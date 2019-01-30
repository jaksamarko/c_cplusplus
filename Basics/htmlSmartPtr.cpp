#include<iostream>
#include<fstream>
#include<memory>
#include<vector>
#include<stack>
#include <algorithm>
#include <regex>
using namespace std;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class tag {
    public:
    string id;
    string nm;
    string dat;
    string style;
    string _class;
    vector<unique_ptr<tag>> child;
    string width;
    string height;
};

class html : public tag {
    public:
    html() {
        nm="html";
    }
    string id;
    string lang;
    string spellcheck;
};

class head : public tag {
    public:
    head() {
        nm="head";
    }
};

class body : public tag {
    public:
    body() {
        nm="body";
    }
    string bgcolor;
    string text;
    string link;

};
class title: public tag {
    public:
    title() {
        nm="title";
    }
};
class meta: public tag {
    public:
    meta() {
        nm="meta";
    }
};
class p: public tag{
    public:
    p() {
        nm="p";
    }
};
class a: public tag {
    public:
    a() {
        nm="a";
    }
    string rel;
};
class script: public tag {
public:
    script() {
        nm="script";
    }
    string src;
};
class img: public script {
    public:
    img() {
        nm="img";
    }
};
class _div: public tag {
public:
    _div() {
        nm="div";
    }
};
class table: public tag {
    table() {
        nm="table";
    }
};

class input: public tag {
    input() {
        nm="input";
    }
};

bool findTag(string &in, string check) {
    size_t p=in.find(check);
    if(p!=string::npos) {
        in.erase(p,check.size());
        return true;
    }
    return false;
}

void parseAttrs(tag* l, string str) {
    regex reg("\\w+");
    sregex_iterator crMtch(str.begin(),str.end(),reg);
    sregex_iterator lstMtch;
    string str1,str2;
    while(crMtch!=lstMtch) {
        str1=(*crMtch).str();
        crMtch++;
        str2=(*crMtch).str();
        crMtch++;
        if(str1=="id") {
            static_cast<html*>(l)->id=str2;
        } else if(str1=="lang") {
            static_cast<html*>(l)->lang=str2;
        } else if(str1=="spellcheck") {
            static_cast<html*>(l)->spellcheck=str2;
        } else if(str1=="src") {
            static_cast<script*>(l)->src=str2;
        } else if(str1=="rel") {
            static_cast<a*>(l)->rel=str2;
        } else if(str1=="type") {
            static_cast<input*>(l)->type=str2;
        } else if(str1=="value") {
            static_cast<>(l)->
        } else if(str1=="width") {
            l->width=str2;
        } else if(str1=="height") {
            l->height=str2;
        } else if(str1=="alt") {
            static_cast<img*>(l)->alt=str2;
        }
    }
}

int main() {
    char tagS;
    string inBuff;
    vector<tag*>q;
    ifstream f;
    unique_ptr<tag> MAIN = make_unique<html>();
    f.open("test.html");
    while(!f.eof()) {
        tagS=f.get();
        if(tagS=='<') {
            getline(f,inBuff,'>');
            f.get();
            if(inBuff.find('/')!=string::npos) {
                if(q.empty()) {
                    q.pop_back();
                }
            } else {
                //cout<<inBuff<<endl;
                if(inBuff=="html") {
                    q.push_back(MAIN.get());
                } else {
                    if(findTag(inBuff,"html")) {
                        q.back()->child.push_back(make_unique<head>());
                    } else if(findTag(inBuff,"title")) {
                        q.back()->child.push_back(make_unique<title>());
                    } else if(findTag(inBuff,"body")) {
                        q.back()->child.push_back(make_unique<body>());
                    } else if(findTag(inBuff,"p")) {
                        q.back()->child.push_back(make_unique<p>());
                    } else if(findTag(inBuff,"head")) {
                        q.back()->child.push_back(make_unique<head>());
                    } else if(findTag(inBuff,"div")) {
                        q.back()->child.push_back(make_unique<_div>());
                    } else if(findTag(inBuff,"script")) {
                        q.back()->child.push_back(make_unique<script>());
                    }  else if(findTag(inBuff,"img")) {
                        q.back()->child.push_back(make_unique<img>());
                    }  else if(findTag(inBuff,"a")) {
                        q.back()->child.push_back(make_unique<a>());
                    }
                    //Attribues
                    parseAttrs(q.back()->child.back().get(),inBuff);
                }
            }
        }
    }
    f.close();
    /*for(auto& i:MAIN->child) {
        cout<<"Name: "<<i->nm<<endl;
    }*/
}

