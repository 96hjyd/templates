int MinimumRepresentation(char *s, int len)
{
    int i = 0, j = 1, count = 0, t;
 
    while (i < len && j < len && count < len)
    {
        if(s[(i + count) % len] == s[(j + count) % len])
            count++;
        else
        {
            if (s[(i + count) % len] > s[(j + count) % len]) 
                 i = i + count + 1;
            else
                 j = j + count + 1;
            if (i == j) ++j;
            count = 0;
        }
    }
    return min(i,j);
}
