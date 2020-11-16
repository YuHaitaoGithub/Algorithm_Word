#define _CRT_SECURE_NO_WARNINGS
#include"stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "Windows.h"
#include "math.h"

#define MAX_LINE 1000


 typedef struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 }BinNode,*BinTree;
 BinTree root;


 int MaxDepth(struct TreeNode* root)
 {
	 if (root == NULL){
		 return 0;
	 }
	 int left_d = MaxDepth(root->left);
	 int right_d = MaxDepth(root->right);

	 if (left_d == 0 && right_d == 0){
		 return 1;
	 }
	 return left_d < right_d ? (right_d + 1) : (left_d + 1);
 }




 void dfs(struct TreeNode* root, int* returnSize, char* temp, int index, char** res){
	 index += sprintf(temp + index, "%d->", root->val);      //将结点值与箭头存入字符数组，并移动下标
	 //判断叶子节点，并赋值给结果数组
	 if (!root->left && !root->right){
		 res[*returnSize] = (char*)calloc(index - 1, sizeof(char));     //因最后一个箭头不需要，所以index-1空间就够了
		 temp[index - 2] = '\0';       //最后一位退两格，去掉箭头
		 strcpy(res[*returnSize], temp);
		 (*returnSize)++;
		 return;
	 }

	 if (root->left){                 //递归遍历左子树
		 dfs(root->left, returnSize, temp, index, res);
	 }
	 if (root->right){                //递归遍历右子树
		 dfs(root->right, returnSize, temp, index, res);
	 }
 }
 char ** binaryTreePaths(struct TreeNode* root, int* returnSize){
	 *returnSize = 0;
	 if (!root)return NULL;

	 int dep = MaxDepth(root);
	 char** res = (char**)malloc(sizeof(char*)*pow(2.0, dep - 1));  //这个长度还挣扎了一下
	 char* temp = (char*)malloc(sizeof(char) * 1001);            //这个长度没办法了，因每个数字位数不确定，向官方低头
	 TreeNode** Left = (TreeNode**)malloc(sizeof(TreeNode) * 100);
	 TreeNode** Right = (TreeNode**)malloc(sizeof(TreeNode) * 100);
	 dfs(root, returnSize, temp, 0, res);
	 
	 return res;
 }



void CreateBinTree1(BinTree &root, int* array, int i)
{

	if (array[i] == -11){
		return;
	}
	if (root == NULL){
		root = (BinNode *)malloc(sizeof(BinNode));
		root->val = array[i];
		root->left = NULL;
		root->right = NULL;
	}
	CreateBinTree1(root->left, array, 2 * i);
	CreateBinTree1(root->right, array, 2 * i + 1);
}

void Freetree1(BinTree &root)
{
	if (root != NULL)
	{
		Freetree1(root->left);
		Freetree1(root->right);
		root = NULL;
		free(root);	//当左右子结点都为空时，调用free,释放空间
	}
}

void main()
{
	char *filename = "E:\\回收站\\ConsoleApplication1\\ConsoleApplication1\\2.ini";
	char *input = "Input";
	char *section = "2";
	
	/*读取并过滤键值*/
	int array_a[200] = { 0 };
	char array_b[150] = {};
	GetPrivateProfileStringA(section, input, NULL, array_b, 100, filename);
	int j = 0;
	int k = 1;
	for (j; array_b[j] != '\0'; j++)
	{
		if (array_b[0] == 'n'){
			array_a[k++] = -11; break;
		}
		if (!j)
		{
			array_a[k++] = atoi(&array_b[0]); continue;
		}
		if (array_b[j] == ',')
		{
			if (array_b[j + 1] == 'n')
			{
				array_a[k++] = -11;
				j = j + 3;

			}
			else array_a[k++] = atoi(&array_b[++j]);
		}
	}
	for (int z = k; z <= (2 * k - 1); z++)//用-1代表空
	{
		array_a[z] = -11;
	}

	/*创建二叉树*/
	int i = 1;
	CreateBinTree1(root, array_a, i);

	/*传入要测的函数*/
	//printf("%d\n",MaxDepth(root));
	int h = 0;
	int *returnSize = &h;
	*returnSize = 0;
	char **p = binaryTreePaths(root, returnSize);
	for (int i = 0; i < *returnSize; i++)
	{
		printf("%s\n", p[i]);
	}
	
	Freetree1(root);//释放第一个测试树的内存
}