#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031 28182)

#define	NodeWIDTH	2
#define	NodeGAP		1
//#define DebugON			// define for testing
#ifdef DebugON
#define NoNODE		7
#else
#define NoNODE		23
#endif

typedef struct Node {
	int	nData;
	unsigned char lThread : 1;
	unsigned char rThread : 1;
	Node *lChild;
	Node *rChild;
}	*NodePtr, *TreePtr;

int  MakeTree(TreePtr& pTree, int nData);
void InorderTrvs(TreePtr pTree, NodePtr* &sOrder);
void MakeThreadTree(NodePtr *inorder);
void ThreadTrvs(TreePtr pHead, char *sOrder);
NodePtr Successor(NodePtr pNode);
void FreeTree(TreePtr pTree);
void ShowTree(TreePtr pTree);
int  CountNode(TreePtr pTree);

void main()
{
#ifdef DebugON
	srand((unsigned)13);
#else
	srand((unsigned)time(NULL));
#endif
	while (1) {
		TreePtr pHead = new Node;
		pHead->lThread = pHead->rThread = 0;
		pHead->rChild = pHead;
		pHead->lChild = NULL;
		for (int i = 1; i <= NoNODE; i++)
			if (MakeTree(pHead->lChild, i) == false)
				return;
		ShowTree(pHead->lChild);
		putchar('\n');

		NodePtr arrNode[NoNODE + 2];
		arrNode[0] = arrNode[NoNODE + 1] = pHead;
		NodePtr *parNode = arrNode + 1;
		InorderTrvs(pHead->lChild, parNode);
		MakeThreadTree(arrNode);
		char sOrder[5 * NoNODE];
		ThreadTrvs(pHead, sOrder);
		printf("Thread Trvs:%s\n", sOrder);
		// deallocate tree
		pHead->rChild = NULL;
		FreeTree(pHead);

		printf("\nContinue[y/*] ? ");
		char sAns[10];
		gets_s(sAns);
		if (*sAns != 'y')
			break;
	}
}

int MakeTree(TreePtr& pTree, int nData)
{
	if (pTree == NULL) {
		pTree = (NodePtr)malloc(sizeof(Node));
		if (pTree) {
			pTree->nData = nData;
			pTree->lThread = pTree->rThread = 0;
			pTree->lChild = pTree->rChild = NULL;
		}
		return pTree != NULL;
	}
	int nlCtr = CountNode(pTree->lChild), nrCtr = CountNode(pTree->rChild);
	int nChild = nlCtr == nrCtr ? rand() % 2 : nlCtr > nrCtr;
	return nChild ? MakeTree(pTree->rChild, nData) : MakeTree(pTree->lChild, nData);
}

void InorderTrvs(TreePtr pTree, NodePtr*& parNode)
{	// inorder로 순회하여 그 결과를 sOrder에 출력한다.
	if (pTree) {
		InorderTrvs(pTree->lChild, parNode);
		*parNode++ = pTree;
		InorderTrvs(pTree->rChild, parNode);
	}
}

void MakeThreadTree(NodePtr* inorder)
{
	for (int i = 1; i <= NoNODE; i++) {
		NodePtr pNode = inorder[i];
		if (pNode->lChild == NULL) {
			pNode->lChild = inorder[i - 1];
			pNode->lThread = 1;
		}
		if (pNode->rChild == NULL) {
			pNode->rChild = inorder[i + 1];
			pNode->rThread = 1;
		}
	}
}

void ThreadTrvs(TreePtr pHead, char* sOrder)
{	// 스레드 이진 트리를 inorder로 순회하여 그 결과를 sOrder에 출력한다.
	/***
	pNode에 pHead를 저장한다
	while (1) {
		pNode에 pNode Successor를 저장하고 pHead와 같으면
			break;
		sOrder에 "%-3d" 형식으로 pNode->nData를 저장하고 sOrder를 3 증가한다
	}
	***/
}

NodePtr Successor(NodePtr pTree)
{	// 스레드 이진 트리에서 다음 노드를 반환한다
	/***
	pNode에 pTree의 rChild를 저장한다
	pTree의 오른 자식이 존재하면
		pNode의 왼쪽 자식이 존재할 동안
			pNode는 왼쪽 자식을 따라 내려간다
	pNode를 반환한다
	***/
	return NULL;
}

void FreeTree(TreePtr pTree)
{	// 이진트리의 모든 노드를 되돌려준다.
	if (pTree) {
		if (pTree->lThread == 0)
			FreeTree(pTree->lChild);
		if (pTree->rThread == 0)
			FreeTree(pTree->rChild);
		free(pTree);
	}
}

void PrintGap(int nCtr)
{
	for (int i = 0; i < nCtr; i++)
		putchar(0x20);
}

void PrintData(int nData)
{
	static char strFmt[] = { '%', '0', 0x30 + NodeWIDTH, 'd', 0 };
	printf(strFmt, nData);
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
			arNode1[i] ? PrintData(arNode1[i]->nData) : PrintGap(NodeWIDTH);
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
