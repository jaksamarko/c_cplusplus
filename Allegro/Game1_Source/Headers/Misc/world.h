void _world::draw(unsigned char id) {
    for(int i=0;i<b.size();i++) {
        if(b[i].angle==0) {
            al_draw_bitmap(tex_buildings[b[i].texid],b[i].x-view[id].x-b[i].cx,b[i].y-view[id].y-b[i].cy,0);
        } else {
            al_draw_rotated_bitmap(tex_buildings[b[i].texid],b[i].cx,
            b[i].cy,b[i].x-view[id].x,b[i].y-view[id].y,DegToRad(b[i].angle),0);
        }
    }
}

bool _world::collide(int x, int y, int w, int h) {
    for(int i=0;i<b.size();i++) {
        if(!b[i].solid) {continue;}
        if(jCollRectRect(x,y,w,h,b[i].x-b[i].cx,b[i].y-b[i].cy,b[i].w,b[i].h)) {
            return true;
        }
    }
    return false;
}

void _world::save() {
    FILE *f=fopen("Files/Map.txt","w");
    /*
    fprintf(f,"%d\n",n);
    fwrite(d,sizeof(struct buildings),n,f);*/
    fprintf(f,"%d\n",b.size());
    fwrite(b.data(),sizeof(struct buildings),b.size(),f);
    fclose(f);
}

void _world::load() {
    int tmp;
    struct buildings *d;
    FILE *f=fopen("Files/Map.txt","r");
    if(f==NULL) {
        printf("Map not found!\n");
    } else {
        fscanf(f,"%d\n",&tmp);
        d=new struct buildings[tmp];
        fread(d,sizeof(struct buildings),tmp,f);
        b.insert(b.begin(),d,d+tmp);
        delete[] d;
    }
    fclose(f);
}
