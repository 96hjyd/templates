dist:=g;
for k:=1 to n do
begin
    for i:=1 to k-1 do
      for j:=i+1 to k-1 do
        answer:=min(answer, dist[i][j]+g[i][k]+g[k][j]);
    for i:=1 to n do
      for j:=1 to n do
        dist[i][j]:=min(dist[i][j], dist[i][k]+dist[k][j]);
end;
