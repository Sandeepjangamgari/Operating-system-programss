#include <stdio.h>

void worstFit(int blocks[], int nb, int processes[], int np)
{
    // This will store the block id of the allocated block to a process
    int alloc[np],occ[nb],i,j;

    // Initially no block is allocated and no block is occupied
    for(i = 0; i < np; i++)	alloc[i] = -1;	
	for(i = 0; i < nb; i++) occ[i] = 0;	
    // assigning first block that can accomadate process
    for (i = 0; i < np; i++){
    	int idx=-1;
        for (j = 0; j < nb; j++){ 
	        if (!occ[j] && blocks[j] >= processes[i]){
	                // allocate block j to p[i] process
	                if(idx==-1) idx=j;
	                else if(blocks[j]>=blocks[idx]) idx=j;
	        }
	    }
	    if(idx!=-1){
	    	alloc[i]=idx;
	    	occ[idx]=1;
	    	blocks[idx]-=processes[i];
		}
	}

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < np; i++)
    {
        printf("%d \t\t %d \t\t", i+1, processes[i]);
        if (alloc[i] != -1)
            printf("%d\t\n",alloc[i] + 1);
        else
            printf("\tNot allocated\n");
    }
    int internal=0,external=0;
    for(i=0;i<np;i++) if(alloc[i]!=-1) internal+=blocks[alloc[i]];
    for(i=0;i<nb;i++) if(!occ[i]) external+=blocks[i];
    printf("Internal and external fragmentations are %d and \t%d",internal,external);
}
void mWorstFit(int blocks[], int nb, int processes[], int np)
{
    // This will store the block id of the allocated block to a process
    int alloc[np],occ[nb],i,j;

    // Initially no block is allocated and no block is occupied
    for(i = 0; i < np; i++)	alloc[i] = -1;	
	for(i = 0; i < nb; i++) occ[i] = 0;	
    // assigning first block that can accomadate process
    for (i = 0; i < np; i++){
    	int idx=-1;
        for (j = 0; j < nb; j++){ 
	        if (blocks[j] >= processes[i]){
	                // allocate block j to p[i] process
	                if(idx==-1) idx=j;
	                else if(blocks[j]>=blocks[idx]) idx=j;
	        }
	    }
	    if(idx!=-1){
	    	alloc[i]=idx;
	    	occ[i]=1;
	    	blocks[idx]-=processes[i];
		}
	}

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < np; i++)
    {
        printf("%d \t\t %d \t\t", i+1, processes[i]);
        if (alloc[i] != -1)
            printf("%d\t\n",alloc[i] + 1);
        else
            printf("\tNot allocated\n");
    }
    int vis[nb];
    for(i=0;i<nb;i++) vis[i]=0;
    int internal=0,external=0;
    for(i=0;i<np;i++) if(alloc[i]!=-1 && !vis[alloc[i]]) {
		vis[alloc[i]]=1;
		internal+=blocks[alloc[i]];
	}
    for(i=0;i<nb;i++) if(!occ[i]) external+=blocks[i];
    printf("Internal and external fragmentations are %d and %d",internal,external);
}

void main()
{
    int m,n,i;
    printf("Enter size of nb and np:\n");
    scanf("%d%d",&m,&n);
    printf("Enter each block size:\n");
    int blocks[m],processes[n];
    for(i=0;i<m;i++) scanf("%d",&blocks[i]);
    printf("Enter each process size:\n");
    for(i=0;i<n;i++) scanf("%d",&processes[i]);
    printf("Enter choice:\n");
    int choice;scanf("%d",&choice);    
    if(choice==1)
    worstFit(blocks, m, processes, n);
    else mWorstFit(blocks, m, processes, n);
}
/*
Output:
Enter size of nb and np:
5 4
Enter each block size:
100 50 30 120 35
Enter each process size:
40 10 30 60
Enter choice:
1

Process No.     Process Size    Block no.
1                40             4
2                10             1
3                30             2
4                60                     Not allocated
Internal and external fragmentations are 190 and 65
Output 2:
Enter size of nb and np:
5 4
Enter each block size:
100 50 30 120 35
Enter each process size:
40 10 30 60
Enter choice:
23

Process No.     Process Size    Block no.
1                40             4
2                10             1
3                30             1
4                60             4
Internal and external fragmentations are 80 and         35
*/
