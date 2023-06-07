#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define	NodeWIDTH	6
#define	NodeGAP		1

typedef const char* CPtr;
typedef struct Node {
	CPtr sName;			// �̸�
	CPtr sPosition;		// ������
	CPtr sBirthday;		// ������� 2002.06.04
	int  nHeight;		// Ű
	int  nWeight;		// ������
	CPtr sClub;
	Node *lChild;
	Node *rChild;
}	*NodePtr, Data, *DataPtr, *TreePtr;

void MakeSearchTree(TreePtr &pTree1, TreePtr &pTree2);
TreePtr SearchTree(TreePtr pTree, char *sName);
void ShowTree(TreePtr pTree);
void SwapTree(TreePtr pTree);
bool EqualTree(TreePtr pTree1, TreePtr pTree2);
void Inorder(TreePtr pTree);
TreePtr InsertNode1(TreePtr pTree, DataPtr pNode);
void InsertNode2(TreePtr& pTree, DataPtr pNode);

void main()
{
	TreePtr pTree1 = NULL, pTree2 = NULL;
	MakeSearchTree(pTree1, pTree2);
	printf("[pTree1]\n");
	ShowTree(pTree1);
	putchar('\n');
	printf("[pTree2]\n");
	ShowTree(pTree2);
	putchar('\n');

	TreePtr pTree = pTree1;
	while (1) {
		char sCmnd[20];
		printf("[12sqnx*e] ? ");
		gets_s(sCmnd);							// ����� �Է��Ѵ�.
		TreePtr pNode;
		switch (*sCmnd) {
		case 'e':								// �ƹ��� ����� ������
			return;
		case '1':								// Ʈ�� pTree1�� ����Ѵ�
		case '2':								// Ʈ�� pTree2�� ����Ѵ�
			ShowTree(*sCmnd == '1' ? pTree1 : pTree2);
			break;
		case 's':								// Ʈ���� ���ʰ� ������ �ڽ��� �ٲ۴�
			SwapTree(pTree);
			printf("Swap: Tree%d\n", (pTree == pTree1) ? 1 : 2);
			break;
		 case 'q':								// �� Ʈ���� ������ ���Ѵ�.
			printf("%s\n", EqualTree(pTree1, pTree2) ? "good" : "bad");
			break;
		 case 'n':								// inorder traverse�ϸ鼭 ���� �̸��� ����Ѵ�.
			Inorder(pTree);
			putchar('\n');
			break;
		 case 'x':								// Ž�� ����� pTree1�� pTree2�� �ٲ۴�.
			pTree = (pTree == pTree2) ? pTree1 : pTree2;
			printf("pTree%c ���\n", 0x31 + (pTree == pTree2));
			break;
		 default:								// �˻��� ������ �̸����� ����
			pNode = SearchTree(pTree, sCmnd);	// �˻��� �Ѵ�.
			if (pNode) {
				printf("    �̸�: %s\n", pNode->sName);
				printf("  ������: %s\n", pNode->sPosition);
				printf("�������: %s\n", pNode->sBirthday);
				printf("      Ű: %d\n", pNode->nHeight);
				printf("  ������: %d\n", pNode->nWeight);
				printf("    �Ҽ�: %s\n", pNode->sClub);
			}
			else
				printf("  No name......\n");
		}
		putchar('\n');
	}
}

#include "nationalTeam.h"

void MakeSearchTree(TreePtr &pTree1, TreePtr &pTree2)
{
	for (int i = 0; i < sizeof(nationalTeam) / sizeof(nationalTeam[0]); i++) {
		pTree1 = InsertNode1(pTree1, nationalTeam + i);
		InsertNode2(pTree2, nationalTeam + i);
	}
}

TreePtr InsertNode1(TreePtr pTree, DataPtr pNode)
{
	// Ʈ���� �ϳ��� ��带 �����Ѵ�.
	// �̹� �����ϸ� �ƹ��� ���� ���� �ʴ´�.
	int nCond;
	if (pTree == NULL) {
		pTree = (TreePtr)malloc(sizeof(Node));
		if (pTree) {
			*pTree = *pNode;		//memcpy(pTree, pNode, sizeof(Data));
			pTree->lChild = pTree->rChild = NULL;
		}
	}
	else if ((nCond = strcmp(pNode->sName, pTree->sName)) < 0)
		pTree->lChild = InsertNode1(pTree->lChild, pNode);
	else if (nCond > 0)
		pTree->rChild = InsertNode1(pTree->rChild, pNode);
	return pTree;
}

void InsertNode2(TreePtr& pTree, DataPtr pNode)
{
	// Ʈ���� �ϳ��� ��带 �����Ѵ�.
	// �̹� �����ϸ� �ƹ��� ���� ���� �ʴ´�.
	int nCond;
	if (pTree == NULL) {
		pTree = (TreePtr)malloc(sizeof(Node));
		if (pTree) {
			*pTree = *pNode;		//memcpy(pTree, pNode, sizeof(Data));
			pTree->lChild = pTree->rChild = NULL;
		}
	}
	else if ((nCond = strcmp(pNode->sName, pTree->sName)) < 0)
		InsertNode2(pTree->lChild, pNode);
	else if (nCond > 0)
		InsertNode2(pTree->rChild, pNode);
}

TreePtr SearchTree(TreePtr pTree, char *sName)
{
	// Ž��Ʈ������ sName�� ���� ������ ã�� �� ��带 return�Ѵ�.
	// �� ������ ������ NULL�� return�Ѵ�.
	if (pTree) {
		int nCond;
		if ((nCond = strcmp(sName, pTree->sName)) < 0)
			pTree = SearchTree(pTree->lChild, sName);
		else if (nCond > 0)
			pTree = SearchTree(pTree->rChild, sName);
	}
	return pTree;
} 

void Inorder(TreePtr pTree)
{
	// �̸��� ����Ѵ�
	if (pTree) {
		Inorder(pTree->lChild);
		printf("%s ", pTree->sName);
		Inorder(pTree->rChild);
	}
}

void SwapTree(TreePtr pTree)
{
	// ����Ʈ���� ��� ����� �����ʰ� ���� �ڽ��� ���� �ٲ۴�.
	// �� �ſ� ��ģ ����� ����Ʈ���� ��ȯ�Ѵ�.
	// Ž��Ʈ���� ����ϹǷ� �������� �۰Եǰ� ������ ũ�� �ȴ�.
	if (pTree) {
		SwapTree(pTree->lChild);
		SwapTree(pTree->rChild);
		TreePtr pTemp = pTree->lChild;
		pTree->lChild = pTree->rChild;
		pTree->rChild = pTemp;
	}
}

bool EqualTree(TreePtr pTree1, TreePtr pTree2)
{
	// �� Ʈ���� ������ ���Ͽ� true/false�� return�Ѵ�.
	// �� ���� sName �ʵ常 ���Ͽ� �Ǵ��Ѵ�.
	if (pTree1 == NULL && pTree2 == NULL)
		return true;
	if (pTree1 && pTree2)
		return strcmp(pTree1->sName, pTree2->sName) == 0 && 
			   EqualTree(pTree1->lChild, pTree2->lChild) && 
			   EqualTree(pTree1->rChild, pTree2->rChild);
	return false;
}

void PrintGap(int nCtr)
{
	for (int i = 0; i < nCtr; i++)
		putchar(0x20);
}

void PrintData(const char *sName)
{
	static char strFmt[] = { '%', 0x30 + NodeWIDTH, 's', 0 };
	printf(strFmt, sName);
}

int TreeHeight(TreePtr pTree)
{
	int nHeight = 0;
	if (pTree) {
		int nlHeight = TreeHeight(pTree->lChild);
		int nrHeight = TreeHeight(pTree->rChild);
		nHeight = (nlHeight > nrHeight ? nlHeight : nrHeight) + 1;
	}
	return nHeight;
}

void ShowTree(TreePtr pTree)
{
	if (pTree == NULL)
		return;
	TreePtr arNode1[256], arNode2[256] = { pTree, NULL };
	int nHeight = TreeHeight(pTree);
	int nMaxLvlNode = 1;
	for (int i = 1; i < nHeight; i++)
		nMaxLvlNode *= 2;
	int nWidth = (NodeWIDTH + NodeGAP) * nMaxLvlNode;
	for (int nLevel = 1, nCtr = 1; nLevel <= nHeight; nLevel++, nCtr *= 2) {
		for (int i = 0; i < nCtr; i++)
			arNode1[i] = arNode2[i];
		float fAvgGap = (float)(nWidth - nCtr * NodeWIDTH) / nCtr;
		for (int i = 0, nGapSum = 0; i < nCtr; i++) {
			int nGapNow = (int)(fAvgGap / 2 + (NodeWIDTH + fAvgGap) * i);
			PrintGap(nGapNow - nGapSum);
			arNode1[i] ? PrintData(arNode1[i]->sName) : PrintGap(NodeWIDTH);
			nGapSum = nGapNow + NodeWIDTH;
			arNode2[2 * i] = arNode1[i] ? arNode1[i]->lChild : NULL;
			arNode2[2 * i + 1] = arNode1[i] ? arNode1[i]->rChild : NULL;
		}
		putchar('\n');
	}
}

int CountNode(TreePtr pTree)
{
	int nCtr = 0;
	if (pTree)
		nCtr = CountNode(pTree->lChild) + CountNode(pTree->rChild) + 1;
	return nCtr;
}
