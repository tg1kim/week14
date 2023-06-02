#include <stdio.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define	MaxCtr		127
#define	NodeWIDTH	2
#define	NodeGAP		1
#define LEFT		0
#define RGHT		1
#define AUTOMATIC	1

typedef struct Node {		// 트리의 노드
	int	nData;
	Node *lChild;
	Node *rChild;
}	*NodePtr, *TreePtr;

typedef union {
	int   nRttn;
	short sRttn[2];
	char  cRttn[4];
}	Rttn;

void AutomaticMakeAVLTree(TreePtr& pTree);
void ManualMakeAVLTree(TreePtr& pTree);
int  AVLInsert(TreePtr& pTree, int nData);
void FreeTree(TreePtr pTree);
int  CheckBalance(TreePtr& pTree, int nData, int nRttn);
int  TreeHeight(TreePtr pTree);
void RotateTree(TreePtr& pTree, int nRttn);
void LeftRotate(TreePtr& pTree);
void RghtRotate(TreePtr& pTree);
void ShowTree(TreePtr pTree);

TreePtr pRoot;

void main()
{
	while (1) {
		pRoot = NULL;
		AUTOMATIC ? AutomaticMakeAVLTree(pRoot) : ManualMakeAVLTree(pRoot);
		FreeTree(pRoot);
		printf("One more(y/n) ? ");
		char nYes;
		scanf(" %c", &nYes);
		if (nYes != 'y')
			break;
	}
	printf("Bye, ...\n\n");
}

void AutomaticMakeAVLTree(TreePtr& pTree)
{
	static int nTurn = 1;
	static char strLR[] = "LR";
	Rttn aRttn;
	int nCtr;
	printf("노드 개수 ? ");
	scanf("%d", &nCtr);
	for (int i = 1; i <= nCtr; i++) {
		int nData = nTurn ? i : nCtr - i + 1;
		printf("[%02d]\n", nData);
		aRttn.nRttn = AVLInsert(pTree, nData);
		if (aRttn.nRttn) {
			printf("\n--> %c%c at [%02d]\n",
				strLR[aRttn.cRttn[0]], strLR[aRttn.cRttn[1]], aRttn.sRttn[1]);
			ShowTree(pTree);
		}
		else {
			ShowTree(pTree);
			printf("\n--> OK\n");
		}
		putchar('\n');
	}
	nTurn = 1 - nTurn;
}

void ManualMakeAVLTree(TreePtr& pTree)
{
	static char strLR[] = "LR";
	Rttn aRttn;
	int nData;
	while (1) {
		printf("? ");
		scanf("%d", &nData);
		if (nData < 0)
			break;
		printf("[%02d]\n", nData);
		aRttn.nRttn = AVLInsert(pTree, nData);
		if (aRttn.nRttn) {
			printf("\n--> %c%c at [%02d]\n\n",
				strLR[aRttn.cRttn[1]], strLR[aRttn.cRttn[0]], aRttn.sRttn[1]);
			ShowTree(pTree);
		}
		else {
			ShowTree(pTree);
			printf("\n--> OK\n");
		}
		putchar('\n');
	}
	putchar('\n');
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
	return CheckBalance(pTree, nData, nRttn);
}

int CheckBalance(TreePtr &pTree, int nData, int nRttn)
{
	Rttn aRttn;
	aRttn.nRttn = nRttn;
	if (pTree) {
		int nBalance = TreeHeight(pTree->lChild) - TreeHeight(pTree->rChild);
		if (nBalance < -1 || nBalance > 1) {
			TreePtr pChld = nData < pTree->nData ? pTree->lChild : pTree->rChild;
			aRttn.cRttn[1] = nData < pTree->nData ? LEFT : RGHT;
			aRttn.cRttn[0] = nData < pChld->nData ? LEFT : RGHT;
			aRttn.sRttn[1] = (short)pTree->nData;
			ShowTree(pRoot);
			RotateTree(pTree, aRttn.sRttn[0]);
		}
	}
	return aRttn.nRttn;
}

void RotateTree(TreePtr &pTree, int nRttn)
{
	switch (nRttn) {
	case 0x0001:						// LR Roation
		LeftRotate(pTree->lChild);
	case 0x0000:						// LL Rotation
		RghtRotate(pTree);
		break;
	case 0x0100:						// RL Rotation
		RghtRotate(pTree->rChild);
	case 0x0101:						// RR Rotation
		LeftRotate(pTree);
	}
}
									
void LeftRotate(TreePtr &pTree)		//         A                 B
{									//                         *
	TreePtr pRoot = pTree->rChild;	//     Al     B   ===>    A     Br
	pTree->rChild = pRoot->lChild;	//                         *
	pRoot->lChild = pTree;			//          Bl Br       Al Bl
	pTree = pRoot;					// A->rChild = Bl
}									// B->lChild = A

void RghtRotate(TreePtr &pTree)		//         A                 B
{									//                             *
	TreePtr pRoot = pTree->lChild;	//     B      Ar   ===>  Bl     A
	pTree->lChild = pRoot->rChild;	//                             *
	pRoot->rChild = pTree;			//   Bl Br                    Br Ar
	pTree = pRoot;					// A->lChild = Br
}									// B->rChild = A

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