# include <stdio.h>
# include <pthread.h>
# define BUFFERSIZE 4

void *producer();
void *consumer();

int bufferIndex=0;
char *buffer;

pthread_cond_t Buffer_Not_Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Not_Empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar=PTHREAD_MUTEX_INITIALIZER;

int main()
{    
    pthread_t ptid,ctid;
    
    buffer=(char *) malloc(sizeof(char) * BUFFERSIZE);            
    
	printf("Pt create begin.\n");
    pthread_create(&ptid,NULL,producer,NULL); printf("Pt create end.\n");
printf("Ct create begin.\n");
    pthread_create(&ctid,NULL,consumer,NULL); printf("Ct create end.\n");
    
 printf("1 end.\n");
    //pthread_join(ptid,NULL); printf("2 end.\n");
    //pthread_join(ctid,NULL); printf("3 end.\n");
        
    
    return 0;
}

void *producer()
{    
	const int toAdd = BUFFERSIZE *3;
	printf("producer, try to add %d numbers.\n", toAdd);
    for(int i =0; i < toAdd; ++i)
    {
        pthread_mutex_lock(&mVar);
        if(bufferIndex==BUFFERSIZE)
        {                        
		//printf("producer start to wait.\n");
            //pthread_cond_wait(&Buffer_Not_Full,&mVar);
        }                        

        printf("Produce : %d \n",bufferIndex);
        buffer[bufferIndex]='@';
	++bufferIndex;
        pthread_mutex_unlock(&mVar);
        pthread_cond_signal(&Buffer_Not_Empty);        
    }    
    
}

void *consumer()
{
	const int toAdd = BUFFERSIZE *3;
	printf("consumer, try to eat %d numbers.\n", toAdd);
    for(int i =0; i < toAdd; ++i)
    {
        pthread_mutex_lock(&mVar);
        if(bufferIndex==0) //<=0
        {            
		//printf("consumer start to wait.\n");
            //while ( pthread_cond_wait(&Buffer_Not_Empty,&mVar) != 0 );
        }                
        printf("Consume : %d \n", --bufferIndex);        
        pthread_mutex_unlock(&mVar);        
        pthread_cond_signal(&Buffer_Not_Full);                
    }    
}

