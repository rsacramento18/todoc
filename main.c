#include "todos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_menu();
void create_todo_menu(Todos* todoArr);
void mark_todo_done_menu(Todos* todoArr);
void mark_todo_deleted_menu(Todos* todoArr);

int main() {
  Todos *todoArr = malloc(sizeof(Todos));
  size_t count;

  if (read_todos("todos.txt", todoArr) != 0) {
    fprintf(stderr, "Error reading file\n");
    return 1;
  }

  int command = 0;

  do {
    command = print_menu();
    printf("%d", command);
    switch (command) {
      case 1:
        create_todo_menu(todoArr);
        break;
      case 2:
        mark_todo_done_menu(todoArr);
        break;
      case 3:
        mark_todo_deleted_menu(todoArr);
        break;
      default:
        command = -1;
        break;
    }
  } while(command > 0);

  save_todos("todos.txt", todoArr);

  free_todos(todoArr);

  return 0;
}

int print_menu() { 
  printf("Select Menu Option=======\n"); 
  printf("1 -> Create new Todo\n");
  printf("2 -> Mark as done\n");
  printf("3 -> Delete todo\n");
  printf("4 -> Exit\n");

  int command = 0;
  scanf("%d", &command);
  
  return command;
}

void create_todo_menu(Todos *todoArr) {
  Todo t;
  printf("\nCreate a new Todo=====\n");
  printf("Insert Name:");
  scanf("%99s", t.todo);
  printf("Insert Day:");
  scanf("%hhd", &t.day);
  printf("Insert Month:");
  scanf("%hhd", &t.month);
  printf("Insert Year:");
  scanf("%hd", &t.year);

  add_todo(todoArr, t);
  print_todo_list(todoArr, false);
}

void mark_todo_done_menu(Todos* todoArr) {
  print_todo_list(todoArr, true);
  int choice;
  scanf("%d", &choice);
  mark_todo_done(todoArr, choice);
}

void mark_todo_deleted_menu(Todos* todoArr) {
  print_todo_list(todoArr, true);
  int choice;
  scanf("%d", &choice);
  mark_todo_deleted(todoArr, choice);
}
