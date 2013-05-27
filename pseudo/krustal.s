bc[] #并查集
initF(n):
	for i:=0 to n
		bc[i]:=i
getF(s): #获得一棵并查树的根
	if(bc[s]==s) return s;
	return bc[s]:=getF(bc[s]) #递归简化并查树
is_conn(s,t):#是否同一棵并查树
	return getF(s)==getF(t)	
conn(s,t):#合并为一棵并查树
	bc[s]:=t

krustal():
	#初始化包含所有边的优先队列
	priority_queue queue
	for i:=0 to n
		for e:=Edges[i].begin to Edges[i].end
			queue.add(e)
	#不断找出连接不同分支的边，加入生成树
	for i:=0 to n
		while !queue.empty()
			edge:=queue.top()
			queue.pop()
			if !is_conn(edge.s,edge.t) #处于不同并查树
				conn(edge.s,edge.t) #合并并查集
				print "edge.s,edge.t,edge.l"
				break
