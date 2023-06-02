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
		printf("��� ���� ? ");
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
	nNdx�� nCtr�� 1 ������ �� �����Ѵ�;
	while (nNdx�� 1���� ũ��  anItem�� �����Ͱ� [nNdx / 2]�� �����ͺ��� ũ��) {
		�θ��� �����͸� �ڽ����� ������
		nNdx�� �� ���� ���� �ø���
	}
	[nNdx]�� anItem�� �����Ѵ�
	***/
}

void DeleteHeap(Element heap[], Element& anItem)
{
	/***
	anItem�� ��Ʈ �����͸� �����Ѵ�
	lastItem�� ������ �����͸� �����ϰ� nCtr�� 1 �����Ѵ�
	parent�� 1��, child�� 2�� �����Ѵ�
	while (child�� nCtr���� �۰ų� ����) {
		if (child�� nCtr���� �۰� [child]�� �����Ͱ� [child + 1]�� �����ͺ��� �۴�)
			child�� 1 �����Ѵ�
		if (lastItem�� �����Ͱ� [child]�� �����ͺ��� ũ�ų� ����)
			break;
		[parent]�� �����Ϳ� [child]�� �����͸� �����Ѵ�
		parent�� child�� �����Ѵ�
		child�� 2�� ���Ѵ�
	}
	[parent]�� lastItem�� �����Ѵ�
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
