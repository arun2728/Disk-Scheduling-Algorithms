# Disk-Scheduling-Algorithms

## Algorithms Implimented

#### 1.FCFS
#### 2. SSTF
#### 3. SCAN
#### 4. C-SCAN

### 1. FCFS : 
            FCFS is the simplest disk scheduling algorithm. As the name suggests, this algorithm entertains requests in the order they arrive in the disk queue. The algorithm looks very fair and there is no starvation (all requests are serviced sequentially) but generally, it does not provide the fastest service.

### 2.SSTF :
            Basic idea is the tracks which are closer to current disk head position should be serviced first in order to minimise the seek operations.

### 3.SCAN :
            In SCAN disk scheduling algorithm, head starts from one end of the disk and moves towards the other end, servicing requests in between one by one and reach the other end. Then the direction of the head is reversed and the process continues as head continuously scan back and forth to access the disk. So, this algorithm works as an elevator and hence also known as the elevator algorithm. As a result, the requests at the midrange are serviced more and those arriving behind the disk arm will have to wait.

### 4.C-SCAN :
              In SCAN algorithm, the disk arm again scans the path that has been scanned, after reversing its direction. So, it may be possible that too many requests are waiting at the other end or there may be zero or few requests pending at the scanned area.These situations are avoided in CSCAN algorithm in which the disk arm instead of reversing its direction goes to the other end of the disk and starts servicing the requests from there. So, the disk arm moves in a circular fashion and this algorithm is also similar to SCAN algorithm and hence it is known as C-SCAN (Circular SCAN).
      
## How To Run the code :
 Steps : 
 1. Create a text file (test.txt) and write your input in the format -> <n> <CT> <direction> <TN1> <TN2> ... <TNn>
      where,
      n = number of requests
      CT = current track number
      direction = "u" to up and "d" to down (For c-scan write direction as 'u')
      TNi = Requested Track number 
 2. Compile : "gcc -Werror -Wall -g -std=c99 -o DSCheduler dscheduler.c main.c"
 3. Run : "./DSCheduler FCFS < test.txt"
    (Replace FCFS with SSTF or SCAN or C-SCAN to test the other algorithms)
    (text.txt is a file containing inputs)
