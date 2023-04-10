// TODO: ID field
// TODO: Delete trans
#include "queue.h"
#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int id = 1; // simple id.

enum PrintOrder { INORDER, PREORDER, POSTORDER };

typedef enum PrintOrder printOrder;

record *treeRoot = NULL;
record *targetrecord = NULL;
record *prevrecord = NULL;

void printUI() {
  printf("\n------------------------------------\n");
  printf("              MENU\n");
  printf("------------------------------------\n");
  printf("1. List transactions(InOrder)\n");
  printf("2. List transactions(PreOrder)\n");
  printf("3. List transactions(PostOrder)\n");
  printf("4. Create a transaction\n");
  printf("5. Delete a transaction\n");
  printf("6. Exit\n");
  printf("------------------------------------\n");
  printf("Enter your choice: ");
}

void printTrans(record *node) {
  struct tm *time_info;
  char time_char[30];

  time_info = localtime(&node->timestamp);
  strftime(time_char, sizeof(time_char), "%Y-%m-%d %H:%M:%S", time_info);

  printf("------------%d--------------\n", node->id);
  printf("Amount: %d\n", node->amount);
  printf("Description: %s\n", node->desc);
  printf("Date: %s\n", time_char);
  printf("----------------------------\n");
}

void tbc() {
  char k[10];
  printf("\n\nType Enter to continue....\n");
  fflush(stdin);
  fgets(k, sizeof(k), stdin);
  if (strchr(k, '\n') != NULL) {
    system("clear");
  }
  return;
}

void inOrder(record *node) {
  if (node == NULL)
    return;

  inOrder(node->left);
  printTrans(node);
  inOrder(node->right);
}

void preOrder(record *node) {
  if (node == NULL)
    return;

  printTrans(node);
  preOrder(node->left);
  preOrder(node->right);
}

void postOrder(record *node) {
  if (node == NULL)
    return;

  postOrder(node->left);
  postOrder(node->right);
  printTrans(node);
}

int compareTime(time_t a, time_t b) { return difftime(a, b); }

int compareAmount(int a, int b) {
  if (a <= b)
    return 1;
  return -1;
}

void insertNode(record *r, record *tmp) {
  record *current, *prev;
  int result;

  // Insert record
  if (r == NULL) {
    r = tmp;
  } else {
    current = r;
    while (current != NULL) {
      result = compareAmount(current->amount, tmp->amount);
      prev = current;
      if (result > 0) {
        // tmp item is after
        current = current->right;
      } else if (result <= 0) {
        current = current->left;
      }
    }

    if (result > 0)
      prev->right = tmp;
    if (result <= 0)
      prev->left = tmp;
  }
}

void createTransaction() {
  record *tmp;
  char inputStr[100];

  system("clear");

  tmp = malloc(sizeof(record));

  fflush(stdin);
  printf("Desc: ");
  fgets(inputStr, sizeof(inputStr), stdin);
  inputStr[strlen(inputStr) - 1] = '\0';

  strcpy(tmp->desc, inputStr);

  fflush(stdin);
  printf("\nAmount: ");
  scanf("%d", &tmp->amount);

  time(&tmp->timestamp);
  /* time_info = localtime(&currentTime); */
  /* strftime(tmp->timeStr, sizeof(tmp->timeStr), "%Y-%m-%d %H:%M:%S",
   * time_info); */

  tmp->id = id++;
  if(treeRoot == NULL) {
      treeRoot = tmp;
  } else {
      insertNode(treeRoot, tmp);
  }
}


void removeNode(record *node) {
  free(node);
}

void deleteNode(record **root, int id) {
  record **current, **tmp ;

  if(*root == NULL) return;

  enqueue(root);

  while (!is_empty()) {
    current = dequeue();

    if((*current)->id == id) {
      if((*current)->left == NULL && (*current)->right != NULL) {
        // if left node is null;
        *current = ((*current)->right);
        return;
      } else if((*current)->right == NULL && (*current)->left != NULL) {
        // if right node is null;
        *current = ((*current)->left);
        return;
      } else if((*current)->right != NULL && (*current)->left != NULL) {
        tmp = &((*current)->left);
        current = &((*current)->right);
        insertNode(*current, *tmp);
        return;
      } else {
        *current = NULL;
        return;
      }

    } else {
      if((*current)->left != NULL) enqueue(&((*current)->left));
      if((*current)->right != NULL) enqueue(&((*current)->right));
    }
  }
}

void deleteTransaction() {
  int targetId;

  system("clear");

  fflush(stdin);
  printf("Target ID: ");
  scanf("%d", &targetId);

  if (treeRoot == NULL) {
    printf("\nNo Transactions!!!!\n");
    return;
  }

  deleteNode(&treeRoot, targetId);


}

void listTransactions(printOrder order) {
  if (treeRoot == NULL) {
    printf("\nNo Transactions!!!!\n");
    return;
  }

  system("clear");
  printf("\nTransaction Details\n");

  if (order == INORDER)
    inOrder(treeRoot);
  if (order == PREORDER)
    preOrder(treeRoot);
  if (order == POSTORDER)
    postOrder(treeRoot);
}

int main() {
  int choice;
  int check;

  system("clear");

  while (1) {
    printUI();

    fflush(stdin);
    check = scanf("%d", &choice);
    // validate input
    if (check != 1 || (choice > 6 || choice < 1)) {
      while (getchar() != '\n')
        ;
      printf("\n Please input 1-6.\n");
    } else {
      switch (choice) {
      case 1:
        listTransactions(INORDER);
        tbc();
        break;
      case 2:
        listTransactions(PREORDER);
        tbc();
        break;
      case 3:
        listTransactions(POSTORDER);
        tbc();
        break;
      case 4:
        createTransaction();
        break;
      case 5:
        deleteTransaction();
        break;
      case 6:
        exit(0);
        break;
      }
    }
  }
}
