#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4326 4996 6001 6031)

#define MAX_ELEMENTS	100
#define	NodeWIDTH		2
#define	NodeGAP			1

typedef struct Node {
	int nData;
}	Element;

void main()
{
	void InsertHeap(Element heap[], Element anItem);
	void DeleteHeap(Element heap[], Element &anItem);
	void ShowTree(Element heap[]);

	Element heap[MAX_ELEMENTS + 1];
	heap[0].nData = 0;					// node counter
	Element anItem;
	srand((unsigned)time(NULL));
	while (1) {
		int nMax;
		printf("노드 개수 ? ");
		scanf("%d", &nMax);
		if (nMax <= 0 || nMax > MAX_ELEMENTS)
			break;
		for (int i = 1; i <= nMax; i++) {
			anItem.nData = rand() % 100;
			printf("[%02d] <-- %d\n\n", i, anItem.nData);
			InsertHeap(heap, anItem);
			ShowTree(heap);
			putchar('\n');
		}
		putchar('\n');
		for (int i = 1; i <= nMax; i++) {
			DeleteHeap(heap, anItem);
			printf("[%02d] --> %d\n\n", i, anItem.nData);
			ShowTree(heap);
			putchar('\n');
		}
		putchar('\n');
	}
}

void InsertHeap(Element heap[], Element anItem)
{
	/***
	nNdx에 nCtr을 1 증가한 후 저장한다;
	while (nNdx가 1보다 크고  anItem의 데이터가 [nNdx / 2]의 데이터보다 크다) {
		부모의 데이터를 자식으로 내린다
		nNdx를 한 레벨 위로 올린다
	}
	[nNdx]에 anItem을 저장한다
	***/
}

void DeleteHeap(Element heap[], Element& anItem)
{
	/***
	anItem에 루트 데이터를 저장한다
	lastItem에 마지막 데이터를 저장하고 nCtr을 1 감소한다
	parent에 1을, child에 2를 저장한다
	while (child가 nCtr보다 작거나 같다) {
		if (child가 nCtr보다 작고 [child]의 데이터가 [child + 1]의 데이터보다 작다)
			child를 1 증가한다
		if (lastItem의 데이터가 [child]의 데이터보다 크거나 같다)
			break;
		[parent]의 데이터에 [child]의 데이터를 저장한다
		parent에 child를 저장한다
		child에 2를 곱한다
	}
	[parent]에 lastItem을 저장한다
	***/
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

int TreeHeight(Element heap[], int nNdx)
{
	int nHeight = 0;
	int nCtr = heap[0].nData;
	if (nNdx <= nCtr) {
		int nlHeight = TreeHeight(heap, 2 * nNdx);
		int nrHeight = TreeHeight(heap, 2 * nNdx + 1);
		nHeight = (nlHeight > nrHeight ? nlHeight : nrHeight) + 1;
	}
	return nHeight;
}

void ShowTree(Element heap[])
{
	int nCtr;
	if ((nCtr = heap[0].nData) == 0)
		return;
	int nHeight = TreeHeight(heap, 1);
	int nMaxLvlNode = 1;
	for (int i = 1; i < nHeight; i++)
		nMaxLvlNode *= 2;
	int nWidth = (NodeWIDTH + NodeGAP) * nMaxLvlNode;
	int nNdx, nLvlCtr;
	nNdx = nLvlCtr = 1;
	while (nNdx <= nCtr) {
		float fAvgGap = (float)(nWidth - nLvlCtr * NodeWIDTH) / nLvlCtr;
		for (int i = 0, nGapSum = 0; i < nLvlCtr; i++, nNdx++) {
			int nGapNow = (int)(fAvgGap / 2 + (NodeWIDTH + fAvgGap) * i);
			PrintGap(nGapNow - nGapSum);
			if (nNdx <= nCtr)
				PrintData(heap[nNdx].nData);
			nGapSum = nGapNow + NodeWIDTH;
		}
		nLvlCtr *= 2;
		putchar('\n');
	}
}
