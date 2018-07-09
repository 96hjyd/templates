#include<bits/stdc++.h>
using namespace std;
void getZarr(string str,int Z[])
{
	int n=str.length();
	int L=0,R=0;
	Z[0] = n;
	for(int i=1;i<n;i++)
	{
		Z[i]=max(0,min(Z[i-L],R-i+1));
		while(i+Z[i]<n&&str[Z[i]]==str[i+Z[i]])
		{
			L=i;
			R=i+Z[i];
			Z[i]++;
		}
	}
}
void search(string text, string pattern)
{
	string concat=pattern+"$"+text;
	int len=concat.length();
	int* Z=new int[len];
	getZarr(concat,Z);
	for(int i=0;i<len;i++)
	{
		if(Z[i]==pattern.length())
		{
			cout<<"Pattern found at index "<<i-pattern.length()-1<<endl;
		}
	}
}
int main()
{
	string text="GEEKS FOR GEEKS";
	string pattern="GEEK";
	search(text,pattern);
	return 0;
}
