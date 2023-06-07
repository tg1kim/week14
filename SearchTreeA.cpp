#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define	NodeWIDTH	6
#define	NodeGAP		1

typedef const char* CPtr;
typedef struct Node {
	CPtr sName;			// 이름
	CPtr sPosition;		// 포지션
	CPtr sBirthday;		// 생년월일 2002.06.04
	int  nHeight;		// 키
	int  nWeight;		// 몸무게
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
		gets_s(sCmnd);							// 명령을 입력한다.
		TreePtr pNode;
		switch (*sCmnd) {
		case 'e':								// 아무런 명령이 없으면
			return;
		case '1':								// 트리 pTree1을 출력한다
		case '2':								// 트리 pTree2를 출력한다
			ShowTree(*sCmnd == '1' ? pTree1 : pTree2);
			break;
		case 's':								// 트리의 왼쪽과 오른쪽 자식을 바꾼다
			SwapTree(pTree);
			printf("Swap: Tree%d\n", (pTree == pTree1) ? 1 : 2);
			break;
		 case 'q':								// 두 트리가 같은지 비교한다.
			printf("%s\n", EqualTree(pTree1, pTree2) ? "good" : "bad");
			break;
		 case 'n':								// inorder traverse하면서 선수 이름을 출력한다.
			Inorder(pTree);
			putchar('\n');
			break;
		 case 'x':								// 탐색 대상을 pTree1과 pTree2를 바꾼다.
			pTree = (pTree == pTree2) ? pTree1 : pTree2;
			printf("pTree%c 사용\n", 0x31 + (pTree == pTree2));
			break;
		 default:								// 검색할 선수의 이름으로 간주
			pNode = SearchTree(pTree, sCmnd);	// 검색을 한다.
			if (pNode) {
				printf("    이름: %s\n", pNode->sName);
				printf("  포지션: %s\n", pNode->sPosition);
				printf("생년월일: %s\n", pNode->sBirthday);
				printf("      키: %d\n", pNode->nHeight);
				printf("  몸무게: %d\n", pNode->nWeight);
				printf("    소속: %s\n", pNode->sClub);
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
	// 트리에 하나의 노드를 삽입한다.
	// 이미 존재하면 아무런 일을 하지 않는다.
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
	// 트리에 하나의 노드를 삽입한다.
	// 이미 존재하면 아무런 일을 하지 않는다.
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
	// 탐색트리에서 sName을 가진 선수를 찾아 그 노드를 return한다.
	// 그 선수가 없으면 NULL을 return한다.
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
	// 이름만 출력한다
	if (pTree) {
		Inorder(pTree->lChild);
		printf("%s ", pTree->sName);
		Inorder(pTree->rChild);
	}
}

void SwapTree(TreePtr pTree)
{
	// 이진트리의 모든 노드의 오른쪽과 왼쪽 자식을 서로 바꾼다.
	// 즉 거울 비친 모습의 이진트리로 변환한다.
	// 탐색트리를 사용하므로 오른쪽은 작게되고 왼쪽은 크게 된다.
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
	// 두 트리를 같은지 비교하여 true/false를 return한다.
	// 두 노드는 sName 필드만 비교하여 판단한다.
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
