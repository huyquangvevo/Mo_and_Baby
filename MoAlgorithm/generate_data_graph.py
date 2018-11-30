import numpy as np
import random

f = open("D:\ICT\Design and analysis of Algorithms\Project\MoAlgorithm\data_graph.txt","a+")

n = 30
m = 50
q = 40
T = 1
f.write("%d\n" %T)

f.write("%d %d %d\n" % (n,m,q))

a = np.random.randint(5,size = n)
a.tolist()
b = np.random.randint(n,size=(q,2))
c = np.sort(b)
c.tolist()

print(a)
print("\nQueries:\n")
print(c)


#for i in range(n):
#   f.write("%d " % (a[i]))
for i in range(m):
    f.write("%d %d\n" % (random.randint(1,n),random.randint(1,n)))

for i in range(q):
    a = random.randint(1,m)
    b = random.randint(1,m)
    if(a>b):
        t=a
        a=b
        b=t
    f.write("%d %d\n" %(a,b))

f.write('\n')


#for i in range(q):
#    f.write("%d %d\n" % (c[i][0],c[i][1]))
f.write('-------Quang Huy-------\n')
f.close()
