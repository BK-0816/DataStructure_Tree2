#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p) //push�Լ�
{
	if (top < SIZE - 1)
		stack[++top] = p;
}
TreeNode* pop() //pop�Լ�
{
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}
void preorder_iter(TreeNode* root) //�ݺ��� ������� ��ȸ ����, NULL�� �ƴ� ���� ���� �ڽ� ���� �̵��ϸ鼭 
                                   //���� ��带 ���ÿ� �߰��ϰ� ���� ��尡 NULL�� �Ǹ� ���ÿ��� ��带 pop
{
	while (1) {
		for (; root; root = root->left) { 
			printf("[%d] ", root->data);
			push(root);
		}
		root = pop();
		if (!root) break;
		root = root->right;
	}
}



void inorder_iter(TreeNode* root) //������ȸ�Լ�
{
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}
void postorder_iter(TreeNode* root) //������ȸ�Լ�
{
	if (!root) return;

	TreeNode* temp = NULL;
	while (1) {
		while (root) {
			if (root->right)
				push(root->right);
			push(root);
			root = root->left;
		}

		root = pop();

		if (root->right && stack[top] == root->right) {
			temp = pop();
			push(root);
			root = root->right;
		}
		else {
			printf("[%d] ", root->data);
			root = NULL;
		}

		if (top == -1) break;
	}
}
//		  1
//	  2		  7
//  3   6   8    9
//4   5        10 11 
TreeNode n1 = { 4, NULL, NULL };
TreeNode n2 = { 5, NULL, NULL };
TreeNode n3 = { 3, &n1, &n2 };
TreeNode n4 = { 6, NULL, NULL };
TreeNode n5 = { 2, &n3, &n4 };
TreeNode n6 = { 8, NULL, NULL };
TreeNode n7 = { 10, NULL, NULL };
TreeNode n8 = { 11, NULL, NULL };
TreeNode n9 = { 9, &n7, &n8 };
TreeNode n10 = { 7, &n6, &n9 };
TreeNode n11 = { 1, &n5, &n10 };
TreeNode* root = &n11;
int main(void)
{
	printf("���� ��ȸ=");
	preorder_iter(root);
	printf("\n");

	printf("���� ��ȸ=");
	inorder_iter(root);
	printf("\n");

	printf("���� ��ȸ=");
	postorder_iter(root);
	printf("\n");

	return 0;
}