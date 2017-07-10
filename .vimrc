set nu
set nocompatible
set tabstop=4
set softtabstop=4
set shiftwidth=4
imap {<CR> {<ESC>o}<ESC>O
set smartindent
set cindent
hi MatchParen ctermbg=black ctermfg=blue
map <F2> :call SetTitle()<CR>
func SetTitle()
let l = 0
let l = l + 1 | call setline(l,'#include<cstdio>')
let l = l + 1 | call setline(l,'#include<cstring>')
let l = l + 1 | call setline(l,'#include<iostream>')
let l = l + 1 | call setline(l,'#include<algorithm>')
let l = l + 1 | call setline(l,'#include<vector>')
let l = l + 1 | call setline(l,'#include<queue>')
let l = l + 1 | call setline(l,'#include<set>')
let l = l + 1 | call setline(l,'#include<map>')
let l = l + 1 | call setline(l,'#include<string>')
let l = l + 1 | call setline(l,'#include<cmath>')
let l = l + 1 | call setline(l,'#include<cstdlib>')
let l = l + 1 | call setline(l,'#include<ctime>')
let l = l + 1 | call setline(l,'using namespace std;')
let l = l + 1 | call setline(l,'')
let l = l + 1 | call setline(l,'int main()')
let l = l + 1 | call setline(l,'{')
let l = l + 1 | call setline(l,'	//freopen("in.txt","r",stdin);')
let l = l + 1 | call setline(l,'	//freopen("out.txt","w",stdout);')
let l = l + 1 | call setline(l,'')
let l = l + 1 | call setline(l,'	return 0;')
let l = l + 1 | call setline(l,'}')
endfunc
