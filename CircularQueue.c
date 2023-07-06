#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"

static queue_status queueFull(queue_t *arr_ptr);
static queue_status queueEmpty(queue_t *arr_ptr);
queue_t *queue1;
queue_status ret = Q_NOK;
uint32 var1 = 33;
uint32 var2 = 44;
uint32 var3 = 55;
uint32 var4 = 66;
uint32 var5 = 77;

uint32 queueSize = 0;
uint32 *ptr1 = NULL;
uint32 *ptr2 = NULL;
int main()
{
    printf("Enter size of queue: ");
    scanf("%i", &queueSize);
    queue1 = createQueue(queueSize, &ret);

    ret = enqueue(queue1, &var1);
    ret = enqueue(queue1, &var2);
    ret = enqueue(queue1, &var3);
    ret = enqueue(queue1, &var4);
    ret = enqueue(queue1, &var5);
    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    ptr1 = queueFront(queue1, &ret);
    printf("Front of queue is : %i \n", *(ptr1));
    ptr1 = queueRear(queue1, &ret);
    printf("Rear of queue is : %i \n", *(ptr1));

    dequeue(queue1, &ret);
    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    ret = enqueue(queue1, &var1);

    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    dequeue(queue1, &ret);
    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    ret = enqueue(queue1, &var1);
    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    ret = enqueue(queue1, &var1);
    dequeue(queue1, &ret);
    dequeue(queue1, &ret);
    dequeue(queue1, &ret);
    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    dequeue(queue1, &ret);
    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    ptr1 = queueFront(queue1, &ret);
    printf("Front of queue is : %i \n", *(ptr1));
    ptr1 = queueRear(queue1, &ret);
    printf("Rear of queue is : %i \n", *(ptr1));
    ret = enqueue(queue1, &var3);
    printf("Index of front element = %i \n", queue1->front);
    printf("Index of rear element = %i \n", queue1->rear);
    destroyQueue(queue1, &ret);
    return 0;
}

static queue_status queueFull(queue_t *arr_ptr)
{
    if (arr_ptr == NULL)
    {
        return Q_NULL_PTR;
    }
    else
    {
        if ((arr_ptr->count == arr_ptr->max_size))
        {
            return Q_FULL;
        }
        else
        {
            return Q_NOTF;
        }
    }
}

static queue_status queueEmpty(queue_t *arr_ptr)
{
    if (arr_ptr == NULL)
    {
        return Q_NULL_PTR;
    }
    else
    {
        if ((arr_ptr->front == -1) && (arr_ptr->rear == -1))
        {
            return Q_EMPTY;
        }
        else
        {
            return Q_NOTF;
        }
    }
}

queue_t *createQueue(uint32 maxSize, queue_status *queue_ret)
{
    queue_t *queue_ptr = NULL;
    if (queue_ret == NULL)
    {
        printf("Error! NULL ptr. \n");
        *queue_ret = Q_NULL_PTR;
        queue_ptr = NULL;
    }
    else
    {
        queue_ptr = (queue_t *)malloc(sizeof(queue_t));
        if (!queue_ptr)
        {
            free(queue_ptr);
            queue_ptr = NULL;
            *queue_ret = Q_NOK;
        }
        else
        {
            queue_ptr->ptr = (void **)calloc(maxSize, sizeof(void *));
            if (!queue_ptr->ptr)
            {
                free(queue_ptr);
                *queue_ret = Q_NOK;
                queue_ptr = NULL;
            }
            else
            {
                queue_ptr->front = -1;
                queue_ptr->rear = -1;
                queue_ptr->count = 0;
                queue_ptr->max_size = maxSize;
                *queue_ret = Q_OK;
                printf("Queue is created! \n");
            }
        }
    }
    return queue_ptr;
}
queue_t *destroyQueue(queue_t *arr_ptr, queue_status *queue_ret)
{
    if ((queue_ret == NULL) || (arr_ptr == NULL))
    {
        printf("Error! NULL ptr. \n");
        *queue_ret = Q_NULL_PTR;
        arr_ptr = NULL;
    }
    else
    {
        free(arr_ptr->ptr);
        free(arr_ptr);
        *queue_ret = Q_OK;
        printf("Queue is destroyed! \n");
    }
    return NULL;
}
queue_status enqueue(queue_t *arr_ptr, void *item_ptr)
{
    queue_status ret = Q_NOK;
    if ((arr_ptr == NULL) || (item_ptr == NULL))
    {
        printf("Error! NULL ptr. \n");
        ret = Q_NOK;
    }
    else
    {
        if (queueFull(arr_ptr) == Q_FULL)
        {
            printf("Queue is full! \n");
            ret = Q_FULL;
        }
        else
        {
            if (queueEmpty(arr_ptr) == Q_EMPTY)
            {
                (arr_ptr->front)++;
                (arr_ptr->rear)++;
                arr_ptr->ptr[arr_ptr->rear] = item_ptr;
                (arr_ptr->count)++;
                ret = Q_OK;
                printf("First Item is added!\n");
            }
            else if ((arr_ptr->rear == (arr_ptr->max_size - 1)) && (arr_ptr->count != arr_ptr->max_size))
            {
                (arr_ptr->rear) = 0;
                arr_ptr->ptr[arr_ptr->rear] = item_ptr;
                (arr_ptr->count)++;
                ret = Q_OK;
                printf("Item is added! \n");
            }
            else
            {
                (arr_ptr->rear)++;
                arr_ptr->ptr[arr_ptr->rear] = item_ptr;
                (arr_ptr->count)++;
                ret = Q_OK;
                printf("Item is added!\n");
            }
        }
    }
    return ret;
}
void *dequeue(queue_t *arr_ptr, queue_status *queue_ret)
{
    void *dataPtr = NULL;
    if ((arr_ptr == NULL) || (queue_ret == NULL))
    {
        dataPtr = NULL;
        *queue_ret = Q_NULL_PTR;
        printf("Error! NULL ptr.\n");
    }
    else
    {
        if (queueEmpty(arr_ptr) == Q_EMPTY)
        {
            dataPtr = NULL;
            *queue_ret = Q_EMPTY;
            printf("Queue is empty!\n");
        }
        else
        {
            if (queueFull(arr_ptr) == Q_FULL)
            {
                dataPtr = arr_ptr->ptr[arr_ptr->front];
                (arr_ptr->front)++;
                if (arr_ptr->front == arr_ptr->max_size)
                {
                    arr_ptr->front = 0;
                }
                (arr_ptr->count)--;
                *queue_ret = Q_OK;
                printf("Dequeue element from full queue. \n");
            }
            else if (((arr_ptr->front) == 0) && ((arr_ptr->rear) == 0))
            {
                dataPtr = arr_ptr->ptr[arr_ptr->front];
                (arr_ptr->front)--;
                (arr_ptr->rear)--;
                (arr_ptr->count)--;
                *queue_ret = Q_OK;
                printf("Dequeue last element in queue! \n");
            }
            else if (((arr_ptr->front) == ((arr_ptr->max_size) - 1)) && ((arr_ptr->rear) == ((arr_ptr->max_size) - 1)))
            {
                dataPtr = arr_ptr->ptr[arr_ptr->front];
                arr_ptr->front = -1;
                arr_ptr->rear = -1;
                *queue_ret = Q_OK;
                printf("Dequeue last element in queue! \n");
            }
            else
            {
                dataPtr = arr_ptr->ptr[arr_ptr->front];
                (arr_ptr->front)++;
                if (arr_ptr->front == arr_ptr->max_size)
                {
                    arr_ptr->front = 0;
                }
                (arr_ptr->count)--;
                *queue_ret = Q_OK;
                printf("Dequeue element from queue! \n");
            }
            *queue_ret = Q_OK;
        }
    }
    return dataPtr;
}
void *queueFront(queue_t *arr_ptr, queue_status *queue_ret)
{
    void *dataPtr = NULL;
    if ((arr_ptr == NULL) || (queue_ret == NULL))
    {
        dataPtr = NULL;
        *queue_ret = Q_NULL_PTR;
        printf("Error! NULL ptr.\n");
    }
    else
    {
        if (queueEmpty(arr_ptr) == Q_EMPTY)
        {
            dataPtr = NULL;
            *queue_ret = Q_EMPTY;
            printf("Queue is empty!\n");
        }
        else
        {
            dataPtr = arr_ptr->ptr[arr_ptr->front];
        }
    }
    return dataPtr;
}
void *queueRear(queue_t *arr_ptr, queue_status *queue_ret)
{
    void *dataPtr = NULL;
    if ((arr_ptr == NULL) || (queue_ret == NULL))
    {
        dataPtr = NULL;
        *queue_ret = Q_NULL_PTR;
        printf("Error! NULL ptr.\n");
    }
    else
    {
        if (queueEmpty(arr_ptr) == Q_EMPTY)
        {
            dataPtr = NULL;
            *queue_ret = Q_EMPTY;
            printf("Queue is empty!\n");
        }
        else
        {
            dataPtr = arr_ptr->ptr[arr_ptr->rear];
        }
    }
    return dataPtr;
}