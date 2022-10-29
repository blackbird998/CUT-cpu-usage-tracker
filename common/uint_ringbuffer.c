#include "uint_ringbuffer.h"


/**
 * @file
 * Implementation of ring buffer functions.
 */

void uint_ring_buffer_init(uint_ring_buffer_t *buffer) {
  buffer->tail_index = 0;
  buffer->head_index = 0;
}

void uint_ring_buffer_queue(uint_ring_buffer_t *buffer, struct CPU_Percentage data) {
  /* Is buffer full? */
  if(uint_ring_buffer_is_full(buffer)) {
    /* Is going to overwrite the oldest byte */
    /* Increase tail index */
    buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_MASK);
  }

  /* Place data in buffer */
  buffer->buffer[buffer->head_index] = data;
  buffer->head_index = ((buffer->head_index + 1) & RING_BUFFER_MASK);
}

void uint_ring_buffer_queue_arr(uint_ring_buffer_t *buffer, const struct CPU_Percentage *data, uint_ring_buffer_size_t size) {
  /* Add bytes; one by one */
  uint_ring_buffer_size_t i;
  for(i = 0; i < size; i++) {
    uint_ring_buffer_queue(buffer, data[i]);
  }
}

uint8_t uint_ring_buffer_dequeue(uint_ring_buffer_t *buffer, struct CPU_Percentage *data) {
  if(uint_ring_buffer_is_empty(buffer)) {
    /* No items */
    return 0;
  }
  
  *data = buffer->buffer[buffer->tail_index];
  buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_MASK);
  return 1;
}

uint_ring_buffer_size_t uint_ring_buffer_dequeue_arr(uint_ring_buffer_t *buffer, struct CPU_Percentage *data, uint_ring_buffer_size_t len) {
  if(uint_ring_buffer_is_empty(buffer)) {
    /* No items */
    return 0;
  }

  struct CPU_Percentage *data_ptr = data;
  uint_ring_buffer_size_t cnt = 0;
  while((cnt < len) && uint_ring_buffer_dequeue(buffer, data_ptr)) {
    cnt++;
    data_ptr++;
  }
  return cnt;
}

uint8_t uint_ring_buffer_peek(uint_ring_buffer_t *buffer, struct CPU_Percentage *data, uint_ring_buffer_size_t index) {
  if(index >= uint_ring_buffer_num_items(buffer)) {
    /* No items at index */
    return 0;
  }
  
  /* Add index to pointer */
  uint_ring_buffer_size_t data_index = ((buffer->tail_index + index) & RING_BUFFER_MASK);
  *data = buffer->buffer[data_index];
  return 1;
}

extern inline uint8_t uint_ring_buffer_is_empty(uint_ring_buffer_t *buffer);
extern inline uint8_t uint_ring_buffer_is_full(uint_ring_buffer_t *buffer);
extern inline uint_ring_buffer_size_t uint_ring_buffer_num_items(uint_ring_buffer_t *buffer);
