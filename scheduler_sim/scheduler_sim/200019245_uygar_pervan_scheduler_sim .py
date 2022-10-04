from numpy import random
import time
import copy

global high_percent
high_percent=50
global med_percent
med_percent=30
global low_percent
low_percent=20

#high shortest job first
#mid round robin
#low fcfs

class Process:
  def __init__(self , burst_time, arrival_time):
    self.burst_time = burst_time
    self.arrival_time = arrival_time
#p=Process(12 , 5)
high_queue=[]
mid_queue=[]
low_queue=[]


def create_low_process(count):
    #print("wip")
    
    start=0
    for x in range(count):
        r = random.poisson(30,1)
        low = random.randint(5, 100)
        #print(r)
        p=Process(low,r[0]+start)
        #p=create_process(r)
        #start=r
        low_queue.append(p)
        start=start+5
    pass
    

def create_mid_process(count):
    #print("wip")
    
    start=0
    for x in range(count):
        r = random.poisson(40,1)
        mid = random.randint(5, 100)
        #print(r)
        p=Process(mid,r[0]+start)
        #p=create_process(r)
        #start=r
        start=start+5
        mid_queue.append(p)
    pass


def create_high_process(count):
    #print("wip")
    
    start=0
    for x in range(count):
        r = random.poisson(50,1)
        high = random.randint(5, 100)
        #print(r)
        p=Process(high,r[0]+start)
        #p=create_process(r)
        #start=r
        high_queue.append(p)
        start=start+5
    pass


def remove_time(t,queue):
    length=len(queue)
    for x in range(length):
        queue[x].arrival_time=queue[x].arrival_time-t
        if queue[x].arrival_time<0:
            queue[x].arrival_time=0
    pass


def print_queue(queue):
    #if len(queue)>0:
        print("arrival")
        for x in range(len(queue)):
            print((queue[x].arrival_time),end='\t')
   
        print("\n")
    
        print("cycle")
        for x in range(len(queue)):
            print(queue[x].burst_time,end='\t')
        print("\n\n")
        pass
    

def find_first(queue):

    for x in range(len(queue)):
        if queue[x].arrival_time==0 and queue[x].burst_time>0 :
            return x;
    return 1;

def FCFS(t,queue):
  
    if len(queue)>0:
        #print_queue(queue)
        #time.sleep(2)
        index=find_first(queue)   
        arrive=queue[index].arrival_time
        remove_time(t,queue)
    
        if queue[index].arrival_time==0:
            queue[index].burst_time=queue[index].burst_time-(t)+arrive
            pass
    
        for x in range(len(queue)): 
            if queue[index-1].burst_time<=0  :
                if len(queue)>1  :
                    ind=find_first(queue)
                    if queue[ind].arrival_time==0:
                        queue[ind].burst_time=queue[ind].burst_time + queue[index].burst_time
                queue.pop(0)
    pass


def remove_all(x,queue):

    try:
        while True:
            queue.remove(x)
    except ValueError:
        pass

    pass

def change_all(queue):

    for x in range(len(queue)):
        if queue[x]!=0:
            queue[x]=queue[x]-1
            pass

pass

ready_queue=[]
global remaining_quantum
global queue2

def round_robin(t,queue,quantum):#q=5
    remaining_quantum=0
    if len(queue)>0:
        
        if len(ready_queue)>0 and remaining_quantum>0:
            queue[ready_queue[x]].burst_time=queue[ready_queue[x]].burst_time-remaining_quantum
            remove_time(remaining_quantum,queue)
            t=t-remaining_quantum

        if t%quantum!=0:
            remaining_quantum=t%quantum
        t=t+quantum
        while t!=0:
            
            #print_queue(queue)
            t=t-quantum
            if t-quantum<0:
                remaining_quantum=abs(t-quantum)
                quantum=abs(t)
           
            queue2=copy.deepcopy(queue)
            remove_time(quantum,queue)
            #print_queue(queue2)
            for x in range(len(queue)) :
                if (queue[x].arrival_time==0) and (x not in ready_queue)  :
                    ready_queue.append(x)

            if len(ready_queue)>0 and len(queue)>0:
                index=ready_queue[0]
                #print(index)
                queue[index].burst_time=queue[index].burst_time-quantum+queue2[index].arrival_time
                x=1
                remaining=abs(queue[index].burst_time)
                if queue[index].burst_time>0:
                    val=copy.deepcopy(ready_queue[0])
                    ready_queue.pop(0)
                    ready_queue.append(val)
                
                
                if queue[index].burst_time==0:
                    queue.pop(index)
                    ready_queue.remove(0)

                    ln=len(queue)-1
                   

                    remove_all(ln,ready_queue)
                    change_all(ready_queue)
                    

                while  x<len(ready_queue) and len(queue)>1:
                    if queue[index].burst_time<0 :
                        i=index
                        i=ready_queue[x]
                        queue[i].burst_time=queue[i].burst_time-remaining
                        if queue[i].burst_time<0:
                            remaining=abs(queue[i].burst_time)
                            remaining_quantum=remaining
                            queue.pop(i)
                    
                        else:
                            queue.pop(index)
                            ready_queue.remove(x)

                            ln=len(queue)-1
                        

                            remove_all(ln,ready_queue)
                            change_all(ready_queue)
                        
                            break
                        x=x+1
                    else:
                        break
                change_all(ready_queue)    
                if queue[index].burst_time<0:    
                    queue.pop(index)
                    ready_queue.remove(0)
                    remove_all(len(queue)-1,ready_queue)
                    change_all(ready_queue)
                   
            #print_queue(queue)
pass


def find_shortest(queue):
    min=queue[0].burst_time
    index=0
    #length=len(queue)-1
    for x in range(len(queue)-1):
        if queue[x+1].burst_time<min and queue[x+1].arrival_time==0 :
            min=queue[x+1].burst_time
            index=x+1
    return index
pass

def SJF(t,queue):#non preemptive
    if len(queue)>0:
        #print_queue(queue)
        time.sleep(0.5)
        bt=0
        queue2=queue
        remove_time(t,queue)
        short_index = find_shortest(queue)
        arrive=queue2[short_index].arrival_time
        queue[short_index].burst_time=queue[short_index].burst_time-(t)+arrive
        if  queue[short_index].burst_time<=0:
            bt=abs(queue[short_index].burst_time)
            queue.pop(short_index)
        while bt!=0 and len(queue)>=1:
            short_index = find_shortest(queue)
            queue[short_index].burst_time=queue[short_index].burst_time-(bt)
            if  queue[short_index].burst_time<=0:
                bt=abs(queue[short_index].burst_time)
                queue.pop(short_index)
            else : bt=0
            #print_queue(queue)
pass


def allocate_priority(queue_low,queue_mid,queue_high,low_priority,mid_priority,high_priority):
    lowlen=len(queue_low)
    midlen=len(queue_mid)
    highlen=len(queue_high)
    if lowlen==midlen==highlen:
        return 0
    give=False

    mini=min(lowlen,midlen,highlen)
    maxi=max(lowlen,midlen,highlen)

    if mini==lowlen and low_priority>10:
         low_priority=low_priority-10;
         give=True

    elif mini==midlen and mid_priority>10:
         mid_priority=mid_priority-10
         give=True

    elif mini==highlen and high_priority>10:         
         high_priority=high_priority-10
         give=True

    if maxi==lowlen and give:
         low_priority=low_priority+10;

    elif maxi==midlen and give:
         
         mid_priority=mid_priority+10
    elif maxi==highlen and give:
         
         high_priority=high_priority+10

    new_priority=[low_priority,mid_priority,high_priority]
    return new_priority
pass


def waiting_time(queue,previous_state,cycle):
    wait=0
    copyq=copy.deepcopy(queue)
    length=len(copyq)
    len2=len(previous_state)-1
    for x in range(len2-1):
        for y in range(length-1):
            length=len(copyq)
            len2=len(previous_state)
            if y<length:
                if previous_state[x].burst_time==copyq[y].burst_time:
                    if copyq[y].arrival_time==0:
                        wait = wait+cycle-previous_state[x].arrival_time
                        copyq.pop(y)
        
    return wait


def turnaround_time(wait,original_queue):
    #burst + waiting_time
    turnaround=0
    for x in range(len(original_queue)):
        turnaround= turnaround + original_queue[x].burst_time
        pass
    return (turnaround+wait)
    pass

global low_wait,high_wait,mid_wait,total_wait
low_wait=0
high_wait=0
mid_wait=0
total_wait=0


global low_copy
global mid_copy
global high_copy

def simulation(high_queue,mid_queue,low_queue,original_high,original_mid,original_low,low_percent,med_percent,high_percent):
    low_wait=0
    high_wait=0
    mid_wait=0
    runcount=0
    while len(low_queue)>0 or len(mid_queue)>0  or len(high_queue)>0:
        print("----------------------------------------------------------------------------------------------")
        print("low priority queue FCFS")
        low_copy=copy.deepcopy(low_queue)
        if len(low_queue)>0:
            FCFS(low_percent,low_queue)
            print_queue(low_queue)
        low_wait=low_wait+ waiting_time(low_queue,low_copy,low_percent)
        
        print("----------------------------------------------------------------------------------------------\n\n")

        print("mid priority queue ROUND ROBIN")
        mid_copy=copy.deepcopy(mid_queue)
        if len(mid_queue)>0:
            round_robin(med_percent,mid_queue,5)
            print_queue(mid_queue)
        mid_wait=mid_wait+ waiting_time(mid_queue,mid_copy,med_percent)
        print("----------------------------------------------------------------------------------------------\n\n")

        print("high priority queue SJF")
        high_copy=copy.deepcopy(high_queue)
        if len(high_queue)>0:   
            SJF(high_percent,high_queue)
            print_queue(high_queue)
        high_wait=high_wait+ waiting_time(high_queue,high_copy,high_percent)    
        print("----------------------------------------------------------------------------------------------\n\n")

        runcount=runcount+1
        print("avg_queue_length")
        print((len(mid_queue)+len(low_queue)+len(high_queue))/3)
        #total_wait = total_wait + low_wait + mid_wait + high_wait

        new_priority = allocate_priority(low_queue, mid_queue, high_queue,low_percent,med_percent,high_percent)
        if type(new_priority) is list:
            med_percent=new_priority[1]
            high_percent=new_priority[2]
            low_percent=new_priority[0]
            pass

        print("new priority for high: "+str(high_percent)+" new priority for low: "+str(low_percent)+" new priority for mid: "+str(med_percent))
        print()
    else:
        print("\n\n----------------------------------------------------------------------")
        print("average waiting_time")
        print("average for high: "+str(high_wait/runcount)+" average for low: "+str(low_wait/runcount)+" average for mid: "+str(mid_wait/runcount))
        print("average turnaround_time")
        print("average for high: "+str(turnaround_time(high_wait,original_high)/runcount)+" average for low: "+str(turnaround_time(low_wait,original_low)/runcount)+" average for mid: "+str(turnaround_time(mid_wait,original_mid)/runcount))
        print("----------------------------------------------------------------------")
pass

low=random.randint(1,101)
mid=random.randint(1,101)
high=random.randint(1,101)

create_low_process(low)
create_high_process(high)
create_mid_process(mid)

global original_high,original_mid,original_low
original_high = copy.deepcopy(high_queue)
original_mid = copy.deepcopy(mid_queue)
original_low = copy.deepcopy(low_queue)

simulation(high_queue,mid_queue,low_queue,original_high,original_mid,original_low,low_percent,med_percent,high_percent)




  