/*
DScheduler.c


*/
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"


#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dscheduler.h"



/*
Any required standard libraries and your header files here
*/

struct schedulerInput loadRequest(){
    struct schedulerInput results;
    int numRequests;
    char line_buffer[MAX_LINE_LENGTH];
    char direction;
    char *token;

    //Process simulation input line by line
    fgets(line_buffer, MAX_LINE_LENGTH, stdin);

    token = strtok(line_buffer, " ");
    sscanf(token, "%d",&numRequests);
    token = strtok(NULL, " ");
    sscanf(token, "%d",&results.startTrack);

    token = strtok(NULL, " ");
    sscanf(token, "%c",&direction);
    results.direction = direction == 'u' ? 1 : -1;

    results.requests.elements = numRequests;
    results.requests.data = (int *)malloc(sizeof(int)*numRequests);
    if ( results.requests.data == NULL ){
        fprintf( stderr, "Was unable to allocate space for requests data.\n");
        exit( BAD_MALLOC );
    }

    for (int i = 0; i < numRequests; i++){
        token = strtok(NULL, " ");
        sscanf(token, "%d", &results.requests.data[i]);
    }

    return results;
}

void printResults(struct schedulerResult results){
    for (int i = 0; i < results.requests.elements; i++){
        printf("%4d", results.requests.data[i]);
    }
    printf(" Total Head Movement %5d\n", results.totalHeadMovement);
}

struct schedulerResult processRequest(enum POLICIES policy, struct schedulerInput request){
    struct schedulerResult results;

    switch(policy){
        case FCFS:
            return process_FCFS_request(request);
        case SSTF:
            return process_SSTF_request(request);
        case SCAN:
            return process_SCAN_request(request);
        case C_SCAN:
            return process_C_SCAN_request(request);
    }
    return results;
}



/* Fill in the following functions */
struct schedulerResult process_FCFS_request(struct schedulerInput request)
{
    struct schedulerResult results;
    //Here be your code
    results.totalHeadMovement = 0;
    int distance, cur_track,i;

    for (i = 0; i < request.requests.elements; i++)
    {
        cur_track = request.requests.data[i];


        distance = abs(cur_track - request.startTrack);


        results.totalHeadMovement += distance;


        request.startTrack = cur_track;
    }
    		printf("\n");

        printf("FCFS -> ");
    	 for(i=0;i<request.requests.elements;i++)
            	printf(" %d  ",request.requests.data[i]);

			printf("\n");

    return results;
}

struct schedulerResult process_SSTF_request(struct schedulerInput request)
{
    struct schedulerResult results;
  int k,t[100],small[100],head;
  int head1 = request.startTrack; // gets the current track number
  int i,j,temp,sub;
             head = head1;
             results.totalHeadMovement = 0;
             for(k=0;k<request.requests.elements;k++)
             {
             for(j=0;j<request.requests.elements;j++)
             	t[j] = abs(head-request.requests.data[j]);

             for(i=0;i<request.requests.elements;i++)
             {
                          for(j=i+1;j<request.requests.elements;j++)
                          {

                                       if(t[i]>t[j])
                                       {
                                                    temp=t[i];
                                                    t[i]=t[j];
                                                    t[j]=temp;
                                       }

                         }
             }

           if(t[0] != 0)
           		{sub = t[0];}
            else
             	{sub = t[1];}
            results.totalHeadMovement+=sub; // calculating head movements
            if(sub>head || head>head1 )
            	head = head + sub;
            else
            	head = head - sub;

             for(j=0;j<request.requests.elements;j++)
             {
             if(head == request.requests.data[j])
             	request.requests.data[j] = 1000;
             }
                          small[k] = head;
             }
             for(i=0;i<request.requests.elements;i++)
            {	request.requests.data[i] = small[i];}

           	printf("\n");
        printf("SSTF -> ");
			 for(i=0;i<request.requests.elements;i++)
           { 	printf(" %d  ",request.requests.data[i]); }

			printf("\n");
           return results;
}

struct schedulerResult process_SCAN_request(struct schedulerInput request)
{
    struct schedulerResult results;
   int queue[20],n,head = request.startTrack,i,j,max,diff,temp,queue1[20],queue2[20],
                        temp1=0,temp2=0,dir;
    results.totalHeadMovement = 0;


           max = 1023;
           n = request.requests.elements;
          dir = request.direction;

            for(i=0;i<n;i++)
            {
                       queue[i] = request.requests.data[i];
             }

             for(i = 0; i<n;i++)
             {
             	temp = queue[i];
                        if(temp>=head)
                        {
                                    queue1[temp1]=temp;
                                    temp1++;
                        }
                        else
                        {
                                    queue2[temp2]=temp;
                                    temp2++;
                        }
            	}
            	for(i=0;i<temp1;i++)
            	{
                        for(j=i+1;j<temp1;j++)
                        {
                                    if(queue1[i]>queue1[j])
                                    {
                                                temp=queue1[i];
                                                queue1[i]=queue1[j];
                                                queue1[j]=temp;
                                    }
                        }
            	}
            	for(i=0;i<temp2;i++)
            	{
                        for(j=i+1;j<temp2;j++)
                        {
                                    if(queue2[i]>queue2[j])
                                    {
                                                temp=queue2[i];
                                                queue2[i]=queue2[j];
                                                queue2[j]=temp;
                                    }
                        }
            	}

            if(dir == 1)
             {


            	for(i=0,j=0;j<temp1;i++,j++)
            	{queue[i]=queue1[j];}
            	queue[i]=max;


            	i++;
            	for(j=temp2-1;j>=0;i++,j--)
                    queue[i]=queue2[j];
            	n = i;


            for(j=0;j<n;j++)
            {
                        diff=abs(queue[j]-head);
                        results.totalHeadMovement+=diff;


                        head = queue[j];
            }

 }
 else
 {

     	for(i=0,j=temp2-1;j>=0;i++,j--)
            {

            	queue[i]=queue2[j];

            }
            	queue[i]=0;
            	i++;
            	for(j=0;j<temp1;i++,j++)
                    queue[i]=queue1[j];
            	n = i;

            for(j=0;j<n;j++)
            {
                       	diff=abs(queue[j]-head);
                        		results.totalHeadMovement+=diff;
                             
                                                head = queue[j];
            }




 }
            for(i=0;i<n;i++)
            {
            	if(queue[i] != 1023 && queue[i] != 0)
            	printf("\n\t\t%d",queue[i]);

            }
      return results;
}

struct schedulerResult process_C_SCAN_request(struct schedulerInput request){
    struct schedulerResult results;
 int queue[200],n,head = request.startTrack,i,head1,j;
 results.totalHeadMovement=0;
 head1  = head;
 int max = 1023,diff,temp,queue1[200],queue2[200],
                        temp1=0,temp2=0;
        n = request.requests.elements;
            for(i=0;i<n;i++)
            {
                queue[i] = request.requests.data[i];
            }
            for(i=0;i<n;i++)
            {
                        temp = queue[i];
                        if(temp>=head)
                        {
                                    queue1[temp1]=temp;
                                    temp1++;
                        }
                        else
                        {
                                    queue2[temp2]=temp;
                                    temp2++;
                        }
            }
            for(i=0;i<temp1-1;i++)
            {
                        for(j=0;j<temp1-i-1;j++)
                        {
                                    if(queue1[j]>queue1[j+1])
                                    {
                                                temp=queue1[j];
                                                queue1[j]=queue1[j+1];
                                                queue1[j+1]=temp;
                                    }
                        }
            }
            for(i=0;i<temp2-1;i++)
            {
                        for(j=0;j<temp2-i-1;j++)
                        {
                                    if(queue2[j]>queue2[j+1])
                                    {
                                                temp=queue2[j];
                                                queue2[j]=queue2[j+1];
                                                queue2[j+1]=temp;
                                    }
                        }
            }
            for(i=1,j=0;j<temp1;i++,j++)
            queue[i]=queue1[j];
            queue[i]=max;
            i++;
            queue[i]=0;
            i++;
            for(j=0;j<temp2;i++,j++)
            queue[i]=queue2[j];
            queue[0]=head;
            n = i;
            for(j=0;j<n;j++)
            {
                        diff=abs(queue[j]-head);
                        head = queue[j];
                        results.totalHeadMovement+=diff;

            }

        	printf("\n");

            j = 0;

        printf("C-SCAN -> ");
			while(j<n)
			{
			if(queue[j] != 0 && queue[j] != max && queue[j] != head1)
				{printf("%d ",queue[j]);}
			j++;
			}
			printf("\n");

    return results;
}


