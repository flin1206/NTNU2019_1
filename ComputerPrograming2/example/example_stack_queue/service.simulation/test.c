#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <time.h> 

#include "linuxlist.h"

typedef struct _sCustomer
{
    int32_t id;
    int32_t arrival;
    int32_t start_service;
    int32_t end_service;
    struct list_head list;
} sCustomer;

void enqueue( struct list_head *pHead, sCustomer *pNode )
{
    list_add_tail( &( pNode -> list ), pHead );
    return;
}

int32_t is_empty( struct list_head *pHead )
{
    return list_empty( pHead );
}

sCustomer *dequeue( struct list_head *pHead )
{
    if( is_empty( pHead ) )
    {
        return NULL;
    }
    
    sCustomer *pNode = list_first_entry( pHead, sCustomer, list );
    list_del( &( pNode -> list ) );
    return pNode;
}

sCustomer *get_first( struct list_head *pHead )
{
    if( is_empty( pHead ) )
    {
        return NULL;
    }
    
    sCustomer *pNode = list_first_entry( pHead, sCustomer, list );
    return pNode;
}

#define ARRIVAL_TIME (4)
#define SERVICE_TIME (4)
#define OPEN_TIME (720)

int main()
{
    LIST_HEAD( service_queue );    
    
    srand( time( 0 ) );    
    
    int32_t next_arrival = rand()%ARRIVAL_TIME + 1; 
    int32_t service = 0;    
    int32_t id = 1;
    sCustomer *pCurrentServicing = NULL;
    
    for( int32_t i = 0 ; i < OPEN_TIME ; i++ )
    {
        // New Customer
        if( next_arrival == 0 )
        {
            sCustomer *pNew = calloc( 1, sizeof( sCustomer ) );
            pNew -> id = id++;
            pNew -> arrival = i;
            enqueue( &service_queue, pNew );
            next_arrival = rand()%ARRIVAL_TIME + 1; 
            
            printf( "Customer %d comes at %d min.\n", pNew -> id, i );
        }
        
        // Service
        if( pCurrentServicing == NULL )
        {
            pCurrentServicing = dequeue( &service_queue );
            if( pCurrentServicing != NULL )
            {
                pCurrentServicing -> start_service = i;
                service = rand()%SERVICE_TIME; // Why do not +1 ??
                
                printf( "Customer %d starts service at %d min.\n", pCurrentServicing -> id, i );
            }
        }
        else if( service == 0 )
        {
            pCurrentServicing -> end_service = i;
            printf( "Customer %d ends service at %d min.\n", pCurrentServicing -> id, i );
            free( pCurrentServicing );
            pCurrentServicing = NULL;
            
            pCurrentServicing = dequeue( &service_queue );
            
            if( pCurrentServicing != NULL )
            {
                pCurrentServicing -> start_service = i;
                service = rand()%SERVICE_TIME; // Why do not +1 ??
                
                printf( "Customer %d starts service at %d min.\n", pCurrentServicing -> id, i );
            }
        }
        else
        {
            service--;
        }
        
        next_arrival--;
    } 
    
    return 0;
}
