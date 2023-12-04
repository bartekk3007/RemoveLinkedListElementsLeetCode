#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* createHead(int n)
{
	struct ListNode *head = (struct ListNode*) malloc(sizeof(struct ListNode));
	if (head)
	{
		head->val = n;
		head->next = NULL;
		return head;
	}
}

void addNode(struct ListNode *head, int n)
{
	struct ListNode* vertex = (struct ListNode*) malloc(sizeof(struct ListNode));
	if (vertex)
	{
		vertex->val = n;
		vertex->next = NULL;
		if (head->next == NULL)
		{
			head->next = vertex;
		}
		else
		{
			addNode(head->next, n);
		}
	}
}

void traverseList(struct ListNode *head)
{
	if (head == NULL)
	{
		printf("\n");
	}
	else if (head != NULL)
	{
		printf("%d ", head->val);
		traverseList(head->next);
	}
}

void freeList(struct ListNode *head)
{
	struct node *tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void deleteFromRoot(struct ListNode* head, int n)
{
	if (head->next->next == NULL)
	{
		head->val = head->next->val;
		free(head->next);
		head->next = NULL;
	}
	else
	{
		head->val = head->next->val;
		deleteFromRoot(head->next, n);
	}
}

void deleteNode(struct ListNode* head, int n)
{
	if (head == NULL)
	{
		return;
	}
	else if (head->next == NULL)
	{
		return;
	}
	else if (head->val == n)
	{
		deleteFromRoot(head, n);
	}
	else if (head->next->val == n)
	{
		if (head->next->next == NULL)
		{
			free(head->next);
			head->next = NULL;
		}
		else
		{
			struct node* temp = head->next->next;
			free(head->next);
			head->next = temp;
		}
	}
	else
	{
		deleteNode(head->next, n);
	}
}

struct ListNode *returnListWithDeletions(struct ListNode *head, int val)
{
	if (head == NULL)
	{
		return NULL;
	}
	else if (head->next == NULL && head->val == val) //sprawdz
	{
		free(head);
		return NULL;
	}
	else if (head->next == NULL) //sprawdz
	{
		return head;
	}
	else
	{
		deleteNode(head, val);
		return head;
	}
}

int countValuesInListAlternative(struct ListNode *head, int val)
{
	int count = 0;
	struct ListNode *current = head;
	while (current != NULL)
	{
		if (current->val == val) //sprawdz
		{
			count++;
		}
		current = current->next;
	}
	return count;
}

int countValuesInList(struct ListNode* head, int val)
{
	int count = 0;
	while (head != NULL)
	{
		if (head->val == val) //sprawdz
		{
			count++;
		}
		head = head->next;
	}
	return count;
}

struct ListNode *removeElements(struct ListNode *head, int val) 
{
	int count = countValuesInList(head, val);
	for (int i = 0; i < count; i++)
	{
		head = returnListWithDeletions(head, val);
	}
	return head;
}

int main(void)
{
	struct ListNode *head = createHead(10);
	addNode(head, 15);
	addNode(head, 15);
	addNode(head, 20);
	addNode(head, 25);
	addNode(head, 25);

	printf("Wypisana lista\n");
	traverseList(head);

	struct ListNode *p = removeElements(head, 15);

	printf("Wypisana lista\n");
	traverseList(p);

	freeList(p);

	return 0;
}