#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAX 26
struct Trie
{
    int num;
    Trie *next[MAX];
};
Trie *root;
Trie *newtrie()
{
    Trie *temp=(Trie*)malloc(sizeof(Trie));
    for(int i=0;i<MAX;i++) temp->next[i]=NULL;
    return temp;
}
void createTrie(char *str)
{
    int len=strlen(str);
    Trie *p=root,*q;
    for(int i=0;i<len;i++)
    {
        int id=str[i]-'a';
        if(p->next[id]==NULL)
        {
            q=(Trie*)malloc(sizeof(Trie));
        	q->num=1;
            for(int j=0;j<MAX;j++)
                q->next[j]=NULL;
            p->next[id]=q;
            p=p->next[id];
        }
        else 
        {
            p->next[id]->num++;
            p=p->next[id];
        }
    }
}
int findTrie(char* str)
{
    int len=strlen(str);
    Trie* p=root;
    for(int i=0;i<len;i++)
    {
        int id=str[i]-'a';
        p=p->next[id];
        if(p==NULL) return 0;
    }
    return p->num;
}
int main()
{
    root=newtrie();
    return 0;
}
