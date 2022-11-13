import numpy as np

arr = [
    [1,10,3,3],
    [2,1,1,0],
    [3,2,3,0],
    [4,7,4,4],
    [5,5,2,5]
]
amp = []
for process in arr:
    amp.append([process[0], 0, 0, 0])

arr.sort(key = lambda x:x[3])
print(arr)
trans = np.array(arr).transpose()
trans = trans.tolist()
print(trans)


total_time = 0
for process in arr:
    total_time+= process[1]

q = []


for i in range(0, total_time):

    arrival = trans[3]
    
    for j in range(0, len(arrival)):
        if i == arrival[j]:
            pid = j
            q.append(arr[pid])
           

 
    print(q)

    if(len(q)!= 0):
        npid = q[0][0]

        if(amp[npid - 1][3] == 0):
            amp[npid - 1][1] = i
            amp[npid - 1][3] = 1        
        
    
        
        q[0][1] = q[0][1] - 1
        if q[0][1] == 0:
            
            amp[npid - 1][2] = i + 1
            q.pop(0)
            q.sort(key = lambda x:x[2], reverse=True)
        
print(amp)