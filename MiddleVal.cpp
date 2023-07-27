multiset<int> S,T; // Always S.size()==T.size() or S.size()==T.size()+1
void eval(){
    if(S.size()){
        auto itr = S.end(); itr--;
        T.insert(*itr); S.erase(itr);
    }
    while(S.size() < T.size()){
        S.insert(*T.begin()); T.erase(T.begin());
    }
}
int val(){  // 获得中位数  
    auto itr = S.end(); itr --;
    if(S.size() == T.size() + 1) return *itr;
    return (*itr + *T.begin()) / 2;
}
void erase(int x){
    auto itr = S.end(); itr--;
    if(*itr < x) T.extract(x);
    else S.extract(x);
}