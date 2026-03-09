#include "todos.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define BOOL (a ? "true" : "false")

int read_todos(const char *filename, Todos *todoArr) {
  FILE *fp = fopen("todos.txt", "r");
  u8 capacity = INITIAL_CAPACITY;
  u8 size = 0;
  Todo *arr = malloc(capacity * sizeof(Todo));

  if (fp != NULL) {
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
      line[strcspn(line, "\n")] = 0;

      if (size >= capacity) {
        capacity *= 2;
        Todo *tmp = realloc(arr, capacity * sizeof(Todo));
        if (!tmp) {
          free(arr);
          fclose(fp);
          return -1;
        }
        arr = tmp;
      }
      char *token = strtok(line, ";");
      if (!token)
        continue;
      strncpy(arr[size].todo, token, 99);

      token = strtok(NULL, ";");
      if (!token)
        continue;
      arr[size].day = atoi(token);

      token = strtok(NULL, ";");
      if (!token)
        continue;
      arr[size].month = atoi(token);

      token = strtok(NULL, ";");
      if (!token)
        continue;
      arr[size].year = atoi(token);

      token = strtok(NULL, ";");
      if (!token)
        continue;
      arr[size].isDone = atoi(token);

      token = strtok(NULL, ";");
      if (!token)
        continue;
      arr[size].isDeleted = atoi(token);

      size++;
    }
    todoArr->todos = arr;
    todoArr->size = size;
    todoArr->capacity = capacity;
    fclose(fp);
  }

  return 0;
}

int add_todo(Todos *todoArr, Todo todo) {
  if (todoArr->size >= todoArr->capacity) {
    todoArr->capacity *= 2;

    Todo *tmp = realloc(todoArr->todos, sizeof(Todo));

    if (!tmp) {
      free(tmp);
      return -1;
    }

    todoArr->todos = tmp;
  }

  todoArr->todos[todoArr->size] = todo;
  todoArr->size += 1;
  return 0;
}

int mark_todo_done(Todos *todoArr, i16 index) {
  if(index > todoArr->size) {
    return -1;
  }
  todoArr->todos[index].isDone = true;
  return 0;
}

int mark_todo_deleted(Todos *todoArr, i16 index) {
  if(index > todoArr->size) {
    return -1;
  }
  todoArr->todos[index].isDeleted = true;
  return 0;
}

void print_todo_list(Todos *todoArr) {

  printf("=================\n");
  for (int i = 0; i < todoArr->size; i++) {
    Todo todo = todoArr->todos[i];
    if (todo.isDeleted)
      continue;
    printf("Todo: %s - %d-%d-%d - done: %d\n", todo.todo, todo.day, todo.month,
           todo.year, todo.isDone);
  }
}

void free_todos(Todos *todoArr) { free(todoArr); }
