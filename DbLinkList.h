#include"String.h"
using namespace std;

struct DblNode {
	DblNode() { prev = next = NULL; }
	DblNode(String temp, DblNode *p, DblNode *n) {
		data = temp;
		prev = p;
		next = n;
	}
	String data;
	DblNode *prev;
	DblNode *next;
};

class DbLinkList {
public:
	DbLinkList(DblNode *h = new DblNode) :head(h) { count = 0; }
	String getElem(int lineNum) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		return temp->data;
	}
	void setElem(int lineNum, String source) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		temp->data = source;
	}
	bool Empty() { return head->next == NULL; }
	int getCount() { return count; }
	void Insert(int lineNum, String source) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		temp->next = new DblNode(source, temp, temp->next);
		if (temp->next->next != NULL)temp->next->next->prev = temp->next;
		count++;
	}
	void Delete(int lineNum) {
		DblNode* temp = head;
		while (lineNum--)
			temp = temp->next;
		temp->prev->next = temp->next;
		if (temp->next != NULL)temp->next->prev = temp->prev;
		temp->next = temp->prev = NULL;
		count--;
	}
private:
	int count;
	DblNode *head;
};