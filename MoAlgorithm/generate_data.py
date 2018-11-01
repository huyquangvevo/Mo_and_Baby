import numpy as np

f = open("D:\ICT\Design and analysis of Algorithms\Project\data_mo.txt","a+")

n = 15
q = 4
f.write("%d %d\n" % (n,q))

a = np.random.randint(5,size = n)
a.tolist()
b = np.random.randint(n,size=(q,2))
c = np.sort(b)
c.tolist()

print(a)
print("\nQueries:\n")
print(c)

for i in range(n):
    f.write("%d " % (a[i]))

f.write('\n')


for i in range(q):
    f.write("%d %d\n" % (c[i][0],c[i][1]))
f.write('-------Quang Huy-------\n')
f.close()
