#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode* insert_last(ListNode *head, element value)
{
    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = (char *)malloc(strlen(value) + 1);
    strcpy(new_node->data, value);
    new_node->link = NULL;

    if (head == NULL) {
        head = new_node;
    } else {
        ListNode *p = head;
        while (p->link != NULL)
            p = p->link;
        p->link = new_node;
    }

    return head;
}

void print_list(ListNode *head)
{
    printf("head->");
    for (ListNode *p = head; p != NULL; p = p->link) {
        printf("%s->", p->data);
    }
    printf("NULL\n");
}

ListNode* search(ListNode *head, char *word) {
    ListNode *p = head;
    while (p != NULL) {
        if (strcmp(p->data, word) == 0) {
            return p;
        }
        p = p->link;
    }
    return NULL; // 찾지 못한 경우
}

ListNode* delete(ListNode *head, char *word) {
    ListNode *prev = NULL, *curr = head;

    // 삭제할 노드가 헤드 노드인 경우
    if (strcmp(curr->data, word) == 0) {
        head = curr->link;
        free(curr->data);
        free(curr);
        return head;
    }

    // 그 외의 경우
    while (curr != NULL) {
        if (strcmp(curr->data, word) == 0) {
            prev->link = curr->link;
            free(curr->data);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->link;
    }

    return head;
}

void split_list(ListNode *head, char *word, ListNode **head1, ListNode **head2) {
    ListNode *curr = head, *prev = NULL;
    *head1 = head;
    *head2 = NULL;

    ListNode *node_to_delete = search(head, word);

    if (node_to_delete == NULL) {
        printf("단어 검색 불가.\n");
        return;
    }

    while (curr != node_to_delete) {
        prev = curr;
        curr = curr->link;
    }

    if (prev != NULL) {
        prev->link = NULL;
    } else {
        *head1 = NULL;
    }
    *head2 = curr->link;
    free(curr->data);
    free(curr);
}
int main(void) {
    ListNode *head = NULL, *head1 = NULL, *head2 = NULL;
    char temp[100];
    head = insert_last(head, "APPLE");
    head = insert_last(head, "KIWI");
    head = insert_last(head, "BANANA");
    head = insert_last(head, "LEMON");
    head = insert_last(head, "MANGO");
    head = insert_last(head, "MELON");
    head = insert_last(head, "PEACH");

    print_list(head);
    printf("MANGO 삭제합니다.\n");
    delete(head,"MANGO");  //망고 삭제
    print_list(head);

    printf("삭제 할 단어: ");
    if (fgets(temp, sizeof(temp), stdin) == NULL) {
        printf("입력 오류\n");
        return 1;
    }
    printf("%s를 중심으로 리스트를 쪼갭니다.\n", temp);
    temp[strcspn(temp, "\n")] = '\0'; //개행문자 삭제

    split_list(head, temp, &head1, &head2);

    printf("list1: ");
    print_list(head1);
    printf("list2: ");
    print_list(head2);
    return 0;
}