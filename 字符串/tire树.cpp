void insert(char *s)
{
    int p = 0;
    for(int i=0;s[i];i++)
    {
        int k = s[i] - 'a'; // 根据题意改动
        if(!tr[p][k]) tr[p][k] = ++ tot;
        p = tr[p][k];
    }
    vis[p] = 1; // 代表该节点有一个单词
}
void qu(char * s)
{
    int p = 0 ;
    for(int i=0;s[i];i++)
    {
        int k = s[i] - 'a' ; //根据题意改动
        int now = tr[p][k];
        if(vis[now]) ans ++ ;
        p = tr[p][k];
    }
}