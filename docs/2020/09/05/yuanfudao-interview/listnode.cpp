#include <iostream>

using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x): val(x), next(nullptr) {};
};

ListNode* reverse(ListNode* head) {
	if (head==nullptr || head->next==nullptr) return head;
	ListNode* nex = head->next;
	ListNode* ans = reverse(nex);
	nex->next = head;
	head->next = nullptr;
	return ans;
}

ListNode* solve(ListNode* head) {
	ListNode* p = head;
	int cnt = 0;
	while (p!=nullptr) {
		++cnt;
		p = p->next;
	}
	if (cnt<3) return head;
	p = head;
	int stop=1;
	while (stop++<(cnt+1)/2) {
		p = p->next;
	}
	ListNode* last = reverse(p->next);
	p->next = nullptr;
	p = head;

	ListNode* q = last;
	while (q!=nullptr) {
		ListNode* tmp = p->next;
		p->next = q;
		q = q->next;
		p->next->next = tmp;
		p = tmp;
	}
	return head;
}

int main(int argc, char const *argv[])
{
	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);
	head->next->next->next->next->next = new ListNode(6);
	ListNode* p = solve(head);
	ListNode* cur = p;
	while (cur!=nullptr) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	cout << endl;
	return 0;
}