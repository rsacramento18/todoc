#ifndef TODOS_H
#define TODOS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;


typedef struct {
  char todo[100];
  u8 day;
  u8 month;
  u16 year;
  bool isDone;
  bool isDeleted;
} Todo;

typedef struct {
  Todo *todos;
  size_t size;
  size_t capacity;
} Todos;

int read_todos(const char* filename, Todos* todoArr);
int add_todo(Todos* todoArr, Todo todo);
int save_todos(const char* filename, Todos* todoArr);
int mark_todo_done(Todos* todoArr, i16 index);
int mark_todo_deleted(Todos* todoArr, i16 index);
void print_todo_list(Todos* todoArr, bool numbered);
void free_todos(Todos* todoArr);


#endif
