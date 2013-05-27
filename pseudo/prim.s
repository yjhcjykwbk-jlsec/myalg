#prim最小生成树贪心算法
#不断地寻找下一个点，扩展到当前最小生成树
var n #点个数
v:=ROOT
priority_queue queue
for i:=1 to n
  visit[v]=true
  #对点v扫描所有邻接边
  for e:=Edges[v].begin to Edges[v].end
    j:=e->t
    if visit[j]==false
      queue.add(Edges[v]) #指向未扩展点的边
  #寻找下一个点v
  while !queue.empty()
    e=queue.pop()
    if visit[e->t]==false #找到下一个扩展点
      print "v,e->t,e->l"
      v=e->t
      break
