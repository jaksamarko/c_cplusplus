class quest_task {
    public:
        int start,finish,amount,camount,item,entity;
        void add(int start, int finish, int amount=0, int item=0, int entity=0) {
            camount=0;this->start=start;this->finish=finish;this->amount=amount;this->item=item;this->entity=entity;
        }
        void destroy() {start=finish=amount=item=entity=-1;camount=0;}
};

class quest {
        char *name,*desc;
        int id;
    public:
        bool completed,undertake;
        quest *prev,*next;
        quest_task qt;
        quest(char *name, char *desc, int id, quest_task qt) {
            this->name=new char[strlen(name)+1]; strcpy(this->name,name);
            this->desc=new char[strlen(desc)+1]; strcpy(this->desc,desc);
            this->id=id; this->qt=qt;
            completed=undertake=false;
        }
};

class _quests {
    vector<quest>q,cq;
    public:
        vector<int>completed;
        _quests() {q.clear();cq.clear();}
        int found(int id);
        int add(char *name, char *desc, quest_task &qt, int prev=-1) {
            quest t(name,desc,q.size(),qt);
            qt.destroy();
            if(prev!=-1) {t.prev=&q[id];}
            q.push_back(t);
            if(prev!=-1) {q[id].next=&q[q.size()-1];}
            return q.size()-1;
        }
        void getquest(int id) {
            quest t=q[found(id)];
            t.undertake=true;
            cq.push_back(t);
        }
        void check_completed() {
            quest_task t;
            for(int i=0;i<cq.size();i++) {
                if(!cq[i].completed) {
                    t=cq[i].qt;
                    if(amount>0) {completed=(camount==amount);}
                }
            }
        }
        void draw();
}quests;

int _quests::found(int id) {
    for(int i=0;i<q.size();i++) {if(q[i].id==id) {return i;}}
    return -1;
}

void _quests::draw() {
    for(int i=0;i<cq.size();i++) {
        al_draw_textf(font,al_map_rgb(0,0,0),0,32+i*32,0,"%s:%s",cq[i].name,cq[i].desc);
    }
}
