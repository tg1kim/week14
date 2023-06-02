#include <stdio.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define	MaxCtr		127
#define	NodeWIDTH	2
#define	NodeGAP		1

typedef struct Node {		// Ʈ���� ���
	int	nData;
	Node *lChild;
	Node *rChild;
}	*NodePtr, *TreePtr;

void MakeAVLTree(TreePtr &pTree, int nCtr);
int  AVLInsert(TreePtr &pTree, int nData);
void FreeTree(TreePtr pTree);
int  CheckBalance(TreePtr &pTree, int nData);
int  IsSkewed(TreePtr pTree, int nData);
int  TreeHeight(TreePtr pTree);
void RotateTree(TreePtr &pTree, int nRttn);
void LeftRotate(TreePtr &pTree);
void RghtRotate(TreePtr &pTree);
void ShowTree(TreePtr pTree);

void main()
{
	while (1) {
		int nCtr;
		printf("��� ���� ? ");
		scanf("%d", &nCtr);
		if (nCtr <= 0 || nCtr > MaxCtr)
			break;
		TreePtr pTree = NULL;
		MakeAVLTree(pTree, nCtr);
		putchar('\n');
		FreeTree(pTree);
	}
	printf("Bye, ...\n\n");
}

void MakeAVLTree(TreePtr &pTree, int nCtr)
{
	static int nTurn = 1;
	int nAVLRttn;
	char *arRttn = (char *)&nAVLRttn;
	for (int i = 1; i <= nCtr; i++) {
		int nData = nTurn ? i : nCtr - i + 1;
		printf("[%02d]", nData);
		nAVLRttn = AVLInsert(pTree, nData);
		if (nAVLRttn)
			printf(": %c%c at [%02d]", arRttn[0], arRttn[1], arRttn[2]);
		else
			printf(" OK");
		printf("\n\n");
		ShowTree(pTree);
		putchar('\n');
	}
	nTurn = 1 - nTurn;
}

int AVLInsert(TreePtr &pTree, int nData)
{
	int nRttn;
	if (pTree == NULL) {
		pTree = new Node;
		if (pTree) {
			pTree->nData = nData;
			pTree->lChild = pTree->rChild = NULL;
		}
		nRttn = 0;
	}
	else if (nData < pTree->nData)
		nRttn = AVLInsert(pTree->lChild, nData);
	else if (nData > pTree->nData)
		nRttn = AVLInsert(pTree->rChild, nData);
	return CheckBalance(pTree, nData) + nRttn;
}

int CheckBalance(TreePtr& pTree, int nData)
{
	int nRttn = 0;
	if (pTree && (nRttn = IsSkewed(pTree, nData)))
		RotateTree(pTree, nRttn & 0xFFFF);
	return nRttn;
}

int IsSkewed(TreePtr pTree, int nData)
{
	int nRttn = 0;
	if (pTree) {
		int nBalance = TreeHeight(pTree->lChild) - TreeHeight(pTree->rChild);
		if (nBalance < -1 || nBalance > 1) {
			char *arRttn = (char *)&nRttn;
			TreePtr pChld = nData < pTree->nData ? pTree->lChild : pTree->rChild;
			arRttn[0] = nData < pTree->nData ? 'L' : 'R';
			arRttn[1] = nData < pChld->nData ? 'L' : 'R';
			arRttn[2] = pTree->nData;
		}
	}
	return nRttn;
}

void RotateTree(TreePtr &pTree, int nRttn)
{
	switch (nRttn) {					// L: 0x4C, R:0x52
	case 0x524C:						// LR Roation
		break;
	case 0x4C4C:						// LL Rotation
		break;
	case 0x4C52:						// RL Rotation
		break;
	case 0x5252:						// RR Rotation
		break;
	}
}
									
void LeftRotate(TreePtr& pTree)
{
}

void RghtRotate(TreePtr &pTree)
{
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

void FreeTree(TreePtr pTree)
{
	if (pTree) {
		FreeTree(pTree->lChild);
		FreeTree(pTree->rChild);
		delete pTree;
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

void ShowTree(TreePtr pTree)
{
	if (pTree == NULL)
		return;
	TreePtr arNode1[513], arNode2[513] = { pTree, NULL };
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
			if (nLevel < nHeight) {
				arNode2[2 * i] = arNode1[i] ? arNode1[i]->lChild : NULL;
				arNode2[2 * i + 1] = arNode1[i] ? arNode1[i]->rChild : NULL;
			}
		}
		putchar('\n');
	}
}