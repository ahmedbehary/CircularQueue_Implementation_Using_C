#ifndef QUEUE_H
#define QUEUE_H
typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned char uint8;
typedef signed char sint8;
typedef float float32;

typedef struct
{
    void **ptr;
    uint32 max_size;
    sint32 count;
    sint32 rear;
    sint32 front;
} queue_t;

typedef enum
{
    Q_OK,
    Q_NOK,
    Q_FULL,
    Q_EMPTY,
    Q_NOTF,
    Q_NULL_PTR,
} queue_status;

queue_t *createQueue(uint32 maxSize, queue_status *queue_ret);
queue_t *destroyQueue(queue_t *arr_ptr, queue_status *queue_ret);
queue_status enqueue(queue_t *arr_ptr, void *item_ptr);
void *dequeue(queue_t *arr_ptr, queue_status *queue_ret);
void *queueFront(queue_t *arr_ptr, queue_status *queue_ret);
void *queueRear(queue_t *arr_ptr, queue_status *queue_ret);

#endif