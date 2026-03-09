#include "todos.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Todos *todoArr = malloc(sizeof(Todos));
  size_t count;

  if (read_todos("todos.txt", todoArr) != 0) {
    fprintf(stderr, "Error reading file\n");
    return 1;
  }

  print_todo_list(todoArr);

  Todo todo = {
    .todo = "This is the newly inserted todo",
    .day = 9,
    .month = 3,
    .year = 2026,
    .isDeleted = false,
    .isDone = false,
  };

  if(add_todo(todoArr, todo) != 0) {
    fprintf(stderr, "Error inserting a new todo\n");
    return 1;
  }
  print_todo_list(todoArr);

  mark_todo_done(todoArr, todoArr->size-1);
  print_todo_list(todoArr);

  mark_todo_deleted(todoArr, todoArr->size-1);
  print_todo_list(todoArr);

  free_todos(todoArr);

  return 0;
}
