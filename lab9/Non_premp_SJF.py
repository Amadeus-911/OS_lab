import numpy as np

arr = [
    [1,10,3,3],
    [2,1,1,0],
    [3,2,3,1],
    [4,7,4,4],
    [5,5,2,5]
]
amp = []
for process in arr:
    amp.append([process[0], 0, 0, 0, process[3], process[1]])

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
        

    if(len(q) != 0):
        npid = q[0][0]

        if(amp[npid - 1][3] == 0):
            amp[npid - 1][1] = i
            amp[npid - 1][3] = 1        
        
        print(q)
        q[0][1] = q[0][1] - 1
        if q[0][1] == 0:
            q.sort(key = lambda x:x[1])
            amp[npid - 1][2] = i + 1
            q.pop(0)
        
print(amp)
waiting = []
response = []
for process in amp:
    processID = process[0]
    start = process[1]
    end = process[2]
    arrival = process[4]
    burst = process[5]

    waiting.insert(0,end - arrival - burst)
    response.insert(0,start - arrival)

    print("Process: ", processID)
    print("Arrival: ", arrival)
    print("start: ", start)
    print("End: ", end)
    print("Waiting: ", waiting[0])
    print("Response: ", response[0])

    print("\n")

print("Average waiting time: ", sum(waiting)/len(arr))
print("Average response time: ", sum(response)/len(arr))