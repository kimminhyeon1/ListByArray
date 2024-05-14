#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
	element array[MAX_LIST_SIZE];
	int size;
	int move_count;
}ArrayListType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
init(ArrayListType* L) {
	L->size = 0;
}
int is_full(ArrayListType* L) {
	return(L->size == MAX_LIST_SIZE);
}
int is_empty(ArrayListType* L) {
	return (L->size == 0);
}
void insert(ArrayListType* L, int pos, element item) {
	L->move_count = 0;
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = L->size - 1; i >= pos; i -= 1) {
			L->array[i + 1] = L->array[i];
			L->move_count++;
		}
		L->array[pos] = item;
		L->size = L->size + 1;
	}
}

void print_list(ArrayListType* L) {
	int i;
	for (i = 0; i < L->size; i++) {
		printf("%d->", L->array[i]);
	}
	printf("NULL\n");
}
element delete(ArrayListType* L, int pos) {
	if (pos < 0 || pos >= L->size) {
		error("위치 오류");
	}
	else {
		L->move_count = 0;
		element item = L->array[pos];
		for (int i = pos; i < (L->size - 1); i++) {
			L->array[i] = L->array[i + 1];
			L->move_count++;
		}
		L->size--;
		return item;
	}
}
int main() {
	ArrayListType list;
	int num, position;
	int move_count = 0;

	init(&list);
	while (1) {
		int choice;
		printf("\n메뉴:\n");
		printf("1. 리스트에 추가\n");
		printf("2. 리스트에서 삭제\n");
		printf("3. 리스트 출력\n");
		printf("0. 프로그램 종료\n");
		printf("선택: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			if (is_full(&list)) {
				printf("리스트가 꽉 찼습니다.\n");
			}
			else {
				printf("숫자를 입력하세요 : ");
				scanf("%d", &num);
				printf("추가할 위치를 입력하세요 : ");
				scanf("%d", &position);
				insert(&list, position, num);
				printf("삽입 완료, 데이터 이동 횟수: %d\n", list.move_count);
			}
			break;
		case 2:
			if (is_empty(&list)) {
				printf("리스트가 비어있습니다.\n");
			}
			else {
				printf("삭제할 위치: ");
				scanf("%d", &position);
				delete(&list, position);
				printf("삭제 완료, 데이터 이동횟수: %d\n", list.move_count);
			}
			break;
		case 3:
			printf("리스트 내용\n");
			print_list(&list);
			break;
		case 0:
			printf("프로그램 종료\n");
			return 0;
		default:
			printf("잘못된 선택입니다. 다시 시도하세요\n");
		}
	}
}