#include <stdio.h>

void firstFit(int blocks[], int nb, int processes[], int np)
{
    // This will store the block id of the allocated block to a process
    int alloc[np],occ[nb],i,j;

    // Initially no block is allocated and no block is occupied
    for(i = 0; i < np; i++)	alloc[i] = -1;	
	for(i = 0; i < nb; i++) occ[i] = 0;	
    // assigning first block that can accomadate process
    for (i = 0; i < np; i++){
        for (j = 0; j < nb; j++){ 
	        if (!occ[j] && blocks[j] >= processes[i]){
	                // allocate block j to p[i] process
	                alloc[i] = j;
	                occ[j] = 1;
	                break;
	        }
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
    for(i=0;i<np;i++) if(alloc[i]!=-1) internal+=blocks[alloc[i]]-processes[i];
    for(i=0;i<nb;i++) if(!occ[i]) external+=blocks[i];
    printf("Internal and external fragmentations are %d and \t%d",internal,external);
}
void mFirstFit(int blocks[], int nb, int processes[], int np)
{
    // This will store the block id of the alloc block to a process
    int alloc[np],occ[nb],i,j;
    
	//	Initially no block is allocated
    for(i = 0; i < np; i++) alloc[i] = -1;
    for(i=0;i<nb;i++) occ[i]=0;
    for (i = 0; i < np; i++){
        for (j = 0; j < nb; j++) { 
            if (blocks[j] >= processes[i]){
                // allocate block j to p[i] process
                alloc[i] = j;
				occ[j]=1; 
                // Reduce size of block j as it has accomodated p[i]
                blocks[j] -= processes[i]; 
                break;
            }
        }
    }
    
    int internal=0,external=0;
    for(i=0;i<nb;i++) if(occ[i]) internal+=blocks[i];
    else external+=blocks[i];

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < np; i++)
    {
        printf("%d \t\t %d \t\t", i+1, processes[i]);
        if (alloc[i] != -1)
            printf("%d\n",alloc[i] + 1);
        else
            printf("Not alloc\n");
    }
    printf("Internal and external fragmentations are %d and\t%d",internal,external);
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
    firstFit(blocks, m, processes, n);
    else mFirstFit(blocks, m, processes, n);
}
/*
Output:
Enter size of nb and np:
3
3
Enter each block size:
30
5
10
Enter each process size:
10
6
9
Enter choice:
24

Process No.     Process Size    Block no.
1                10             1
2                6              1
3                9              1
Internal and external fragmentations are 5 and  15
*/
